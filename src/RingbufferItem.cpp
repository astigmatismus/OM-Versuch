/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "RingbufferItem.h"
#include "FPGA_Interface_Core.h"
#include <stdutils.h>

#include <QDateTime>
#include <QLocale>
#include <QTextStream>
#include <QFile>
#include <stdutils.h>

#include <math.h>

using namespace std;

unsigned __int64	FPGA_IF_Img::m_timestampstart = 0;

FPGA_IF_Img::FPGA_IF_Img		(FPGA_IF_Core& core) : m_core(core)		
{
	this->m_frmNum	= -1;
	this->m_flags	= 0;
	this->m_timestampFormat = "yyyy-MM-dd  hh:mm:ss:zzz";
	this->m_timestampCorrected = false;

	this->Clear();
	this->ClearTimestamp();
}

//Clear 
FPGA_IF_Img::~FPGA_IF_Img		()			
{
	this->m_ImgDMA0.release();
}

//Clear image
void	FPGA_IF_Img::Clear			()
{
	QMutexLocker locker(&this->m_core.m_mutex);
	
	this->m_flags		&= Grabbed;

	this->m_DMA0MatRef.release();
	this->m_DMA0MatRef.release();
}

//Clear the timestamp
void	FPGA_IF_Img::ClearTimestamp	()
{
	QMutexLocker locker(&this->m_core.m_mutex);

	this->m_timestamp.clear();
	this->m_sisotimestamp = 0;
	this->m_frmNum		= -1;
	this->m_timestampCorrected = false;
}

//overload "equal" operator
FPGA_IF_Img&	FPGA_IF_Img::operator=		(FPGA_IF_Img &obj)
{	
	QMutexLocker locker(&this->m_core.m_mutex);
	
	this->m_frmNum			=	obj.m_frmNum;
	//this->m_ImgDMA0		=	obj.m_ImgDMA0.clone();
	
		this->m_DMA0MatRef	=	obj.m_DMA0MatRef.clone();

#ifdef __MULTI_DMA_APPLET__
	memcpy(this->m_ImgDMA1Buffer , obj.m_ImgDMA1Buffer, g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.y * sizeof(UINT32));
	memcpy(this->m_ImgDMA2Buffer , obj.m_ImgDMA2Buffer, g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.y * sizeof(UINT32));
#endif
	this->m_flags			=	obj.m_flags;
	this->m_Hist			=	obj.m_Hist;
	this->m_timestamp		=	obj.m_timestamp;
	this->m_sisotimestamp	=	obj.m_sisotimestamp;
	
	return *this;
}

//Get the size of data type associated with certain DMA
long	FPGA_IF_Img::GetTypeSize		(int DMA)
{
	switch(DMA)
	{
	case 0:
		return sizeof(unsigned char);	break;
	case 1:
		return sizeof(UINT32);	break;
	case 2:
		//return sizeof(MImageG32::PixValType);	break;
	default:
		return 0;
		break;
	}
	
	return 1;
}

//Get the size of data type in byte associated with certain DMA
long	FPGA_IF_Img::GetByteSize		(int DMA)
{
	switch(DMA)
	{
	case -1:
		return
#ifdef __MULTI_DMA_APPLET__
				(m_ImgDMA0.data != NULL  ? (int)(g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y * sizeof(unsigned char)) : 0)//;	break;
			+	(m_ImgDMA1Buffer != NULL ? (int)(g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.y * sizeof(UINT32)) : 0)
			+	(m_ImgDMA1Buffer != NULL ? (int)(g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.y * sizeof(UINT32)) : 0);
#else
			(m_ImgDMA0.data != NULL ? (int)(g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y * sizeof(unsigned char)) : 0 );
#endif
#ifdef trnasferROI 
#endif
		break;
	
	case 0:
		return m_ImgDMA0.data != NULL ? (g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y * sizeof(unsigned char)) : 0;	break;
	case 1:
		return m_ImgDMA1Buffer != NULL ? (g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.y * sizeof(UINT32)) : 0;	break;
	case 2:
		return m_ImgDMA2Buffer != NULL ? (g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.x * g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.y * sizeof(UINT32)) : 0;	break;
	case 3:
		//return m_ImgDMA3 != NULL ? m_ImgDMA3->getBufferSize() : 0;	break;
	default:
		return 0;
		break;
	}
	return 1;
}


//Get pointer handle to DMA buffer
unsigned char*	FPGA_IF_Img::GetBuffer		(int DMA)
{
	switch(DMA)
	{
	case 0:
		return m_ImgDMA0.data != NULL ? m_ImgDMA0.data : NULL;	break;
	case 1:	       
		return (unsigned char*)m_ImgDMA1Buffer != NULL ? (unsigned char*)m_ImgDMA1Buffer : NULL;	break;
	case 2:	      
		return (unsigned char*)m_ImgDMA2Buffer != NULL ? (unsigned char*)m_ImgDMA2Buffer : NULL;	break;
	case 3:	       
	default:
		return NULL;
		break;
	}
	return NULL;
}

