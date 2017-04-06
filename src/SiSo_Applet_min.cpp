/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "SiSo_Applet_min.h"
#include "FPGA_Interface_Core.h"
#include <QKeyEvent>
#include <QProcess>
#include <QProgressDialog>
#include <stdio.h>
#include <Windows.h>
#include <qdir.h>

#pragma warning( disable : 4996 )

FILE *filetimestamps	= NULL;
int ret;

using namespace FPGA_IF;

//Default constructor
SiSo_AppletMin::SiSo_AppletMin		(FPGA_IF_Core& core):SiSo_AppletIF(core)
{
MESSAGE("SiSo_AppletCOG::SiSo_AppletCOG()");
	this->m_fg			= NULL;
#ifdef transferROI
	this->m_DMAsUsed	= 4;
#else
	this->m_DMAsUsed	= MAXDMA;
#endif // CONDS

	this->m_thresh_min	= 0;
	this->m_modulo		=__PARALLEL_MODULO__;

	QDir directory;
	directory = QDir::currentPath();
	directory.cdUp();
	QString path = directory.path();
	path= path+"/hap_Files/";
	
#ifndef __MULTI_DMA_APPLET__
	#ifdef __ME5__
		m_hap = "C:\\Program Files\\SiliconSoftware\\Runtime5.4.1.2\\DLL\\mE5VQ8-CXP6D\\Acq_SingleCXP6x4AreaGray8.dll";
	#else
		//m_hap = "C:\\Program Files (x86)\\SiliconSoftware\\VisualApplets 2.1\\Designs\\mE4VD4-CL\\AnalyzeCellVGARawCOG.hap";
	#endif
#else
	#ifdef __ME5__
		#ifdef __USE_COEFFICIENT_BUFFER__
			m_hap = path + "ME5/CellAnalysisME5_Test_Input.hap";
		#else
			m_hap = path + "ME5/CellAnalysisME5_Camera_Input_Max.hap";
		#endif
	#else
		#ifdef __USE_COEFFICIENT_BUFFER__
		///m_hap = path + "ME4/CellAnalysisME4_Test_Input.hap";
			m_hap = path + "ME4/CellAnalysisME4_Test_Input_MeanAddThresh.hap";
		#else
			//m_hap = path + "ME4/CellAnalysisME4_Camera_Input.hap";
			m_hap = path + "ME4/CellAnalysisME4_Camera_Input_Max.hap";
		#endif
	#endif
#endif
}
//----------------------------------------------------------------

SiSo_AppletMin::~SiSo_AppletMin		()
{
	MESSAGE("SiSo_AppletCOG::~SiSo_AppletCOG()");
	this->DeInit();
}
//----------------------------------------------------------------


//Initialize the Applet - read parameters from framegrabber
bool SiSo_AppletMin::Init			()
{
	if (this->m_fg)
		this->DeInit();

	SiSo_AppletIF::Init();
	MESSAGE("SiSo_AppletCOG::Init()");
	QString	hap(m_hap);

	this->m_fg = Fg_Init(hap.toLatin1().data(),0);

	if (!this->m_fg)
	{
		Fg_Error(this->m_fg);
		cout << "FG not initialized" << endl;

		MESSAGE("Framegrabber could not be initialized!");
		QMessageBox::warning(NULL, "Framegrabber initialization Error", " Framegrabber could not be initialized! \n Possible reasons: \n - Micro Display still open \n - Wrong firmware on board \n - Hardware issues");
		return false;
	}

#ifdef __MULTI_DMA_APPLET__
	int nrOfParameter = Fg_getNrOfParameter(this->m_fg);
       
	int	ret;
	int	nr_process, port, board, dmastatus, 
		nr_dmas[2]={0}, nr_cams[2]={0}, timeout[2]={0}, dma_port[2] = {0}, cam_port[2] = {0},
		width[4]={0}, height[4]={0}, format[4]={0};
	{
		try
		{
			if ((ret = Fg_getParameter(this->m_fg, FG_PORT			, &port		, 0)) != FG_OK)	throw ret;
			fprintf(stdout, " FG_PORT           : %8d\n", port);

			if ((ret = Fg_getParameter(this->m_fg, FG_GLOBAL_ACCESS		, &board	, 0)) != FG_OK)	throw ret;
			fprintf(stdout, " FG_GLOBAL_ACCESS  : %8d\n", board);

			if ((ret = Fg_getParameter(this->m_fg, FG_NR_OF_PROCESSES	, &nr_process	, 0)) != FG_OK)	throw ret;
			fprintf(stdout, " FG_NR_OF_PROCESSES: %8d\n", nr_process);

			if ((ret = Fg_getParameter(this->m_fg, FG_DMASTATUS		, &dmastatus	, 0)) != FG_OK)	throw ret;
			fprintf(stdout, " FG_DMASTATUS      : 0x%08x\n", dmastatus);

			for (int p = 0; p < nr_process; p++)
			{
				fprintf(stdout, "\nProzess       : %d\n", p);

				if ((ret = Fg_getParameter(this->m_fg, FG_NR_OF_CAMS	, &nr_cams[p]	, p)) != FG_OK)	throw ret;
				fprintf(stdout, " FG_NR_OF_CAMS: %8d\n", nr_cams[p]);
	
				if ((ret = Fg_getParameter(this->m_fg, FG_NR_OF_DMAS	, &nr_dmas[p]	, p)) != FG_OK)	throw ret;
				fprintf(stdout, " FG_NR_OF_DMAS: %8d\n", nr_dmas[p]);

				if ((ret = Fg_getParameter(this->m_fg, FG_TIMEOUT	, &timeout[p]	, p)) != FG_OK)	throw ret;
				fprintf(stdout, " FG_TIMEOUT   : %8d\n", timeout[p]);

				if ((ret = Fg_getParameter(this->m_fg, FG_DMA_PORT	, &dma_port[p]	, p)) != FG_OK)	throw ret;
				fprintf(stdout, " FG_DMA_PORT  : %8u\n", dma_port[p]);

				if ((ret = Fg_getParameter(this->m_fg, FG_CAM_PORT	, &cam_port[p]	, p)) != FG_OK)	throw ret;
				fprintf(stdout, " FG_CAM_PORT  : %8u\n", cam_port[p]);
			}

			for (int r = 0; r < (nr_dmas[0]+nr_dmas[1]); r++)
			{
				fprintf(stdout, "\nDMA Res       : %d\n", r);

				if ((ret = Fg_getParameter(this->m_fg, FG_WIDTH		, &width [r]	, r)) == FG_OK)	//throw ret;
				fprintf(stdout, " FG_WIDTH     : %8d\n", width [r]);

				if ((ret = Fg_getParameter(this->m_fg, FG_HEIGHT	, &height[r]	, r)) == FG_OK)	//throw ret;
				fprintf(stdout, " FG_HEIGHT    : %8d\n", height[r]);

				if ((ret = Fg_getParameter(this->m_fg, FG_FORMAT	, &format[r]	, r)) == FG_OK)	//throw ret;
				fprintf(stdout, " FG_FORMAT    : %8d\n", format[r]);
			}	

			m_DMA0Size.x =  width[0];
			m_DMA0Size.y = height[0];
			
			m_DMA1Size.x =  width[1];
			m_DMA1Size.y = height[1];

			m_DMA2Size.x =  width[2];
			m_DMA2Size.y = height[2];
		}
		catch(int r)
		{
			r;
			Fg_Error(this->m_fg);
		}
	}
#endif

	this->Init_ThreadArgs();

	return true;
}

