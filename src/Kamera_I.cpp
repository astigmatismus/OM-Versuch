/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "Kamera_I.h"

//----------------------------------------------------------------

CKamera_I::CKamera_I(Fg_Struct*& fg):m_fg(fg)
{
	this->m_activeallowed			=	false;
	this->m_active					=	false;
	this->m_Name					=	"Camera Interface (You will never see this name)";

	this->m_TriggerMode				=	TrgPortArea::GrabberControlled;
	this->m_ExsyncPolarity			=	TrgPortArea::LowActive;

	this->m_Board					=	FPGA_IF::NB;
	this->m_Port					=	FPGA_IF::NP;

	// info
	this->m_Sensortype				=	FPGA_IF::NK;
	this->m_Tapcount				=	0;
	this->m_Sensor_PixelPitch_um	= dPoint(1,1);

	// settings
	this->m_TapVoffset	[0][0]		= 
	this->m_TapVoffset	[1][0]		=	0;	// min

	this->m_TapVoffset	[0][1]		= 
	this->m_TapVoffset	[1][1]		=	0;	// value

	this->m_TapVoffset	[0][2]		= 
	this->m_TapVoffset	[1][2]		=	0;	// max

	this->m_TapVGain	[0][0]		= 
	this->m_TapVGain	[1][0]		=	0;	// min
								
	this->m_TapVGain	[0][1]		= 
	this->m_TapVGain	[1][1]		=	0;	// value
								
	this->m_TapVGain	[0][2]		=		
	this->m_TapVGain	[1][2]		=	0;	// max

	this->m_Sensor_Size_Pixel		=	LPoint(2048,2048);
	this->m_Image_Size_Pixel		=	this->m_Sensor_Size_Pixel;
	this->m_Image_Offset_Pixel		=	(this->m_Sensor_Size_Pixel - this->m_Image_Size_Pixel)/2;

	this->m_DirectShutter	[0]		=	0;
	this->m_DirectShutter	[1]		=	0;
	this->m_DirectShutter	[2]		=	0;

	this->m_framerate	[0]			=
	this->m_framerate	[1]			=	1;

	this->m_numOfTestImages			=	0;				
	this->m_actTestImage			=	0;
	this->m_hasTestImages			=	false;
	this->m_testImageActive			=	false;

	this->m_overlay					=	true;

}

CKamera_I::~CKamera_I(void)
{
	this->DeInit();
}

bool	CKamera_I::Init()
{
	if (!this->m_fg)
		return false;

	emit updateActive(true);

	return true;
}

bool	CKamera_I::DeInit()
{
	if (!this->m_serial.Close())
		return false;

	emit updateActive(false);

	return true;
}

