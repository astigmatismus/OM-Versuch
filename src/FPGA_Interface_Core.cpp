/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "FPGA_Interface_Core.h"
#include "SiSo_Applet_min.h"

#include "FPGA_Interfaceiniselectionwindow.h"
#include <stdio.h>
#include <windows.h>
#include <string>

//#define TEST

FPGA_IF_Core		*g_pFPGA_IFcore = new FPGA_IF_Core();
extern FPGA_IFMainWindow* pFPGA_IFMainWindow;

//Default constructor - provide with default values via initialization list
FPGA_IF_Core::FPGA_IF_Core		(): m_ini (), m_project		(*this)
{
	MESSAGE("FPGA_IF_Core::FPGA_IF_Core()");

	this->m_pFPGA_IFMainWindow	= NULL;
	this->m_CL_Applet		= new SiSo_AppletMin(*this);


	if (!this->m_CL_Applet)
		assert(0);
	this->m_CL_camera[FPGA_IF::noCam]	= new CKamera_Dummy			(this->m_CL_Applet->m_fg);
	if (!this->m_CL_camera[FPGA_IF::noCam])
		assert(0);
	this->m_CL_camera[FPGA_IF::jaiPu]	= new CKamera_JAI_Pulnix_AccuPixel	(this->m_CL_Applet->m_fg);
	if (!this->m_CL_camera[FPGA_IF::jaiPu])
		assert(0);
	this->m_CL_camera[FPGA_IF::Mikrotron]	= new CKamera_Mikrotron_MC258x	(this->m_CL_Applet->m_fg);
	if (!this->m_CL_camera[FPGA_IF::Mikrotron])
		assert(0);
	
	//this->SetCamSelected(FPGA_IF::Mikrotron);

}

//Free resources via destructor
FPGA_IF_Core::~FPGA_IF_Core		()
{
	MESSAGE("FPGA_IF_Core::~FPGA_IF_Core()");
	if (this->m_CL_camera[FPGA_IF::noCam]) 
		delete this->m_CL_camera[FPGA_IF::noCam];

	if (this->m_CL_camera[FPGA_IF::jaiPu]) 
		delete this->m_CL_camera[FPGA_IF::jaiPu];

	if (this->m_CL_camera[FPGA_IF::Mikrotron]) 
		delete this->m_CL_camera[FPGA_IF::Mikrotron];

	this->m_CL_camera[FPGA_IF::noCam]		= NULL;
	this->m_CL_camera[FPGA_IF::jaiPu]		= NULL;
	this->m_CL_camera[FPGA_IF::Mikrotron]	= NULL;
	
	if (this->m_CL_Applet) 
		delete this->m_CL_Applet;
	this->m_CL_Applet					= NULL;
	this->m_pFPGA_IFMainWindow				= NULL;
}
//----------------------------------------------------------------

//Open Dialog windiow for selecting ini file
bool	FPGA_IF_Core::SelectIniFile        (){
	FPGA_IFIniSelectionWindow iniSelectionWindow( "LOAD", m_ini.getActualVersionNr());

	int nSelWindowRet = iniSelectionWindow.exec();
	QString dd = iniSelectionWindow.getSelectedIni();

	if(nSelWindowRet && !iniSelectionWindow.getSelectedIni().isEmpty())
	{
		// read ini to structure
		if (!this->m_ini.readFPGA_IFIni(iniSelectionWindow.getSelectedIni()))
			return false;
	}
	else
	{
		return false;
	}

	double iniVersion = 0.0;

	// Evaluate iniFile Verion & check if it fits to the actual version to be used! 
	this->m_ini.m_ini.getItem((INI_VERSION).toStdString(), iniVersion, 0.0);

	MESSAGE("SelectIniFile(), INI-File Version-NR: " << iniVersion << " Actual Version-NR: " << this->m_ini.getActualVersionNr());
	if( this->m_ini.getActualVersionNr() != iniVersion ){
		MESSAGE("WARNING: The used inifile has not the correct iniFile version-nr!");
		QMessageBox::StandardButton btn;
		btn = QMessageBox::warning(0, tr("Warning: Wrong Ini-File-Version"), 
			tr("This ini-file version is not in actual state.\nThe actual version number is %1.\n\n").arg(this->m_ini.getActualVersionNr(), 0, 'f', 1) +
			tr("You'll have to save it and load it again.\nActually some settings maybe be missing!"),
			QMessageBox::Retry | QMessageBox::Ignore);
		
		if( btn == QMessageBox::Retry ){
			if( !SelectIniFile() )
				return false;
		}
	}
	return true;
}

