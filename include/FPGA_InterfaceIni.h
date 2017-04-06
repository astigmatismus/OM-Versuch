/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef FPGA_InterfaceIni_H_
#define FPGA_InterfaceIni_H_

#include <QStringList>
#include <inifile.h>
#include "defines.h"

#define INI_FILE_ACT_VERSION 1.8  // defines the version number for the actual inifile which should be use


class FPGA_IFIni //Encapsulates the Ini-Load and Save logic
{
public:
						FPGA_IFIni						();//MWorkspaceIF& ws);
						~FPGA_IFIni						();
	bool				readFPGA_IFIni					(QString strIniPath="");
	bool				writeFPGA_IFIni					(QString strIniPath="", bool setVersion = true);
	bool				readRecentlyOpenedFPGA_IFInis	(QStringList & list, int & nCbIndex);
	bool				writeRecentlyOpenedFPGA_IFInis	(const QStringList & list, int nCbIndex);
	double				getActualVersionNr				(){return m_actIniFileVersion;};

	QString				m_ini_filename;
	QString				m_iniStartUp_filename;
	MIniFile			m_ini;
	MIniFile			m_iniStartUp;
protected:
	bool 				fileExists						(QString strFilename);

private:
	double				m_actIniFileVersion;
	QStringList			m_actIniEntrys;

	void				compareEntrysList				(QStringList list2compare, QString camSelected = "Virtual Dummy");
};

#endif //_FPGA_IFINI_H_