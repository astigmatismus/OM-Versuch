/*
	Milan Mult i-Platform Imaging Language, an open source image processing library

	Copyright (C) 2008  	Harald Kloess

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

	This program is free software; you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software Foundation version 2 of the License

	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
	even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
	Public License for more details.

	You should have received a copy of the GNU General Public License along with this program; if not, write
	to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA

	Dieses Programm ist freie Software. Sie koennen es unter den Bedingungen der GNU General Public License, wie
	von der Free Software Foundation veroeffentlicht, weitergeben und/oder modifizieren, gemaess Version 2 der Lizenz.

	Die Veroeffentlichung dieses Programms erfolgt in der Hoffnung, dass es Ihnen von Nutzen sein wird, aber OHNE
	IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FUER EINEN BESTIMMTEN
	ZWECK. Details finden Sie in der GNU General Public License.

	Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht,
	schreiben Sie an die Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA.
*/

#include "Kamera_JAI_Pulnix_AccuPixel.h"
//----------------------------------------------------------------

CKamera_JAI_Pulnix_AccuPixel::CKamera_JAI_Pulnix_AccuPixel(Fg_Struct*& fg):CKamera_I(fg)
{
	this->m_fg				= fg;
	// status
	this->m_activeallowed			= true;
	this->m_active				= false;

	this->m_serial.SetLastChar		('\r');

	// init
	this->m_Name				= "JAI Pulnix AccuPixel TM-6740 CL";
	this->m_Board				= FPGA_IF::board0;
	this->m_Port				= FPGA_IF::portA;

	this->m_ExsyncPolarity			= TrgPortArea::LowActive;

	// info
	this->m_Sensortype			= FPGA_IF::CCD;
	this->m_Tapcount			= 2;
	this->m_Sensor_PixelPitch_um		= dPoint(7.4,7.4);
	this->m_framerate	[0]		=	1;
	this->m_framerate	[1]		= 200.0;
	this->m_framerate	[2]		= 200.0;
	this->m_horizontalclock			= 100000;	//Hz

	// settings
	this->m_TapVoffset	[0][0]		= 
	this->m_TapVoffset	[1][0]		= 0x000;	// min

	this->m_TapVoffset	[0][1]		= 
	this->m_TapVoffset	[1][1]		= 0x000;	// value

	this->m_TapVoffset	[0][2]		= 
	this->m_TapVoffset	[1][2]		= 0x1FF;	// max

	this->m_TapVGain	[0][0]		= 
	this->m_TapVGain	[1][0]		= 0x042;	// min
								
	this->m_TapVGain	[0][1]		= 
	this->m_TapVGain	[1][1]		= 0x042;	// value
								
	this->m_TapVGain	[0][2]		=		
	this->m_TapVGain	[1][2]		= 0x1E8;	// max

	this->m_Sensor_Size_Pixel		= LPoint(640,480);
	this->m_Image_Size_Pixel		= this->m_Sensor_Size_Pixel;
	this->m_Image_Offset_Pixel		= (this->m_Sensor_Size_Pixel - this->m_Image_Size_Pixel)/2;

	this->m_DirectShutter	[0]		= 0;
	this->m_DirectShutter	[1]		= 480;
	this->m_DirectShutter	[2]		= this->m_Image_Size_Pixel.y;

	this->m_hasTestImages			= true;
	this->m_numOfTestImages			= 1;
}
//----------------------------------------------------------------


CKamera_JAI_Pulnix_AccuPixel::~CKamera_JAI_Pulnix_AccuPixel(void)
{
	this->DeInit();
}
//----------------------------------------------------------------

