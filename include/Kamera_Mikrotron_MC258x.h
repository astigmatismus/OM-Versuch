/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef KAMERA_MIKROTRON_MC258X_H
#define KAMERA_MIKROTRON_MC258X_H

#pragma once
#include "kamera_I.h"

#define		__MAX_MIKROTRON__		5120

#define		__MODULO_MIKROTRON_W_	64
#define		__MODULO_MIKROTRON_DX_	64
#define		__MODULO_MIKROTRON_Y_	2

//inherited class of kamera_I for coaXPress cam Microtron MC258x
class CKamera_Mikrotron_MC258x :
	public CKamera_I
{
public:
						CKamera_Mikrotron_MC258x	(Fg_Struct*& fg);
	virtual				~CKamera_Mikrotron_MC258x	(void);
	virtual bool		Init					();
	virtual bool		DeInit					();
	virtual bool		ReadIni					(MIniFile& ini);
	virtual bool		WriteIni				(MIniFile& ini);
	bool				ReadAllParameters		();
	long				GetShutter_us			(FPGA_IF::kind kind);
	virtual long		GetShutterStep_us		();
	virtual bool		SetShutter_us			(long shutter);
	virtual void		SetTriggerMode			(TrgPortArea::TriggerModeN triggermode);
	float				GetFramerate			(FPGA_IF::kind kind);
	virtual void		SetFramerate			(int freq , FPGA_IF::kind kind);
	LPoint				GetImageSize_px			();
	LPoint				GetImageOffset_px		();
	bool				SetImageSize			(LPoint size);
	bool				SetImageOffset			(LPoint offset);
	long				GetGlobGain				(FPGA_IF::kind kind = FPGA_IF::val);
	void				SetGlobGain				(FPGA_IF::kind kind, int val );
	bool				DoStartAcquisition();
	bool				DoStopAcquisition();

private:

	int64_t				m_shutter_max;
	int64_t				m_shutter_curr;

};

#endif  KAMERA_MIKROTRON_MC258X_H
