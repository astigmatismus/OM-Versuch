/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "Project.h"
#include "FPGA_Interface_Core.h"
#include <QDir>
#include <QList>

CProject::CProject	(FPGA_IF_Core& core) : m_core(core)
{
	m_path_base	= "";
	m_path		= "";
	m_pathRef	= "";
	m_pathini	= "";
	m_user_1	= "";
	m_comment	= "Fügen Sie hier bitte eindeutige Informationen für diese Messung ein.";
	m_measuremode = FPGA_IF::manual;
}
//----------------------------------------------------------------


//----------------------------------------------------------------

// returns the path depending on proband or labor
QString	CProject::GetPathActive		()
{
	QString fn = GetPath();
	if( GetMeasuremode() == FPGA_IF::automatic ){
		fn = GetAutoPath();	
	}
	return fn; 
}

//----------------------------------------------------------------

QString	CProject::GetAutoPath()
{
	// Bsp.: D:/HS_Messungen/Probanden/Nachname_Vorname_Geb/l|r/timestamp.* + Ini-datei
	QString str = GetPathBase().append("User/");
		str += QString("%1_%2_%3/")
			.arg(GetUser1())
			.arg(GetUser1())
			.arg(QDateTime::currentDateTime().toString("yyyy/MM/dd/"))
			;
	return str;
}
//----------------------------------------------------------------

bool	CProject::ReadIni			(MIniFile& ini)
{
	QString qstr;
	ini.getItem((INI_PROJECT_PATH)		.toStdString(), qstr, QCoreApplication::applicationDirPath());
		this->m_path_base	= qstr;
#ifdef _MSC_VER
	this->m_path_base.replace("\\", "/");
#endif
	if (this->m_path_base.right(1) != "/")
		this->m_path_base.append("/");
	this->m_path = this->m_path_base;
	this->m_path.append(QString("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd/"))); 
	QDir d;
	d.mkpath(this->m_path);

	ini.getItem((INI_PROJECT_PATHREF)	.toStdString(), qstr, QCoreApplication::applicationDirPath());
		this->m_pathRef	= qstr;
	ini.getItem((INI_PROJECT_LASTREF)	.toStdString(), qstr, "Ref.bmp");
		this->m_lastRef	= qstr;

	ini.getItem((INI_PROJECT_MODE)	.toStdString(), qstr, (QString)FPGA_IF::Measuremode[FPGA_IF::manual]);
	if (qstr == (QString)FPGA_IF::Measuremode[FPGA_IF::manual])
		this->m_measuremode	= FPGA_IF::manual;
	if (qstr == (QString)FPGA_IF::Measuremode[FPGA_IF::automatic])
		this->m_measuremode	= FPGA_IF::automatic;
	ini.getItem((INI_PROJECT_USER_1)	.toStdString(), qstr, "Vorname");
		this->m_user_1	= qstr;
	ini.getItem((INI_PROJECT_USER_2)	.toStdString(), qstr, "Nachname");
		this->m_user_2	= qstr;
	ini.getItem((INI_PROJECT_COMMENT)	.toStdString(), qstr, "");
		this->m_comment	= qstr;

	//emit updateProject();
	return true;
}
//----------------------------------------------------------------

bool isNumber(const QString& str)
{
	for (int i=0; i < str.size(); i++)
		if (!str[i].isDigit())
			return false;
	return true;
}

bool	CProject::WriteIni		(MIniFile& ini)
{
	// "D:\\path\\subpath\\...\\yyyy\\MM\\dd\\appendix\\"      ->
	// "D:\\path\\subpath\\...\\"
	QStringList sl = this->m_path.split("/", QString::SkipEmptyParts); 
	QString path;
	for (int i=0; i < sl.size(); i++)
	{
		//cout << sl[i].toStdString() << endl;
		if ((sl[i].size() == 4) && (isNumber(sl[i])))
			break;
		path.append(sl[i]).append("/");
	}
	ini.setItem((INI_PROJECT_PATH)		.toStdString(),	this->m_path_base);
	ini.setItem((INI_PROJECT_PATHREF)	.toStdString(),	this->m_pathRef);
	ini.setItem((INI_PROJECT_LASTREF)	.toStdString(),	this->m_lastRef);
	ini.setItem((INI_PROJECT_USER_1)	.toStdString(),	this->m_user_1);
	ini.setItem((INI_PROJECT_USER_2)	.toStdString(),	this->m_user_2);
	ini.setItem((INI_PROJECT_COMMENT)	.toStdString(),	this->m_comment);
	ini.setItem((INI_PROJECT_MODE)		.toStdString(), (QString)FPGA_IF::Measuremode[this->m_measuremode]);
	return true;
}
//----------------------------------------------------------------

QString	CProject::SetPath		(QString path)
{
	this->m_path = path;
//*
#ifdef _MSC_VER
	this->m_path.replace("\\", "/");
#endif
//*/
	if (this->m_path.right(1) != "/")
		this->m_path.append("/");
	//emit updateProject();
	QDir d;
	d.mkpath(this->m_path);
	
	return this->m_path;
}
//----------------------------------------------------------------

QString	CProject::SetPathIni		(QString path)
{
	this->m_pathini = path;
#ifdef _MSC_VER
	this->m_pathini.replace("\\", "/");
#endif
	if (this->m_pathini.right(1) != "/")
		this->m_pathini.append("/");
	return this->m_pathini;
}
//----------------------------------------------------------------

QString	CProject::SetUser1		(QString user)
{
	this->m_user_1 = user;
	//emit updateProject();
	return this->m_user_1;
}
//----------------------------------------------------------------

QString	CProject::SetUser2		(QString user)
{
	this->m_user_2 = user;
	//emit updateProject();
	return this->m_user_2;
}
//----------------------------------------------------------------


FPGA_IF::measuremode CProject::SetMeasuremode	(FPGA_IF::measuremode measuremode)
{
	this->m_measuremode = measuremode;
	//emit updateProject();
	return this->m_measuremode;
}
//----------------------------------------------------------------

QString	CProject::SetComment		(QString comment)
{
	this->m_comment = comment;
	//emit updateProject();
	return this->m_comment;
}
//----------------------------------------------------------------

