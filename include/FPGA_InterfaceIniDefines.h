/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef FPGA_IF_INI_DEFINES_H
#define FPGA_IF_INI_DEFINES_H

#define INI_RECENTLY_OPENED				QString("Plugins/FPGA_IF/INI/")
#define INI_RECENTLY_OPENED_INIS		QString(INI_RECENTLY_OPENED+"RecentlyOpenedInis")
#define INI_RECENTLY_OPENED_INIS_COUNT	QString(INI_RECENTLY_OPENED+"RecentlyOpenedInisCount")
#define INI_RECENTLY_OPENED_CB_INDEX	QString(INI_RECENTLY_OPENED+"DefaultIniIndex")

// --> Define Keys (subdirectories where to place depending entrys)
#define INI_HW							QString("Hardware/")
#define INI_SW							QString("Software/")
#define INI_PROJECT_KEY					QString("Project/")
 
#define INI_META_KEY					QString(INI_SW+"IniMeta/")
#define INI_VIEW_KEY					QString(INI_SW+"Ansicht/")

#define INI_FG_KEY						QString(INI_HW+"Framegrabber/")
#define INI_CAM_KEY						QString(INI_HW+"Cameras/")
// --------------------------------------------------------------------<

// --> Now define all entrys for the ini-file
// --> Important NOTE: Each must be added to class FPGA_IFIniFileEntrys aswell! (see down under)
#define INI_VERSION						QString(INI_META_KEY+"INI Version NR")


#define INI_FG_TRIGGERMODE				QString(INI_FG_KEY+"Trigger-Mode_(swt)")
#define INI_FG_RUNNING					QString(INI_FG_KEY+"Grabbing")
#define INI_FG_SIZEIMAGEBUF				QString(INI_FG_KEY+"SizeImagebuffer")
#define INI_FG_THRESHOLD				QString(INI_FG_KEY+"Threshold")	   
#define INI_FG_THRESHINI				QString(INI_FG_KEY+"Threshold - Blob Analysis")	
#define INI_FG_CIRCINI					QString(INI_FG_KEY+"Circularity - Blob Analysis")	
#define INI_FG_CONVINI					QString(INI_FG_KEY+"Convexity - Blob Analysis")	
#define INI_FG_DISTINI					QString(INI_FG_KEY+"Minimum dist between spots - Blob Analysis")
#define INI_FG_MINAREA					QString(INI_FG_KEY+"Min Area - Blob Analysis")
#define INI_FG_MAXAREA					QString(INI_FG_KEY+"Max Area - Blob Analysis")
#define INI_FG_ROISIZEX					QString(INI_FG_KEY+"ROISizeX_px")
#define INI_FG_ROISIZEY					QString(INI_FG_KEY+"ROISizeY_px")
#define INI_FG_ROIID					QString(INI_FG_KEY+"ROI_Id")
#define INI_FG_MAXAMPL					QString(INI_FG_KEY+"Max. expected distance")
#define INI_FG_NSAMPLES					QString(INI_FG_KEY+"Number of diplayed samples")
#define INI_FG_MEASURETIME				QString(INI_FG_KEY+"Measurement_Time")
#define INI_FG_CELLX					QString(INI_FG_KEY+"total of Cells in X")
#define INI_FG_CELLY					QString(INI_FG_KEY+"total of Cells in Y")

#define INI_CAM_SELECTED				QString(INI_CAM_KEY+"Selected")
#define INI_CAM_NAME					QString("Name")
#define INI_CAM_ACTIVE					QString("Active")
#define INI_CAM_BOARD					QString("Board")
#define INI_CAM_PORT					QString("Port")
#define INI_CAM_TAPOFFSET_A				QString("TapOffsetA")
#define INI_CAM_TAPOFFSET_B				QString("TapOffsetB")
#define INI_CAM_TAPGAIN_A				QString("TapGainA")
#define INI_CAM_TAPGAIN_B				QString("TapGainB")
#define INI_CAM_GAIN_AB					QString("Gain A+B")
#define INI_CAM_SHUTTER					QString("Shutter")
#define INI_CAM_IMAGE_SIZE				QString("ImageSize")
#define INI_CAM_IMAGE_OFFSET			QString("ImageOffset")
#define INI_CAM_IMAGE_BRIGHTNESS		QString("AnalogGain")

#define INI_CAM_IMAGE_FRAMERATE			QString("Framerate")

#define INI_PROJECT_PATH				QString(INI_PROJECT_KEY+"ProjectPath")
#define INI_PROJECT_PATHREF				QString(INI_PROJECT_KEY+"ProjectPathRef")
#define INI_PROJECT_LASTREF				QString(INI_PROJECT_KEY+"Last Ref Image")
#define INI_PROJECT_MODE				QString(INI_PROJECT_KEY+"Messmethode")
#define INI_PROJECT_USER_1				QString(INI_PROJECT_KEY+"User first name")
#define INI_PROJECT_USER_2				QString(INI_PROJECT_KEY+"User last name")
#define INI_PROJECT_COMMENT				QString(INI_PROJECT_KEY+"Comment")

// --------------------------------------------------------------------<

#include <QStringList>
#include <QString>
#include <QFileInfo>
#include <QDir>

