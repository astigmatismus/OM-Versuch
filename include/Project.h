/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#ifndef CPROJECT_INCLUDED
#define CPROJECT_INCLUDED

class FPGA_IF_Core;

#include "Point.h"
#include "FPGA_InterfaceIni.h"
#include "RingbufferItem.h"
#include <QDate>
#include <QList>

namespace FPGA_IF
{
	
	enum measuremode
	{ manual, automatic };
	static QString	Measuremode[2]	= {"manual", "automatic"};
}

class Person
{
public:
	Person		(){}

	QString		nameV, name;
};

class CProject: public QObject
{
	Q_OBJECT
public:
					CProject		(FPGA_IF_Core& core);
	
protected:
	FPGA_IF_Core&			m_core;

	FPGA_IF::measuremode	m_measuremode;
	QString					m_path_base;	// D:/HSMessungen/
	QString					m_path;			// D:/Messungen/YYYY/MM/DD/
	QString					m_pathRef;		// D:/Messungen/Refs/
	QString					m_lastRef;		//			Ref001.bmp
	QString					m_user_1;
	QString					m_user_2;
	QString					m_comment;
	QString					m_pathini;
	
public:
	bool					ReadIni			(MIniFile& ini);
	bool					WriteIni		(MIniFile& ini);
	FPGA_IF::measuremode	SetMeasuremode	(FPGA_IF::measuremode measuremode);
	QString					SetPath			(QString path);
	void					SetPathRef		(QString path){this->m_pathRef = path;}
	void					SetLastRef		(QString file){this->m_lastRef = file;}
	QString					SetPathIni		(QString path);
	QString					SetUser1		(QString user);
	QString					SetUser2		(QString user);
	QString					SetComment		(QString comment);

	FPGA_IF::measuremode	GetMeasuremode	(){return this->m_measuremode;}
	QString					GetPathBase		(){return this->m_path_base;}
	QString					GetPath			(){return this->m_path;}
	QString					GetPathActive	();
	QString					GetAutoPath		();
	QString					GetPathRef		(){return this->m_pathRef;}
	QString					GetLastRef		(){return this->m_lastRef;}
	QString					GetPathIni		(){return this->m_pathini;}
	QString					GetUser1		(){return this->m_user_1;}
	QString					GetUser2		(){return this->m_user_2;}
	QString					GetComment		(){return this->m_comment;}
	//Person				GetPerson		(int value);
signals:
	void					updateProject		();
};
//----------------------------------------------------------------

#endif //CPROJECT_INCLUDED
