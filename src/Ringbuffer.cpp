/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "Ringbuffer.h"
#include "FPGA_Interface_Core.h"
#include <QMessageBox>

Ringbuffer::Ringbuffer		(FPGA_IF_Core& core) : m_core(core), m_refImg(core)
{
	this->m_buffer.clear();	
	this->m_actualImgNum		= -1;
	this->m_buffercount2use		= 1;
	m_myMeasure = new MeasurementData;

	m_myMeasure->nSamples		= 0;
	m_referenz = false;
	//m_myMeasure->empty = true;

	int totROIS					= __MAX_ROIS__;
	m_myMeasure->	nROIS		= totROIS;
	m_myMeasure->	validROI.resize(totROIS);
	m_myMeasure->	leftROIImgCoordsx.resize(totROIS);
	m_myMeasure->	rightROIImgCoordsx.resize(totROIS);
	m_myMeasure->	leftROIImgCoordsy.resize(totROIS);
	m_myMeasure->	rightROIImgCoordsy.resize(totROIS);
    
	m_myMeasure->	circleL_centROIx.resize(totROIS);
	m_myMeasure->	circleR_centROIx.resize(totROIS);
	m_myMeasure->	circleL_centROIy.resize(totROIS);
	m_myMeasure->	circleR_centROIy.resize(totROIS);
	m_myMeasure->	distance.resize(totROIS);
	m_myMeasure->	distancePlot.resize(totROIS);
}

Ringbuffer::~Ringbuffer		()
{
	delete m_myMeasure;
	this->Free();
}

//Clear the measurement data
void Ringbuffer::clearMeasData(bool delete_all)
{
	m_myMeasure->nSamples=0;
	m_myMeasure->measTstamp.clear();

	for(int i = 0 ;i< m_myMeasure->nROIS;i++)
	{
		m_myMeasure->circleL_centROIx[i].clear();   
		m_myMeasure->circleL_centROIy[i].clear();    
		m_myMeasure->circleR_centROIx[i].clear();    
		m_myMeasure->circleR_centROIy[i].clear();    
		m_myMeasure->distance[i].clear();

		m_myMeasure->distancePlot[i].clear();

	}

	if(!delete_all)
		return;
	
	//if everything should be deleted also erase the ROI positions
	for(int i = 0 ;i< m_myMeasure->nROIS;i++)
	{
		m_myMeasure->validROI			[i]= -1;
		m_myMeasure->leftROIImgCoordsx	[i]= -1;       
		m_myMeasure->leftROIImgCoordsy	[i]= -1;          
		m_myMeasure->rightROIImgCoordsx [i]= -1;       
		m_myMeasure->rightROIImgCoordsy [i]= -1;
	}
	//m_myMeasure->empty = true;
}

//calculate the maximum number of images that can be hold by RAM 
unsigned long	Ringbuffer::CalcMaxImageCount	(long bytesize)
{
#define KB	1024	
#define MB	KB * KB
#define GB	MB * KB

#define	MAXBUFSIZE	GB * 3
static char *divisor = "M";
#define DIV (MB)
#define WIDTH 5

	unsigned long ImgBYTESize	= bytesize;//size.x * size.y * sizeof(UCHAR);

	MEMORYSTATUS stat;
	GlobalMemoryStatus (&stat);
	if (1)
	{
		printf ("\nMemory status in %sB:\n", divisor);
		printf ("%ld%% of memory is in use.\n", stat.dwMemoryLoad);
		printf ("physical memory %*ld / %*ld\n",	WIDTH, stat.dwTotalPhys/DIV,	WIDTH, stat.dwAvailPhys/DIV);
		printf ("paging   memory %*ld / %*ld\n",	WIDTH, stat.dwTotalPageFile/DIV,WIDTH, stat.dwAvailPageFile/DIV);
		printf ("virtual  memory %*ld / %*ld\n",	WIDTH, stat.dwTotalVirtual/DIV,	WIDTH, stat.dwAvailVirtual/DIV);
	}
/*
	if (ImgBYTESize * count >= stat.dwAvailPhys*0.99)
		return false;

	//stat.dwAvailPhys = MAXBUFSIZE;
	//this->m_ImgCount = (unsigned long)((unsigned long)(stat.dwAvailPhys*0.9) / this->m_ImgBYTESize);
	fprintf(stdout	,"RAM: %4d %sB, used: %4d %sB (%6.2lf%%)\n"
		,(stat.dwAvailPhys)/DIV
		, divisor
		,(ImgBYTESize * count)/DIV
		, divisor
		,((ImgBYTESize * count*100.) / stat.dwAvailPhys));
*/
	unsigned long imgcount = stat.dwAvailPhys / ImgBYTESize;
	//printf("MaxImgCount: %d\n", imgcount);
	return imgcount;

}


