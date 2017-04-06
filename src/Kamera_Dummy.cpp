/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#include "Kamera_Dummy.h"
//----------------------------------------------------------------

CKamera_Dummy::CKamera_Dummy(Fg_Struct*& fg):CKamera_I(fg)
{
	this->m_fg				= fg;
	this->m_Name				= "Virtueller Dummy";
	this->m_activeallowed			= true;
	this->m_active				= false;
}
//----------------------------------------------------------------

CKamera_Dummy::~CKamera_Dummy(void)
{
	this->DeInit();
}
//----------------------------------------------------------------

bool	CKamera_Dummy::Init()
{
	if (!this->m_activeallowed)
		return false;

	if (this->m_active)
		return true;

	return true;
}
//----------------------------------------------------------------

bool	CKamera_Dummy::DeInit()
{
	if (!this->m_active)
		return true;

	this->m_active = false;

	return true;
}
//----------------------------------------------------------------

bool	CKamera_Dummy::SetImageSize(LPoint size)
{
	if (!(size > LPoint(0,0)))
	{
		emit updateImageSize	(this->GetImageSize_px(),   this->GetImageSize_um());
		return false;
	}

	if (!(size <= m_Sensor_Size_Pixel))
		size = this->m_Image_Size_Pixel;


	this->m_Image_Size_Pixel = size;

	emit updateImageSize	(this->GetImageSize_px(),   this->GetImageSize_um());

	return true;	
}
//----------------------------------------------------------------

bool	CKamera_Dummy::SetSensorPixelPitch		(dPoint pitch)
{
	if (!(pitch > dPoint(0,0)))
		return false;

	this->m_Sensor_PixelPitch_um = pitch;

	emit updateSensorSize	(this->GetSensorSize_px(), this->GetSensorSize_um());
	emit updateImageSize	(this->GetImageSize_px(), this->GetImageSize_um());
	emit updateImageOffset	(this->GetImageOffset_px(), this->GetImageOffset_um());

	return true;
}
//----------------------------------------------------------------


bool	CKamera_Dummy::ReadIni(MIniFile& ini)
{
	QString qstr;
	QString key(INI_CAM_KEY + this->m_Name + "/");

	//ini.getItem((key+INI_CAM_PIXELPITCH)	.toStdString(), qstr, (QString)this->m_Sensor_PixelPitch_um);
	//this->m_Sensor_PixelPitch_um = qstr;

	ini.getItem((key+INI_CAM_IMAGE_SIZE)	.toStdString(), qstr, (QString)this->m_Image_Size_Pixel);
	this->m_Image_Size_Pixel = qstr;

	emit updateActive(this->m_active);

	return true;
}
//----------------------------------------------------------------

bool	CKamera_Dummy::WriteIni(MIniFile& ini)
{
	QString key(INI_CAM_KEY + this->m_Name + "/");

	ini.setItem((key+INI_CAM_NAME)		.toStdString(), this->m_Name);
	ini.setItem((key+INI_CAM_IMAGE_SIZE)	.toStdString(), (QString)this->m_Image_Size_Pixel);
	return true;
}
//----------------------------------------------------------------