//Deninitialize Applet - free ressources
void SiSo_AppletMin::DeInit			()
{
	MESSAGE("SiSo_Applet::DeInit()");

	if (!this->m_fg)
		return;
	this->m_update_timer.stop();
	MESSAGE("SiSo_AppletMin::stop()");
	this->stop();

	SiSo_AppletIF::DeInit();

	if (this->m_fg)
	{
		Fg_FreeGrabber(this->m_fg);
		this->m_fg = NULL;
	}
}


//Initialize DMA ports
void SiSo_AppletMin::Init_ThreadArgs		()
{
//	this->m_RB.ResetImgNum();

	this->m_DMA[0].name		= "Overview";
	this->m_DMA[0].dmaNr		= 0;
	this->m_DMA[0].sdma.size.x	= g_pFPGA_IFcore->GetpCamSelected()->GetImageSize_px().x;
	this->m_DMA[0].sdma.size.y	= g_pFPGA_IFcore->GetpCamSelected()->GetImageSize_px().y;
	this->m_DMA[0].sdma.byteWidth	= 1;
	this->m_DMA[0].sdma.status[0]	= 0;
	this->m_DMA[0].sdma.status[1]	= 0;
	this->m_DMA[0].sdma.count	= 0;
	if(MAXDMA >1)
	{
	this->m_DMA[1].name		= "COGs";
	this->m_DMA[1].dmaNr		= 1;
	this->m_DMA[1].sdma.size	= m_DMA1Size;
	this->m_DMA[1].sdma.byteWidth	= 4;
	this->m_DMA[1].sdma.status[0]	= 0;
	this->m_DMA[1].sdma.status[1]	= 0;
	this->m_DMA[1].sdma.count	= 0;
	
	this->m_DMA[2].name		= "Histogram";
	this->m_DMA[2].dmaNr		= 2;
	this->m_DMA[2].sdma.size	= m_DMA2Size;
	this->m_DMA[2].sdma.byteWidth	= 4;
	this->m_DMA[2].sdma.status[0]	= 0;
	this->m_DMA[2].sdma.status[1]	= 0;
	this->m_DMA[2].sdma.count	= 0;

#ifdef transferROI
	this->m_DMA[3].name		= "Raw ROI";
	this->m_DMA[3].dmaNr		= 3;
	this->m_DMA[3].sdma.size.x	= 1;
//	this->m_DMA[3].sdma.size.y	= MAXROICOUNT;
	this->m_DMA[1].sdma.size.y	= PupilClasses[MAXROICLASSUSED];
	this->m_DMA[3].sdma.byteWidth	= 1;
	this->m_DMA[3].sdma.status[0]	= 0;
	this->m_DMA[3].sdma.status[1]	= 0;
	this->m_DMA[3].sdma.count	= 0;
#endif
	}
}

//Allocate actual memory for storing image data in buffer
bool	SiSo_AppletMin::SetImageBuffer	(long count)
{
	MESSAGE2("SetImageBuffer", count);
	cout << this->m_DMA[0].sdma.size.x<< " " << this->m_DMA[0].sdma.size.y << endl;

	this->DisconnectGrabBuffer();

	this->m_RB.	Alloc(count);
	for (long nr = 0; nr < count; nr++)
	{

		this->m_RB.m_buffer.find(nr)->second->m_ImgDMA0 = cv::Mat(cv::Size(g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x, g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y),CV_8UC1);
#ifdef __MULTI_DMA_APPLET__
		this->m_RB.m_buffer.find(nr)->second->m_ImgDMA1Buffer = new UINT32[this->m_DMA[1].sdma.size.x*this->m_DMA[1].sdma.size.y*sizeof(UINT32)];
		this->m_RB.m_buffer.find(nr)->second->m_ImgDMA2Buffer = new UINT32[this->m_DMA[2].sdma.size.x*this->m_DMA[2].sdma.size.y*sizeof(UINT32)];
#endif
	#ifdef transferROI
		this->m_RB.m_buffer.find(nr)->second->m_ImgDMA3Buffer = new unsigned char[this->m_DMA[3].sdma.size.x*this->m_DMA[3].sdma.size.y*sizeof(unsigned char)];
	#endif
	}

	this->m_RB.SetActualImgNum(0);
	this->ConnectGrabBuffer	();

	emit updateRingBufferCount(count, 0);

	return true;
}

