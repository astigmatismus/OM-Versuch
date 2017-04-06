/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#endif
#include <string.h>
#include <stdlib.h>

#include <siso_genicam.h>
#include "CoaXPress.h"
#include <stdio.h>


#pragma warning(disable:4996)


//default Parameters for coaXpress interface
COAX_Interface::COAX_Interface	()
{
	this->m_WaitPowerOn = 10000;					// default idle time after PowerOn
	this->m_PortMask = 0x0F;						// all frame grabber ports are activated
	const char cGenicamXMLFile[]="";				//always use internal camera xml 
	strcpy(m_GenicamXMLFile,cGenicamXMLFile);
	this->m_NrOfLinks = 4;							// camera specific no. of links
	this->m_LinkSpeed = CXP_SPEED_3125;				// CXP-bitrate
	this->m_StreamPaketDataSize = 1024*4;			// CXP-Stream Packet Size
	this->m_GenicamXMLFile[512];					// Buffer for filename of camera's Genicam file
	this->m_Width = 9*256;							// Image width
	this->m_Height = 1024;							// Image Height
	this->m_PixelFormat = 0x101; // mono8			// Pixel format
	this->m_TriggerMode = 0;						// FreeRun mode as a default   
}

COAX_Interface::~COAX_Interface	()
{
}

//Set applet settings
void COAX_Interface::DoAppletSettings( Fg_Struct* FrameGrabber , uint32_t  width, uint32_t height, int triggerMode)
{
	int Timeout(10000);// 10 sec. to wait for first frame
	Fg_setParameterWithType(FrameGrabber, FG_TIMEOUT, &Timeout, 0, FG_PARAM_TYPE_UINT32_T );

	uint32_t appletWidth = width;
	Fg_setParameterWithType(FrameGrabber, FG_WIDTH, &appletWidth, 0, FG_PARAM_TYPE_UINT32_T );

	uint32_t appletHeight = height;
	Fg_setParameterWithType(FrameGrabber, FG_HEIGHT, &appletHeight, 0, FG_PARAM_TYPE_UINT32_T );

	// Select type of trigger
	if (triggerMode == 1){
		// settings for grabber controlled mode
		int TriggerState(0);// TS_ACTIVE
		Fg_setParameterWithType(FrameGrabber, FG_TRIGGERSTATE, &TriggerState, 0, FG_PARAM_TYPE_UINT32_T );
	}
	else{
		// settings for grabber free run mode
		int TriggerState(2);// TS_SYNC_STOP
		Fg_setParameterWithType(FrameGrabber, FG_TRIGGERSTATE, &TriggerState, 0, FG_PARAM_TYPE_UINT32_T );
	}
}


bool COAX_Interface::manualExit()
{
	return true;
}

unsigned int COAX_Interface::getTimeStamp()
{
	return GetTickCount();
}

//-----------------------------------------------------------------
// activates power control over CoaxPress and waits a certain
// period of time for booting up the camera
//-----------------------------------------------------------------
void COAX_Interface::DoPowerOnForVariousCams( Fg_Struct* fg, struct SgcBoardHandle* bh,  unsigned int portIndex)
{
	printf("Idle time for booting camera: %d\n", m_WaitPowerOn);
	Sgc_powerSwitch(bh, 0xff);
	Sleep(m_WaitPowerOn); // Wait for boot up of the camera
}

