/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef FPGA_IF_CORE_INCLUDED
#define FPGA_IF_CORE_INCLUDED

#include <QMutex>
#include <Kamera_Dummy.h>
#include "Kamera_JAI_Pulnix_AccuPixel.h"
#include "Kamera_Mikrotron_MC258x.h"
#include "Project.h"

#include "SiSo_AppletIF.h"
#include "FPGA_InterfaceIni.h"
#include "point.h"	
#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "FPGA_Interfacemainwindow.h"

#define		__MAX_ROIPAIRS__		48   //Maximum expected number of ROIs

//Substitute some lengthy Pointers
#define pCLcamSelected	g_pFPGA_IFcore->GetpCamSelected()
#define pCLApplet		g_pFPGA_IFcore->m_CL_Applet
#define pCLcamDummy		g_pFPGA_IFcore->GetpCam(FPGA_IF::noCam)
#define pCLcamPulnix	g_pFPGA_IFcore->GetpCam(FPGA_IF::jaiPu)
#define pCLcamMikro		g_pFPGA_IFcore->GetpCam(FPGA_IF::Mikrotron)

//Top-level pointer instance 
class FPGA_IF_Core: public QObject
{
	Q_OBJECT
public:
						FPGA_IF_Core		();//MWorkspaceIF &ws);
						~FPGA_IF_Core		();
	bool				Init				();
	bool				DeInit				();
	bool				SelectIniFile		();

	bool				ReadIni				();
	bool				WriteIni			();

	FPGA_IF::camera getCamPos				(FPGA_IF::camera cam)
											{
												if( cam == 3 ) return (FPGA_IF::camera)1;
												if( cam == 4 ) return (FPGA_IF::camera)2;
												return cam;
											}
	QMutex				m_mutex;			//Threads mutual exclusion
	FPGA_IFIni			m_ini;
	SiSo_AppletIF*		m_CL_Applet;		//Main applet being initialized

	//view
	FPGA_IFMainWindow*	m_pFPGA_IFMainWindow;
	
	CProject			m_project;			
	bool				m_calcCPU;

	CKamera_I*			m_CL_camera[3];		// noCam jaiPu Mikrotron

protected:

	
	FPGA_IF::camera		m_CL_camSelected;	
	QString				m_CL_camSelectedqStr;

public:
	CKamera_I*			GetpCam				(FPGA_IF::camera cam){return this->m_CL_camera[cam];}
	CKamera_I*			GetpCamSelected		(){return this->m_CL_camera[m_CL_camSelected];}
	QString				GetCamSelectedStr	(){return this->m_CL_camSelectedqStr;}
	FPGA_IF::camera		GetCamSelected		(){return m_CL_camSelected;}
bool					SetCamSelected		(FPGA_IF::camera cam)
											{
												this->m_CL_camSelected = getCamPos(cam); 
												m_CL_camSelectedqStr = GetpCam(cam)->GetName();
												//emit this->updateCamera(this->m_CL_camSelected); 
												return true;
											}
public slots:
	bool				slotUpdateInternalData();

signals:
	void				updateCamera		(FPGA_IF::camera cam);
	void				updateRefImg		();
	void				updateGUI			();

};

extern FPGA_IF_Core			*g_pFPGA_IFcore;


#endif //FPGA_IF_CORE_INCLUDED
