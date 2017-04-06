/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef FPGA_IFMAINWINDOW_H_
#define FPGA_IFMAINWINDOW_H_

// Disable warning messages 4125.
#pragma warning( disable:4125 )
#include "ui_FPGA_Interfacemainwindow.h"
#pragma warning(default:4125)

#include <QKeyEvent>
#include <QDialog>
#include <QMainWindow>
#include <stdutils.h>
#include "point.h"	
#include <QObject>

#include "RingbufferItem.h"	
#include "Kamera_I.h"
#include <QPainter>
#include <QCloseEvent>
#include <QDateTime>
#include <QTimeEdit>
#include <fstream>
#include <iomanip>
#include "RB_Plot.h"


extern FPGA_IF_Core			*g_pFPGA_IFcore;

namespace Ui
{
	class FPGA_InterfaceMainWindow;
}

class myGraphicsView:public QGraphicsView
{
	public:
		myGraphicsView(QWidget * parent = 0);

	protected:
		virtual void wheelEvent				(QWheelEvent *event);
		virtual void mousePressEvent		(QMouseEvent *event);
};

class FPGA_IFMainWindow :public QMainWindow
{
	//friend class CKamera_I;

	Q_OBJECT
public:
						FPGA_IFMainWindow	(QWidget *parent = 0);
	virtual				~FPGA_IFMainWindow	();

	void				closeEvent			(QCloseEvent *event);
	void				startGrabbing		();
	void				stopGrabbing		();
	bool				isCameraRunning		();
	FPGA_IF_Img&		GetActualElement	();

	bool				m_allowAutoCalc;
	QString				m_logFileName;
	QFile				m_logFile;
	bool				m_log;
	bool				m_logEach;
	long				m_lastLogRBNr;
	QGraphicsScene		*RefScene;
	QGraphicsPixmapItem *item;
	CV_plot				*ROIPlot;

	vector<float>		m_distVec;
	float				m_maxDist;
	float				m_avgDist;
	bool				m_liveView;

protected:

	void				createStatusBar						();
	void				InitializeControls					();
	void				DeinitializeControls				();
	void				InitializeControlsTapGeneral		();
	void				InitializeControlsTapCamera			();
	void				InitializeControlsTapShowAndCalc	();
	void				connectUpdateCamera					();
	void				disconnectUpdateCamera				();
	void				DrawImage							(FPGA_IF_Img &img, int index);
	void				PlotData							(bool flag);
	void				ClearOverlay						();
	void				SetConvertedTime					(long msecs);

private:
	Ui::FPGA_InterfaceMainWindow	*ui;
	myGraphicsView					*graphicsView;

protected slots:

	// camera
	void slotCamName					(int value);
	void slotCamBoardAndPort			(int value);
	void slotCamActive					(bool value);
	void slotCamShutter					(int value);
	void slotCamTapOffset				();
	void slotCamTapGain					();
	void slotAutoCalib					();

	// uni control cameras
	void slotCamBrightness				(int value);
	void slotFGTriggerMode				(bool swt);
	void slotFGThreshold				(int value);
	void slotFGAverageImages			(int value);
	void slotFGBufferNewSize			();
	void slotFGBufferSave				();
	void slotFGBufferLoad				();
	void slotLiveImageShow				(bool value);

	void slotFGROIWidth					(int value);
	void slotFGROIHeight				(int value);
	void slotFGROIId					(int value);
	void slotClearRefImg				();
	void slotCapRef						();
	void slotFGROISy					(int value);
	void slotFGROISx					(int value);

	void saveMeasXML					();
	void slotCamHeight					(int value);
	void slotCamWidth					(int value);
	void slotCamOffsetY					(int value);
	void slotCamOffsetX					(int value);
	void slotCamFramerate				(int value);

	void slotPlotAmpl					(int ampl);
	void slotPlotN						(int n);

	// RefImg
	void slotReferenceImageShow			(bool value);
	void slotReferenceImageClear		();
	void slotReferenceImageLoad			();
	void slotCalcROIs					();
	void slotLoadRois					();
	void slotSaveRois					();
	void slotSaveMeasure				();

	void slotFGThresh					(int);
	void slotFGConvexity				(int);
	void slotFGCircularity				(int);
	void slotFGDistBetween				(int);
	void slotFGMinArea					(int);
	void slotFGMaxArea					(int);

	// Project
	void slotProjectIniLoad				(QString iniFilePath = "");
	void slotProjectIniSave				();
	void slotProjectPath				();
	void slotProjectPathSelect			();
	void slotProjectUser1				();
	void slotProjectUser2				();
	void slotProjectComment				();
	void slotProjectOK_Save				();
	void slotProjectMessungTyp			();

	// Update
	void slotUpdateGUI					();
	void slotUpdateGUICamera			(FPGA_IF::camera cam);
	void slotUpdateGUIBoard				(FPGA_IF::board board);
	void slotUpdateGUIPort				(FPGA_IF::port port);
	void slotUpdateGUIActive			(bool active);
	void slotUpdateGUIShutter			(long min, long val, long max);
	
	void slotUpdateGUIGain				(FPGA_IF::tap tap, long min, long val, long max);
	void slotUpdateGUIRingBufferCount	(long ccount, long icount);
	void slotUpdateGUIProject			();
	
	
	// Uni Control Camera spezific
	void slotUpdateGUIFrameRate			(long min, long val, long max);
	void slotUpdateGUIBrightness		(long min, long val, long max);
	void slotUpdateGUIGeometryDX		(int val);
	void slotUpdateGUIGeometryDY		(int val);
	void slotUpdateGUIGeometryWX		(int val);
	void slotUpdateGUIGeometryWY		(int val);
	void slotRefreshImgSize				();

	void slotLiveView					(bool act);
	
public slots:

	void slotUpdateGUIRB				(int frmnum = 0);
	void slotUpdateGUIImageView			(int frmnum = -1);
	void slotUpdateGUIRefImg			();
	void slotUpdateGUIFGMeasure			(bool running);

	// FG
	void slotFGGrabContinuous			();
	void slotFGGrabSingle				();
	void slotFGGrabN					();
	void slotFGGrabDur					();
	void slotFGGrabBuffer				();

signals:
	
};

#endif // end of #ifndef MAINWINDOW_H_
