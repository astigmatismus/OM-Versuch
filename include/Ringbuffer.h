/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef FPGA_IF_RINGBUFFER_INCLUDED
#define FPGA_IF_RINGBUFFER_INCLUDED

class FPGA_IF_Core;

#include <map>
#include <RingbufferItem.h>
#include <assert.h>
#include <Point.h>	

#include "ROIManager.h"

using namespace std;

static int		offsetx;
static int		offsety;

static int		ROIWidth;
static int		ROIHeight;
static bool		invertFlag = false;
static bool		centerFlag = true;
static bool		logFlag = true;

//_________________________________________________________

class Ringbuffer
{
public:
						Ringbuffer			(FPGA_IF_Core& core);
						~Ringbuffer			();
	FPGA_IF_Core&		m_core;

	bool				Alloc				(long count);
	bool				Free				();
	MeasurementData		getMeasData			(){return *m_myMeasure;};

	float				getDist				(int index){return m_myMeasure->distance[index].back();}
	float				getSamples			(){if(!m_myMeasure->distance.empty())return m_myMeasure->distance[0].size(); else return 0;}
	void				clearMeasData		(bool delete_all);

	MeasurementData		*m_myMeasure;

public:
	unsigned long		CalcMaxImageCount	(long bytesize);
	inline long			GetSize				(){return static_cast<long>(this->m_buffer.size());}
	FPGA_IF_Img&		GetElement			(long num);
	long				GetElementNum		(FPGA_IF_Img* imgs);
	FPGA_IF_Img&		GetLatestElement	();
	//FPGA_IF_Img&		GetActualElement	();  - now in mainwindow.h
	void				SetBufferCount2Use	(int count){this->m_buffercount2use = count;}
	inline int			GetBufferCount2Use	(){return this->m_buffercount2use;}
	void				UpdateInfoView		(cv::Mat &img);
	void				SetRefImg			(FPGA_IF_Img *img, bool write = false);
	void				SetRefImg			(cv::Mat &img);
	void				ClearRefImg			();
	inline FPGA_IF_Img&	GetRefImg			(){return this->m_refImg;}
	bool				refIsSet			(){return this->m_referenz;}

	inline void			SetActualImgNum		(int num)
						{
							this->m_actualImgNum = num; 
							//cout << "set-> " << this->m_actualImgNum << endl;
						}
	inline long			GetActualImgNum		()
						{
							//printf("get<-%05d\n", this->m_actualImgNum);
							return this->m_actualImgNum;
						}

	map<int,FPGA_IF_Img*>m_buffer;
	cRefImg				m_myRef;

protected:

	int					m_actualImgNum;
	int					m_buffercount2use;
	bool				m_referenz;
	FPGA_IF_Img			m_refImg;
};
//----------------------------------------------------------------

#endif //FPGA_IF_RINGBUFFER_INCLUDED