#ifdef __USE_COEFFICIENT_BUFFER__
void SiSo_AppletMin::CoeffBuffParam()
{
	QDir directory;
	directory = QDir::currentPath();
	directory.cdUp();
	QString Filename = directory.path();
	Filename= Filename+"/res/Testimages/";

#ifndef __ME5__
	//Silicon Software... Whats wrong here? Not able to change image during runtime?!
	//Filename = "C:\_Projekt2016\FPGA_Interface_Cell_VS2013\res\Testimages\crossFrameBin.tif";
	Filename = Filename + "inputSmall.tif";
#else
	Filename = Filename + "testInputME5.tif";
#endif
	cout << "TestImage" << Filename.toStdString() << endl;
	/*============ CoefficientBuffer : TestInput ============== */ 

	int Device1_Process0_TestInput_BufferWidth_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_BufferWidth");	/* static parameter */

	int Device1_Process0_TestInput_BufferHeight_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_BufferHeight");	/* static parameter */

	int Device1_Process0_TestInput_XOffset_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_XOffset");
	unsigned int Device1_Process0_TestInput_XOffset;
	Device1_Process0_TestInput_XOffset = 0;
	Fg_setParameterWithType(this->m_fg, Device1_Process0_TestInput_XOffset_Id, &Device1_Process0_TestInput_XOffset, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_TestInput_XLength_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_XLength");
	unsigned int Device1_Process0_TestInput_XLength;
	Device1_Process0_TestInput_XLength = 640;
	Fg_setParameterWithType(this->m_fg, Device1_Process0_TestInput_XLength_Id, &Device1_Process0_TestInput_XLength, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_TestInput_YOffset_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_YOffset");
	unsigned int Device1_Process0_TestInput_YOffset;
	Device1_Process0_TestInput_YOffset = 0;
	Fg_setParameterWithType(this->m_fg, Device1_Process0_TestInput_YOffset_Id, &Device1_Process0_TestInput_YOffset, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_TestInput_YLength_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_YLength");
	unsigned int Device1_Process0_TestInput_YLength;
	Device1_Process0_TestInput_YLength = 480;
	Fg_setParameterWithType(this->m_fg, Device1_Process0_TestInput_YLength_Id, &Device1_Process0_TestInput_YLength, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_TestInput_UpdateROI_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_UpdateROI");
	unsigned int Device1_Process0_TestInput_UpdateROI;
	Device1_Process0_TestInput_UpdateROI = 1;
	Fg_setParameterWithType(this->m_fg, Device1_Process0_TestInput_UpdateROI_Id, &Device1_Process0_TestInput_UpdateROI, 0, FG_PARAM_TYPE_UINT32_T);

	//Silicon Software... Whats wrong here? Not able to change image during runtime?!
	
	int Device1_Process0_TestInput_CoefficientFile_0_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_CoefficientFile 0");
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_TestInput_CoefficientFile_0_Id, Filename.toLatin1().data(), 0, FG_PARAM_TYPE_CHAR_PTR);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));
	MESSAGE("Silicon Software Bug - Only able to load image set at compile time of applet");

	int Device1_Process0_TestInput_LoadCoefficients_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_LoadCoefficients");
	unsigned int Device1_Process0_TestInput_LoadCoefficients;
	Device1_Process0_TestInput_LoadCoefficients = 1;
	Fg_setParameterWithType(this->m_fg, Device1_Process0_TestInput_LoadCoefficients_Id, &Device1_Process0_TestInput_LoadCoefficients, 0, FG_PARAM_TYPE_UINT32_T);

	int Device1_Process0_TestInput_LinesToSimulate_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_LinesToSimulate");	/* static parameter */

	int Device1_Process0_TestInput_PixelsToSimulate_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_TestInput_PixelsToSimulate");	/* static parameter */
}
#endif


//Set "global" parameters for the applet
void SiSo_AppletMin::Param			()
{
	bool running = this->m_run;
	if (running)
	{
		this->stop();
	}

	this->Init_ThreadArgs();

	if (!this->m_fg)
		return;

	MESSAGE("Update Parameters");

	/*============ Process : Process0 ============== */ 

	int Device1_Process0_Enable_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Enable");
	unsigned int Device1_Process0_Enable;
	Device1_Process0_Enable = 0;
	ret = Fg_setParameter(this->m_fg, Device1_Process0_Enable_Id, &Device1_Process0_Enable, 0);
//	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

/*============ CameraGrayAreaBase : Kamera0 ============== */ 

#ifndef __USE_COEFFICIENT_BUFFER__

	int Device1_Process0_Kamera0_MaxCameraClockFreq_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Kamera0_MaxCameraClockFreq");	/* static parameter */

	int Device1_Process0_Kamera0_UseDval_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Kamera0_UseDval");
	int Device1_Process0_Kamera0_UseDval;
	Device1_Process0_Kamera0_UseDval = CameraGrayAreaBase::DVAL_Enabled;
	ret = Fg_setParameter(this->m_fg, Device1_Process0_Kamera0_UseDval_Id, &Device1_Process0_Kamera0_UseDval, 0);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));
#endif
	//int Device1_Process0_Kamera0_Format_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Kamera0_Format");
	//int Device1_Process0_Kamera0_Format;
	//Device1_Process0_Kamera0_Format = CameraGrayAreaBase::DualTap8Bit;
	//ret = Fg_setParameter(this->m_fg, Device1_Process0_Kamera0_Format_Id, &Device1_Process0_Kamera0_Format, 0);
	//if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

#ifdef __USE_COEFFICIENT_BUFFER__
	this->CoeffBuffParam();
#endif
	this->SetTriggerMode	(this->GetTriggerMode());
	this->SetThresholdMin	(this->GetThresholdMin());

	if (running)
	{
		this->start();
	}
}


//Start running the applet - in this function data provided by the framgrabber gets pulled into the CPU
void SiSo_AppletMin::run			()
{
	if (!this->m_fg)
		return;
	cout << "Thread: " << this->thread()->currentThreadId() << " start." << endl;
	this->setPriority( QThread::IdlePriority);

	FPGA_IF_Img *imgs;

	DMAThreadArgs *arg = (DMAThreadArgs*) this->m_DMA;

	int actimgnum, lastimgnum;
	actimgnum = lastimgnum = 0;

#define Fg_getLastPicB(picNr, dma, mem)Fg_getLastPicNumberBlockingEx	(this->m_fg, picNr,dma, 10, mem)	//Get last pic number with blocking
#define Fg_getLastPic(picNr, dma, mem)Fg_getLastPicNumberEx		(this->m_fg, dma, mem)					//Get last pic number without blocking
#define CHECKDMAB(dma, picNr)arg[dma].sdma.status[0] = Fg_getLastPicB	(picNr,dma,arg[dma].sdma.pmem)  //Get last pic with blocking
#define CHECKDMA(dma, picNr)arg[dma].sdma.status[0] = Fg_getLastPic		(picNr,dma,arg[dma].sdma.pmem)	//Get last pic without blocking
#define LOOPALL for(int t = 0; t < this->m_DMAsUsed; t++)													//Iterate through all DMAs

	this->iDMA0();
#ifdef __MULTI_DMA_APPLET__
	this->iDMA1();
	this->iDMA2();
#endif
	Beep(300, 1);
	   
	LOOPALL
	{
		fprintf(stdout,"DMA%d started\n", arg[t].dmaNr);
	}

	LOOPALL
	{
		Fg_AcquireEx(this->m_fg,arg[t].dmaNr,this->m_grabcount,ACQ_STANDARD,arg[t].sdma.pmem);
	}

#ifdef __ME5__
	g_pFPGA_IFcore->m_CL_camera[2]->DoStartAcquisition();
#endif

#ifdef __SHOW_HFR__
	int dispId0 = CreateDisplay(8*1*1,g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x,g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y);
	SetBufferWidth(dispId0,g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x,g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y);
#endif

	//Infinite loop - transfer DMA Data as long as all conditions within this loop are met
	do
	{
		//Sleep(0);
		LOOPALL
		{
			arg[t].sdma.status[1] = arg[t].sdma.status[0];
		}


#ifdef TRIGGER
		// softwaretrigger
		if (this->m_TriggerMode == TrgPortArea::ExternSw_Trigger)
		{
			ret = Fg_setParameter(this->m_fg, Device1_Process0_Trigger_SoftwareTrgPulse_Id, &Device1_Process0_Trigger_SoftwareTrgPulse, 0);
			if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));
		}
#endif //TRIGGER
		
#ifdef __MULTI_DMA_APPLET__
		CHECKDMAB(1, arg[1].sdma.status[0]+1); //Slowest first with blocking - COG
		CHECKDMA(0, arg[0].sdma.status[0]+1);  //Image second
		CHECKDMA(2, arg[2].sdma.status[0]+1);  //Histogramm third
#else
		CHECKDMAB(0, arg[0].sdma.status[0]+1);  //Image second
#endif
		//this->m_core.m_pc.Now("DMA0");
		
		//this->m_core.m_mutex.lock();
		//cout << "statusDMA0(" << arg[0].sdma.status[0] << ")" << endl;
