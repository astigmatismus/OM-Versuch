/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "Kamera_Mikrotron_MC258x.h"
//----------------------------------------------------------------

CKamera_Mikrotron_MC258x::CKamera_Mikrotron_MC258x(Fg_Struct*& fg):CKamera_I(fg)
{
	this->m_fg				= fg;
	// status
	this->m_activeallowed	= true;
	this->m_active			= false;

	// init
	this->m_Name				= "Mikrotron MC258x";
	this->m_Board				= FPGA_IF::board0;
	this->m_Port				= FPGA_IF::portA;

	// info
	this->m_Sensortype				=	FPGA_IF::CMOS;
	this->m_Tapcount				=	1;
	this->m_Sensor_PixelPitch_um	=	dPoint(4.5,4.5);

	this->m_GlobGain[0]= 1;
	this->m_GlobGain[2]= 4;

	this->m_DirectShutter	[0]		= 1;
	this->m_framerate		[0]		= 10;

	this->m_Sensor_Size_Pixel		= LPoint(5120,5120);
	
}
//----------------------------------------------------------------

CKamera_Mikrotron_MC258x::~CKamera_Mikrotron_MC258x(void)
{
	this->DeInit();
}
//----------------------------------------------------------------

bool	CKamera_Mikrotron_MC258x::Init()
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

	MESSAGE("CKamera_Mikrotron_MC258x::Init()");
	this->m_Coax.m_WaitPowerOn = 1000;

#ifdef __QUAD_MAXSPEED__
	this->m_Coax.m_LinkSpeed = CXP_SPEED_3125;
	this->m_Coax.m_NrOfLinks = 4*1;
	this->m_Coax.m_PortMask = 0x0F;
	this->m_Coax.m_StreamPaketDataSize = 4*1024;
#else
	this->m_Coax.m_LinkSpeed = CXP_SPEED_1250;
	this->m_Coax.m_NrOfLinks = 1*1;
	this->m_Coax.m_PortMask = 0x0F;
	this->m_Coax.m_StreamPaketDataSize = 1*1024;
#endif
	this->m_Coax.m_Width  = this->GetImageSize_px().x; 
	this->m_Coax.m_Height = this->GetImageSize_px().y;
	this->m_Coax.m_TriggerMode = 0; // freeRunning mode
	this->m_Coax.m_board_handle		=	NULL;
	this->m_Coax.m_camera_handle	=	NULL;
	this->m_DirectShutter	[0]		= 1;
	this->m_DirectShutter	[1]		= this->GetShutter_us(FPGA_IF::val);
	this->m_framerate		[0]		= 10;

	int ret = Sgc_initBoard(this->m_fg,0,&this->m_Coax.m_board_handle);
	if (ret != 0){
		printf("Sgc_initBoard returned %d\n",ret);
		getchar();
		exit(-1);
	}

	//----------------------------------------------------------------------
	// power-On PowerOverCoaxPress and wait a camera specific time for boot up
	// if camera shall be resetted, otherwise skip this procedure
	//----------------------------------------------------------------------
	this->m_Coax.DoPowerOnForVariousCams(this->m_fg, this->m_Coax.m_board_handle, this->m_Port);
	
	//----------------------------------------------------------------------
	//Manually detect and configure the cameras in use
	//----------------------------------------------------------------------
	DiscoveryStyle manualDisc = Automatic; // Manual;
	this->m_Coax.DoConnectToCamera(this->m_Coax.m_board_handle,&this->m_Coax.m_camera_handle, this->m_Port, manualDisc);

	//----------------------------------------------------------------------
	// Display available / configured cameras
	//----------------------------------------------------------------------
	this->m_Coax.DoLookForCameras( this->m_Coax.m_board_handle);

	//----------------------------------------------------------------------
	// Connect to camera by using GenICam Standard by using the XML file stored at camera
	//----------------------------------------------------------------------
	ret = Sgc_connectCamera(this->m_Coax.m_camera_handle);
	if (ret != 0){
		printf("Sgc_connectCamera(%s) failed\n",this->m_Coax.m_GenicamXMLFile);
		printf("Error Code: %d\n",ret);
		printf("Error: %s\n",Sgc_getErrorDescription(ret));
		return false;
		//exit(ret);
	}

	//----------------------------------------------------------------------
	// configure image dimension and image format according to the cameras
	//----------------------------------------------------------------------
	this->m_Coax.DoAppletSettings		(this->m_fg, this->m_Coax.m_Width, this->m_Coax.m_Height,this->m_Coax.m_TriggerMode);
	this->m_Coax.DoSetImageFormat		(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle, this->m_Coax.m_Width, this->m_Coax.m_Height, this->m_Coax.m_PixelFormat);
	this->m_Coax.DoSetAcquisitionControl(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle, this->m_Coax.m_TriggerMode);
	this->m_Coax.DoSetImageGain			(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle, this->m_GlobGain[FPGA_IF::val]);
	this->m_Coax.DoSetImageFramerate	(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle, this->m_framerate[FPGA_IF::val]);
	this->m_Coax.DoSetImageShutter		(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle, this->m_DirectShutter[FPGA_IF::val]);
	

	this->ReadAllParameters();

	int64_t fr= 0;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"AcquisitionFrameRateMax",&fr);
	this->m_framerate	[2]			=	fr;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"ExposureTimeMax",&fr);
	this->m_DirectShutter	[2]			=	fr;

	emit updateActive(true);

	return true;
}
//----------------------------------------------------------------