// Important NOTE: Add all entrys here to this class aswell (push them back into m_iniEntrys)!!!
//
// This class is finally used just to iterrate through all entrys, to find out missing entrys in the actual loaded file.
//
// Just the function FPGA_IFIni::compareEntrysList(...) uses this class. New entrys must just be added, and compareEntrysList(...)
// function will detect missing entrys automatically. Especially camera settings behave a little different, see below...
// NOTE: All camera spezific entrys must be pushed back in the correct order! E.g. Dummy and AVT differ from the CL cameras.
class FPGA_IFIniFileEntrys
{
public:
	FPGA_IFIniFileEntrys	()
	{
		m_iniEntrys.clear();

		m_iniEntrys.push_back(INI_VERSION);

		m_iniEntrys.push_back(INI_FG_TRIGGERMODE);
		m_iniEntrys.push_back(INI_FG_RUNNING);
		m_iniEntrys.push_back(INI_FG_SIZEIMAGEBUF);
		m_iniEntrys.push_back(INI_FG_THRESHOLD);
		m_iniEntrys.push_back(INI_FG_THRESHINI);
		m_iniEntrys.push_back(INI_FG_CONVINI);
		m_iniEntrys.push_back(INI_FG_CIRCINI);
		m_iniEntrys.push_back(INI_FG_DISTINI);
		m_iniEntrys.push_back(INI_FG_MINAREA);
		m_iniEntrys.push_back(INI_FG_MAXAREA);
		m_iniEntrys.push_back(INI_FG_ROISIZEX);
		m_iniEntrys.push_back(INI_FG_ROISIZEY);
		m_iniEntrys.push_back(INI_FG_ROIID);
		m_iniEntrys.push_back(INI_FG_MAXAMPL);
		m_iniEntrys.push_back(INI_FG_NSAMPLES);
		m_iniEntrys.push_back(INI_FG_MEASURETIME);
		m_iniEntrys.push_back(INI_FG_CELLX);
		m_iniEntrys.push_back(INI_FG_CELLY);
		
		// *********************************************
		//
		// These following settings are camera spezific! 
		// IMPORTANT: Do not resort or reorder them!!!
		//
		m_iniEntrys.push_back(INI_CAM_SELECTED);
		// The "Virtual Dummy" only uses the following settings
		m_iniEntrys.push_back(INI_CAM_NAME);
		m_iniEntrys.push_back(INI_CAM_IMAGE_SIZE);
		// The following settings are used for every kind of camera!
		// Savety add new camera entrys here, if u don't now where to put them.
		m_iniEntrys.push_back(INI_CAM_ACTIVE);
		m_iniEntrys.push_back(INI_CAM_BOARD);
		m_iniEntrys.push_back(INI_CAM_PORT);
		m_iniEntrys.push_back(INI_CAM_TAPOFFSET_A);
		m_iniEntrys.push_back(INI_CAM_TAPOFFSET_B);
		m_iniEntrys.push_back(INI_CAM_TAPGAIN_A);
		m_iniEntrys.push_back(INI_CAM_TAPGAIN_B);
		m_iniEntrys.push_back(INI_CAM_GAIN_AB);
		m_iniEntrys.push_back(INI_CAM_SHUTTER);
		m_iniEntrys.push_back(INI_CAM_IMAGE_OFFSET);
		// The following settings are only used for AVT-Camera!
		m_iniEntrys.push_back(INI_CAM_IMAGE_BRIGHTNESS);
		m_iniEntrys.push_back(INI_CAM_IMAGE_FRAMERATE);
		
		// IMPORTANT: You have to update these numbers in case of changed entrys! 
		m_nrOfCamSettings[0] = 3;		// Number of settings only used by "Virtual Dummy"
		m_nrOfCamSettings[1] = 10;		// Number of settings used for every kind of camera
		m_nrOfCamSettings[2] = 1;       // Number of settings only used by "AVT Cameras"
		//
		// *********************************************

		m_iniEntrys.push_back(INI_PROJECT_PATH);
		m_iniEntrys.push_back(INI_PROJECT_PATHREF);
		m_iniEntrys.push_back(INI_PROJECT_LASTREF);
		m_iniEntrys.push_back(INI_PROJECT_MODE);
		m_iniEntrys.push_back(INI_PROJECT_USER_1);
		m_iniEntrys.push_back(INI_PROJECT_USER_2);
		m_iniEntrys.push_back(INI_PROJECT_COMMENT);
		
	};
	~FPGA_IFIniFileEntrys	(){};

	// function to get the current FPGA_IF-Plugin source path
	QString GetCurrentFPGA_IFSourcePath(){
		QFileInfo fi(QString(__FILE__));
		return QDir::toNativeSeparators(fi.dir().absolutePath() + QString("/Mirror/config-files/"));
	}

	QStringList	m_iniEntrys;
	int		m_nrOfCamSettings[2];
};

#define INI_ENTRYS			FPGA_IFIniFileEntrys()
#define FPGA_IF_DIRECTORY			QString(INI_ENTRYS.GetCurrentFPGA_IFSourcePath())

#endif // FPGA_IF_INI_DEFINES_H