bool	CKamera_JAI_Pulnix_AccuPixel::Init()
{
	if (!this->m_activeallowed)
		return false;

	if (this->m_active)
		return true;

	if (!CKamera_I::Init())
	{
		this->m_active;
		return false;
	}

	this->m_active = true;

	MESSAGE("CKamera_JAI_Pulnix_AccuPixel::Init()");

	if (!this->m_serial.Open(this->m_fg, this->m_Board, this->m_Port))
	{
		this->m_active = false;
		emit updateActive(this->m_active);
		return this->m_active;
	}

	this->ReadAllParameters();

	if (!this->m_serial.Write	(this->m_fg, QString(":VDOC\r")))	// video data output order A <--- <---, B <--- --->, C <<------
	{
		return false;
	}
	if (this->m_serial.GetBufferSimple()[0] != ':')
	{
		QMessageBox::information(0
			, QString("%1 ::Init()").arg(this->GetName())
			, QString("The camera answers in a wrong format.\n"
			"So maybe the camera connected to\n"
			"this port is not the one expected!")
			);
		this->m_active = false;
		emit updateActive(this->m_active);
		return this->m_active;
	}
	this->m_serial.Write	(this->m_fg, QString(":DDP=0\r"));	// 0=8bit, 1=10bit
	this->SetTestImage	(this->m_actTestImage);			// kein Testbild = 0
	this->m_serial.Write	(this->m_fg, QString(":SMDA\r"));	// scan mode A, B, C, D (partielles auslesen)
	this->m_serial.Write	(this->m_fg, QString(":SMB=0\r"));	// binning (0..8)=(1x1..2x2..4x4)

	QChar	chr('0');
	this->SetTriggerMode	(this->m_TriggerMode);

	this->m_serial.Write	(this->m_fg, QString(":VRA=%1\r").arg(this->m_TapVoffset[0][1], 3, 16, chr).toUpper());	// off Volt A 000-1FF
	this->m_serial.Write	(this->m_fg, QString(":VRB=%1\r").arg(this->m_TapVoffset[1][1], 3, 16, chr).toUpper());	// off Volt B 000-1FF

	this->m_serial.Write	(this->m_fg, QString(":MGA=%1\r").arg(this->m_TapVGain[0][1], 3, 16, chr).toUpper());	// CDS Gain A 042-1E8
	this->m_serial.Write	(this->m_fg, QString(":MGB=%1\r").arg(this->m_TapVGain[1][1], 3, 16, chr).toUpper());	// CDS Gain B 042-1E8


	//this->m_serial.Write	(":EABL\r");	//Sleep(10000);		// enable auto gain chan bal
	this->m_serial.Write	(this->m_fg, ":DABL\r");	Sleep(1000);		// disable auto gain chan bal

	//this->m_serial.Write	(":EACL\r");	Sleep(10000);		// enable auto calibration
	//this->m_serial.Write	(":DACL\r");	//Sleep(1000);		// disable auto calibration


	emit updateActive(true);

	return true;
}
//----------------------------------------------------------------

bool	CKamera_JAI_Pulnix_AccuPixel::SetTestImage			(int num)
{
	if (!this->m_active)
		return false;

	this->m_actTestImage = num;
	if (num == 0)
		this->m_serial.Write(this->m_fg, QString(":TPTN0\r"));	// Testbild 0=aus, 1=an
	else
		this->m_serial.Write(this->m_fg, QString(":TPTN1\r"));	// Testbild 0=aus, 1=an
	
	return true;
}
//----------------------------------------------------------------

bool	CKamera_JAI_Pulnix_AccuPixel::DeInit()
{
	if (!this->m_active)
		return true;

	MESSAGE("CKamera_JAI_Pulnix_AccuPixel::DeInit()");

	this->m_active = false;

	emit updateActive(false);

	return CKamera_I::DeInit();
}
//----------------------------------------------------------------


