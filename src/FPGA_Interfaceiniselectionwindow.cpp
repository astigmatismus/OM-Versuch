/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "FPGA_Interfaceiniselectionwindow.h"
#include <QMessagebox>
#include <QFileDialog>
#include "FPGA_InterfaceIni.h"


//Dialog window for choosing the Inifile to be read or written
FPGA_IFIniSelectionWindow::FPGA_IFIniSelectionWindow(QString rw, double actVersion) : QDialog()
{
	setupUi(this);
	this->setModal(true);

	if( actVersion != -1. ){
		m_label_Version->setText(QString("The actual ini-file version is: %1").arg(actVersion, 0, 'f', 1));
	} else m_label_Version->setText("");

	if( rw == "SAVE" ){
		m_label_text->setText(tr("Do you want to save the settings? Choose an ini-file where to save the settings..."));
		m_btnLoad->setText("Save");
		m_typeOfSelection = "SAVE";
	} else{
		m_label_text->setText(tr("Choose the ini-file you want to load..."));
		m_btnLoad->setText("Load");
		m_typeOfSelection = "LOAD";		
	}

	this->m_strSelectedIni = "";
	QString Filename	= "Default.ini";
	QDir currentPath	= QDir::current();
	currentPath.cdUp();
	this->m_default_ini	= currentPath.path().append("/res/StartUp/").append(Filename);

	InitializeControls();
}


FPGA_IFIniSelectionWindow::~FPGA_IFIniSelectionWindow()
{
	disconnect(m_cbIniFile,		SIGNAL(currentIndexChanged(int)),	this, SLOT(slotComboIniFileChanged(int)));
	disconnect(m_btnLoad,		SIGNAL(clicked()),			this, SLOT(slotButtonLoad()));
	disconnect(m_btnStd,		SIGNAL(clicked()),			this, SLOT(slotButtonStd()));
	disconnect(m_btnCancel,		SIGNAL(clicked()),			this, SLOT(slotButtonCancel()));
	disconnect(m_tbSelectIniFile,	SIGNAL(clicked()),			this, SLOT(slotButtonSelectIniFile()));
}

void FPGA_IFIniSelectionWindow::InitializeControls()
{
	QStringList slInis;
	int nCbIndexFromIni=0;
	bool hasdefault = false;

	connect(m_cbIniFile,		SIGNAL(currentIndexChanged(int)),	this, SLOT(slotComboIniFileChanged(int)));
	connect(m_btnLoad,		SIGNAL(clicked()),			this, SLOT(slotButtonLoad()));
	connect(m_btnStd,		SIGNAL(clicked()),			this, SLOT(slotButtonStd()));
	connect(m_btnCancel,		SIGNAL(clicked()),			this, SLOT(slotButtonCancel()));
	connect(m_tbSelectIniFile,	SIGNAL(clicked()),			this, SLOT(slotButtonSelectIniFile()));

	FPGA_IFIni	ini;
	ini.readRecentlyOpenedFPGA_IFInis(slInis, nCbIndexFromIni);

	for(int i = 0; i < slInis.count(); i++)
	{
		m_cbIniFile->insertItem(m_cbIniFile->count(), slInis.at(i));
		if (slInis.at(i) == this->m_default_ini)
			hasdefault = true;
	}
	m_cbIniFile->setCurrentIndex(nCbIndexFromIni);
	if (!hasdefault)
		m_cbIniFile->insertItem(0, this->m_default_ini);
}

void FPGA_IFIniSelectionWindow::slotComboIniFileChanged(int value)
{
}

void FPGA_IFIniSelectionWindow::slotButtonLoad()
{
	
	QStringList slInis;

	for(int i = 0; i < m_cbIniFile->count(); i++)
		slInis.append(m_cbIniFile->itemText(i));

	FPGA_IFIni	ini;
	ini.writeRecentlyOpenedFPGA_IFInis(slInis, m_cbIniFile->currentIndex());

	m_strSelectedIni = m_cbIniFile->itemText(m_cbIniFile->currentIndex());

	done(FPGA_IF::loadIni);
}

void FPGA_IFIniSelectionWindow::slotButtonStd()
{
	m_strSelectedIni = this->m_default_ini;
	done(FPGA_IF::stdIni);
}

void FPGA_IFIniSelectionWindow::slotButtonCancel()
{
	m_strSelectedIni = "";
	done(0);
}

void FPGA_IFIniSelectionWindow::slotButtonSelectIniFile()
{
QString path = m_cbIniFile->itemText(m_cbIniFile->currentIndex());
	int pos = path.lastIndexOf("/");
	path = path.left(pos+1);

//	cout << path.toStdString() << endl;
	QStringList filters;
	filters << "Ini-Files (*.ini)";
	QFileDialog	dlg	(this);
	dlg.setWindowTitle	(tr("Select ini-file..."));
	dlg.setNameFilters (filters);
	dlg.selectNameFilter	("Ini-Files (*.ini)");
	dlg.setDefaultSuffix	("ini");
	if( m_typeOfSelection == "LOAD" )
		dlg.setAcceptMode	(QFileDialog::AcceptOpen);
	else	dlg.setAcceptMode	(QFileDialog::AcceptSave);
	dlg.setViewMode		(QFileDialog::Detail);
	dlg.setDirectory	(path);
	dlg.setFileMode		(QFileDialog::AnyFile);
	if (!dlg.exec())
		return ;
    
	QStringList fileNamelist = dlg.selectedFiles();
	QStringList::Iterator it = fileNamelist.begin();

#ifdef _MSC_VER
		(*it).replace("\\", "/");
#endif
	QString strFile = *it;

	if(!strFile.isEmpty())
	{//user has selected a file
		//check if file is already in list
		for(int i=0; i<m_cbIniFile->count(); i++)
			if(m_cbIniFile->itemText(i).toUpper() == strFile.toUpper())
			{
				m_cbIniFile->setCurrentIndex(i);
				return;
			}
		m_cbIniFile->insertItem(m_cbIniFile->count(), strFile);
		m_cbIniFile->setCurrentIndex(m_cbIniFile->count()-1);
	}
}