bool	CKamera_Mikrotron_MC258x::DeInit()
{
	if (!this->m_active)
		return true;

	MESSAGE("CKamera_Mikrotron_MC258x::DeInit()");

	this->m_active = false;

	emit updateActive(false);

	// Additional CXP resources
	Sgc_freeBoard(this->m_Coax.m_board_handle);

	return CKamera_I::DeInit();
}
//----------------------------------------------------------------


bool	CKamera_Mikrotron_MC258x::ReadIni(MIniFile& ini)
{
	bool	bvalue;
	int	ivalue;
	float	fvalue;
	QString qstr;
	std::string sstr;
	QString key(INI_CAM_KEY + this->m_Name + "/");

	ini.getItem((key+INI_CAM_BOARD)	.toStdString(), ivalue, (int)this->m_Board);
		this->m_Board = (FPGA_IF::board)ivalue;
	ini.getItem((key+INI_CAM_PORT)	.toStdString(), ivalue, (int)this->m_Port);
		this->m_Port = (FPGA_IF::port)ivalue;

	ini.getItem((key+INI_CAM_IMAGE_BRIGHTNESS)	.toStdString(), ivalue, (int)1);
	this->m_GlobGain	[1] = ivalue;

	ini.getItem((key+INI_CAM_IMAGE_FRAMERATE)	.toStdString(), fvalue, (float)11);
	this->m_framerate	[1] = (int)fvalue;

	ini.getItem((key+INI_CAM_IMAGE_SIZE)	.toStdString(), qstr, (QString)this->m_Sensor_Size_Pixel);
	this->m_Image_Size_Pixel = qstr;

	ini.getItem((key+INI_CAM_IMAGE_OFFSET)	.toStdString(), qstr, (QString)LPoint(0,0));
	this->m_Image_Offset_Pixel = qstr;

	ini.getItem((key+INI_CAM_SHUTTER)	.toStdString(), ivalue, 1);
	this->m_DirectShutter	[1] = ivalue;

	ini.getItem((key+INI_CAM_ACTIVE)	.toStdString(), bvalue, this->m_active);
		if (bvalue)
			this->Init();

	emit updateActive(this->m_active);

	return true;
}
//----------------------------------------------------------------

bool	CKamera_Mikrotron_MC258x::WriteIni(MIniFile& ini)
{
	QString key(INI_CAM_KEY + this->m_Name + "/");

	ini.setItem((key+INI_CAM_NAME)		.toStdString(), this->m_Name);
	ini.setItem((key+INI_CAM_ACTIVE)	.toStdString(), this->m_active);
	ini.setItem((key+INI_CAM_BOARD)		.toStdString(), (long)this->m_Board);
	ini.setItem((key+INI_CAM_PORT)		.toStdString(), (long)this->m_Port);
	ini.setItem((key+INI_CAM_IMAGE_SIZE)	.toStdString(), (QString)this->m_Image_Size_Pixel);
	ini.setItem((key+INI_CAM_IMAGE_OFFSET)	.toStdString(), (QString)this->m_Image_Offset_Pixel);
	ini.setItem((key+INI_CAM_SHUTTER)	.toStdString(), this->m_DirectShutter	[1]);
	ini.setItem((key+INI_CAM_IMAGE_BRIGHTNESS)	.toStdString(), this->m_GlobGain[1]);
	ini.setItem((key+INI_CAM_IMAGE_FRAMERATE)	.toStdString(), this->m_framerate[1]);
	return true;
}