bool	CKamera_JAI_Pulnix_AccuPixel::ReadIni(MIniFile& ini)
{
	bool	bvalue;
	int	ivalue;
	QString qstr;
	std::string sstr;
	QString key(INI_CAM_KEY + this->m_Name + "/");

	ini.getItem((key+INI_CAM_BOARD)	.toStdString(), ivalue, (int)this->m_Board);
		this->m_Board = (FPGA_IF::board)ivalue;
	ini.getItem((key+INI_CAM_PORT)	.toStdString(), ivalue, (int)this->m_Port);
		this->m_Port = (FPGA_IF::port)ivalue;
	ini.getItem((key+INI_CAM_TAPOFFSET_A)	.toStdString(), ivalue, (int)this->m_TapVoffset	[0][1]);
	if (ivalue >= this->m_TapVoffset	[0][0] && ivalue <= this->m_TapVoffset	[0][2])
		this->m_TapVoffset	[0][1] = ivalue;
	ini.getItem((key+INI_CAM_TAPOFFSET_B)	.toStdString(), ivalue, (int)this->m_TapVoffset	[1][1]);
	if (ivalue >= this->m_TapVoffset	[1][0] && ivalue <= this->m_TapVoffset	[1][2])
		this->m_TapVoffset	[1][1] = ivalue;
	ini.getItem((key+INI_CAM_TAPGAIN_A)	.toStdString(), ivalue, (int)this->m_TapVGain	[0][1]);
	if (ivalue >= this->m_TapVGain	[0][0] && ivalue <= this->m_TapVGain	[0][2])
		this->m_TapVGain	[0][1] = ivalue;
	ini.getItem((key+INI_CAM_TAPGAIN_B)	.toStdString(), ivalue, (int)this->m_TapVGain	[1][1]);
	if (ivalue >= this->m_TapVGain	[1][0] && ivalue <= this->m_TapVGain	[1][2])
		this->m_TapVGain	[1][1] = ivalue;

	ini.getItem((key+INI_CAM_GAIN_AB)	.toStdString(), ivalue, (int)this->m_gain);
	this->m_gain = ivalue;

	ini.getItem((key+INI_CAM_IMAGE_BRIGHTNESS)	.toStdString(), ivalue, (int)this->m_gain);
	this->m_gain = ivalue;

	ini.getItem((key+INI_CAM_IMAGE_SIZE)	.toStdString(), qstr, (QString)this->m_Image_Size_Pixel);
	this->m_Image_Size_Pixel = qstr;

	ini.getItem((key+INI_CAM_IMAGE_OFFSET)	.toStdString(), qstr, (QString)this->m_Image_Offset_Pixel);
	this->m_Image_Offset_Pixel = qstr;

	

	ini.getItem((key+INI_CAM_SHUTTER)	.toStdString(), ivalue, (int)this->m_DirectShutter	[1]);
	if (ivalue >= this->m_DirectShutter	[0] && ivalue <= this->m_DirectShutter	[2])
		this->m_DirectShutter	[1] = ivalue;

	ini.getItem((key+INI_CAM_ACTIVE)	.toStdString(), bvalue, this->m_active);
		if (bvalue)
			this->Init();

	emit updateActive(this->m_active);

	return true;
}
//----------------------------------------------------------------

bool	CKamera_JAI_Pulnix_AccuPixel::WriteIni(MIniFile& ini)
{
	QString key(INI_CAM_KEY + this->m_Name + "/");

	ini.setItem((key+INI_CAM_NAME)		.toStdString(), this->m_Name);
	ini.setItem((key+INI_CAM_ACTIVE)	.toStdString(), this->m_active);
	ini.setItem((key+INI_CAM_BOARD)		.toStdString(), (long)this->m_Board);
	ini.setItem((key+INI_CAM_PORT)		.toStdString(), (long)this->m_Port);
	ini.setItem((key+INI_CAM_TAPOFFSET_A)	.toStdString(), this->m_TapVoffset	[0][1]);
	ini.setItem((key+INI_CAM_TAPOFFSET_B)	.toStdString(), this->m_TapVoffset	[1][1]);
	ini.setItem((key+INI_CAM_TAPGAIN_A)	.toStdString(), this->m_TapVGain	[0][1]);
	ini.setItem((key+INI_CAM_TAPGAIN_B)	.toStdString(), this->m_TapVGain	[1][1]);
	ini.setItem((key+INI_CAM_GAIN_AB)	.toStdString(), this->m_gain);
	ini.setItem((key+INI_CAM_IMAGE_SIZE)	.toStdString(), (QString)this->m_Image_Size_Pixel);
	ini.setItem((key+INI_CAM_IMAGE_OFFSET)	.toStdString(), (QString)this->m_Image_Offset_Pixel);
	ini.setItem((key+INI_CAM_SHUTTER)	.toStdString(), this->m_DirectShutter	[1]);
	ini.setItem((key+INI_CAM_IMAGE_BRIGHTNESS)	.toStdString(), this->m_gain);
	return true;
}

bool	CKamera_JAI_Pulnix_AccuPixel::ReadAllParameters	()
{
	if (!this->m_active)
		return false;

	if (!this->m_serial.Write(this->m_fg, QString(":RPST\r")))	// read all parameters
	{
		return false;
	}
	if (!this->m_serial.Write	(this->m_fg, QString(":VDOC\r")))	// video data output order A <--- <---, B <--- --->, C <<------
	{
		return false;
	}

	char	buf[60]={0};

	_snprintf_s(buf, 60, this->m_serial.GetBuffer().length(), "%s", this->m_serial.GetBuffer().mid(2).toLatin1().data());

	/*
	QMessageBox::information(0
		, QString("%1 ::ReadAllParameters()").arg(this->GetName())

		, QString(	"Gain Chl A:\t0x%1\n"
				"Gain Chl B:\t0x%1\n")
				.arg((unsigned short)&buf[0],0, 16)
				.arg((unsigned short)&buf[4],0, 16).toUpper()
		, this->m_serial.GetBuffer());
		*/


	return true;
}
//----------------------------------------------------------------

