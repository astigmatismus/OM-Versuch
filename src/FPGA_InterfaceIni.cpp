/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "FPGA_InterfaceIni.h"
#include "FPGA_Interface_Core.h"
#include <inifile.h>
#include <QFile>
#include <string.h>

FPGA_IFIni::FPGA_IFIni():m_ini(""),m_iniStartUp("")
{
	m_actIniFileVersion = INI_FILE_ACT_VERSION;
	QString Filename	= "RecentlyOpened.ini";
	QDir currentPath	= QDir::current();
	currentPath.cdUp();
	m_iniStartUp_filename = currentPath.path().append("/res/StartUp/").append(Filename);
}

FPGA_IFIni::~FPGA_IFIni()
{

}

bool FPGA_IFIni::fileExists(QString strFilename)
{
	QFile file(strFilename);
	return file.exists();
}

//Read the Ini file
bool FPGA_IFIni::readFPGA_IFIni(QString strIniPath)
{
	
	if(!fileExists(strIniPath)){
	QMessageBox::information(0,"FPGA_IF INI read",QString("Ini-file \"%1\" does not exist.").arg(strIniPath));
		return false;
	}

	this->m_ini_filename = strIniPath;
     
	// Erease all elements
	this->m_ini.clearItems();
	m_actIniEntrys.clear();

	QString camSelected = "Virtual Dummy";
       
	this->m_ini.read(this->m_ini_filename.toStdString());
	
	cout << endl << setw(200) << setfill('*') << "" << endl;
	cout << "Content of Ini-File: " << this->m_ini_filename.toStdString() << endl;
	for (MIniFileConstIterator iniIT = this->m_ini.getConstIterator(); iniIT != this->m_ini.end(); iniIT++){
		cout << setw(100) << setfill('.') << (*iniIT).getKey() << (*iniIT).getValue() << endl;
		if( QString((*iniIT).getKey().c_str()) == INI_CAM_SELECTED ){
			camSelected = QString((*iniIT).getValue().c_str());
		}
		m_actIniEntrys.push_back(QString((*iniIT).getKey().c_str()));
	}
	cout << setw(200) << setfill('*') << "" << endl;
	cout << setfill(' ') << endl;

	compareEntrysList(m_actIniEntrys, camSelected);
	
	return true;
}

//Write the entire ini file
bool FPGA_IFIni::writeFPGA_IFIni(QString strIniPath, bool setVersion)
{

	// Insert the actual version numer
	if( setVersion == true )
		this->m_ini.setItem((INI_VERSION).toStdString(), m_actIniFileVersion);

	cout << endl << setw(200) << setfill('*') << "" << endl;
	cout << "Content of Ini-File: " << strIniPath.toStdString() << endl;
	for (MIniFileConstIterator iniIT = this->m_ini.getConstIterator(); iniIT != this->m_ini.end(); iniIT++)
		cout << setw(100) << setfill('.') << (*iniIT).getKey() << (*iniIT).getValue() << endl;
	cout << setw(200) << setfill('*') << "" << endl;
	cout << setfill(' ') << endl;

	this->m_ini.write(strIniPath.toStdString());
	
	return true;
}

//Read the list of recently opened files
bool FPGA_IFIni::readRecentlyOpenedFPGA_IFInis(QStringList & list, int & nCbIndex)
{
	if (!this->m_iniStartUp.read(this->m_iniStartUp_filename.toStdString()))
	{
		MESSAGE("Startup inifile directory not found - check directories!");
		return false;
	}

	std::string strStd;
	QString strToSplit;
	int count;

	list.clear();
	this->m_iniStartUp.getItem(INI_RECENTLY_OPENED_CB_INDEX.toStdString(), nCbIndex, 0);
	this->m_iniStartUp.getItem(INI_RECENTLY_OPENED_INIS_COUNT.toStdString(), count, 0);
	for (long num = 0; num < count; num++)
	{
		this->m_iniStartUp.getItem(QString(INI_RECENTLY_OPENED_INIS+"%1").arg(num).toStdString(), strStd, "");
		list.push_back(QString(strStd.c_str()));
	}
	
	return true;
}

//Append to the list of recently opened files
bool FPGA_IFIni::writeRecentlyOpenedFPGA_IFInis(const QStringList & list, int nCbIndex)
{
	
	this->m_iniStartUp.setItem(INI_RECENTLY_OPENED_INIS_COUNT.toStdString(), list.size());
	this->m_iniStartUp.setItem(INI_RECENTLY_OPENED_CB_INDEX.toStdString(), nCbIndex);
	for (long num = 0; num < list.size(); num++)
	{
		this->m_iniStartUp.setItem(QString(INI_RECENTLY_OPENED_INIS+"%1").arg(num).toStdString()
			, list.at(num));
	}

	this->m_iniStartUp.write(this->m_iniStartUp_filename.toStdString());

	this->m_iniStartUp.flush();
	
	return true;
}

