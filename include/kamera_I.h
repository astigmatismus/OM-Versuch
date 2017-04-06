/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef KAMERA_I_H
#define KAMERA_I_H

#pragma once

#include "CL.h"
#include "CoaXPress.h"
#include "Ringbuffer.h"
#include <qobject>
#include <qstring>
#include <qtimer>
#include <qmessagebox>
#include <qfile>
#include <Point.h>	
#include <defines.h>		
#include "inifile.h" 

namespace FPGA_IF
{
	enum camera
	{ noCam, jaiPu, Mikrotron};

	enum sensor
	{ NK = -1, CCD, CMOS };

	enum board
	{ NB = -1, board0, board1, board2 };

	enum port
	{ NP = -1, portA, portB };

	enum tap
	{ tapA, tapB };

	enum kind
	{ min, val, max };

static QString	Sensortype[2]	= {"CCD", "CMOS"};
}

//"Template" Camera Class - lots of variables and functions not being used within the scope of this programm
class CKamera_I : public QObject
{
	Q_OBJECT

public:	
						CKamera_I				(Fg_Struct*& fg);
	virtual				~CKamera_I				(void);
	virtual bool		Init					()=0;
	virtual bool		DeInit					()=0;
	bool				IsInit					(){return this->m_active;}
	bool				IsActivalable			(){return this->m_activeallowed;}
	virtual bool		ReadIni					(MIniFile& ini) = 0;
	virtual bool		WriteIni				(MIniFile& ini) = 0;
	bool				ReadAllParameters		(){return true;}
	QString				GetName					(){return this->m_Name;}
	LPoint				GetSensorSize_px		(){return this->m_Sensor_Size_Pixel;}
	dPoint				GetSensorSize_um		(){return (dPoint)this->m_Sensor_Size_Pixel * this->m_Sensor_PixelPitch_um;}
	LPoint				GetImageSize_px			(){return this->m_Image_Size_Pixel;}
	dPoint				GetImageSize_um			(){return (dPoint)this->m_Image_Size_Pixel * this->m_Sensor_PixelPitch_um;}
	LPoint				GetImageOffset_px		(){return this->m_Image_Offset_Pixel;}
	dPoint				GetImageOffset_um		(){return (dPoint)this->m_Image_Offset_Pixel * this->m_Sensor_PixelPitch_um;}
	virtual bool		SetSensorPixelPitch		(dPoint pitch){return false;}
	virtual bool		SetImageSize			(LPoint size){this->m_Image_Size_Pixel = size; return false;}
	virtual bool		SetImageOffset			(LPoint offset){this->m_Image_Offset_Pixel = offset; return false;}

	TrgPortArea::TriggerModeN GetTriggerMode	(){return this->m_TriggerMode;}
	virtual void		SetTriggerMode			(TrgPortArea::TriggerModeN triggermode)	{}
	TrgPortArea::PolarityN	GetExsyncPolarity	(){return this->m_ExsyncPolarity;}

	virtual long	GetShutter_us				(FPGA_IF::kind kind){return this->m_DirectShutter[kind];}
	virtual long	GetShutterStep_us			(){return 1;}
	FPGA_IF::board	GetBoard					(){return (FPGA_IF::board)((int)this->m_Board/2);}
	FPGA_IF::port	GetPort						(){return this->m_Port;}
	FPGA_IF::sensor	GetSensorType				(){return this->m_Sensortype;}
	long			GetNumTaps					(){return this->m_Tapcount;}
	dPoint			GetPixelPitch				(){return this->m_Sensor_PixelPitch_um;}
	float			GetFramerate				(FPGA_IF::kind kind){return this->m_framerate[kind];};
	virtual void	SetFramerate				(int freq , FPGA_IF::kind kind){ this->m_framerate[kind] = freq;};

	long			GetTapVOffset				(FPGA_IF::tap tap, FPGA_IF::kind kind = FPGA_IF::val){return this->m_TapVoffset[tap][kind];}
	long			GetTapVGain					(FPGA_IF::tap tap, FPGA_IF::kind kind = FPGA_IF::val){return this->m_TapVGain[tap][kind];}

