/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef FPGA_IF_RINGBUFFERITEM_INCLUDED
#define FPGA_IF_RINGBUFFERITEM_INCLUDED
//----------------------------------------------------------------

class FPGA_IF_Core;
class SiSo_AppletMin;


#include "Point.h"	// Types: xPoint
#include <vector>
#include <algorithm>
#include <qdatetime>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

template <class Type>
class MultValue
{
   private:
      Type Factor;   // The value to multiply by
   public:
      // Constructor initializes the value to multiply by
      MultValue		( const Type& _Val ) : Factor ( _Val ) {
      }

      // The function call for the element to be multiplied
      Type operator () ( Type& elem ) const 
      {
         return elem * Factor;
      }
};

template <class Type>
class AddValue
{
   private:
      Type Summand;   // The value to be added
   public:
      // Constructor initializes the value to multiply by
      AddValue		( const Type& _Val ) : Summand ( _Val ) {
      }

      // The function call for the element to be multiplied
      Type operator () ( Type& elem ) const 
      {
         return elem + Summand;
      }
};


#include <string>

#define	COGsProcessed	0x00000001
#define	HistProcessed	0x00000002
#define Grabbed			0x00000040
#define	IsLiveHist		0x00000080
#define	IsLiveCOGs		0x00000100

#define	FLAG_ADD(flags, mask)	(flags |= mask)	
#define	FLAG_REM(flags, mask)	(flags &= ~mask)

class FPGA_IF_Img;

template <class T>
class cHistoram
{
public:
				cHistoram		()
				{
					m_data.resize(256);
					this->Clear();
				}

	void		Clear			()
				{
					fill(this->m_data.begin(), this->m_data.end(), 0);
					m_minGW		= 0;
					m_meanGW	= 0;
					m_stddevGW	= 0;
					m_maxGW		= 0;
					memset(m_quant, 0, 11*sizeof(T));
				}
	std::vector<T>		m_data;

	T			m_minGW;
	T			m_meanGW;
	T			m_stddevGW;
	T			m_quant[11];
	T			m_maxGW;

};

class FPGA_IF_Img
{
public:
							FPGA_IF_Img				(FPGA_IF_Core& core);			
							~FPGA_IF_Img				();
	FPGA_IF_Core&			m_core;
	void					Clear			();
	void					ClearTimestamp		();
	static long				GetTypeSize		(int DMA);
	long					GetByteSize		(int DMA = -1);
	unsigned char*			GetBuffer		(int DMA);
	LPoint					GetBufferSize		(int DMA);
	void					SetTimestamp		(int num, FILE* file = NULL);
	void					SetTimestamp		(QDateTime dt);
	QString&				GetTimestampAsString	();
	QDateTime				GetTimestampAsDateTime	();
	
	FPGA_IF_Img&			operator=		(FPGA_IF_Img &obj);

	unsigned long			m_flags;	// status flags
	long					m_frmNum;	// SiSo frame number [1..inf]

	QString					m_timestamp;
	QString					m_timestampFormat;
	unsigned __int64		m_sisotimestamp;
	static unsigned __int64	m_timestampstart;
	bool					m_timestampCorrected;
	
	cv::Mat					m_ImgDMA0;				// image from DMA0 (overview live image)
	cv::Mat					m_ImgDMA1;
	cv::Mat					m_ImgDMA2;

	UINT32 *				m_ImgDMA1Buffer;		//COG list
	UINT32 *				m_ImgDMA2Buffer;		//Histogramm

	cv::Mat					m_DMA0MatRef;			//referenceImage in capsulated cv Mat container  
	cv::Mat					m_DMAInfoMatRef;		//referenceImage in capsulated cv Mat container : overlay with Information
	cHistoram<long>			m_Hist;					// histogramm values
	fPoint					m_meandCOG;				// mean displacement of spots for each component (x and y); 
	int						m_meanspotGW;
	void					HistList		();
	void					COGList			();
};

#endif //FPGA_IF_RINGBUFFERITEM_INCLUDED