bool	CKamera_Mikrotron_MC258x::ReadAllParameters	()
{
	//----------------------------------------------------------------------
	// Display camera properties defined by GenICam
	//----------------------------------------------------------------------

	int64_t valueReadback = -1;

	valueReadback = -1;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"Width",&valueReadback);
	printf("Width of Camera %d\n",valueReadback);

	valueReadback = -1;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"Height",&valueReadback);
	printf("Height of Camera %d \n",valueReadback);
	
	valueReadback = -1;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"AcquisitionFrameRate",&valueReadback);
	printf("Framerate of Camera %d \n",valueReadback);
	
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"AFEGainReg",&valueReadback);
	printf("Gain of Camera %d \n",valueReadback);

	const char *DeviceVendorNameStr=NULL;
	Sgc_getStringValue(this->m_Coax.m_camera_handle,"DeviceVendorName",&DeviceVendorNameStr);
	printf("\nDeviceVendorName %s \n",DeviceVendorNameStr);

	const char *DeviceModelNameStr=NULL;
	Sgc_getStringValue(this->m_Coax.m_camera_handle,"DeviceModelName",&DeviceModelNameStr);
	printf("DeviceModelNameStr %s \n",DeviceModelNameStr);

	const char *DeviceManufacturerInfo=NULL;
	Sgc_getStringValue(this->m_Coax.m_camera_handle,"DeviceManufacturerInfo",&DeviceManufacturerInfo);
	printf("\nDeviceManufacturerInfo %s \n",DeviceManufacturerInfo);

	const char *DeviceVersion=NULL;
	Sgc_getStringValue(this->m_Coax.m_camera_handle,"DeviceVersion",&DeviceVersion);
	printf("DeviceVersion %s \n",DeviceVersion);

	const char *DeviceFirmwareVersion=NULL;
	Sgc_getStringValue(this->m_Coax.m_camera_handle,"DeviceFirmwareVersion",&DeviceFirmwareVersion);
	printf("DeviceFirmwareVersion %s \n",DeviceFirmwareVersion);

	const char *DeviceIdStr=NULL;
	Sgc_getStringValue(this->m_Coax.m_camera_handle,"DeviceID",&DeviceIdStr);
	printf("DeviceID %s \n \n",DeviceIdStr);

	/*
	int64_t DeviceLinkIDi=-1;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"DeviceLinkID",&DeviceLinkIDi);
	printf("DeviceLink ID of Camera %d\n",DeviceLinkIDi);

	int64_t ControlPacketDataSizei=-1;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"ControlPacketDataSize",&ControlPacketDataSizei);
	printf("ControlPacketDataSize of Camera %d\n",ControlPacketDataSizei);

	Sgc_getEnumerationValue(this->m_Coax.m_camera_handle,"SynchroMode",&valueReadback);
	printf("SynchroMode of Camera %d\n",valueReadback);

	valueReadback = -1;
	Sgc_getEnumerationValue(this->m_Coax.m_camera_handle,"ExposureMode",&valueReadback);
	printf("ExposureMode of Camera %d\n",valueReadback);

	valueReadback = -1;
	Sgc_getEnumerationValue(this->m_Coax.m_camera_handle,"TriggerMode",&valueReadback);
	printf("TriggerMode of Camera %d\n",valueReadback);


	valueReadback = -1;
	Sgc_getEnumerationValue(this->m_Coax.m_camera_handle,"LinkConfig",&valueReadback);
	printf("LinkConfig of Camera %d\n",valueReadback);
	
	unsigned int ret  = -1;
	Sgc_getBooleanValue(this->m_Coax.m_camera_handle,"PixelResetMode",&ret);
	printf("PixelResetMode of Camera %d\n" , ret);
	*/

	return true;
}
//----------------------------------------------------------------

void CKamera_Mikrotron_MC258x::SetFramerate(int freq , FPGA_IF::kind kind)
{
	int64_t fr= int64_t(freq);
	
	this->m_Coax.DoSetImageFramerate(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle, fr);

	//Update maximum shutter time according to framerate!
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"ExposureTimeMax",&this->m_shutter_max);
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"ExposureTimeReg",&this->m_shutter_curr);
	this->m_DirectShutter	[1]		= this->m_shutter_curr;
	this->m_DirectShutter	[2]		= this->m_shutter_max;

	this->m_framerate[kind] = freq;

	return;
}

long	CKamera_Mikrotron_MC258x::GetShutter_us(FPGA_IF::kind kind)
{
	return (long)(this->m_DirectShutter[kind]);
	printf("Exposure time of Camera kind %d\n",this->m_DirectShutter[kind]);
}
//----------------------------------------------------------------

long	CKamera_Mikrotron_MC258x::GetShutterStep_us()
{
	return (long)(2);
}
//----------------------------------------------------------------

