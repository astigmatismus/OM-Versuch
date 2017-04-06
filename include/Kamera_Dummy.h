/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef KAMERA_Dummy_H
#define KAMERA_Dummy_H

#pragma once
#include "Kamera_I.h"

class CKamera_Dummy :
	public CKamera_I
{
public:
						CKamera_Dummy		(Fg_Struct*& fg);
	virtual				~CKamera_Dummy		(void);
	virtual bool		Init				();
	virtual bool		DeInit				();
	virtual bool		ReadIni				(MIniFile& ini);
	virtual bool		WriteIni			(MIniFile& ini);
	bool				SetImageSize		(LPoint size);
	bool				SetSensorPixelPitch	(dPoint pitch);
};
#endif KAMERA_Dummy_H