long	CKamera_JAI_Pulnix_AccuPixel::GetShutter_us(FPGA_IF::kind kind)
{
	return (long)(this->m_DirectShutter[kind] * 1.E6 / this->m_horizontalclock);
}
//----------------------------------------------------------------

long	CKamera_JAI_Pulnix_AccuPixel::GetShutterStep_us()
{
	return (long)(1.E6 / this->m_horizontalclock);
}
//----------------------------------------------------------------

void	CKamera_JAI_Pulnix_AccuPixel::SetTriggerMode(TrgPortArea::TriggerModeN triggermode)
{
	this->m_TriggerMode = triggermode;		
	if (!this->m_active)
		return ;

	QChar	chr('0');

	if (this->m_TriggerMode == TrgPortArea::GrabberControlled)
	{
		this->m_serial.Write(this->m_fg, QString(":DSH=%1\r").arg(this->m_DirectShutter[1], 3, 16, chr).toUpper());	// direct shutter
	}
	else
	{
		this->m_serial.Write(this->m_fg, QString(":ASH=9\r"));
	}
}

//----------------------------------------------------------------

bool	CKamera_JAI_Pulnix_AccuPixel::SetShutter_us(long shutter)
{
	shutter = (long)(shutter * this->m_horizontalclock / 1.E6 + 0.5);
	if (	shutter < this->m_DirectShutter[0] || 
		shutter > this->m_DirectShutter[2]	)
		return false;

	this->m_DirectShutter[1] = shutter;
	
	emit updateShutter(	this->GetShutter_us(FPGA_IF::min)
			,	this->GetShutter_us(FPGA_IF::val)
			,	this->GetShutter_us(FPGA_IF::max));
			
	if (!this->m_active)
		return false;

	QChar	chr('0');
	if (this->m_TriggerMode == TrgPortArea::GrabberControlled)
		this->m_serial.Write(this->m_fg, QString(":DSH=%1\r").arg(this->m_DirectShutter[1], 3, 16, chr).toUpper());	// direct shutter

	return true;
}
//----------------------------------------------------------------


bool	CKamera_JAI_Pulnix_AccuPixel::SetTapOffset(FPGA_IF::tap tap, long offset)
{
	if (	offset < this->m_TapVoffset[tap][0] || 
		offset > this->m_TapVoffset[tap][2]	)
		return false;

	this->m_TapVoffset[tap][1] = offset;

	emit updateOffset(tap, this->m_TapVoffset[tap][0], this->m_TapVoffset[tap][1], this->m_TapVoffset[tap][2]);

	if (!this->m_active)
		return false;

	QChar	chr('0');
	if (tap == FPGA_IF::tapA)
		this->m_serial.Write(this->m_fg, QString(":VRA=%1\r").arg(this->m_TapVoffset[0][1], 3, 16, chr).toUpper());	// off Volt A 000-1FF
	if (tap == FPGA_IF::tapB)
		this->m_serial.Write(this->m_fg, QString(":VRB=%1\r").arg(this->m_TapVoffset[1][1], 3, 16, chr).toUpper());	// off Volt B 000-1FF

	return true;
}
//----------------------------------------------------------------


bool	CKamera_JAI_Pulnix_AccuPixel::SetTapGain(FPGA_IF::tap tap, long gain)
{
	if (	gain < this->m_TapVGain[tap][0] || 
		gain > this->m_TapVGain[tap][2]	)
		return false;

	this->m_TapVGain[tap][1] = gain;

	emit updateGain(tap, this->m_TapVGain[tap][0], this->m_TapVGain[tap][1], this->m_TapVGain[tap][2]);

	if (!this->m_active)
		return false;

	QChar	chr('0');
	if (tap == FPGA_IF::tapA)
		this->m_serial.Write(this->m_fg, QString(":MGA=%1\r").arg(this->m_TapVGain[0][1], 3, 16, chr).toUpper());	// off Volt A 000-1FF
	if (tap == FPGA_IF::tapB)
		this->m_serial.Write(this->m_fg, QString(":MGB=%1\r").arg(this->m_TapVGain[1][1], 3, 16, chr).toUpper());	// off Volt B 000-1FF

	return true;
}
//----------------------------------------------------------------