//Initialize FPGA Interface 
bool	FPGA_IF_Core::Init			()
{
	MESSAGE("FPGA_IF_Core::Init()");
	
	if (!this->SelectIniFile())
		return false;

	if (!this->ReadIni())
	{
		MESSAGE("Initialization file not readable!");
		QMessageBox::warning(NULL, "Ini file read error", " Initialization file not readable ");
		return false;
	}

	// Init
	if (!this->m_CL_Applet->Init())
		return false;

	// camera
	if (!this->GetpCamSelected()->Init())
	{
		MESSAGE("Camera could not be initialized!");
		QMessageBox::warning(NULL, "Camera initialization Error", " Camera could not be initialized!");
		return false;
	}

	this->m_CL_Applet->SetTriggerMode(this->m_CL_Applet->GetTriggerMode());

	this->m_CL_Applet->SetImageBuffer	(this->m_CL_Applet->GetRB().GetBufferCount2Use());
	//this->m_CL_Applet->SetImageBufferRef	();
	
#ifdef __MULTI_DMA_APPLET__
	this->m_CL_Applet->Param		();
#endif

	return true;
}
//----------------------------------------------------------------

bool	FPGA_IF_Core::DeInit		()
{
	MESSAGE("FPGA_IF_Core::DeInit()");

	if (!m_CL_Applet)
		return true;

	// set INI struct to actual values
	this->WriteIni();

	// camera first - > necessary for coaxPresss to deinitialize board 
	this->GetpCamSelected()->	DeInit();
	//Applet 
	this->m_CL_Applet->DeInit();

	// write INI struct to file
	FPGA_IFIniSelectionWindow iniSelectionWindow("SAVE", m_ini.getActualVersionNr());
	
	int nSelWindowRet = iniSelectionWindow.exec();

	if(nSelWindowRet && !iniSelectionWindow.getSelectedIni().isEmpty())
		this->m_ini.writeFPGA_IFIni(iniSelectionWindow.getSelectedIni());

	this->m_pFPGA_IFMainWindow		= NULL;
	
	return true;
}
//----------------------------------------------------------------

bool	FPGA_IF_Core::slotUpdateInternalData	()
{
	MESSAGE("slotUpdateInternalData");
	// set values
	// cameras, project, applet,
	// core

	// applet
#ifdef __MULTI_DMA_APPLET__
	//this->m_CL_Applet->Param();
#endif
	emit updateGUI();
	
	return true;
}


bool	FPGA_IF_Core::ReadIni		()
{
	QString qstr;
	std::string sstr;

	// camera
	this->GetpCam(FPGA_IF::noCam)		->ReadIni(this->m_ini.m_ini);
	this->GetpCam(FPGA_IF::jaiPu)		->ReadIni(this->m_ini.m_ini);
	this->GetpCam(FPGA_IF::Mikrotron)	->ReadIni(this->m_ini.m_ini);
	this->m_CL_Applet				->ReadIni(this->m_ini.m_ini);

	this->m_ini.m_ini.getItem((INI_CAM_SELECTED)	.toStdString(), this->m_CL_camSelectedqStr, "Virtueller Dummy");
	if (m_CL_camSelectedqStr == pCLcamPulnix->GetName())
	{
		this->SetCamSelected(FPGA_IF::jaiPu);
	}
	else if(m_CL_camSelectedqStr == pCLcamDummy->GetName())
	{
		this->SetCamSelected(FPGA_IF::noCam);
	}
	else if(m_CL_camSelectedqStr == pCLcamMikro->GetName())
	{
		this->SetCamSelected(FPGA_IF::Mikrotron);
	}
	

	this->m_project			.ReadIni(this->m_ini.m_ini);

	slotUpdateInternalData();
	
	return true;
}

bool	FPGA_IF_Core::WriteIni		()
{
	this->m_ini.m_ini.setItem((INI_CAM_SELECTED)	.toStdString(), pCLcamSelected->GetName());
	this->m_CL_Applet		->WriteIni(this->m_ini.m_ini);

	this->m_project			.WriteIni(this->m_ini.m_ini);
	
	this->GetpCam(FPGA_IF::jaiPu)	->WriteIni(this->m_ini.m_ini);
	this->GetpCam(FPGA_IF::noCam)	->WriteIni(this->m_ini.m_ini);
	this->GetpCam(FPGA_IF::Mikrotron)	->WriteIni(this->m_ini.m_ini);

	return true;
}
