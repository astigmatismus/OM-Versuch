/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/
#ifndef COAXPRESS_H
#define COAXPRESS_H

#include <QString>
#include <QMessagebox>
#include "defines.h"
#include <siso_genicam.h>
#include <fgrab_prototyp.h>
#include <fgrab_struct.h>

#define FG_PORT_A 0
#define FG_PORT_B 1
#define FG_PORT_C 2
#define FG_PORT_D 3

#define FG_APPLETPORT_A 0
#define FG_APPLETPORT_B 1
#define FG_APPLETPORT_C 2
#define FG_APPLETPORT_D 3


//-----------------------------------------------------------------------------
enum DiscoveryStyle { Manual, Automatic, ConfigFile };

#define LINKCONFIGFILE "custom.cxpconfig.xml"  // name of the link configuration file

class COAX_Interface
{
public:
	COAX_Interface	();
	~COAX_Interface	();
	//----------------------------------------------------------------

	// global variables for camera specific control
	//-----------------------------------------------------------------
	unsigned int		m_WaitPowerOn;					// default idle time after PowerOn
	unsigned int		m_PortMask;						// all frame grabber ports are activated
	unsigned int		m_NrOfLinks;					// camera specific no. of links
	unsigned int		m_LinkSpeed;					// CXP-bitrate
	unsigned int		m_StreamPaketDataSize;			// CXP-Stream Packet Size
	char				m_GenicamXMLFile[512];			// Buffer for filename of camera's Genicam file
	int					m_Width;						// Image width
	int					m_Height;						// Image Height
	int					m_PixelFormat;					// mono8         // Pixel format
	int					m_TriggerMode;					// FreeRun mode as a default   
	long				m_status;

	struct SgcBoardHandle*	m_board_handle;
	SgcCameraHandle *		m_camera_handle;

public:
	//-----------------------------------------------------------------
	// activates power control over CoaxPress and waits a certain
	// period of time for booting up the camera
	//-----------------------------------------------------------------
	void DoPowerOnForVariousCams( Fg_Struct* fg, struct SgcBoardHandle* bh,  unsigned int portIndex);
	//----------------------------------------------------------------------
	// connects to CXP cameras either by automatic discovery of
	// by manual link topology setup
	//----------------------------------------------------------------------
	void DoConnectToCamera( struct SgcBoardHandle* bh,  struct SgcCameraHandle** chOut, unsigned int portIndex, DiscoveryStyle discoveryStyle);
	//----------------------------------------------------------------------
	// tries to retrieve a valid GenICam XML either from camera or
	// from a given file
	//----------------------------------------------------------------------
	void DoGenicamConnection( struct SgcCameraHandle* ch, const char* GenicamXMLFile, bool UseCameraInternalXML);
	//----------------------------------------------------------------------
	// queries the available cameras and displays some camera properties
	//----------------------------------------------------------------------
	void DoLookForCameras(struct SgcBoardHandle* bh);
	//----------------------------------------------------------------------
	// sets the image dimension and pixel format at the camera by using the 
	// GenICam interface
	//----------------------------------------------------------------------
	void DoSetImageFormat(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aWidth, int aHeight, int aPixelFormat);

	void DoSetImageOffset(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aoffsetX, int aoffsetY);

	void DoSetImageFramerate(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aFramerate);

	void DoSetImageGain(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aGain);

	void DoSetImageShutter(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int aShutter);

	//----------------------------------------------------------------------
	// enables a certain trigger mode at the camera by using the GenICam 
	// interface.
	// TriggerMode 0: "FreeRun" mode
	// TriggerMode 1: "GrabberControlled" mode
	//----------------------------------------------------------------------
	void DoSetAcquisitionControl(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch, int TriggerMode);
	//----------------------------------------------------------------------
	// Starts the acquisition at the camera by using the GenICam interface
	//----------------------------------------------------------------------
	void DoStartAcquisition(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch);
	//----------------------------------------------------------------------
	// Stops the acquisition at the camera by using the GenICam interface
	//----------------------------------------------------------------------
	void DoStopAcquisition(struct SgcBoardHandle* bh, struct SgcCameraHandle* ch);

	void getAndShowCameraProperty( SgcCameraHandle* ch, char* propertyStringIn, unsigned int& value, unsigned int addValue, const int linkIndex = -1);

	void DoAppletSettings( Fg_Struct* FrameGrabber , uint32_t  width, uint32_t height, int triggerMode);
	// helper functions
	bool			manualExit();
	unsigned int	getTimeStamp();
};

#endif //COAXPRESS_H