#ifdef __MULTI_DMA_APPLET__
		//cout << "statusDMA1(" << arg[1].sdma.status[0] << ")" << endl;
		//cout << "statusDMA2(" << arg[2].sdma.status[0] << ")" << endl;
#endif
		//this->m_core.m_mutex.unlock();

	#ifdef __SHOW_HFR__
		void *imgAdress;	//Adresse des bildes
		imgAdress = Fg_getImagePtrEx(this->m_fg, lastimgnum, 0, this->m_DMA[0].sdma.pmem);
		//Draw buffer via stored pointer- only works for frameindex > 0
		if(lastimgnum>3)
		DrawBuffer(dispId0,imgAdress, static_cast<int>(lastimgnum), "");
		
	#endif

		if (	   arg[0].sdma.status[0] < 0
#ifdef __MULTI_DMA_APPLET__
				|| arg[1].sdma.status[0] < 0
				|| arg[2].sdma.status[0] < 0
#endif
			)
		{
			this->m_core.m_mutex.lock();
			cout << 
					"statusDMA0(" << arg[0].sdma.status[0] << ")\n)"<< 
#ifdef __MULTI_DMA_APPLET__
				    "statusDMA1(" << arg[1].sdma.status[0] << ")\n)"<<
					"statusDMA2(" << arg[2].sdma.status[0] << ")\n)"<<
#endif
				endl;
			this->m_core.m_mutex.unlock();
			LOOPALL
			{
				arg[t].sdma.count++;
			}
			break;
		}

#ifndef _DEBUG
		DWORD	priorityclass	= GetPriorityClass(GetCurrentProcess());
		int	threadpriority	= GetThreadPriority(GetCurrentProcess());
		SetPriorityClass	(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
		SetThreadPriority	(GetCurrentThread() , THREAD_PRIORITY_TIME_CRITICAL);
#endif
		lastimgnum = actimgnum;
#ifdef __MULTI_DMA_APPLET__
		actimgnum = __min(__min(arg[0].sdma.status[0], arg[1].sdma.status[0]), arg[2].sdma.status[0]);
#else 
		actimgnum = arg[0].sdma.status[0];
#endif
		this->GetRB().SetActualImgNum(actimgnum);

		// no new images
		if (lastimgnum == actimgnum)
		{
			continue;
		}
		// if some images are missing
		if (lastimgnum+1 != actimgnum)
		{
			// adapt counters
			LOOPALL
			{
#ifdef __MULTI_DMA_APPLET__
				arg[t].sdma.count += (actimgnum - (lastimgnum+1));
				arg[t].sdma.status[1] = arg[t].sdma.status[0];
				arg[t].sdma.status[0] = arg[t].sdma.count;
#endif
			}
		}
		// reset buffers of missing frames and actual frame
		for (long iRB = lastimgnum+1; iRB <= actimgnum; iRB++)
		{
			imgs = &this->GetRB().GetElement(iRB-1);
			imgs->Clear();
			imgs->ClearTimestamp();
			FLAG_ADD(imgs->m_flags, Grabbed);
			FLAG_ADD(imgs->m_flags, IsLiveCOGs);
			FLAG_ADD(imgs->m_flags, IsLiveHist);
			imgs->SetTimestamp(iRB, filetimestamps);
			imgs->m_frmNum	= iRB;
		}

		if (actimgnum > 10 && (actimgnum % 10 == 1))
		{
			this->SetFramrate((float)( (1E6 * 10) 
			/	 (this->GetRB().GetElement(actimgnum-1).m_sisotimestamp	- this->GetRB().GetElement(actimgnum-11).m_sisotimestamp)));
		}
		LOOPALL
		{
			arg[t].sdma.count++;
		}
	
#ifndef _DEBUG
		SetPriorityClass	(GetCurrentProcess(), priorityclass);
		SetThreadPriority	(GetCurrentThread() , threadpriority);
#endif
		if (	(
				this->m_grabcount > 0 
				&&(  arg[0].sdma.count >= this->m_grabcount) 
#ifdef __MULTI_DMA_APPLET__
				&&(  arg[1].sdma.count >= this->m_grabcount)
				&&(  arg[2].sdma.count >= this->m_grabcount)
#endif
				)
				|| (this->m_DurMSec> 0 &&(timer.elapsed() > this->m_DurMSec))
			)
			this->m_run = false;
#ifdef __MULTI_DMA_APPLET__
		if(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_ROISset)
			slotCalcMonitoring();
#endif

	}
	while(this->m_run);
#ifdef __SHOW_HFR__
	CloseDisplay(dispId0);
#endif
	LOOPALL
	{
		
#ifdef __ME5__ //todo maybe - dependent on chosen camera 
		g_pFPGA_IFcore->m_CL_camera[2]->DoStopAcquisition();
#endif
		Fg_stopAcquireEx(this->m_fg,arg[t].dmaNr,arg[t].sdma.pmem,STOP_ASYNC);
		//fprintf(stdout,"DMA%d stopped (%d)\n", arg[t].dmaNr, arg[t].sdma.count);
	}
}