//----------------------------------------------------------------------
// connects to CXP cameras either by automatic discovery of
// by manual link topology setup
//----------------------------------------------------------------------
void COAX_Interface::DoConnectToCamera( struct SgcBoardHandle* bh,  struct SgcCameraHandle** chOut, unsigned int portIndex, DiscoveryStyle discoveryStyle)
{
	//----------------------------------------------
	//----------------------------------------------
	*chOut = NULL;
	SgcCameraHandle* ch = 0;
	int rc = 0;
	const unsigned int DiscoveryTimeout = 5000; // 5 sec.

	if (discoveryStyle == Automatic){
		rc = Sgc_scanPorts(bh, m_PortMask, DiscoveryTimeout, m_LinkSpeed );
		if (rc != 0){
			printf("Error during camera discovery: %s", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Error during camera discovery");
			msgBox.exec();
			return;
		}
		printf("Camera discovery done");
		rc = Sgc_getCamera(bh,portIndex,&ch);
		if (rc != 0){
			printf("Cannot get camera handle: %s\n", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Cannot get camera handle");
			msgBox.exec();
			return;
		}
		// connect by using the discovered connection parameters and topology
		rc = Sgc_CxpConnect(bh, ch);
		if (rc != 0){
			printf("unable to connect to camera: %s\n", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Unable to connect to camera");
			msgBox.exec();
			return;
		}
	} else if (discoveryStyle == ConfigFile) {
		rc = Sgc_LoadBoardConfiguration(bh, LINKCONFIGFILE);
		if (rc != 0){
			printf("Cannot load configuration file '%s': %s\n", LINKCONFIGFILE, Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Cannot load configuration file");
			msgBox.exec();
			return;
		}
		if ((rc = Sgc_SaveBoardConfiguration(bh, LINKCONFIGFILE)) == SGC_OK) {
			printf("Wrote discovery results to file '%s'\n", LINKCONFIGFILE);
		} else {
			printf("Error writing scan results to file '%s': %s\n", LINKCONFIGFILE, Sgc_getErrorDescription(rc));
		}
		int linkGroupCount = Sgc_getCameraCount(bh);
		bool found = false;
		for (unsigned int linkGroup = 0; linkGroup < static_cast<unsigned int>(linkGroupCount); ++linkGroup)
		{
			Sgc_getCameraByIndex(bh, linkGroup, &ch);
			if ((rc = Sgc_CxpConnect(bh, ch)) == SGC_OK){
				found = true;
				break;
			}
		}
		if (!found) {
			printf("unable to connect to camera: %s\n", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Unable to connect to camera");
			msgBox.exec();
			return;
		}
	}
	else{
		//--------------------------------------------------------
		// manual configuration
		//--------------------------------------------------------
		rc = Sgc_getCamera(bh,portIndex,&ch);
		if (rc != 0){
			printf("Cannot get camera handle: %s\n", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Cannot get camera handle");
			msgBox.exec();
			return;
		}

		//--------------------------------------------------------
		// configure the link - topology
		//--------------------------------------------------------
		rc = Sgc_setCameraPropertyWithType(ch, CAM_PROP_NROFLINKS_S, &m_NrOfLinks, SGC_PROPERTY_TYPE_UINT, NULL);
		if (rc == 0){
			// configure ports


			// set 1. link as Master
			unsigned int link2Set = 0;
			Sgc_setCameraPropertyWithType(ch, CAM_PROP_MASTERLINK_S, &link2Set, SGC_PROPERTY_TYPE_UINT, NULL);

			// set 1. Link connected to frame grabber port A
			int fgPort = FG_PORT_A; // FG-Port A
			Sgc_setCameraPropertyWithType(ch, CAM_PROP_FGPORT_S, &fgPort, SGC_PROPERTY_TYPE_UINT, &link2Set);

			// assign this link to 1st applet applet port(= 0)
			int appletPort = FG_APPLETPORT_A; // applet port A
			Sgc_setCameraPropertyWithType(ch, CAM_PROP_APPLETPORT_S, &appletPort, SGC_PROPERTY_TYPE_UINT, &link2Set);


			if (m_NrOfLinks > 1){
				// set 2. link as Extension Link
				link2Set = 1;
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_EXTENSIONLINK_S, &link2Set, SGC_PROPERTY_TYPE_UINT, NULL);

				// set 2. Link connected to frame grabber port D
				fgPort = FG_PORT_B; // FG-Port B
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_FGPORT_S, &fgPort, SGC_PROPERTY_TYPE_UINT, &link2Set);

				// set 2. Link connected to 2nd applet port (=1)
				appletPort = FG_APPLETPORT_B; // Applet port B
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_APPLETPORT_S, &appletPort, SGC_PROPERTY_TYPE_UINT, &link2Set);
			}

			if (m_NrOfLinks > 2){
				// set 3. link as Extension Link
				link2Set = 2;
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_EXTENSIONLINK_S, &link2Set, SGC_PROPERTY_TYPE_UINT, NULL);

				// set 3. Link connected to frame grabber port C
				fgPort = FG_PORT_C; // FG-Port C
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_FGPORT_S, &fgPort, SGC_PROPERTY_TYPE_UINT, &link2Set);

				// set 3. Link connected to 2nd applet port (=1)
				appletPort = FG_APPLETPORT_C; // Applet port C
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_APPLETPORT_S, &appletPort, SGC_PROPERTY_TYPE_UINT, &link2Set);
			}

			if (m_NrOfLinks > 3){
				// set 3. link as Extension Link
				link2Set = 3;
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_EXTENSIONLINK_S, &link2Set, SGC_PROPERTY_TYPE_UINT, NULL);

				// set 3. Link connected to frame grabber port D
				fgPort = FG_PORT_D; // FG-Port D
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_FGPORT_S, &fgPort, SGC_PROPERTY_TYPE_UINT, &link2Set);

				// set 3. Link connected to 2nd applet port (=1)
				appletPort = FG_APPLETPORT_D; // Applet port D
				Sgc_setCameraPropertyWithType(ch, CAM_PROP_APPLETPORT_S, &appletPort, SGC_PROPERTY_TYPE_UINT, &link2Set);
			}

		}
		//---------------------------------------------------------------------------
		// set Link - speed
		rc = Sgc_setCameraPropertyWithType(ch, CAM_PROP_LINKSPEED_S, &m_LinkSpeed, SGC_PROPERTY_TYPE_UINT, NULL);
		if (rc != 0){
			printf("Cannot Set CAM_PROP_LINKSPEED_S: %s", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Cannot Set CAM_PROP_LINKSPEED_S");
			msgBox.exec();
		}
		// StreamPacketSize
		rc = Sgc_setCameraPropertyWithType(ch, CAM_PROP_STREAMPACKET_SIZE_S, &m_StreamPaketDataSize, SGC_PROPERTY_TYPE_UINT, NULL);
		if (rc != 0){
			printf("Cannot Set CAM_PROP_STREAMPACKET_SIZE_S: %s", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Cannot Set CAM_PROP_STREAMPACKET_SIZE_S");
			msgBox.exec();
		}

		// connect by using the predefined connection parameters and topology
		rc = Sgc_CxpConnect(bh, ch);
		if (rc != 0){
			printf("unable to connect to camera: %s\n", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Unable to connect to camera");
			msgBox.exec();
			return;
		}

		//---------------------------------------------------------------------------
		// read LinkConfig register for testing of connection
		uint32_t linkConfig = 0;
		rc = Sgc_registerReadFromCamera(ch, &linkConfig, 0x00004014);
		if (rc != 0){
			printf("Reading LinkConfig failed: %s\n", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Reading LinkConfig failed");
			msgBox.exec();
		}
		else{
			printf("LinkConfig at port x is: %x\n", linkConfig);
		}

		uint32_t StreamPacketSize = 0;
		rc = Sgc_registerReadFromCamera(ch, &StreamPacketSize, 0x00004010);
		if (rc != 0){
			printf("Reading StreamPacketSize failed: %s\n", Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Reading StreamPacketSize failed");
			msgBox.exec();
		}
		else{
			printf("StreamPacketSize at port x is: %x\n", StreamPacketSize);
		}
	}

	/*
	if ((rc = Sgc_SaveBoardConfiguration(bh, LINKCONFIGFILE)) == SGC_OK) {
		printf("Wrote discovery results to file '%s'\n", LINKCONFIGFILE);
	} else {
		printf("Error writing scan results to file '%s': %s\n", LINKCONFIGFILE, Sgc_getErrorDescription(rc));
	}
	*/
	*chOut = ch;
}

//----------------------------------------------------------------------
// displays some camera properties
//----------------------------------------------------------------------
void COAX_Interface::getAndShowCameraProperty( SgcCameraHandle* ch, char* propertyStringIn, unsigned int& value, unsigned int addValue, const int linkIndex)
{
	int rc = 0;
	char propertyString[255];
	strcpy(propertyString, propertyStringIn);
	unsigned int propertyType = SGC_PROPERTY_TYPE_UINT;
	rc = Sgc_getCameraPropertyWithType(ch,propertyString, &value, &propertyType, &addValue);
	if (rc != 0){
		printf("Error reading: %s : %s \n", propertyString, Sgc_getErrorDescription(rc));
	}
	else{
		if (linkIndex >= 0){
			printf("%s[%d]: %d\n", propertyString, linkIndex, value);
		}
		else{
			printf("%s: %d\n", propertyString, value);
		}
	}
}

//----------------------------------------------------------------------
// queries the available cameras and displays some camera properties
//----------------------------------------------------------------------
void COAX_Interface::DoLookForCameras(struct SgcBoardHandle* bh)
{
	int rc = 0;
	const unsigned int nrOfCams = Sgc_getCameraCount(bh);
	printf("No. of Cameras : %d\n", nrOfCams);

	for (unsigned int cameraIndex = 0; cameraIndex < nrOfCams; cameraIndex++){
		SgcCameraHandle* ch = NULL;
		rc = Sgc_getCameraByIndex(bh,cameraIndex, &ch);
		if (rc == 0 ){
			//---------------------------------------------------------------
			// Show Camera Connection Properties
			//---------------------------------------------------------------
			unsigned int value;
			unsigned int addValue;
			unsigned int nrOfLinks = 0;

			addValue = 0;
			value = 0;
			getAndShowCameraProperty(ch, CAM_PROP_LINKSPEED_S, value, addValue);

			value = 0;
			getAndShowCameraProperty(ch, CAM_PROP_DISCOVERYSPEED_S, value, addValue);

			value = 0;
			getAndShowCameraProperty(ch, CAM_PROP_CONTROLPACKETSIZE_S, value, addValue);

			value = 0;
			getAndShowCameraProperty(ch, CAM_PROP_STREAMPACKET_SIZE_S, value, addValue);

			value = 0;
			getAndShowCameraProperty(ch, CAM_PROP_MASTERID_S, value, addValue);

			nrOfLinks = 0;
			getAndShowCameraProperty(ch, CAM_PROP_NROFLINKS_S, nrOfLinks, addValue);

			// Iteration over all links
			for (unsigned int linkIndex = 0; linkIndex < nrOfLinks; linkIndex++){
				addValue = linkIndex;
				value = 0;
				getAndShowCameraProperty(ch, CAM_PROP_MASTERLINK_S, value, addValue, linkIndex);

				value = 0;
				getAndShowCameraProperty(ch, CAM_PROP_EXTENSIONLINK_S, value, addValue, linkIndex);

				value = 0;
				getAndShowCameraProperty(ch, CAM_PROP_FGPORT_S, value, addValue, linkIndex);

				value = 0;
				getAndShowCameraProperty(ch, CAM_PROP_APPLETPORT_S, value, addValue, linkIndex);

				value = 0;
				getAndShowCameraProperty(ch, CAM_PROP_LINKORDER_INDEX_S, value, addValue, linkIndex);
			}
		}
		else{
			const char* errorMsg = Sgc_getErrorDescription(rc);
			printf("Error while looking for camera %i : Error : %s\n", cameraIndex, errorMsg);
		}
	}
}

//----------------------------------------------------------------------
// Create a GenICam handling
//----------------------------------------------------------------------
void COAX_Interface::DoGenicamConnection( struct SgcCameraHandle* ch, const char* GenicamXMLFile, bool UseCameraInternalXML)
{
	int rc = 0;

	// Add genapi to temp. to path variable in oder to load the DLLs	
	const char* sisodir = getenv("SISODIR5");
	const char* pathvar = getenv("PATH");
	char pathVarNew[2048];
	char sisoGenApiDir[512];

	strcpy(pathVarNew, "PATH=");
	strcat(pathVarNew, pathvar);
	strcat(pathVarNew, ";");

	strcpy(sisoGenApiDir, sisodir);
	// Add (SISODIR5)\genicam\bin\Win32_i86 to path
	strcat(sisoGenApiDir, "/genicam/bin/Win32_i86");
	strcat(pathVarNew, sisoGenApiDir);

	// Add (SISODIR5)\genicam\bin\Win32_i86\GenApi to path
	strcpy(sisoGenApiDir, sisodir);
	strcat(sisoGenApiDir, "/genicam/bin/Win32_i86/GenApi");
	strcat(pathVarNew, ";");
	strcat(pathVarNew, sisoGenApiDir);
	putenv(pathVarNew);

	if (UseCameraInternalXML){
		printf("Sgc_connectCamera\n");
		rc = Sgc_connectCamera(ch);
		if (rc != 0){
			printf("Sgc_connectCamera() failed\n");
			printf("Error Code: %d\n",rc);
			printf("Error: %s\n",Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Sgc_connectCamera() failed");
			msgBox.exec();
			exit(rc);
		}
	}
	else
	{
		printf("Sgc_connectCameraWithExternalXml\n");
		rc = Sgc_connectCameraWithExternalXml(ch, GenicamXMLFile);
		if (rc != 0){
			printf("Sgc_connectCameraWithExternalXml(%s) failed\n",GenicamXMLFile);
			printf("Error Code: %d\n",rc);
			printf("Error: %s\n",Sgc_getErrorDescription(rc));
			QMessageBox msgBox;
			msgBox.setText("Sgc_connectCameraWithExternalXml failed");
			msgBox.exec();
			exit(rc);
		}
	}
}

//----------------------------------------------------------------------
// sets the image dimension and pixel format at the camera by using the 
// GenICam interface
//----------------------------------------------------------------------
void COAX_Interface::DoSetImageFormat(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aWidth, int aHeight, int aPixelFormat)
{
	int rc = 0;
	int64_t width  = aWidth;
	int64_t height = aHeight;
	int64_t pixelFormat = aPixelFormat; // format 0x101 Mono8, 0x103 Mono12
	rc = Sgc_setIntegerValue(ch,"Width",width);
	if (rc != 0){
		printf("Error writing: %s: %s\n", "Width", Sgc_getErrorDescription(rc));
	}
	else{
		int64_t widthRead = 0; 
		rc = Sgc_getIntegerValue(ch,"Width",&widthRead);
		if (rc != 0){
			printf("Error reading: %s: %s\n", "Width", Sgc_getErrorDescription(rc));
		}
		else{
			if (widthRead != width){
				printf("Error Setting Width: %d\n", width);
			}
			else{
				printf("Width set to: %d\n", width);
			}
		}
	}

	rc = Sgc_setIntegerValue(ch,"Height",height);
	if (rc != 0){
		printf("Error writing: %s: %s\n", "Height", Sgc_getErrorDescription(rc));

	}
	else{
		int64_t heightRead = 0; 
		rc = Sgc_getIntegerValue(ch,"Height",&heightRead);
		if (rc != 0){
			printf("Error reading: %s: %s\n", "Height", Sgc_getErrorDescription(rc));
		}
		else{
			if (heightRead != height){
				printf("Error Setting Height: %d\n", height);
			}
			else{
				printf("Height set to: %d\n", height);
			}
		}
	};
	rc = Sgc_setEnumerationValue(ch,"PixelFormat","Mono8");
	if (rc != 0){
		printf("Error reading: %s\n", "PixelFormat");
	}
	else{
	}
}

//"Manually" adjust Imageoffset
void COAX_Interface::DoSetImageOffset(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aoffsetX, int aoffsetY)
{
	int rc = 0;
	int64_t offsetX  = aoffsetX;
	int64_t offsetY = aoffsetY;

	rc = Sgc_setIntegerValue(ch,"OffsetX",offsetX);
	if (rc != 0)
	{
		printf("Error writing: %s: %s\n", "OffsetX", Sgc_getErrorDescription(rc));
	}
	else
	{
		int64_t offsetXRead = 0; 
		rc = Sgc_getIntegerValue(ch,"OffsetX",&offsetXRead);
		if (rc != 0){
			printf("Error reading: %s: %s\n", "OffsetX", Sgc_getErrorDescription(rc));
		}
		else{
			if (offsetXRead != offsetX){
				printf("Error Setting offsetX: %d\n", offsetX);
			}
			else{
				printf("offsetX set to: %d\n", offsetX);
			}
		}
	}

	rc = Sgc_setIntegerValue(ch,"OffsetY",offsetY);
	if (rc != 0)
	{
		printf("Error writing: %s: %s\n", "OffsetY", Sgc_getErrorDescription(rc));

	}
	else
	{
		int64_t offsetYRead = 0; 
		rc = Sgc_getIntegerValue(ch,"OffsetY",&offsetYRead);
		if (rc != 0){
			printf("Error reading: %s: %s\n", "OffsetY", Sgc_getErrorDescription(rc));
		}
		else{
			if (offsetYRead != offsetY){
				printf("Error Setting OffsetY: %d\n", offsetY);
			}
			else{
				printf("OffsetY set to: %d\n", offsetY);
			}
		}
	};
}

//"Manually" adjust framerate
void COAX_Interface::DoSetImageFramerate(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aFramerate)
{
	int rc = 0;
	int64_t Framerate  = aFramerate;

	rc = Sgc_setIntegerValue(ch,"AcquisitionFrameRate",Framerate);
	if (rc != 0)
	{
		printf("Error writing: %s: %s\n", "AcquisitionFrameRate", Sgc_getErrorDescription(rc));
	}
	else
	{
		int64_t FramerateRead = 0; 
		rc = Sgc_getIntegerValue(ch,"AcquisitionFrameRate",&FramerateRead);
		if (rc != 0){
			printf("Error reading: %s: %s\n", "Framerate", Sgc_getErrorDescription(rc));
		}
		else{
			if (FramerateRead != Framerate){
				printf("Error Setting Framerate: %d\n", Framerate);
			}
			else{
				printf("Framerate set to: %d\n", Framerate);
			}
		}
	}
}

//"Manually" adjust Gain
void COAX_Interface::DoSetImageGain(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aGain)
{
	int rc = 0;
	int64_t Gain  = aGain;

	rc = Sgc_setIntegerValue(ch,"AFEGainReg",Gain);
	if (rc != 0)
	{
		printf("Error writing: %s: %s\n", "AFEGainReg", Sgc_getErrorDescription(rc));
	}
	else
	{
		int64_t GainRead = 0; 
		rc = Sgc_getIntegerValue(ch,"AFEGainReg",&GainRead);
		if (rc != 0){
			printf("Error reading: %s: %s\n", "OffsetX", Sgc_getErrorDescription(rc));
		}
		else{
			if (GainRead != Gain){
				printf("Error Setting Gain: %d\n", Gain);
			}
			else{
				printf("Gain set to: %d\n", Gain);
			}
		}
	}
}

//"Manually" adjust shutter
void COAX_Interface::DoSetImageShutter(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aShutter)
{
	int rc = 0;
	int64_t Shutter  = aShutter;

	rc = Sgc_setIntegerValue(ch,"ExposureTimeReg",Shutter);

	if (rc != 0)
	{
		printf("Error writing: %s: %s\n", "ExposureTimeReg", Sgc_getErrorDescription(rc));
	}
	else
	{
		int64_t ShutterRead = 0; 
		rc = Sgc_getIntegerValue(ch,"ExposureTimeReg",&ShutterRead);
		if (rc != 0){
			printf("Error reading: %s: %s\n", "ExposureTimeReg", Sgc_getErrorDescription(rc));
		}
		else{
			if (ShutterRead != Shutter){
				printf("Error Setting Shutter: %d\n", Shutter);
			}
			else{
				printf("Shutter set to: %d\n", Shutter);
			}
		}
	}
}

//----------------------------------------------------------------------
// enables a certain trigger mode at the camera by using the GenICam 
// interface.
// TriggerMode 0: "FreeRun" mode
// TriggerMode 1: "GrabberControlled" mode
//----------------------------------------------------------------------
void COAX_Interface::DoSetAcquisitionControl(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int TriggerMode)
{
	
}

//----------------------------------------------------------------------
// Starts the acquisition at the camera by using the GenICam interface
//----------------------------------------------------------------------
void COAX_Interface::DoStartAcquisition(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch)
{
	// use GenICam command to start acquisition
	//Sgc_startAcquisition(ch, true);

	int rc = 0;
	const char regName[] = "AcquisitionStart";
	rc = Sgc_executeCommand(ch,  regName);
	if (rc != 0){
		printf("Error stopping Acquisition\n");
	}
	else{
		printf("Acquisition stopped\n");
	}
}

//----------------------------------------------------------------------
// Stops the acquisition at the camera by using the GenICam interface
//----------------------------------------------------------------------
void COAX_Interface::DoStopAcquisition(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch)
{

	int rc = 0;
	const char regName[] = "AcquisitionStop";
	rc = Sgc_executeCommand(ch,  regName);
	if (rc != 0){
		printf("Error stopping Acquisition\n");
	}
	else{
		printf("Acquisition stopped\n");
	}
}