void	CKamera_Mikrotron_MC258x::SetTriggerMode(TrgPortArea::TriggerModeN triggermode)
{
	this->m_TriggerMode = triggermode;		
	if (!this->m_active)
		return ;
}

//----------------------------------------------------------------

bool	CKamera_Mikrotron_MC258x::SetShutter_us(long shutter)
{
	shutter = (long)(shutter);
	if (	shutter < this->m_DirectShutter[0] || 
		shutter > this->m_DirectShutter[2]	)
		return false;

	int64_t exp1=static_cast<int64_t>(shutter);

	this->m_DirectShutter[1] = shutter;
	
	emit updateShutter(	this->GetShutter_us(FPGA_IF::min)
			,	this->GetShutter_us(FPGA_IF::val)
			,	this->GetShutter_us(FPGA_IF::max));
			
	if (!this->m_active)
		return false;

	if (this->m_TriggerMode == TrgPortArea::GrabberControlled)	
		this->m_Coax.DoSetImageShutter(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle, exp1);

	return true;
}
//----------------------------------------------------------------

float	CKamera_Mikrotron_MC258x::GetFramerate(FPGA_IF::kind kind)
{
	return this->m_framerate[kind];
}

LPoint	CKamera_Mikrotron_MC258x::GetImageSize_px()
{
	return this->m_Image_Size_Pixel;
}

LPoint	CKamera_Mikrotron_MC258x::GetImageOffset_px()
{
	return this->m_Image_Offset_Pixel;
}

//Set the size of the cropped image in x and y
bool	CKamera_Mikrotron_MC258x::SetImageSize(LPoint size)
{
	int64_t width	= static_cast<int64_t>(size.x) ;
	int64_t height	= static_cast<int64_t>(size.y) ;

	this->m_Coax.m_Width	= width;
	this->m_Coax.m_Height	= height;

	this->m_Coax.DoSetImageFormat(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle,width, height, this->m_Coax.m_PixelFormat);

	this->m_Coax.DoAppletSettings(this->m_fg, this->m_Coax.m_Width, this->m_Coax.m_Height,this->m_Coax.m_TriggerMode);

	this->m_Image_Size_Pixel.x = width;
	this->m_Image_Size_Pixel.y = height;

	int64_t fr= 0;
	Sgc_getIntegerValue(this->m_Coax.m_camera_handle,"AcquisitionFrameRateMax",&fr);
	this->m_framerate	[2]			=	fr;
	if(this->m_framerate	[1] > this->m_framerate	[2])
		this->m_framerate	[1] = this->m_framerate	[2];

	return false;
}

//Set the offset of the cropped image in x and y
bool	CKamera_Mikrotron_MC258x::SetImageOffset(LPoint offset)
{
	int64_t offsetX	= static_cast<int64_t>(offset.x) ;
	int64_t offsetY	= static_cast<int64_t>(offset.y) ;

	this->m_Coax.DoSetImageOffset(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle,offsetX,offsetY);

	this->m_Image_Offset_Pixel.x = offsetX;
	this->m_Image_Offset_Pixel.y = offsetY;

	return false;
}

long	CKamera_Mikrotron_MC258x::GetGlobGain			(FPGA_IF::kind kind)
{
	return this->m_GlobGain[kind];
}

void	CKamera_Mikrotron_MC258x::SetGlobGain			(FPGA_IF::kind kind, int val )
{
	int64_t tGain = static_cast<int64_t>(val);

	emit updateBrightness(	this->GetGlobGain(FPGA_IF::min)
						,	this->GetGlobGain(FPGA_IF::val)
						,	this->GetGlobGain(FPGA_IF::max));

	this->m_Coax.DoSetImageGain(this->m_Coax.m_board_handle, this->m_Coax.m_camera_handle,tGain);

	this->m_GlobGain[kind] = tGain;

	return;
};


// Starts the acquisition at the camera by using the GenICam interface
//----------------------------------------------------------------------
bool CKamera_Mikrotron_MC258x::DoStartAcquisition()
{
	// use GenICam command to start acquisition
	Sgc_startAcquisition(this->m_Coax.m_camera_handle, true);
	return true;
}

//----------------------------------------------------------------------
// Stops the acquisition at the camera by using the GenICam interface
//----------------------------------------------------------------------
bool CKamera_Mikrotron_MC258x::DoStopAcquisition()
{
	int rc = 0;
	const char regName[] = "AcquisitionStop";
	rc = Sgc_executeCommand(this->m_Coax.m_camera_handle,  regName);
	if (rc != 0){
		printf("Error stopping Acquisition\n");
	}
	else{
		printf("Acquisition stopped\n");
	}
	return true;
}