//Provide framegrabber with ROI positions and size of ROIs
void	SiSo_AppletMin::SetRoIs()
{
	unsigned int totalROIS	= this->GetRB().m_myRef.getTotalROIs()*2;
	unsigned int height		= this->GetRB().m_myRef.getWidthSubROI();
	unsigned int width		= this->GetRB().m_myRef.getWidthSubROI();
	unsigned int ImgWidth	= this->m_DMA[0].sdma.size.x;
	unsigned int ImgHeight	= this->m_DMA[0].sdma.size.y;

	if (!this->m_fg)
		return;

	int ret;

	/*============ ImageBufferMultiRoI : ImageBufROI ============== */

	int Device1_Process0_ImageBufROI_Mode_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_Mode");	/* static parameter */

	int Device1_Process0_ImageBufROI_MaxNumRoI_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_MaxNumRoI");	/* static parameter */

	int Device1_Process0_ImageBufROI_NumRoI_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_NumRoI");
	unsigned int Device1_Process0_ImageBufROI_NumRoI;
	Device1_Process0_ImageBufROI_NumRoI = totalROIS;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_ImageBufROI_NumRoI_Id, &Device1_Process0_ImageBufROI_NumRoI, 0, FG_PARAM_TYPE_UINT32_T);
	ret = Fg_setParameter(this->m_fg, Device1_Process0_ImageBufROI_NumRoI_Id, &Device1_Process0_ImageBufROI_NumRoI, 0);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_ImageBufROI_XOffset_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_XOffset");
	int Device1_Process0_ImageBufROI_XLength_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_XLength");
	int Device1_Process0_ImageBufROI_YOffset_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_YOffset");
	int Device1_Process0_ImageBufROI_YLength_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_YLength");
	FieldParameterInt Device1_Process0_ImageBufROI_XOffset;
	FieldParameterInt Device1_Process0_ImageBufROI_XLength;
	FieldParameterInt Device1_Process0_ImageBufROI_YOffset;
	FieldParameterInt Device1_Process0_ImageBufROI_YLength;

	//reorganize ROIs
	FPGA_IF_Img*		imgs = &this->GetRB().GetRefImg();
	std::vector<ROIInfo> ROIS = this->GetRB().m_myRef.getROIs();
	std::vector<int> xvals;
	std::vector<int> yvals;

	int offsetX = 0;
	int offsetY = 0;

	//Reorganize ROIs in sequential order - forget about pair structure
	if(this->GetRB().m_myRef.m_ROISset)
	{
		for (unsigned int ROIidx = 0;ROIidx < this->GetRB().m_myRef.getTotalROIs() ; ROIidx++)
		{
			offsetX = ROIS[ROIidx].OriginSubLeftImg.x;
			offsetY = ROIS[ROIidx].OriginSubLeftImg.y;
			//first Left
			xvals.push_back(offsetX);
			yvals.push_back(offsetY);
			//then right
			offsetX = ROIS[ROIidx].OriginSubRightImg.x;
			offsetY = ROIS[ROIidx].OriginSubRightImg.y;
			xvals.push_back(offsetX);
			yvals.push_back(offsetY);
		}
	}
	else
	{
		for (unsigned int ROIidx = 0;ROIidx < this->GetRB().m_myRef.getTotalROIs() ; ROIidx++)
		{
			offsetX = 0;
			offsetY = 0;
			//first Left
			xvals.push_back(offsetX);
			yvals.push_back(offsetY);
			//then right
			offsetX = 0;
			offsetY = 0;
			xvals.push_back(offsetX);
			yvals.push_back(offsetY);
		}
	}
		
	for(unsigned int idx = 0; idx<totalROIS; idx++)
	{
		unsigned int	xVal	= static_cast<unsigned int>(xvals[idx]);
		unsigned int	yVal	= static_cast<unsigned int>(yvals[idx]);
		unsigned int	tempW	= width;
		unsigned int	tempH	= height;

		int ret;

		//Check if ROI within image!
		if(xVal+tempW > ImgWidth)
		{
			cout << "Critical value for setting ROI" << endl;
		}

		if(yVal+tempH > ImgHeight)
		{
			cout << "Critical value for setting ROI" << endl;
		}

		Device1_Process0_ImageBufROI_XOffset.value = xVal;
		Device1_Process0_ImageBufROI_XOffset.index = idx;
		ret = Fg_setParameter(this->m_fg, Device1_Process0_ImageBufROI_XOffset_Id, &Device1_Process0_ImageBufROI_XOffset, 0);
		if (ret != 0) std::cout<<(Fg_getErrorDescription(this->m_fg, ret)) << std::endl;

		Device1_Process0_ImageBufROI_YOffset.value = yVal;
		Device1_Process0_ImageBufROI_YOffset.index = idx;
		ret = Fg_setParameter(this->m_fg, Device1_Process0_ImageBufROI_YOffset_Id, &Device1_Process0_ImageBufROI_YOffset, 0);
		if (ret != 0) std::cout<<(Fg_getErrorDescription(this->m_fg, ret))<< std::endl;

		Device1_Process0_ImageBufROI_XLength.value = tempW;
		Device1_Process0_ImageBufROI_XLength.index = idx;
		ret = Fg_setParameter(this->m_fg, Device1_Process0_ImageBufROI_XLength_Id, &Device1_Process0_ImageBufROI_XLength, 0);
		if (ret != 0) std::cout<<(Fg_getErrorDescription(this->m_fg, ret))<< std::endl;

		Device1_Process0_ImageBufROI_YLength.value = tempH;
		Device1_Process0_ImageBufROI_YLength.index = idx;
		ret = Fg_setParameter(this->m_fg, Device1_Process0_ImageBufROI_YLength_Id, &Device1_Process0_ImageBufROI_YLength, 0);
		if (ret != 0) std::cout<<(Fg_getErrorDescription(this->m_fg, ret))<< std::endl;
	}

	int Device1_Process0_ImageBufROI_Unlock_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_Unlock");
	unsigned int Device1_Process0_ImageBufROI_Unlock;
	Device1_Process0_ImageBufROI_Unlock = 0;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_ImageBufROI_Unlock_Id, &Device1_Process0_ImageBufROI_Unlock, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_ImageBufROI_InfiniteSource_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_InfiniteSource");	/* static parameter */

	int Device1_Process0_ImageBufROI_FillLevel_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_FillLevel");	/* dynamic read only parameter */

	int Device1_Process0_ImageBufROI_Overflow_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBufROI_Overflow");	/* dynamic read only parameter */

	return;
}

//Set main ROI - Main cropped camera image
void	SiSo_AppletMin::SetMainRoI()
{
	//Todo - make configurable
	LPoint dim = pCLcamSelected->GetImageSize_px();
	LPoint offset = pCLcamSelected->GetImageOffset_px();
	int ImageBuf_XOffset = offset.x;
	int ImageBuf_XLength = dim.x;
	int ImageBuf_YOffset = offset.y;
	int ImageBuf_YLength = dim.y;

	if (!this->m_fg)
		return;


	/*============ DmaToPC : Hist_GBL ============== */

	int Device1_Process0_Hist_GBL_PixelsPerLine_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Hist_GBL_PixelsPerLine");	/* dynamic read only parameter */

	int Device1_Process0_Hist_GBL_BytesPerLine_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Hist_GBL_BytesPerLine");	/* dynamic read only parameter */

	/*============ DmaToPC : Image ============== */

	int Device1_Process0_Image_PixelsPerLine_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Image_PixelsPerLine");	/* dynamic read only parameter */

	int Device1_Process0_Image_BytesPerLine_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Image_BytesPerLine");	/* dynamic read only parameter */

	/*============ ImageBuffer : ImageBuf ============== */

	int Device1_Process0_ImageBuf_XOffset_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBuf_XOffset");
	unsigned int Device1_Process0_ImageBuf_XOffset;
	Device1_Process0_ImageBuf_XOffset = ImageBuf_XOffset;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_ImageBuf_XOffset_Id, &Device1_Process0_ImageBuf_XOffset, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_ImageBuf_XLength_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBuf_XLength");
	unsigned int Device1_Process0_ImageBuf_XLength;
	Device1_Process0_ImageBuf_XLength = ImageBuf_XLength;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_ImageBuf_XLength_Id, &Device1_Process0_ImageBuf_XLength, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_ImageBuf_YOffset_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBuf_YOffset");
	unsigned int Device1_Process0_ImageBuf_YOffset;
	Device1_Process0_ImageBuf_YOffset = ImageBuf_YOffset;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_ImageBuf_YOffset_Id, &Device1_Process0_ImageBuf_YOffset, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_ImageBuf_YLength_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBuf_YLength");
	unsigned int Device1_Process0_ImageBuf_YLength;
	Device1_Process0_ImageBuf_YLength = ImageBuf_YLength;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_ImageBuf_YLength_Id, &Device1_Process0_ImageBuf_YLength, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_ImageBuf_FillLevel_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBuf_FillLevel");	/* dynamic read only parameter */

	int Device1_Process0_ImageBuf_Overflow_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBuf_Overflow");	/* dynamic read only parameter */

	int Device1_Process0_ImageBuf_InfiniteSource_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_ImageBuf_InfiniteSource");	/* static parameter */
}