	long			GetGlobGain					(FPGA_IF::kind kind = FPGA_IF::val){return this->m_GlobGain[kind];}
	virtual void	SetGlobGain					(FPGA_IF::kind kind, int val ){this->m_GlobGain[kind] = val; return;};

	virtual bool	FPN							(){QMessageBox::information(NULL, "FPN - Fix Pattern Noise", "Feature not available!"); return false;}
	virtual bool	PRNU						(){QMessageBox::information(NULL, "PRNU - Photo Response Non Uniformity", "Feature not available!"); return false;}


	virtual bool	SetTapOffset				(FPGA_IF::tap tap, long offset){return false;}
	virtual bool	SetTapGain					(FPGA_IF::tap tap, long gain){return false;}
	virtual bool	SetShutter_us				(long shutter)		{return false;}
	bool			SetBoard					(FPGA_IF::board board)	{return this->m_Board = (FPGA_IF::board)(board*2); /*emit updateBoard(board);*/}
	bool			SetPort						(FPGA_IF::port port)	{return this->m_Port = port;			/*emit updatePort(port);*/}
	
	virtual bool	SetTestImage				(int num){return false;}
	int				GetActualTestImage			(){return this->m_actTestImage;}
	bool			HasTestImages				(){return this->m_hasTestImages;}
	bool			IsTestImageActive			(){return this->m_testImageActive;}
	int				NumOfTestImages				(){return this->m_numOfTestImages;}

	void			SetOverlay					(bool value){this->m_overlay = value;}
	bool			IsOverlay					(){return this->m_overlay;}

	virtual bool	DoStartAcquisition			(){return false;};
	virtual bool	DoStopAcquisition			(){return false;};

	int				m_gain;
protected:
	// status
	bool			m_active;
	bool			m_activeallowed;

	// init
	QString			m_Name;
	FPGA_IF::board	m_Board;
	FPGA_IF::port	m_Port;

	TrgPortArea::TriggerModeN	m_TriggerMode;
	TrgPortArea::PolarityN	    m_ExsyncPolarity;


	// info
	FPGA_IF::sensor	m_Sensortype;
	long			m_Tapcount;
	dPoint			m_Sensor_PixelPitch_um;
	float			m_framerate		[3];		//[0] = min, [1] = val , [2] = max 
	// settings
	long			m_TapVoffset	[2][3];		//[0][x] = A, [1][x] = B, [x][0] = min, [x][1] = value, [x][2] = max 
	long			m_TapVGain		[2][3];		//[0][x] = A, [1][x] = B, [x][0] = min, [x][1] = value, [x][2] = max 
	long			m_GlobGain		[3];		//[0] = min, [1] = val , [2] = max 
	
	LPoint			m_Sensor_Size_Pixel;
	LPoint			m_Image_Offset_Pixel;
	LPoint			m_Image_Size_Pixel;

	long			m_DirectShutter	[3];		//[0] = min,  [1] = value, [2] = max 

	//comunication
	CL_Serial		m_serial;
	COAX_Interface	m_Coax;

	Fg_Struct*&		m_fg;

	int				m_numOfTestImages;			// number of available test images
	int				m_actTestImage;				// current selected/active image number (0...m_testimages-1)
	bool			m_hasTestImages;			// testimages available for the camera
	bool			m_testImageActive;			// indicates if testimage feature is activated

	bool			m_overlay;

public:

signals:
	void			updateActive		(bool active);
	void			updateBoard			(FPGA_IF::board board);
	void			updatePort			(FPGA_IF::port port);
	void			updateShutter		(long min, long val, long max);
	void			updateBrightness	(long min, long val, long max);
	void			updateOffset		(FPGA_IF::tap tap, long min, long val, long max);
	void			updateGain			(FPGA_IF::tap tap, long min, long val, long max);
	void			updateSensorSize	(LPoint size_px,	dPoint dsize_um);
	void			updateImageOffset	(LPoint offset_px,	dPoint doffset_um);
	void			updateImageSize		(LPoint size_px,	dPoint dsize_um);
};
//----------------------------------------------------------------

#endif //KAMERA_I_H