//Allocate the frame buffer
bool	Ringbuffer::Alloc		(long count)
{
	this->Free();

	// map::key = ImgNumber [0..N-1]
	for (long c = 0; c < count; c++)
		this->m_buffer[c] = new FPGA_IF_Img(this->m_core);

	this->m_buffer.size();
	
	return true;
}

//Free the buffer
bool	Ringbuffer::Free		()
{
	for (long c = 0; c < (int)this->m_buffer.size(); c++)
		delete this->m_buffer[c];

	this->m_buffer.clear();		

	return true;
}

//get desired image out of buffer
FPGA_IF_Img&	Ringbuffer::GetElement	(long num)
{	
	if (this->m_buffer.size()==0)
	{
		MESSAGE("No ringbuffer allocated");
		assert(0);
	}

	if (num < -(long)this->m_buffer.size())
		num %= this->m_buffer.size();

	num += static_cast<long>(this->m_buffer.size());	// shift to positve values
	num %= static_cast<long>(this->m_buffer.size());	// modulo in buffer range

//	cout << "Get<- " << num << endl;

	return *(this->m_buffer.find(num))->second;
}

//Get the number of image in buffer
long	Ringbuffer::GetElementNum		(FPGA_IF_Img* imgs)
{
	if( imgs == NULL )
		return -1;

	map<int, FPGA_IF_Img*>::iterator	imap;
	for (imap = this->m_buffer.begin(); imap != this->m_buffer.end(); imap++)
	{
		if (imap->second == imgs)
			return imap->first;
	}
	return -1;
}

//Get the latest image from the buffer
FPGA_IF_Img&	Ringbuffer::GetLatestElement	()
{
	return GetElement(m_actualImgNum-1);
}

//Update the preview image - the one with the info overlays
void	Ringbuffer::UpdateInfoView(cv::Mat &img)
{
	this->m_refImg.m_DMAInfoMatRef = img.clone();
}

//
void	Ringbuffer::SetRefImg		(cv::Mat &img)
{
	if (img.empty())
	{
		this->m_referenz = false;
		return;
	}

	MESSAGE("SetRefImg()");

	this->m_referenz = true;

	this->m_refImg.m_DMA0MatRef = img.clone();
	this->m_refImg.m_DMA0MatRef.convertTo(this->m_refImg.m_DMA0MatRef, CV_8UC3);
}

//Set the reference image for finding ROI positions
void	Ringbuffer::SetRefImg		(FPGA_IF_Img *img, bool write)
{
	if (!img)
	{
		this->m_referenz = false;
		return;
	}

	MESSAGE("SetRefImg()");

	this->m_referenz = true;

	this->m_refImg.m_DMA0MatRef = img->m_ImgDMA0.clone();
	this->m_refImg.m_DMA0MatRef.convertTo(this->m_refImg.m_DMA0MatRef, CV_8UC3);

	if (!write)
		return;

	QString		filePath, file;
	QChar		chr = '0';
	QString		fn;
	QDir		dir;
	QString		tsmp = QString("%1").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz_"));

	filePath	= g_pFPGA_IFcore->m_project.GetPathRef();
	file		= tsmp + "_Referenz";

	g_pFPGA_IFcore->m_project.SetLastRef(file+".tif");

	if (!dir.exists(filePath))
		dir.mkpath(filePath);

	fn = filePath + file;
	imwrite((fn+".bmp").toStdString().c_str(),pCLApplet->GetRB().GetRefImg().m_DMA0MatRef);
}

//Clear the reference image and release all ressources associated with it
void	Ringbuffer::ClearRefImg	()
{
	this->m_myRef.clear();
	this->m_refImg.m_DMA0MatRef.release();
	this->m_refImg.m_DMAInfoMatRef.release();

	this->m_refImg.m_ImgDMA0.release();
	this->m_refImg.m_ImgDMA1.release();
	this->m_refImg.m_ImgDMA2.release();
	this->m_referenz = false;

	return ;
}