//Set threshold thats being added to the mean of local roi
void	SiSo_AppletMin::SetThresholdMin(int thresh)
{
	
	if (thresh == m_thresh_min)
		return;

	if (thresh < 0 || thresh > 255)
		return;

	m_thresh_min = thresh;
	/*============ IS_GreaterEqual : globalOffset ============== */

	//cout << "Threshold: " << this->m_thresh << endl;

	if (!this->m_fg)
		return;

	/*============ CONST : ThresholdL2Z ============== */

	int Device1_Process0_Low2Zero_ThresholdL2Z_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_ThresholdL2Z_Value");
	int Device1_Process0_Low2Zero_ThresholdL2Z_Value;
	Device1_Process0_Low2Zero_ThresholdL2Z_Value = thresh;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Low2Zero_ThresholdL2Z_Value_Id, &Device1_Process0_Low2Zero_ThresholdL2Z_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ CONST : 0 ============== */

	int Device1_Process0_Low2Zero_0_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_0_Value");
	int Device1_Process0_Low2Zero_0_Value;
	Device1_Process0_Low2Zero_0_Value = 0;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Low2Zero_0_Value_Id, &Device1_Process0_Low2Zero_0_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ CONST : devide2one ============== */

	int Device1_Process0_Low2Zero_devide2one_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_devide2one_Value");
	int Device1_Process0_Low2Zero_devide2one_Value;
	Device1_Process0_Low2Zero_devide2one_Value = 100;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Low2Zero_devide2one_Value_Id, &Device1_Process0_Low2Zero_devide2one_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

}

//Triggermode - not really interesting here since freerun
void SiSo_AppletMin::SetTriggerMode(TrgPortArea::TriggerModeN triggermode)
{
	static bool first = true;
	if (this->m_TriggerMode == triggermode && !first)
		return;
	first = false;

	MESSAGE2("TriggerMode", (triggermode == TrgPortArea::ExternSw_Trigger ? "swt (async)" : "gc (sync)"));

	if (!this->m_fg)
		return;
	bool running = this->isRunning();
	if (running)
	{
		this->stop();
	}
	this->m_TriggerMode = triggermode;
	this->SetTrigger(this->m_TriggerMode == TrgPortArea::ExternSw_Trigger ? true : false);
	pCLcamSelected->	SetTriggerMode(this->m_TriggerMode);

	// one dummy grab to avoid timeouts
	if (this->m_TriggerMode == TrgPortArea::ExternSw_Trigger && GetImageBufferCount())
	{
		this->SetGrabCount(1);
		this->start();
		this->wait();
	}

	if (running)
	{
		this->SetGrabCount(-1);
		this->start();
	}
}

//Update displayed frame
void SiSo_AppletMin::Update			(int frm)
{
	if (!this->isRunning())
	{
		emit timerstop();
		emit updateLiveGrab(false);
	}
	else
	{
		if (frm == -1)
			frm = this->m_RB.GetActualImgNum()-3;

		FPGA_IF_Img* imgs = &this->m_RB.GetElement(frm-1);
		
		emit this->updateImageView(frm);
	}
}

void	SiSo_AppletMin::slotCalcMonitoring(){
	
	FPGA_IF_Img* imgs	= &this->GetRB().GetLatestElement();

	// perform fit to enable real time monitoring
	//imgs->HistList();
	imgs->COGList();
	//main analysis functionality goes here!!!
}

//Initialize DMA0 - raw  image
void	SiSo_AppletMin::iDMA0	()
{
	this->m_DMA[0].sdma.status[0]	= 0;
	this->m_DMA[0].sdma.status[1]	= 0;
	this->m_DMA[0].sdma.count	= 0;

#ifndef __ME5__ //CoaXPress interface handles global ROI !
	this->SetMainRoI();
#endif

}