//Get buffer size - Dimensions of DMA image
LPoint	FPGA_IF_Img::GetBufferSize		(int DMA)
{
	LPoint	ret;
	switch(DMA)
	{
	case 0:
		return m_ImgDMA0.data != NULL ? LPoint(g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x,g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y) : ret;	break;
	case 1:	 
		return m_ImgDMA1Buffer != NULL ? LPoint(g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.x,g_pFPGA_IFcore->m_CL_Applet->m_DMA[1].sdma.size.y) : ret;	break;
	case 2:	 
		return m_ImgDMA2Buffer != NULL ? LPoint(g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.x,g_pFPGA_IFcore->m_CL_Applet->m_DMA[2].sdma.size.y) : ret;	break;
	case 3:	       
	//	return m_ImgDMA3 != NULL ? LPoint(m_ImgDMA3->width(), m_ImgDMA3->height()) : ret;	break;
	default:
		return ret;
		break;
	}
}

//Set timestamp based on time in between dT
void FPGA_IF_Img::SetTimestamp(QDateTime dt){
	QMutexLocker locker(&this->m_core.m_mutex);
	m_timestamp = QString("%1").arg(dt.toString(m_timestampFormat));
}


void FPGA_IF_Img::SetTimestamp			(int num, FILE* file)
{
	QMutexLocker locker(&this->m_core.m_mutex);
	// timestamp /µs
	static QDateTime starttime;
	QDateTime now, act;
	unsigned __int64	timestamp = 0;

	act = QDateTime::currentDateTime();
	//LONGLONG		g_CurentCount, g_CurentFreq;
	//QueryPerformanceCounter	((LARGE_INTEGER*)&g_CurentCount);
	//QueryPerformanceFrequency	((LARGE_INTEGER*)&g_CurentFreq);

	if (num == -1)	// get actual time instead of the buffers timestamp
	{
		SetTimestamp(QDateTime::currentDateTime());
		return;
	}

	timestamp = num;

	Fg_getParameter(this->m_core.m_CL_Applet->GetFG(), FG_TIMESTAMP, &timestamp , 0);
//	Fg_getParameter(this->m_core.m_CL_Applet->GetFG(), FG_TIMESTAMP_LONG, &timestamp , 0);

	if (num == 1)
	{
		m_timestampstart =  timestamp;
		starttime = QDateTime::currentDateTime();
	}

	this->m_sisotimestamp = timestamp - m_timestampstart;
//	cout << "SetT(" << num << ") " << this->m_sisotimestamp << endl;

	qint64	add = (qint64)(this->m_sisotimestamp/1000.);
	now = starttime.addMSecs(add);

	// Correcting the date in case of SISO-timestamp error... //Todo time - is there a more elegant way of correcting the timestamp? Probably...
	// Note: The time will not be corrected, releatively it's still correct!
	if( now.date().year() != act.date().year() ){
		m_timestampCorrected = true;
		const QDate date(act.date().year(), act.date().month(), act.date().day());
		now.setDate(date);
	} else m_timestampCorrected = false;

	m_timestamp = QString("%1").arg(now.toString(m_timestampFormat));

	//printf("%06d\t#%016I64X\t#%016I64X\t#%016I64X\t#%016I64X\t%s\n", num, m_timestampstart, timestamp, this->m_sisotimestamp, add, m_timestamp.toStdString().c_str());
	cout << m_timestamp.toStdString() << endl;


	if (file)
	{
		fprintf(file, "%010d\t#%016I64X\t#%016I64X\t#%016I64X\t%s\n", num, m_timestampstart, timestamp, this->m_sisotimestamp, this->m_timestamp.toStdString().c_str());
		//fprintf(file, "%010d\tcount %016I64x, frq %016I64x,%016I64dsec\n", num, g_CurentCount,	g_CurentFreq,	g_CurentCount	/g_CurentFreq);
		//fprintf(file, "%010d\ttStam %016I64x, frq %016I64x,%016I64dsec\n", num, timestamp,	g_CurentFreq,	timestamp	/g_CurentFreq);
	}

}
//----------------------------------------------------------------

QString& FPGA_IF_Img::GetTimestampAsString			()
{
	return m_timestamp;
}

QDateTime FPGA_IF_Img::GetTimestampAsDateTime		()
{
	return QDateTime::fromString(m_timestamp, m_timestampFormat);
}

//fetch histogramm data from DMA port 2 - not really interesting yet
void	FPGA_IF_Img::HistList()
{
#ifdef	__MULTI_DMA_APPLET__
	//TODO maybe global Histogramm
	QMutexLocker locker(&this->m_core.m_mutex);
	cout << "Hist checked" <<endl;
	vector<int>vals;
	int sumGW = 0;
	int px = 0;

	int hist[256];

	for (int i = 0 ; i<256; i++)
	{
		hist[i]= 0;
	}
	
	
	if ((this->m_flags & IsLiveHist))
	{
		int GW = 0;
		UINT32* HistPtr = this->m_ImgDMA2Buffer;

		for (int i= 0 ; i < 256; i++)
		{
			int dd = *HistPtr; 
			vals.push_back(dd);
				sumGW = sumGW + dd;
				px++;
				hist[i] = dd;
				//this->m_Hist.m_data[dd] =+ 1;
				HistPtr++;
		}
	}
#endif
}

