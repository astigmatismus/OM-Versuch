/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef INISELECTIONWINDOW_H_
#define INISELECTIONWINDOW_H_

#include <QMutex>
#include <QDialog>
#include "ui_FPGA_Interfaceiniselectionwindow.h"
#include "FPGA_Interface_Core.h"
//#include "FPGA_IF.h"

class MWorkspaceIF;

namespace FPGA_IF
{
	enum iniselectionwindow{ stdIni=1, loadIni=2 };
}

class FPGA_IFIniSelectionWindow : public QDialog, protected Ui_FPGA_InterfaceIniSelectionWindow//, QLayoutItem
{
	Q_OBJECT
public:

				FPGA_IFIniSelectionWindow	(QString rw, double actVersion = -1.0);
	virtual		~FPGA_IFIniSelectionWindow	();
	QString		getSelectedIni				() { return m_strSelectedIni; }

protected:
	void		InitializeControls			();
	QString		m_strSelectedIni;

protected slots:
	void 		slotComboIniFileChanged		(int value);
	void 		slotButtonLoad				();
	void 		slotButtonStd				();
	void 		slotButtonCancel			();
	void 		slotButtonSelectIniFile		();
private:
	QString		m_default_ini;
	QString		m_typeOfSelection;

};
#endif // end of #ifndef INISELECTIONWINDOW_H_