//Initialize DMA1 - raw output of weighted sumx,sumY,sumAll
void	SiSo_AppletMin::iDMA1	()
{
	int totalROIS = this->GetRB().m_myRef.getTotalROIs()*2;
	int ROIHeight   = this->GetRB().m_myRef.getWidthSubROI();
	int ROIWidth   = this->GetRB().m_myRef.getWidthSubROI();
	this->m_DMA[1].sdma.status[0]	= 0;
	this->m_DMA[1].sdma.status[1]	= 0;
	this->m_DMA[1].sdma.count	= 0;

	this->SetRoIs();
	this->SetThresholdMin(this->GetThresholdMin());

	if (!this->m_fg)
		return;

	/*============ AppendImage : CollectDataG ============== */

	int Device1_Process0_CollectDataG_AppendNumber_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_CollectDataG_AppendNumber");
	unsigned int Device1_Process0_CollectDataG_AppendNumber;
	Device1_Process0_CollectDataG_AppendNumber = totalROIS;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_CollectDataG_AppendNumber_Id, &Device1_Process0_CollectDataG_AppendNumber, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_CollectDataG_LinesToSimulate_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_CollectDataG_LinesToSimulate");	/* static parameter */

	/*============ AppendImage : CollectDataGY ============== */

	int Device1_Process0_CollectDataGY_AppendNumber_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_CollectDataGY_AppendNumber");
	unsigned int Device1_Process0_CollectDataGY_AppendNumber;
	Device1_Process0_CollectDataGY_AppendNumber = totalROIS;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_CollectDataGY_AppendNumber_Id, &Device1_Process0_CollectDataGY_AppendNumber, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_CollectDataGY_LinesToSimulate_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_CollectDataGY_LinesToSimulate");	/* static parameter */

	/*============ AppendImage : CollectDataGX ============== */

	int Device1_Process0_CollectDataGX_AppendNumber_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_CollectDataGX_AppendNumber");
	unsigned int Device1_Process0_CollectDataGX_AppendNumber;
	Device1_Process0_CollectDataGX_AppendNumber = totalROIS;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_CollectDataGX_AppendNumber_Id, &Device1_Process0_CollectDataGX_AppendNumber, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_CollectDataGX_LinesToSimulate_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_CollectDataGX_LinesToSimulate");	/* static parameter */

	/*============ CONST : FrameSumFlag_0 ============== */

	int Device1_Process0_getCOG_FrameSumFlag_0_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_FrameSumFlag_0_Value");
	int Device1_Process0_getCOG_FrameSumFlag_0_Value;
	Device1_Process0_getCOG_FrameSumFlag_0_Value = 0;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_getCOG_FrameSumFlag_0_Value_Id, &Device1_Process0_getCOG_FrameSumFlag_0_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ IS_Equal : lastY ============== */

	int Device1_Process0_getCOG_getScalarGX_lastY_Number_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGX_lastY_Number");
	int Device1_Process0_getCOG_getScalarGX_lastY_Number;
	Device1_Process0_getCOG_getScalarGX_lastY_Number = ROIHeight-1;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_getCOG_getScalarGX_lastY_Number_Id, &Device1_Process0_getCOG_getScalarGX_lastY_Number, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ RemovePixel : RemPix ============== */

	int Device1_Process0_getCOG_getScalarGX_RemPix_FlushCondition_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGX_RemPix_FlushCondition");	/* static parameter */

	/*============ IS_Equal : lastX ============== */

	int Device1_Process0_getCOG_getScalarGX_lastX_Number_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGX_lastX_Number");
	int Device1_Process0_getCOG_getScalarGX_lastX_Number;
	Device1_Process0_getCOG_getScalarGX_lastX_Number = ROIWidth-1;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_getCOG_getScalarGX_lastX_Number_Id, &Device1_Process0_getCOG_getScalarGX_lastX_Number, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ SelectFromParallel : GetFirstParallel ============== */

	int Device1_Process0_getCOG_getScalarGX_GetFirstParallel_ParNum_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGX_GetFirstParallel_ParNum");	/* static parameter */

	/*============ IS_Equal : lastY ============== */

	int Device1_Process0_getCOG_getScalarGY_lastY_Number_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGY_lastY_Number");
	int Device1_Process0_getCOG_getScalarGY_lastY_Number;
	Device1_Process0_getCOG_getScalarGY_lastY_Number = ROIHeight - 1;
	Fg_setParameterWithType(this->m_fg, Device1_Process0_getCOG_getScalarGY_lastY_Number_Id, &Device1_Process0_getCOG_getScalarGY_lastY_Number, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ RemovePixel : RemPix ============== */

	int Device1_Process0_getCOG_getScalarGY_RemPix_FlushCondition_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGY_RemPix_FlushCondition");	/* static parameter */

	/*============ IS_Equal : lastX ============== */

	int Device1_Process0_getCOG_getScalarGY_lastX_Number_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGY_lastX_Number");
	int Device1_Process0_getCOG_getScalarGY_lastX_Number;
	Device1_Process0_getCOG_getScalarGY_lastX_Number = ROIWidth-1;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_getCOG_getScalarGY_lastX_Number_Id, &Device1_Process0_getCOG_getScalarGY_lastX_Number, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ SelectFromParallel : GetFirstParallel ============== */

	int Device1_Process0_getCOG_getScalarGY_GetFirstParallel_ParNum_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarGY_GetFirstParallel_ParNum");	/* static parameter */

	/*============ IS_Equal : lastY ============== */

	int Device1_Process0_getCOG_getScalarG_lastY_Number_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarG_lastY_Number");
	int Device1_Process0_getCOG_getScalarG_lastY_Number;
	Device1_Process0_getCOG_getScalarG_lastY_Number = ROIHeight - 1;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_getCOG_getScalarG_lastY_Number_Id, &Device1_Process0_getCOG_getScalarG_lastY_Number, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ RemovePixel : RemPix ============== */

	int Device1_Process0_getCOG_getScalarG_RemPix_FlushCondition_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarG_RemPix_FlushCondition");	/* static parameter */

	/*============ IS_Equal : lastX ============== */

	int Device1_Process0_getCOG_getScalarG_lastX_Number_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarG_lastX_Number");
	int Device1_Process0_getCOG_getScalarG_lastX_Number;
	Device1_Process0_getCOG_getScalarG_lastX_Number = ROIWidth - 1;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_getCOG_getScalarG_lastX_Number_Id, &Device1_Process0_getCOG_getScalarG_lastX_Number, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ SelectFromParallel : GetFirstParallel ============== */ 

	int Device1_Process0_getCOG_getScalarG_GetFirstParallel_ParNum_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_getCOG_getScalarG_GetFirstParallel_ParNum");	/* static parameter */

	/*============ Histogram : HistLine ============== */ 

	int Device1_Process0_HistLine_AutoSync_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_HistLine_AutoSync");	/* static parameter */

	/*============ CONST : ThresholdL2Z ============== */ 
	
	int Device1_Process0_Low2Zero_ThresholdL2Z_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_ThresholdL2Z_Value");
	int Device1_Process0_Low2Zero_ThresholdL2Z_Value;
	Device1_Process0_Low2Zero_ThresholdL2Z_Value = m_thresh_min;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Low2Zero_ThresholdL2Z_Value_Id, &Device1_Process0_Low2Zero_ThresholdL2Z_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ CONST : 0 ============== */

	int Device1_Process0_Low2Zero_0_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_0_Value");
	int Device1_Process0_Low2Zero_0_Value;
	Device1_Process0_Low2Zero_0_Value = 0;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Low2Zero_0_Value_Id, &Device1_Process0_Low2Zero_0_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ DmaToPC : RawROI ============== */

	int Device1_Process0_RawROI_PixelsPerLine_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_RawROI_PixelsPerLine");	/* dynamic read only parameter */

	int Device1_Process0_RawROI_BytesPerLine_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_RawROI_BytesPerLine");	/* dynamic read only parameter */

	/*============ SelectFromParallel : RelevantVals ============== */

	int Device1_Process0_RelevantVals_ParNum_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_RelevantVals_ParNum");	/* static parameter */

	/*============ CameraGrayAreaBase : Kamera0 ============== */

	int Device1_Process0_Kamera0_UseDval_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Kamera0_UseDval");
	unsigned int Device1_Process0_Kamera0_UseDval;
	Device1_Process0_Kamera0_UseDval = CameraGrayAreaBase::DVAL_Enabled;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Kamera0_UseDval_Id, &Device1_Process0_Kamera0_UseDval, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	int Device1_Process0_Kamera0_Format_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Kamera0_Format");
	unsigned int Device1_Process0_Kamera0_Format;
	Device1_Process0_Kamera0_Format = CameraGrayAreaBase::DualTap8Bit;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Kamera0_Format_Id, &Device1_Process0_Kamera0_Format, 0, FG_PARAM_TYPE_UINT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ CONST : module89 ============== */

	int Device1_Process0_Low2Zero_module89_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_module89_Value");
	int Device1_Process0_Low2Zero_module89_Value;
	Device1_Process0_Low2Zero_module89_Value = 0;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Low2Zero_module89_Value_Id, &Device1_Process0_Low2Zero_module89_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ CONST : devide2one ============== */

	int Device1_Process0_Low2Zero_devide2one_Value_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_devide2one_Value");
	int Device1_Process0_Low2Zero_devide2one_Value;
	Device1_Process0_Low2Zero_devide2one_Value = 100;
	ret = Fg_setParameterWithType(this->m_fg, Device1_Process0_Low2Zero_devide2one_Value_Id, &Device1_Process0_Low2Zero_devide2one_Value, 0, FG_PARAM_TYPE_INT32_T);
	if (ret != 0) MESSAGE(Fg_getErrorDescription(this->m_fg, ret));

	/*============ ExpandPixel : module96 ============== */

	int Device1_Process0_Low2Zero_module96_Init_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_module96_Init");	/* static parameter */

	int Device1_Process0_Low2Zero_module96_AutoSync_Id = Fg_getParameterIdByName(this->m_fg, "Device1_Process0_Low2Zero_module96_AutoSync");	/* static parameter */

}

//Histogramm - not used for now
void	SiSo_AppletMin::iDMA2	()
{
	this->m_DMA[2].sdma.status[0]	= 0;
	this->m_DMA[2].sdma.status[1]	= 0;
	this->m_DMA[2].sdma.count	= 0;
}

//Tap Gain - only used for cameras with multiple taps
void FPGA_IFMainWindow::slotCamTapGain()
{
	pCLcamSelected->SetTapGain(FPGA_IF::tapA, ui->m_sbTapGainA->value());
	pCLcamSelected->SetTapGain(FPGA_IF::tapB, ui->m_sbTapGainB->value());
	g_pFPGA_IFcore->slotUpdateInternalData();
}

//Set trigger - freerun
void SiSo_AppletMin::SetTrigger(bool swt)
{
	if (!this->m_fg)
		return;
}

//Set width of (all) ROIs
void	SiSo_AppletMin::SetROIWidth		(int roiWidth)
{
	//this->GetRB().m_myRef.m_SubOffset.x	= (MAXFPGAROISIZEX - roiWidth) /2;
	//if (this->GetRB().m_myRef.m_SubOffset.x % this->m_modulo != 0) this->GetRB().m_myRef.m_SubOffset.x -= this->GetRB().m_myRef.m_SubOffset.x % this->m_modulo;

	this->m_ROIWidth = roiWidth;
	this->GetRB().m_myRef.setWidthSubROI(roiWidth);
	if (!this->m_fg)
		return ;
}

//Set height of (all) ROIs
void	SiSo_AppletMin::SetROIHeight	(int roiHeight)
{
	//this->GetRB().m_myRef.m_SubOffset.y	= (MAXFPGAROISIZEY - roiHeight) /2;
	//if (this->GetRB().m_myRef.m_SubOffset.y % this->m_modulo != 0) this->GetRB().m_myRef.m_SubOffset.y -= this->GetRB().m_myRef.m_SubOffset.y % this->m_modulo;

	this->m_ROIHeight = roiHeight;
	this->GetRB().m_myRef.setHeightSubROI(roiHeight);
	if (!this->m_fg)
		return ;
}

//Set ID of ROI that should be displayed individually
void	SiSo_AppletMin::SetROIId	(int roiId)
{
	this->m_ROIId = roiId;
	if (!this->m_fg)
		return ;
}

//Set ID of ROI that should be displayed individually
void	SiSo_AppletMin::SetMaxAmp(int maxAmp)
{
	this->m_maxAmpl= maxAmp;
	if (!this->m_fg)
		return;
}

//Set ID of ROI that should be displayed individually
void	SiSo_AppletMin::SetNSamples(int nSamples)
{
	this->m_NSamples = nSamples;
	if (!this->m_fg)
		return;
}

//Update Board and Port number
void FPGA_IFMainWindow::slotCamBoardAndPort(int value)
{
	if (pCLcamSelected->IsInit())
		return;

	pCLcamSelected->SetBoard((board)ui->m_cbBoard->currentIndex());
	pCLcamSelected->SetPort	((port)ui->m_cbPort->currentIndex());
	g_pFPGA_IFcore->slotUpdateInternalData();
}

//Set certain camera active - only really important if multiple cameras are used
void FPGA_IFMainWindow::slotCamActive(bool value)
{
	if (value)	// switch camera on
	{
		if (!pCLcamSelected->Init())
		{
			QMessageBox msgBox;
			msgBox.setText("Camera can not be initialized");
			msgBox.exec();
			cout << "Camera can not be initialized in this configuration!" << endl;
			ui->m_cbCameraActive->setChecked(false);
			ui->m_cbCameraActive->repaint();
		}
	}
	else
	{
		pCLcamSelected->DeInit();
	}
	g_pFPGA_IFcore->slotUpdateInternalData();
}

//Read Initialization file
bool SiSo_AppletMin::ReadIni		(MIniFile& ini)
{
	SiSo_AppletIF::ReadIni(ini);
	QString qstr;

	bool triggermode;
	ini.getItem(INI_FG_TRIGGERMODE	.toStdString(), triggermode, false);
	this->m_TriggerMode = triggermode ? TrgPortArea::ExternSw_Trigger : TrgPortArea::GrabberControlled;
	ini.getItem(INI_FG_RUNNING	.toStdString(), this->m_startallowed, false);
	int ival;
	ini.getItem(INI_FG_SIZEIMAGEBUF	.toStdString(), ival, 1);
		this->m_RB.SetBufferCount2Use(ival);
	ini.getItem(INI_FG_THRESHOLD	.toStdString(), this->m_thresh_min, 0);
	ini.getItem(INI_FG_ROISIZEX		.toStdString(), this->m_ROIWidth,0);
	ini.getItem(INI_FG_ROISIZEY		.toStdString(), this->m_ROIHeight,0);
	ini.getItem(INI_FG_ROIID		.toStdString(), this->m_ROIId,0);
	ini.getItem(INI_FG_MAXAMPL.toStdString(), this->m_maxAmpl, 0);
	ini.getItem(INI_FG_NSAMPLES.toStdString(), this->m_NSamples, 0);
	ini.getItem(INI_FG_MEASURETIME	.toStdString(), this->m_DurMSec, 0);
	
	return true;	     
}

//Write Initialization file
bool SiSo_AppletMin::WriteIni		(MIniFile& ini)
{
	ini.setItem(INI_FG_TRIGGERMODE	.toStdString(), this->m_TriggerMode == TrgPortArea::ExternSw_Trigger ? true : false);
	ini.setItem(INI_FG_RUNNING		.toStdString(), this->isRunning());
	ini.setItem(INI_FG_SIZEIMAGEBUF	.toStdString(), this->GetImageBufferCount());
	ini.setItem(INI_FG_THRESHOLD	.toStdString(), this->m_thresh_min);
	ini.setItem(INI_FG_MAXAMPL.toStdString(), this->m_maxAmpl);
	ini.setItem(INI_FG_NSAMPLES.toStdString(), this->m_NSamples);
	//ini.setItem(INI_FG_THRESHINI	.toStdString(), this->m_threshIni);
	ini.setItem(INI_FG_ROISIZEX		.toStdString(), this->m_ROIWidth);
	ini.setItem(INI_FG_ROISIZEY		.toStdString(), this->m_ROIHeight);
	ini.setItem(INI_FG_ROIID		.toStdString(), this->m_ROIId);
	ini.setItem(INI_FG_MEASURETIME	.toStdString(), this->m_DurMSec);

	SiSo_AppletIF::WriteIni(ini);
	return true;
}