//fetch CoG data from DMA port 1 - pretty much the most critical part of the whole fpga-CPU-interface
//COG calculation takes a lot of time on FPGA caused by bandwidth limitations. because of that the CoG DMA port
//is the slowest. Actually one could think of completely performing all calculations on cpu and use FPGA as 
//framegrabber only. This would prevent us from struggling with silicon software Visual Applets. On the other hand
//with the CoG Calculation on the frame grabber the CPU is relieved and the processing speed is guaranteed. 
void	FPGA_IF_Img::COGList()
{
#ifdef	__MULTI_DMA_APPLET__
	QMutexLocker locker(&this->m_core.m_mutex);
	cout << "checking COGs" <<endl;						//comment this part - output takes time
	//this->m_core.m_pc.Now("COG start");

	int totalROIS	= g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getTotalROIs();

	cv::Point		GlobLeft;
	cv::Point		GlobRight;
	cv::Point2f		Dist;
	double			dist;
	unsigned int  SUMX, SUMY;
	SUMX = SUMY = 0;
	
	double avgR	=  0;
	double cXL , cXR	=  0;
	double cYL, cYR		=  0;

	UINT32 TMPcogx;
	UINT32 TMPcogy;
	UINT32 TMPcog;

	//std::vector<double>cogX;
	//std::vector<double>cogY;
	//vector<int>vals;
	//vector<int>sumX;
	//vector<int>sumY;
	//vector<int>sumAll;

	if ((this->m_flags & IsLiveCOGs))
	{
		//g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->empty = false;
		int GW = 0;
		UINT32* imgContent = this->m_ImgDMA1Buffer;

		for (int i= 0 ; i < totalROIS; i++)
		{
			TMPcogx = *imgContent;
			//sumX.push_back(TMPcogx);
			//vals.push_back(*imgContent);
			imgContent++;

			//save y value
			TMPcogy = *imgContent;
			//sumY.push_back(TMPcogy);
			//vals.push_back(*imgContent);
			imgContent++;
				
			//save sum value
			TMPcog = *imgContent;
			//sumAll.push_back(TMPcog);
			//vals.push_back(*imgContent);
			imgContent++;

			//calculate cog Left:
			cXL = static_cast<double>(TMPcogx) / static_cast<double>(TMPcog);
			cYL = static_cast<double>(TMPcogy) / static_cast<double>(TMPcog);

			//cogX.push_back(cXL);
			//cogY.push_back(cYL);

			g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->circleL_centROIx[i].push_back(static_cast<float>(cXL));
			g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->circleL_centROIy[i].push_back(static_cast<float>(cYL));

			TMPcogx = *imgContent;
			//sumX.push_back(TMPcogx);
			//vals.push_back(*imgContent);
			imgContent++;

			//save y value
			TMPcogy = *imgContent;
			//sumY.push_back(TMPcogy);
			//vals.push_back(*imgContent);
			imgContent++;
				
			//save sum value
			TMPcog = *imgContent;
			//sumAll.push_back(TMPcog);
			//vals.push_back(*imgContent);
			imgContent++;

			//calculate cog right:
			cXR = static_cast<double>(TMPcogx) / static_cast<double>(TMPcog);
			cYR = static_cast<double>(TMPcogy) / static_cast<double>(TMPcog);

			//cogX.push_back(cXR);
			//cogY.push_back(cYR);

			g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->circleR_centROIx[i].push_back(static_cast<float>(cXR));
			g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->circleR_centROIy[i].push_back(static_cast<float>(cYR));

			//Distance calculation only if valid ROI
			if (g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getROI(i).twoCircles)
			{
				GlobLeft  = g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getROIPosLeft(i);
				GlobRight = g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getROIPosRight(i);

				Dist.x	= (GlobRight.x+cXR) - (GlobLeft.x+cXL);
				Dist.y	= (GlobRight.y+cYR) - (GlobLeft.y+cYL);

				dist = sqrt(Dist.x*Dist.x + Dist.y*Dist.y);
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distance[i].push_back(dist);

				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distancePlot[i].push_back(dist);//Plot data
			}
			else
			{
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distance[i].push_back(0.0);
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distancePlot[i].push_back(0.0);//Plot data
			}
			//Plot data
			if (g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distancePlot[i].size() > pCLApplet->GetNSamples())
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distancePlot[i].pop_front();
		}
		g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->measTstamp.push_back(this->m_timestamp);
		g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->nSamples++;
	}
#endif
}