// Finds missing elements and prints them out to the console
void FPGA_IFIni::compareEntrysList(QStringList list2compare, QString camSelected)
{
	if( list2compare.size() == 0 )
		return;

	int camLoopCnt = 0;
	int cameraCase = -1;
	bool camera = false;
	QString camKey = "";
	QStringList missing;
	int numOfCamSettings =	INI_ENTRYS.m_nrOfCamSettings[0] + 
							INI_ENTRYS.m_nrOfCamSettings[1] +
							INI_ENTRYS.m_nrOfCamSettings[2] + 1;

	// Spezial handling for different cameras
	if( camSelected == "Virtueller Dummy" )
		cameraCase = 0;
	if( camSelected == "JAI Pulnix AccuPixel TM-6740 CL" )
		cameraCase = 1;
	if( camSelected == "Mikrotron MC258x" )
		cameraCase = 2;

	for( int i=0; i<INI_ENTRYS.m_iniEntrys.size(); i++ ){

		// Initialize spezial handling for camera settings
		if( INI_ENTRYS.m_iniEntrys[i] == INI_CAM_SELECTED ){
			camera = true;
		}

		if( list2compare.contains(camKey + INI_ENTRYS.m_iniEntrys[i]) == false ){
			missing.push_back(camKey + INI_ENTRYS.m_iniEntrys[i]);
		}

		if( cameraCase == 2 ){
			if( (camKey + INI_ENTRYS.m_iniEntrys[i]) == "Hardware/Cameras/Mikrotron MC258x/TapOffsetA" )
				missing.removeAt(missing.indexOf("Hardware/Cameras/Mikrotron MC258x/TapOffsetA"));
			if( (camKey + INI_ENTRYS.m_iniEntrys[i]) == "Hardware/Cameras/Mikrotron MC258x/TapOffsetB" )
				missing.removeAt(missing.indexOf("Hardware/Cameras/Mikrotron MC258x/TapOffsetB"));
			if( (camKey + INI_ENTRYS.m_iniEntrys[i]) == "Hardware/Cameras/Mikrotron MC258x/TapGainA" )
				missing.removeAt(missing.indexOf("Hardware/Cameras/Mikrotron MC258x/TapGainA"));
			if( (camKey + INI_ENTRYS.m_iniEntrys[i]) == "Hardware/Cameras/Mikrotron MC258x/TapGainB" )
				missing.removeAt(missing.indexOf("Hardware/Cameras/Mikrotron MC258x/TapGainB"));
			if( (camKey + INI_ENTRYS.m_iniEntrys[i]) == "Hardware/Cameras/Mikrotron MC258x/Gain A+B" )
				missing.removeAt(missing.indexOf("Hardware/Cameras/Mikrotron MC258x/Gain A+B"));
			
		}

		if( camera == true ){
			camLoopCnt++;
			camKey = INI_CAM_KEY + camSelected + "/";

			switch( cameraCase ){
			case 0:	// For Virtual Dummy 
				if( camLoopCnt == INI_ENTRYS.m_nrOfCamSettings[0] ){
					i += numOfCamSettings - INI_ENTRYS.m_nrOfCamSettings[0];
					camKey = "";
					camera = false;
				} break;
			case 1:	// For AVT Marlin F131B-NIR
				if( camLoopCnt == numOfCamSettings ){
					camKey = "";
					camera = false;
				} break;
			default: // For all other cameras
				if( camLoopCnt == numOfCamSettings - INI_ENTRYS.m_nrOfCamSettings[2] ){
					i += 1;
					camKey = "";
					camera = false;
				} break;					
			}
		}
	}

	if( missing.size() > 0 ){
		MESSAGE("WARNING: Missing ini-file-entrys!");
		cout << endl << setw(200) << setfill('*') << "" << endl;
		cout << "Missing Tags inside the Ini-File: " << this->m_ini_filename.toStdString() << endl;
		for( int i=0; i<missing.size(); i++ )
			cout << setw(100) << setfill('.') << missing[i].toStdString().c_str() << "" << endl;
		cout << setw(200) << setfill('*') << "" << endl;
		cout << setfill(' ') << endl;
	}
}
