/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "FPGA_Interfacemainwindow.h"
#include <QMessagebox>
#include <QFileDialog>
#include <QDateTime>
#include <QProgressDialog>
#include <QTextStream>
#include "FPGA_Interfaceiniselectionwindow.h"
#include "stringutils.h"
#include <conio.h>


using namespace FPGA_IF;   

myGraphicsView::myGraphicsView(QWidget *parent)
	:QGraphicsView(parent)
{
}

//Reimplement wheel event for zooming 
void myGraphicsView::wheelEvent(QWheelEvent *event)
{
	if(event->modifiers() & Qt::ControlModifier)
	{
		QGraphicsView::wheelEvent(event);
	}
	else
	{
		this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        // Scale the view / do the zoom
        double scaleFactor = 1.15;
        if(event->delta() > 0) {
            // Zoom in
            this-> scale(scaleFactor, scaleFactor);
 
        } else {
            // Zooming out
             this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
	}
}

//reimplement mouse event for setting image
void myGraphicsView::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		this->fitInView(g_pFPGA_IFcore->m_pFPGA_IFMainWindow->RefScene->itemsBoundingRect() ,Qt::KeepAspectRatio);
		this->setScene(g_pFPGA_IFcore->m_pFPGA_IFMainWindow->RefScene);
	}
	else
	{
		QGraphicsView::mousePressEvent(event);
	}
}

//Startup new window - default constructor
 FPGA_IFMainWindow::FPGA_IFMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPGA_InterfaceMainWindow)
{
    ui->setupUi(this);
	setFocusPolicy(Qt::StrongFocus); 
	MESSAGE("FPGA_IFMainWindow::FPGA_IFMainWindow()");
	this->createStatusBar();
	RefScene = new QGraphicsScene(this);

	graphicsView = new myGraphicsView(ui->tab_2);
    graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
    graphicsView->setGeometry(QRect(0, 0, 716, 542));
    graphicsView->setMouseTracking(true);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
	graphicsView->setScene(RefScene);

	//set stepsize according to max parallelism of applet
	ui->m_sbROIWidth->setSingleStep	(__PARALLEL_MODULO__);
	ui->m_sbROIWidth->setMinimum	(__PARALLEL_MODULO__);
	ui->m_sbROIHeight->setSingleStep(__PARALLEL_MODULO__);
	ui->m_sbROIHeight->setMinimum	(__PARALLEL_MODULO__);
	ui->m_saveMeasure->setEnabled(false);
	ui->m_progressBar->setValue(0);
	ui->m_measComp->hide();

	ROIPlot = new CV_plot();

	///-------temporary 
	int lastn = 50;
	int maxY  = 60;
	std::string yLabel =	"Distance[PX]";
	std::string xLabel =	"Last n samples";

	ROIPlot->setUpWindow(800,142,50,35,3,3,lastn, yLabel, xLabel, lastn, maxY);

	this->InitializeControls();

	ui->m_slBrightness->	setEnabled(true);
	ui->m_sbBrightness->	setEnabled(true);
	ui->m_sbFramerate->		setEnabled(true);

	ui->m_sbOfSetX->		setEnabled(true);
	ui->m_sbOfSetY->		setEnabled(true);
	ui->m_sbWidth->			setEnabled(true);
	ui->m_sbHeight->		setEnabled(true);
	
	m_liveView			=	true;
	ui->m_cbLive->			setChecked(true);      

	m_logFileName = "";
	m_log = false;
}

 //clear ressources upon shutdown
 FPGA_IFMainWindow::~FPGA_IFMainWindow()
{
	delete ROIPlot;
	delete RefScene;
	MESSAGE("FPGA_IFMainWindow::~FPGA_IFMainWindow()");
}

//Sequentially initialize all GUI elements
void FPGA_IFMainWindow::InitializeControls()
{
	this->InitializeControlsTapGeneral		();
	this->InitializeControlsTapCamera		();
	this->InitializeControlsTapShowAndCalc		();

	connect(g_pFPGA_IFcore,			SIGNAL(updateGUI()), 			this, SLOT(slotUpdateGUI()));
	slotUpdateGUI();
}

//Denitialize the GUI Elements of all elements
void FPGA_IFMainWindow::DeinitializeControls()
{
	disconnect(g_pFPGA_IFcore,				SIGNAL(updateGUI()), 			this, SLOT(slotUpdateGUI()));
		
	disconnect(&g_pFPGA_IFcore->m_project,	SIGNAL(updateProject()), 		this, SLOT(slotUpdateGUIProject()));
	disconnect(ui->m_ProjectIniLoad,		SIGNAL(clicked()), 				this, SLOT(slotProjectIniLoad()));
	disconnect(ui->m_ProjectIniSave,		SIGNAL(clicked()), 				this, SLOT(slotProjectIniSave()));
	disconnect(ui->m_ProjectPath_btn,		SIGNAL(clicked()), 				this, SLOT(slotProjectPathSelect()));
	disconnect(ui->m_ProjectPath,			SIGNAL(editingFinished()), 		this, SLOT(slotProjectPath()));
	disconnect(ui->m_ProjectUser,			SIGNAL(editingFinished()), 		this, SLOT(slotProjectUser1()));
	disconnect(ui->m_ProjectUser_2,			SIGNAL(editingFinished()), 		this, SLOT(slotProjectUser2()));
	disconnect(ui->m_ProjectComment,		SIGNAL(textChanged()), 			this, SLOT(slotProjectComment()));
	disconnect(ui->m_ProjectOK,				SIGNAL(clicked()), 				this, SLOT(slotProjectOK_Save()));
	disconnect(ui->m_Project_praxis,		SIGNAL(clicked()), 				this, SLOT(slotProjectMessungTyp()));
	
	disconnect(g_pFPGA_IFcore,				SIGNAL(updateCamera(FPGA_IF::camera)),		this, SLOT(slotUpdateGUICamera(FPGA_IF::camera )));
	disconnect(pCLApplet,					SIGNAL(updateLiveGrab(bool)),				this, SLOT(slotUpdateGUIFGMeasure(bool)));
	disconnect(pCLApplet,					SIGNAL(updateRingBufferCount(long, long)),	this, SLOT(slotUpdateGUIRingBufferCount	(long, long)));
	disconnect(pCLApplet,					SIGNAL(updateImageView(int)),				this, SLOT(slotUpdateGUIImageView(int)));;
	disconnect(pCLApplet,					SIGNAL(updateGUIFit(int)),					this, SLOT(slotUpdateGUIFitData(int)));

	disconnect(ui->m_slBuffer,				SIGNAL(sliderMoved(int)),	this, SLOT(slotUpdateGUIRB(int)));
	disconnect(ui->m_slBuffer,				SIGNAL(valueChanged(int)),	this, SLOT(slotUpdateGUIRB(int)));
	disconnect(ui->m_sbBuffer,				SIGNAL(valueChanged(int)),	this, SLOT(slotUpdateGUIRB(int))); 

	disconnect(ui->m_SetGeometry,			SIGNAL(clicked()), 			this, SLOT(slotRefreshImgSize()));

	disconnect(ui->m_cbCameraName,			SIGNAL(currentIndexChanged(int)),	this, SLOT(slotCamName(int)));
	disconnect(ui->m_btnSaveBuffer,			SIGNAL(clicked()), 					this, SLOT(slotFGBufferSave()));
	disconnect(ui->m_btnLoadBuffer,			SIGNAL(clicked()), 					this, SLOT(slotFGBufferLoad()));
	disconnect(ui->m_sbSizeControlbuffer,	SIGNAL(editingFinished()),			this, SLOT(slotFGBufferNewSize()));

	disconnect(ui->m_btnGrabContinuous,		SIGNAL(clicked()), 			this, SLOT(slotFGGrabContinuous()));
	disconnect(ui->m_btnGrabSingle,			SIGNAL(clicked()), 			this, SLOT(slotFGGrabSingle()));
	
	disconnect(ui->m_btnGrabN,				SIGNAL(clicked()), 			this, SLOT(slotFGGrabDur()));
	disconnect(ui->m_btnGrabBuffer,			SIGNAL(clicked()), 			this, SLOT(slotFGGrabBuffer()));
	
	disconnect(g_pFPGA_IFcore,				SIGNAL(updateRefImg()), 	this, SLOT(slotUpdateGUIRefImg()));
	disconnect(ui->m_btn_RefImg_clear,		SIGNAL(clicked()), 			this, SLOT(slotReferenceImageClear()));
	disconnect(ui->m_btn_RefImg_load,		SIGNAL(clicked()), 			this, SLOT(slotReferenceImageLoad()));
	disconnect(ui->m_btn_Calc_ROIs,			SIGNAL(clicked()), 			this, SLOT(slotCalcROIs()));
	
	disconnect(ui->m_sbThreshold,			SIGNAL(valueChanged(int)),		this, SLOT(slotFGThreshold(int)));
	
	disconnect(ui->m_sbROIWidth,			SIGNAL(valueChanged(int)),		this, SLOT(slotFGROIWidth(int)));
	disconnect(ui->m_sbROIHeight,			SIGNAL(valueChanged(int)),		this, SLOT(slotFGROIHeight(int)));
	disconnect(ui->m_sbROIId,				SIGNAL(valueChanged(int)),		this, SLOT(slotFGROIId(int)));

	disconnect(ui->m_sb_expAmpl,			SIGNAL(valueChanged(int)),		this, SLOT(slotPlotAmpl(int)));
	disconnect(ui->m_sbNSamples,			SIGNAL(valueChanged(int)),		this, SLOT(slotPlotN(int)));
	
	disconnect(ui->m_xROIs,					SIGNAL(valueChanged(int)),		this, SLOT(slotFGROISx(int)));
	disconnect(ui->m_yROIs,					SIGNAL(valueChanged(int)),		this, SLOT(slotFGROISy(int)));
		
	disconnect(ui->m_btn_RefImg_clear,		SIGNAL(clicked()), 			this, SLOT(slotClearRefImg()));
	disconnect(ui->m_saveRois,				SIGNAL(clicked()), 			this, SLOT(slotSaveRois()));
	disconnect(ui->m_loadRois,				SIGNAL(clicked()), 			this, SLOT(slotLoadRois()));
	disconnect(ui->m_btn_Cap_Ref,			SIGNAL(clicked()), 			this, SLOT(slotCapRef()));
	disconnect(ui->m_btn_RefImg_clear,		SIGNAL(clicked()), 			this, SLOT(slotReferenceImageClear()));
	disconnect(ui->m_saveMeasure,			SIGNAL(clicked()), 			this, SLOT(slotSaveMeasure()));

	//disconnect(ui->m_AutoCalib,		SIGNAL(clicked()),		this, SLOT(slotAutoCalib()));

	disconnect(ui->m_slBrightness,			SIGNAL(sliderMoved(int)),		this, SLOT(slotCamBrightness(int)));
	disconnect(ui->m_slBrightness,			SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));
	disconnect(ui->m_sbBrightness,			SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));

	disconnect(ui->m_sbOfSetX,				SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));
	disconnect(ui->m_sbOfSetY,				SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetY(int)));
	disconnect(ui->m_sbWidth,				SIGNAL(valueChanged(int)),		this, SLOT(slotCamWidth(int)));
	disconnect(ui->m_sbHeight,				SIGNAL(valueChanged(int)),		this, SLOT(slotCamHeight(int)));

	disconnect(ui->m_cbLive,				SIGNAL(toggled(bool)),			this, SLOT(slotLiveView(bool)));

	disconnect(ui->m_sbThresh,				SIGNAL(valueChanged(int)),		this, SLOT(slotFGThresh(int)));
	disconnect(ui->m_sbConvexity,			SIGNAL(valueChanged(int)),		this, SLOT(slotFGConvexity(int)));
	disconnect(ui->m_sbCircularity,			SIGNAL(valueChanged(int)),		this, SLOT(slotFGCircularity(int)));
	disconnect(ui->m_sbDistBetween,			SIGNAL(valueChanged(int)),		this, SLOT(slotFGDistBetween(int)));
	disconnect(ui->m_sbMinArea,				SIGNAL(valueChanged(int)),		this, SLOT(slotFGMinArea(int)));
	disconnect(ui->m_sbMaxArea,				SIGNAL(valueChanged(int)),		this, SLOT(slotFGMaxArea(int)));

	
}
//----------------------------------------------------------------

//Initialize the GUI Elements of the camera dialog window according to the type of camera being chosen
void FPGA_IFMainWindow::connectUpdateCamera()
{

	if(g_pFPGA_IFcore->GetCamSelected() == noCam)
	{
		ui->groupBox_9->setEnabled(false);
		ui->groupBox_8->setEnabled(false);
		ui->groupBox_6->setEnabled(false);
	}

	if(g_pFPGA_IFcore->GetCamSelected() == jaiPu)
	{
		ui->groupBox_6->setEnabled(true);
		ui->groupBox_9->setEnabled(true);
		ui->groupBox_8->setEnabled(false);
	}

	if(g_pFPGA_IFcore->GetCamSelected() == Mikrotron)
	{
		ui->groupBox_6->setEnabled(false);
		ui->groupBox_9->setEnabled(true);
		ui->groupBox_8->setEnabled(true);
	}

	// connect the (new selected) camera to update slots
	connect(pCLcamSelected, SIGNAL(updateActive		(bool)),							this, SLOT(slotUpdateGUIActive		(bool )));
	connect(pCLcamSelected, SIGNAL(updateBoard		(FPGA_IF::board)),					this, SLOT(slotUpdateGUIBoard		(FPGA_IF::board )));
	connect(pCLcamSelected, SIGNAL(updatePort		(FPGA_IF::port)),					this, SLOT(slotUpdateGUIPort		(FPGA_IF::port )));
	connect(pCLcamSelected, SIGNAL(updateShutter		(long, long, long)),			this, SLOT(slotUpdateGUIShutter		(long, long , long )));
	connect(pCLcamSelected, SIGNAL(updateBrightness		(long, long, long)),			this, SLOT(slotUpdateGUIBrightness		(long , long , long )));
	connect(pCLcamSelected, SIGNAL(updateGain		(FPGA_IF::tap, long, long, long)),	this, SLOT(slotUpdateGUIGain		(FPGA_IF::tap, long, long , long )));
}

//Initialize the GUI Elements of the Camera dialog window
void FPGA_IFMainWindow::InitializeControlsTapCamera()
{
	this->slotCamName			(g_pFPGA_IFcore->GetCamSelected());
	this->slotCamShutter		(pCLcamSelected->GetShutter_us(FPGA_IF::val));

	// fill comboboxes
	ui->m_cbCameraName->	addItem(g_pFPGA_IFcore->GetpCam(FPGA_IF::noCam)->GetName(), 	noCam);
	ui->m_cbCameraName->	addItem(g_pFPGA_IFcore->GetpCam(FPGA_IF::jaiPu)->GetName(), 	jaiPu);
	ui->m_cbCameraName->	addItem(g_pFPGA_IFcore->GetpCam(FPGA_IF::Mikrotron)->GetName(), 	Mikrotron);
	connect(ui->m_cbCameraName,		SIGNAL(currentIndexChanged(int)),	this, SLOT(slotCamName(int)));
	
	ui->m_cbBoard->		addItem(tr("0"), board0); 
	ui->m_cbBoard->		addItem(tr("1"), board1);

	ui->m_cbPort->		addItem(tr("A"), portA);
	ui->m_cbPort->		addItem(tr("B"), portB);

	ui->m_eSensortype->	setReadOnly(true);
	ui->m_eNumberTaps->	setReadOnly(true);
	
	// connect update
	connect(g_pFPGA_IFcore,	SIGNAL(updateCamera(FPGA_IF::camera)),	this, SLOT(slotUpdateGUICamera(FPGA_IF::camera )));
	//connect(g_pFPGA_IFcore->m_CL_camera[g_pFPGA_IFcore->GetCamSelected()],	SIGNAL(updateShutter(long min, long val, long max)),this, SLOT(slotUpdateGUIShutter(long min, long val, long max)));
	
	connect(pCLApplet,		SIGNAL(updateLiveGrab(bool)),		this, SLOT(slotUpdateGUIFGMeasure(bool)));
	connect(pCLApplet,		SIGNAL(updateRingBufferCount(long, long)),this, SLOT(slotUpdateGUIRingBufferCount	(long, long)));
	connect(pCLApplet,		SIGNAL(updateImageView(int)),		this, SLOT(slotUpdateGUIImageView(int)));
	
	connect(ui->m_slBuffer,		SIGNAL(sliderMoved(int)),		this, SLOT(slotUpdateGUIRB(int)));
	connect(ui->m_slBuffer,		SIGNAL(valueChanged(int)),		this, SLOT(slotUpdateGUIRB(int)));
	connect(ui->m_sbBuffer,		SIGNAL(valueChanged(int)),		this, SLOT(slotUpdateGUIRB(int)));

	connect(ui->m_slBrightness,		SIGNAL(sliderMoved(int)),		this, SLOT(slotCamBrightness(int)));
	connect(ui->m_slBrightness,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));
	connect(ui->m_sbBrightness,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));

	connect(ui->m_sbOfSetX,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));
	connect(ui->m_sbOfSetY,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetY(int)));
	connect(ui->m_sbWidth,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamWidth(int)));
	connect(ui->m_sbHeight,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamHeight(int)));

	connect(ui->m_sbBuffer,			SIGNAL(valueChanged(int)),		this, SLOT(slotUpdateGUIRB(int)));

	connect(ui->m_btnSaveBuffer,	SIGNAL(clicked()), 			this, SLOT(slotFGBufferSave()));
	connect(ui->m_btnLoadBuffer,	SIGNAL(clicked()), 			this, SLOT(slotFGBufferLoad()));
	connect(ui->m_sbSizeControlbuffer,	SIGNAL(editingFinished()),		this, SLOT(slotFGBufferNewSize()));

	connect(ui->m_sbThreshold,		SIGNAL(valueChanged(int)),		this, SLOT(slotFGThreshold(int)));
	
	connect(ui->m_sbROIWidth,		SIGNAL(valueChanged(int)),		this, SLOT(slotFGROIWidth(int)));
	connect(ui->m_sbROIHeight,		SIGNAL(valueChanged(int)),		this, SLOT(slotFGROIHeight(int)));
	connect(ui->m_sbROIId,			SIGNAL(valueChanged(int)),		this, SLOT(slotFGROIId(int)));
	
	connect(ui->m_sb_expAmpl,			SIGNAL(valueChanged(int)),		this, SLOT(slotPlotAmpl(int)));
	connect(ui->m_sbNSamples,			SIGNAL(valueChanged(int)),		this, SLOT(slotPlotN(int)));

	connect(ui->m_xROIs,		SIGNAL(valueChanged(int)),		this, SLOT(slotFGROISx(int)));
	connect(ui->m_yROIs,		SIGNAL(valueChanged(int)),		this, SLOT(slotFGROISy(int)));
	
//	connect(ui->m_AutoCalib,		SIGNAL(clicked()),		this, SLOT(slotAutoCalib()));

	connect(ui->m_SetGeometry,		SIGNAL(clicked()), 			this, SLOT(slotRefreshImgSize()));

	connect(ui->m_cbLive,	SIGNAL(toggled(bool)),				this, SLOT(slotLiveView(bool)));

	connect(ui->m_sbThresh, SIGNAL(valueChanged(int)),			this, SLOT(slotFGThresh(int)));
	connect(ui->m_sbConvexity, SIGNAL(valueChanged(int)),		this, SLOT(slotFGConvexity(int)));
	connect(ui->m_sbCircularity, SIGNAL(valueChanged(int)),		this, SLOT(slotFGCircularity(int)));
	connect(ui->m_sbDistBetween, SIGNAL(valueChanged(int)),		this, SLOT(slotFGDistBetween(int)));
	connect(ui->m_sbMinArea, SIGNAL(valueChanged(int)),			this, SLOT(slotFGMinArea(int)));
	connect(ui->m_sbMaxArea, SIGNAL(valueChanged(int)),			this, SLOT(slotFGMaxArea(int)));
	
}

//Future feature- automatically adjust gain and shuttertime to optimize lighting conditions for image acquisition
void FPGA_IFMainWindow::slotAutoCalib()
{
	QMessageBox::warning(NULL, "Not implemented yet", "Histogramm for setting shutter and gain!");

}

//Convert msecs to hh::mm::ss
void FPGA_IFMainWindow::SetConvertedTime(long msecs)
{
	QTime myTime;

	int hours = msecs/(1000*60*60);
	int minutes = (msecs-(hours*1000*60*60))/(1000*60);
	int seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;

	myTime.setHMS(hours,minutes,seconds);
	ui->m_timeEdit->setTime(myTime);

	pCLApplet->SetGrabTime(msecs);

}

//Initialize the GUI Elements of the Measruement dialog window
void FPGA_IFMainWindow::InitializeControlsTapShowAndCalc()
{
	ui->m_lframeNum->setText		(QString(tr("Frame Number")));
	ui->m_lTimestamp->setText(QString(tr("Timestamp")));
	ui->m_sbBuffer->setValue(0);
	ui->m_sbROIWidth->setValue(g_pFPGA_IFcore->m_CL_Applet->GetROIWidth());
	ui->m_sbROIHeight->setValue(g_pFPGA_IFcore->m_CL_Applet->GetROIHeight());
	ui->m_sbROIId->setValue(g_pFPGA_IFcore->m_CL_Applet->GetROIId());

	//ui->m_sb_expAmpl->setValue(this->ROIPlot->getMaxDist());
	//ui->m_sbNSamples->setValue(this->ROIPlot->getSamplesN());

	ui->m_sbThresh->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetThresh());
	ui->m_sbConvexity->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetConvexity());
	ui->m_sbCircularity->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetCircularity());
	ui->m_sbDistBetween->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetDistBetween());
	ui->m_sbMinArea->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetMinArea());
	ui->m_sbMaxArea->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetMaxArea());

	ui->m_sbThreshold->setValue(g_pFPGA_IFcore->m_CL_Applet->GetThresholdMin());

	/*ui->m_timeEdit->*/SetConvertedTime(g_pFPGA_IFcore->m_CL_Applet->GetGrabTime());

	ui->m_sb_expAmpl->setValue(g_pFPGA_IFcore->m_CL_Applet->GetMaxAmp());
	ui->m_sbNSamples->setValue(g_pFPGA_IFcore->m_CL_Applet->GetNSamples());
	
	connect(ui->m_btnGrabContinuous,	SIGNAL(clicked()), 			this, SLOT(slotFGGrabContinuous()));
	connect(ui->m_btnGrabSingle,		SIGNAL(clicked()), 			this, SLOT(slotFGGrabSingle()));
	connect(ui->m_btnGrabN,				SIGNAL(clicked()), 			this, SLOT(slotFGGrabDur()));
	connect(ui->m_btnGrabBuffer,		SIGNAL(clicked()), 			this, SLOT(slotFGGrabBuffer()));

	connect(ui->m_btn_RefImg_load,		SIGNAL(clicked()), 			this, SLOT(slotReferenceImageLoad()));
	connect(ui->m_btn_Calc_ROIs,		SIGNAL(clicked()), 			this, SLOT(slotCalcROIs()));
	connect(ui->m_btn_RefImg_clear,		SIGNAL(clicked()), 			this, SLOT(slotClearRefImg()));
	connect(ui->m_saveRois,				SIGNAL(clicked()), 			this, SLOT(slotSaveRois()));
	connect(ui->m_loadRois,				SIGNAL(clicked()), 			this, SLOT(slotLoadRois()));
	connect(ui->m_btn_Cap_Ref,			SIGNAL(clicked()), 			this, SLOT(slotCapRef()));
	connect(ui->m_btn_RefImg_clear,		SIGNAL(clicked()), 			this, SLOT(slotReferenceImageClear()));
	connect(ui->m_saveMeasure,			SIGNAL(clicked()), 			this, SLOT(slotSaveMeasure()));
	
	connect(g_pFPGA_IFcore,				SIGNAL(updateRefImg()), 		this, SLOT(slotUpdateGUIRefImg()));
}

//Initialize the GUI Elements of the genereal dialog window
void FPGA_IFMainWindow::InitializeControlsTapGeneral()
{
	connect(&g_pFPGA_IFcore->m_project,	SIGNAL(updateProject()), 	this, SLOT(slotUpdateGUIProject()));
	connect(ui->m_ProjectIniLoad,		SIGNAL(clicked()), 			this, SLOT(slotProjectIniLoad()));
	connect(ui->m_ProjectIniSave,		SIGNAL(clicked()), 			this, SLOT(slotProjectIniSave()));
	connect(ui->m_ProjectPath_btn,		SIGNAL(clicked()), 			this, SLOT(slotProjectPathSelect()));
	connect(ui->m_ProjectPath,			SIGNAL(editingFinished()), 	this, SLOT(slotProjectPath()));
	
	connect(ui->m_ProjectUser,			SIGNAL(editingFinished()), 	this, SLOT(slotProjectUser1()));
	connect(ui->m_ProjectUser_2,		SIGNAL(editingFinished()), 	this, SLOT(slotProjectUser2()));
	
	connect(ui->m_ProjectComment,		SIGNAL(textChanged()), 		this, SLOT(slotProjectComment()));
	connect(ui->m_ProjectOK,			SIGNAL(clicked()), 			this, SLOT(slotProjectOK_Save()));
	connect(ui->m_Project_praxis,		SIGNAL(clicked()), 			this, SLOT(slotProjectMessungTyp()));
	connect(ui->m_Project_Einzelmessung,SIGNAL(clicked()), 			this, SLOT(slotProjectMessungTyp()));
	
	slotUpdateGUIProject();
}

//Exit the programm - Are you sure?-Dialog
void FPGA_IFMainWindow::closeEvent (QCloseEvent *event)
{
	g_pFPGA_IFcore->slotUpdateInternalData(); //Update all internal Data one last time to save all changes upon shutdown
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "FPGA Interface",
                                                                tr("Are you sure you want to quit?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

//Disconnect the cameras GUI functionalities
void FPGA_IFMainWindow::disconnectUpdateCamera()
{
	// disconnect the old camera from update slots
	disconnect(pCLcamSelected, SIGNAL(updateActive		(bool)),			this, SLOT(slotUpdateGUIActive		(bool )));
	disconnect(pCLcamSelected, SIGNAL(updateBoard		(FPGA_IF::board)),			this, SLOT(slotUpdateGUIBoard		(FPGA_IF::board )));
	disconnect(pCLcamSelected, SIGNAL(updatePort		(FPGA_IF::port)),			this, SLOT(slotUpdateGUIPort		(FPGA_IF::port )));
	disconnect(pCLcamSelected, SIGNAL(updateShutter		(long, long, long)),		this, SLOT(slotUpdateGUIShutter		(long, long, long)));
	disconnect(pCLcamSelected, SIGNAL(updateBrightness	(long, long, long)),		this, SLOT(slotUpdateGUIBrightness		(long, long, long)));
	//disconnect(pCLcamSelected, SIGNAL(updateOffset		(FPGA_IF::tap, long, long, long)), this, SLOT(slotUpdateGUIOffset		(FPGA_IF::tap, long, long, long)));
	disconnect(pCLcamSelected, SIGNAL(updateGain		(FPGA_IF::tap, long, long, long)), this, SLOT(slotUpdateGUIGain		(FPGA_IF::tap, long, long, long)));
}

//Update the entire GUI including all menues and dialogues
void FPGA_IFMainWindow::slotUpdateGUI	()
{
	slotUpdateGUICamera			(g_pFPGA_IFcore->GetCamSelected());
	long size	= pCLApplet->GetRB().GetSize();
	slotUpdateGUIRingBufferCount		(size, 0);

	slotUpdateGUIRB				();
	slotUpdateGUIRefImg			();
	slotUpdateGUIProject			();
	slotUpdateGUIFGMeasure			(isCameraRunning());
}

//Reallocate new buffersize
void FPGA_IFMainWindow::slotFGBufferNewSize()
{
	if( ui->m_sbSizeControlbuffer->value() != pCLApplet->GetImageBufferCount() )
	{
		this->setCursor(Qt::WaitCursor);
		pCLApplet->SetImageBuffer(ui->m_sbSizeControlbuffer->value());
		g_pFPGA_IFcore->slotUpdateInternalData();
		MESSAGE("Ringbuffer reallocated!");
		this->setCursor(Qt:: ArrowCursor);
		pCLApplet->GetRB().SetBufferCount2Use(ui->m_sbSizeControlbuffer->value());
	}
}

void FPGA_IFMainWindow::slotUpdateGUIRefImg		()
{
}

//Get the latest element from the frame buffer
FPGA_IF_Img& FPGA_IFMainWindow::GetActualElement	()
{
	if( g_pFPGA_IFcore->m_pFPGA_IFMainWindow != NULL )     
	{ 
		int bufferNum = ui->m_sbBuffer->value();
		int imgNr = g_pFPGA_IFcore->m_CL_Applet->GetRB().GetActualImgNum();
		return g_pFPGA_IFcore->m_CL_Applet->GetRB().GetElement(imgNr + bufferNum - 1);
	}
	return g_pFPGA_IFcore->m_CL_Applet->GetRB().GetLatestElement();
}

//Update the image view section of gui
void FPGA_IFMainWindow::slotUpdateGUIImageView	(int frmnum)
{
	QMutexLocker locker(&g_pFPGA_IFcore->m_CL_Applet->m_core.m_mutex); 

	FPGA_IF_Img* imgs = NULL;
	if( frmnum == -1 )
	{
		imgs = &GetActualElement();
	}
	else imgs = &pCLApplet->GetRB().GetElement(frmnum-1);
	if( imgs == NULL )
		return;
	
	float frr = pCLApplet->GetFramrate();

	if (frr == 0)
	{
		ui->m_lFramerate->setText		(QString(tr("not active")));
//		m_lframeNum->setText		(QString(tr("not active")));
		ui->m_lframeNum->setText		(QString("%1").arg(pCLApplet->GetRB().GetActualImgNum()));
	}
	else
	{
		ui->m_lFramerate->setText		(QString("%1Hz (%2ms)").arg((double)frr, 7, 'f', 2).arg(1000/(double)frr, 7, 'f', 2));
		ui->m_lframeNum->setText		(QString("%1").arg(pCLApplet->GetRB().GetActualImgNum()));

		float frt = ui->m_sbSizeControlbuffer->value()*1000/frr;
		ui->m_sbSizeControlbuffer->setToolTip(tr("Buffer time: %1ms").arg(QString::number(frt,'f', 2)));
	}

	// Set timestamp text color depending on correction
	QPalette pal = ui->m_lTimestamp->palette();
	if( imgs->m_timestampCorrected )
		pal.setColor(QPalette::WindowText, QColor(200,0,0));
	else 
		pal.setColor(QPalette::WindowText, QColor(0,0,0));

	ui->m_lTimestamp->setPalette(pal);
	QString temp_TimeStampStr = QString("%1").arg(imgs->GetTimestampAsString());
	if(temp_TimeStampStr!=NULL)
		ui->m_lTimestamp->setText(temp_TimeStampStr);

	this->DrawImage(*imgs,0);
	this->DrawImage(*imgs,2);
	this->PlotData(true);

	//Update progress bar
	
	if (g_pFPGA_IFcore->m_CL_Applet->GetGrabTime() > 1 && isCameraRunning())
	{
		ui->m_progressBar->setValue(static_cast<int>(floor(100 * ((g_pFPGA_IFcore->m_CL_Applet->timer.elapsed()) / ((double)g_pFPGA_IFcore->m_CL_Applet->GetGrabTime())))));
	}
}


//Load reference image - how to deal with image dimensions that differ from the current camera frame geometry?
void FPGA_IFMainWindow::slotReferenceImageLoad()
{
	this->statusBar()->showMessage("Load reference image...");

	RefScene->clear();
	this->graphicsView->setScene(RefScene);
	pCLApplet->GetRB().ClearRefImg();

	QStringList filters;

	filters 	<< "Tiff files\t\t(*.tif)"
			<< "all files\t\t(*.*)"
			/*
			<< "Portable Network files\t(*.png)"
			<< "TIFF files\t\t(*.tif)"
			*/;

	QString	filePath = QDir::fromNativeSeparators(g_pFPGA_IFcore->m_project.GetPathRef());
	MESSAGE2("Filepath for loading Referenz: ", filePath.toStdString());

	QFileDialog dialog		(this);
	dialog.setNameFilters		(filters);
	dialog.selectNameFilter		(filters[0]);
	dialog.setAcceptMode	(QFileDialog::AcceptOpen);
	dialog.setViewMode		(QFileDialog::Detail);
	dialog.setDirectory		(filePath);
	dialog.setFileMode		(QFileDialog::ExistingFile);
	if (!dialog.exec())
	{
		this->statusBar()->showMessage("Ready");
		return;
	}


	QStringList fileNamelist = dialog.selectedFiles();

	long imgcount = fileNamelist.count();
	if (!imgcount)
	{
		this->statusBar()->showMessage("Ready");
		return;
	}
		

	QString fname	= fileNamelist[0];
	QDir resDir		= QFileInfo(fname).absoluteDir();
	QString resDirS	= resDir.absolutePath();
	cv::Mat Input = cv::imread(fname.toStdString());

	FPGA_IF_Img *refPtr = &pCLApplet->GetRB().GetRefImg();
	/* TODO //Only load images if the current image size is fitting!!*/
	/*
	if(refPtr == NULL || Input.rows != refPtr->m_DMA0MatRef.rows || Input.cols != refPtr->m_DMA0MatRef.cols)
	{
		MESSAGE("Reference image has wrong size!");
		QMessageBox::warning(NULL, "Load reference image failed...", "The reference image has wrong size!\n It must have equal size as allocated!");
		pCLApplet->GetRB().SetRefImg(NULL, false);
		g_pFPGA_IFcore->m_project.SetLastRef("");
		return;
	}
	*/
	
	refPtr->m_ImgDMA0 = Input;
	pCLApplet->GetRB().SetRefImg(refPtr, false);
	g_pFPGA_IFcore->m_project.SetPathRef(resDirS);
	g_pFPGA_IFcore->m_project.SetLastRef(fname.section('/', -1, -1));

	this->DrawImage(pCLApplet->GetRB().GetRefImg(), 1);
	ui->m_tabView->setCurrentIndex(1);
	this->statusBar()->showMessage("Ready");
	return ;
}


//Calculate ROIs on the reference image
void FPGA_IFMainWindow::slotCalcROIs()
{
	this->statusBar()->showMessage("Calculating ROI positions");

	if(pCLApplet->GetRB().refIsSet())
	{
		pCLApplet->GetRB().clearMeasData(true);
		cv::Mat Input = pCLApplet->GetRB().GetRefImg().m_DMA0MatRef.clone();

		if(!Input.empty())
		{
			cv::Mat Result = pCLApplet->GetRB().m_myRef.m_getROICoords(Input);
			std::vector<ROIInfo> ResROIs = pCLApplet->GetRB().m_myRef.getROIs();

			for(unsigned int i = 0; i < g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getTotalROIs(); i++) //Transfer latest roi information to current measurement
			{
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->validROI[i]				=	ResROIs[i].twoCircles;
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->leftROIImgCoordsx[i]		=	ResROIs[i].OriginSubLeftImg.x;
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->leftROIImgCoordsy[i]		=	ResROIs[i].OriginSubLeftImg.y;
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->rightROIImgCoordsx[i]		=	ResROIs[i].OriginSubRightImg.x;
				g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->rightROIImgCoordsy[i]		=	ResROIs[i].OriginSubRightImg.y;
			}

			pCLApplet->GetRB().GetRefImg().m_DMAInfoMatRef = Result.clone();
			slotFGThreshold(pCLApplet->GetThresholdMin());
			this->DrawImage(pCLApplet->GetRB().GetRefImg(), 1);
			ui->m_tabView->setCurrentIndex(1);
		}
		else 	
		{
			QMessageBox msgBox;
			msgBox.setText("Reference image not valid!");
			msgBox.exec();
		}
	}
	else 	
	{
		QMessageBox msgBox;
		msgBox.setText("No reference image loaded!");
		msgBox.exec();
	}
	this->statusBar()->showMessage("Ready");
}

//
void FPGA_IFMainWindow::slotUpdateGUIActive		(bool active)
{
	disconnect(ui->m_cbCameraActive,		SIGNAL(toggled(bool)),			this, SLOT(slotCamActive(bool)));
	
	ui->m_cbCameraActive->setEnabled	(pCLcamSelected->IsActivalable());
	ui->m_cbCameraActive->setChecked	(active);
	ui->m_cbCameraActive->repaint();

	connect(ui->m_cbCameraActive,	SIGNAL(toggled(bool)),			this, SLOT(slotCamActive(bool)));
	
	slotUpdateGUIBoard		(pCLcamSelected->GetBoard());
	slotUpdateGUIPort		(pCLcamSelected->GetPort());
	slotUpdateGUIShutter	(pCLcamSelected->GetShutter_us(FPGA_IF::min),pCLcamSelected->GetShutter_us(FPGA_IF::val),pCLcamSelected->GetShutter_us(FPGA_IF::max));
	slotUpdateGUIBrightness	(pCLcamSelected->GetGlobGain(FPGA_IF::min),pCLcamSelected->GetGlobGain(FPGA_IF::val),pCLcamSelected->GetGlobGain(FPGA_IF::max));
	slotUpdateGUIGain		(tapA, pCLcamSelected->GetTapVGain  (tapA, FPGA_IF::min), pCLcamSelected->GetTapVGain  (tapA, FPGA_IF::val), pCLcamSelected->GetTapVGain  (tapA, FPGA_IF::max));
	slotUpdateGUIGain		(tapB, pCLcamSelected->GetTapVGain  (tapB, FPGA_IF::min), pCLcamSelected->GetTapVGain  (tapB, FPGA_IF::val), pCLcamSelected->GetTapVGain  (tapB, FPGA_IF::max));
	slotUpdateGUIFrameRate	(pCLcamSelected->GetFramerate(FPGA_IF::min),pCLcamSelected->GetFramerate(FPGA_IF::val),pCLcamSelected->GetFramerate(FPGA_IF::max));

	slotUpdateGUIGeometryDX	(pCLcamSelected->GetImageOffset_px().x);
	slotUpdateGUIGeometryDY	(pCLcamSelected->GetImageOffset_px().y);
	slotUpdateGUIGeometryWX	(pCLcamSelected->GetImageSize_px().x);
	slotUpdateGUIGeometryWY	(pCLcamSelected->GetImageSize_px().y);

	//info
	ui->m_eSensortype->setText		(Sensortype[pCLcamSelected->GetSensorType()]);
	ui->m_eNumberTaps->setText		(QString("%1").arg(pCLcamSelected->GetNumTaps()));
	ui->m_eSensortype->repaint();
	ui->m_eNumberTaps->repaint();
}

//Update the framegrabber board number
void FPGA_IFMainWindow::slotUpdateGUIBoard		(FPGA_IF::board board)
{
	disconnect(ui->m_cbBoard,		SIGNAL(currentIndexChanged(int)),	this, SLOT(slotCamBoardAndPort(int)));

	ui->m_cbBoard->setEnabled		(pCLcamSelected->IsActivalable() && !pCLcamSelected->IsInit());
	ui->m_cbBoard->setCurrentIndex	(pCLcamSelected->GetBoard());

	connect(ui->m_cbBoard,			SIGNAL(currentIndexChanged(int)),	this, SLOT(slotCamBoardAndPort(int)));

	ui->m_cbBoard->repaint();
}

//Update the framegrabber port
void FPGA_IFMainWindow::slotUpdateGUIPort		(FPGA_IF::port port)
{
	disconnect(ui->m_cbPort,		SIGNAL(currentIndexChanged(int)),	this, SLOT(slotCamBoardAndPort(int)));
	
	ui->m_cbPort->setEnabled		(pCLcamSelected->IsActivalable() && !pCLcamSelected->IsInit());
	ui->m_cbPort->setCurrentIndex	(pCLcamSelected->GetPort());

	connect(ui->m_cbPort,			SIGNAL(currentIndexChanged(int)),	this, SLOT(slotCamBoardAndPort(int)));

	ui->m_cbPort->repaint();
}

//Select camera in GUI
void FPGA_IFMainWindow::slotCamName(int value)
{
	this->statusBar()->showMessage("Switch Camera");
	bool running = isCameraRunning();
	stopGrabbing();

	this->disconnectUpdateCamera();

	g_pFPGA_IFcore->SetCamSelected((camera) value);

	this->connectUpdateCamera();

	g_pFPGA_IFcore->slotUpdateInternalData();

	if (pCLcamSelected->IsActivalable())
	{
		if (running)
			startGrabbing();
	}
	this->statusBar()->showMessage("Ready");
}

//Start grabbing images
void FPGA_IFMainWindow::startGrabbing()
{
	MESSAGE("Started Grabber...");

	if(!g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_ROISset)
	{
		QMessageBox msgBox;
		msgBox.setText("No ROIs calculated nor loaded! \n No valid output will be generated.");
		msgBox.exec();

		//return;
	}
	pCLApplet->start();
}

void FPGA_IFMainWindow::stopGrabbing()
{

	MESSAGE("Stopped Grabber...");
	
	pCLApplet->stop();
}

bool FPGA_IFMainWindow::isCameraRunning()
{
	return pCLApplet->isRunning();
}

//Update cam info in GUI
void FPGA_IFMainWindow::slotUpdateGUICamera		(FPGA_IF::camera cam)
{
	ui->m_cbCameraName			->blockSignals(true);
	ui->m_cbCameraName			->setCurrentIndex(cam);
	ui->m_cbCameraName			->blockSignals(false);
	ui->m_cbCameraName			->repaint();
	slotUpdateGUIActive		(pCLcamSelected->IsInit());
}

//Update the ringbuffer GUI elements - counter
void FPGA_IFMainWindow::slotUpdateGUIRingBufferCount	(long ccount, long icount)
{
	QTime tt ;
	tt.addSecs(600);
	QTime tt2 ;
	tt2.addSecs(00);

	ui->m_sbSizeControlbuffer->blockSignals(true);

	ui->m_sbSizeControlbuffer	->setMaximum	(4000);
	ui->m_sbSizeControlbuffer	->setMinimum	(1);
	//ui->m_sbSizeControlbuffer	->setSingleStep	(1<<pCLApplet->GetAverageImageNum2PotRef());
	ui->m_sbSizeControlbuffer	->setValue	(ccount);

	ui->m_sbImagebufferSaveCount->setMaximum	(ccount);
	ui->m_sbImagebufferSaveCount->setMinimum	(1);
	ui->m_sbImagebufferSaveCount->setValue	(ccount);

	ui->m_timeEdit->setMaximumTime	(tt);
	ui->m_timeEdit->setMinimumTime	(tt2);
	ui->m_timeEdit->setTime			(tt);

	ui->m_btnGrabBuffer->setText	(QString("Grab %1").arg(ccount));

	ui->m_sbSizeControlbuffer->blockSignals(false);

	slotUpdateGUIRB(0);
}	

//Update the ringbuffer GUI elements
void FPGA_IFMainWindow::slotUpdateGUIRB		(int num) // [-(bufsize-1)..0]
{

	connect(ui->m_sbThresh,		SIGNAL(valueChanged(int)), this, SLOT(slotFGThresh(int)));
	connect(ui->m_sbConvexity,	SIGNAL(valueChanged(int)), this, SLOT(slotFGConvexity(int)));
	connect(ui->m_sbCircularity,SIGNAL(valueChanged(int)), this, SLOT(slotFGCircularity(int)));
	connect(ui->m_sbDistBetween,SIGNAL(valueChanged(int)), this, SLOT(slotFGDistBetween(int)));
	connect(ui->m_sbMinArea,	SIGNAL(valueChanged(int)), this, SLOT(slotFGMinArea(int)));
	connect(ui->m_sbMaxArea,	SIGNAL(valueChanged(int)), this, SLOT(slotFGMaxArea(int)));

	ui->m_sbBuffer			->blockSignals(true);
	ui->m_slBuffer			->blockSignals(true);
	ui->m_sbThreshold		->blockSignals(true);		
	ui->m_sbROIWidth		->blockSignals(true);
	ui->m_sbROIHeight		->blockSignals(true);
	ui->m_sbROIId			->blockSignals(true);
	ui->m_sb_expAmpl		->blockSignals(true);
	ui->m_sbNSamples		->blockSignals(true);
	ui->m_xROIs				->blockSignals(true);
	ui->m_yROIs				->blockSignals(true);

	ui->m_sbThresh->blockSignals(true);
	ui->m_sbConvexity->blockSignals(true);
	ui->m_sbCircularity->blockSignals(true);
	ui->m_sbDistBetween->blockSignals(true);
	ui->m_sbMinArea->blockSignals(true);
	ui->m_sbMaxArea->blockSignals(true);

	ui->m_sbSizeControlbuffer	->setEnabled	(!pCLApplet->m_run);
	ui->m_sbBuffer				->setEnabled	(!pCLApplet->m_run);
	ui->m_slBuffer				->setEnabled	(!pCLApplet->m_run);
	ui->m_btnSaveBuffer			->setEnabled	(!pCLApplet->m_run);
	ui->m_btnLoadBuffer			->setEnabled	(!pCLApplet->m_run);

	ui->m_sbImagebufferSaveCount->setEnabled	(!pCLApplet->m_run);

	long size	= pCLApplet->GetRB().GetSize();

	ui->m_sbBuffer->setMinimum		(-size+1);
	ui->m_sbBuffer->setMaximum		(0);
	ui->m_sbBuffer->setSingleStep	(1);
	ui->m_slBuffer->setMinimum		(-size+1);
	ui->m_slBuffer->setMaximum		(0);
	ui->m_slBuffer->setSingleStep	(1);
	ui->m_slBuffer->setPageStep		(10);
	
	
	ui->m_sbThreshold->		setMinimum(-1);
	ui->m_sbThreshold->		setMaximum(256);
	ui->m_sbThreshold->		setValue(g_pFPGA_IFcore->m_CL_Applet->GetThresholdMin());

	ui->m_sbThresh->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetThresh());
	ui->m_sbConvexity->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetConvexity());
	ui->m_sbCircularity->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetCircularity());
	ui->m_sbDistBetween->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetDistBetween());
	ui->m_sbMinArea->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetMinArea());
	ui->m_sbMaxArea->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.GetMaxArea());

	ui->m_sbBuffer->setValue		(num);
	ui->m_slBuffer->setValue		(num);
	
	ui->m_xROIs	->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getTotalX());
	ui->m_yROIs	->setValue(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getTotalY());
	
	static long frmNum, pos;
	frmNum = pCLApplet->GetRB().GetActualImgNum(); // [0..+inf]

	pos = frmNum + num ;	
	slotUpdateGUIImageView(pos);

	ui->m_sbBuffer			->blockSignals(false);
	ui->m_slBuffer			->blockSignals(false);
	ui->m_sbThreshold		->blockSignals(false);		

	ui->m_sbROIWidth		->blockSignals(false);
	ui->m_sbROIHeight		->blockSignals(false);
	ui->m_sbROIId			->blockSignals(false);
	ui->m_xROIs				->blockSignals(false);
	ui->m_yROIs				->blockSignals(false);
	ui->m_sb_expAmpl		->blockSignals(false);
	ui->m_sbNSamples		->blockSignals(false);

	ui->m_sbThresh->blockSignals(false);
	ui->m_sbConvexity->blockSignals(false);
	ui->m_sbCircularity->blockSignals(false);
	ui->m_sbDistBetween->blockSignals(false);
	ui->m_sbMinArea->blockSignals(false);
	ui->m_sbMaxArea->blockSignals(false);


	ui->m_sb_expAmpl		->repaint();
	ui->m_sbNSamples		->repaint();
	ui->m_yROIs				->repaint();
	ui->m_xROIs				->repaint();
	ui->m_sbROIWidth		->repaint();
	ui->m_sbROIHeight		->repaint();
	ui->m_sbROIId			->repaint();
	ui->m_sbBuffer			->repaint();
	ui->m_slBuffer			->repaint();
	ui->m_sbThreshold		->repaint();


	ui->m_sbThresh->repaint();
	ui->m_sbConvexity->repaint();
	ui->m_sbCircularity->repaint();
	ui->m_sbDistBetween->repaint();
	ui->m_sbMinArea->repaint();
	ui->m_sbMaxArea->repaint();
}

//Update the brightness(gain) slider elements for dual tap cams
void FPGA_IFMainWindow::slotUpdateGUIGain		(FPGA_IF::tap tap, long min, long val, long max)
{
	disconnect(ui->m_sbTapGainA,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamTapGain()));
	disconnect(ui->m_sbTapGainB,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamTapGain()));

	ui->m_lTapGainMin->setText	(QString("<%1").arg(min));
	ui->m_lTapGainMax->setText	(QString(">%1").arg(max));

	if (tap == FPGA_IF::tapA)
	{
		ui->m_sbTapGainA->setEnabled	(pCLcamSelected->IsActivalable());
		ui->m_sbTapGainA->setMinimum	(min);
		ui->m_sbTapGainA->setMaximum	(max);
		ui->m_sbTapGainA->setValue		(val);
	}
	if (tap == FPGA_IF::tapB)
	{
		ui->m_sbTapGainB->setEnabled	(pCLcamSelected->IsActivalable());
		ui->m_sbTapGainB->setMinimum	(min);
		ui->m_sbTapGainB->setMaximum	(max);
		ui->m_sbTapGainB->setValue		(val);
	}

	connect(ui->m_sbTapGainA,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamTapGain()));
	connect(ui->m_sbTapGainB,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamTapGain()));

	ui->m_lTapGainMin->repaint();
	ui->m_lTapGainMax->repaint();
	ui->m_sbTapGainA->repaint();
	ui->m_sbTapGainB->repaint();
}

//Update the shutter gui elements
void FPGA_IFMainWindow::slotUpdateGUIShutter(long min, long val, long max)
{
	disconnect(ui->m_slShutter,		SIGNAL(sliderMoved(int)),		this, SLOT(slotCamShutter(int)));
	disconnect(ui->m_slShutter,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamShutter(int)));
	disconnect(ui->m_sbShutter,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamShutter(int)));

	ui->m_sbShutter->setEnabled		(pCLcamSelected->IsActivalable());
	ui->m_slShutter->setEnabled		(pCLcamSelected->IsActivalable());

	ui->m_sbShutter->setMinimum		(min);
	ui->m_sbShutter->setMaximum		(max);
	ui->m_sbShutter->setValue		(val);
	ui->m_sbShutter->setSingleStep	(pCLcamSelected->GetShutterStep_us());
	ui->m_slShutter->setMinimum		(min);
	ui->m_slShutter->setMaximum		(max);
	ui->m_slShutter->setValue		(val);
	ui->m_slShutter->setSingleStep	(pCLcamSelected->GetShutterStep_us());
	ui->m_slShutter->setPageStep	((long)pow(10.,(long)log10((float)pCLcamSelected->GetShutter_us(FPGA_IF::max)))/10);

	connect(ui->m_slShutter,		SIGNAL(sliderMoved(int)),		this, SLOT(slotCamShutter(int)));
	connect(ui->m_slShutter,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamShutter(int)));
	connect(ui->m_sbShutter,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamShutter(int)));

	ui->m_sbShutter->repaint();
	ui->m_slShutter->repaint();
}

//Update the geometry GUI elements - offset main cropped image in X
void FPGA_IFMainWindow::slotUpdateGUIGeometryDX(int val)
{
	disconnect(ui->m_sbOfSetX,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));
	ui->m_sbOfSetX->setValue		(val);
	disconnect(ui->m_sbOfSetX,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));
	connect(ui->m_sbOfSetX,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));
	ui->m_sbOfSetX->repaint();
}

//Update the geometry GUI elements - offset main cropped image in Y
void FPGA_IFMainWindow::slotUpdateGUIGeometryDY(int val)
{
	disconnect(ui->m_sbOfSetY,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetY(int)));
	ui->m_sbOfSetY->setValue		(val);
	disconnect(ui->m_sbOfSetY,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetY(int)));
	connect(ui->m_sbOfSetY,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetY(int)));
	ui->m_sbOfSetY->repaint();
}

//Update the geometry GUI elements - width main cropped image
void FPGA_IFMainWindow::slotUpdateGUIGeometryWX(int val)
{
	disconnect(ui->m_sbWidth,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamWidth(int)));
	ui->m_sbWidth->setValue		(val);
	disconnect(ui->m_sbWidth,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamWidth(int)));
	connect(ui->m_sbWidth,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamWidth(int)));
	ui->m_sbWidth->repaint();
}

//Update the geometry GUI elements - height main cropped image
void FPGA_IFMainWindow::slotUpdateGUIGeometryWY(int val)
{
	disconnect(ui->m_sbHeight,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamHeight(int)));
	ui->m_sbHeight->setValue		(val);
	disconnect(ui->m_sbHeight,	SIGNAL(valueChanged(int)),		this, SLOT(slotCamHeight(int)));
	connect(ui->m_sbHeight,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamHeight(int)));
	ui->m_sbHeight->repaint();
}

//Update the brightness(gain) slider elements
void FPGA_IFMainWindow::slotUpdateGUIBrightness(long min, long val, long max)
{
	disconnect(ui->m_slBrightness,		SIGNAL(sliderMoved(int)),		this, SLOT(slotCamBrightness(int)));
	disconnect(ui->m_slBrightness,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));
	disconnect(ui->m_sbBrightness,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));

	ui->m_slBrightness->setEnabled		(pCLcamSelected->IsActivalable());
	ui->m_sbBrightness->setEnabled		(pCLcamSelected->IsActivalable());

	ui->m_sbBrightness->setMinimum		(min);
	ui->m_sbBrightness->setMaximum		(max);
	ui->m_sbBrightness->setValue		(val);
	ui->m_sbBrightness->setSingleStep	(2);
	ui->m_slBrightness->setMinimum		(min);
	ui->m_slBrightness->setMaximum		(max);
	ui->m_slBrightness->setValue		(val);
	ui->m_slBrightness->setSingleStep	(2);
	
	connect(ui->m_slBrightness,			SIGNAL(sliderMoved(int)),		this, SLOT(slotCamBrightness(int)));
	connect(ui->m_slBrightness,			SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));
	connect(ui->m_sbBrightness,			SIGNAL(valueChanged(int)),		this, SLOT(slotCamBrightness(int)));

	ui->m_slBrightness->repaint();
	ui->m_sbBrightness->repaint();
}

//Update the framerate slider elements
void FPGA_IFMainWindow::slotUpdateGUIFrameRate(long min, long val, long max)
{
	disconnect(ui->m_slFrameRate,		SIGNAL(sliderMoved(int)),		this, SLOT(slotCamFramerate(int)));
	disconnect(ui->m_slFrameRate,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));
	disconnect(ui->m_sbFramerate,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));

	ui->m_slFrameRate->setEnabled		(pCLcamSelected->IsActivalable());
	ui->m_sbFramerate->setEnabled		(pCLcamSelected->IsActivalable());

	ui->m_sbFramerate->setMinimum		(min);
	ui->m_sbFramerate->setMaximum		(max);
	ui->m_sbFramerate->setValue			(val);
	ui->m_sbFramerate->setSingleStep	(2);
	ui->m_slFrameRate->setMinimum		(min);
	ui->m_slFrameRate->setMaximum		(max);
	ui->m_slFrameRate->setValue			(val);
	ui->m_slFrameRate->setSingleStep	(2);
	
	connect(ui->m_slFrameRate,			SIGNAL(sliderMoved(int)),		this, SLOT(slotCamFramerate(int)));
	connect(ui->m_slFrameRate,			SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));
	connect(ui->m_sbFramerate,			SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));

	ui->m_slFrameRate->repaint();
	ui->m_sbFramerate->repaint();
}

//Update the measurement menue according to the current running state of programm
void FPGA_IFMainWindow::slotUpdateGUIFGMeasure		(bool running)
{
	disconnect(ui->m_btnGrabContinuous,	SIGNAL(clicked()), 			this, SLOT(slotFGGrabContinuous	()));
	disconnect(ui->m_btnGrabSingle,		SIGNAL(clicked()), 			this, SLOT(slotFGGrabSingle	()));
	disconnect(ui->m_btnGrabN,			SIGNAL(clicked()), 			this, SLOT(slotFGGrabDur()));
	disconnect(ui->m_btnGrabBuffer,		SIGNAL(clicked()), 			this, SLOT(slotFGGrabBuffer	()));
	ui->m_timeEdit			->blockSignals(true);

	if (running)
	{
		this->ui->m_btnGrabContinuous->setChecked(true);
		if (g_pFPGA_IFcore->m_CL_Applet->GetGrabCount() == -1){
			this->ui->m_btnGrabContinuous->setText(tr("Live Stop"));
		}
		else{
			this->ui->m_btnGrabContinuous->setText(tr("Stop"));
		}
		
		this->ui->m_btnGrabSingle->	setEnabled(false);
		this->ui->m_btnGrabN->	setEnabled(false);	
		this->ui->m_btnGrabBuffer->	setEnabled(false);
		//this->ui->m_sbGrabN->	setEnabled(false);
		this->ui->m_saveMeasure->setEnabled(false);
		this->ui->m_timeEdit->	setEnabled(false);

		this->ui->m_sbOfSetX->	setEnabled(false);
		this->ui->m_sbOfSetY->	setEnabled(false);
		this->ui->m_sbWidth->	setEnabled(false);
		this->ui->m_sbHeight->	setEnabled(false);
		this->ui->m_SetGeometry->setEnabled(false);

	}
	else
	{
		this->ui->m_btnGrabContinuous->setChecked(false);
		this->ui->m_btnGrabContinuous->setText(tr("Live Start"));

		this->ui->m_btnGrabContinuous->	setEnabled(pCLcamSelected->IsActivalable());
		this->ui->m_btnGrabSingle->		setEnabled(true && pCLcamSelected->IsActivalable());
		this->ui->m_btnGrabN->			setEnabled(true && pCLcamSelected->IsActivalable());	
		this->ui->m_btnGrabBuffer->		setEnabled(true && pCLcamSelected->IsActivalable());
		this->ui->m_timeEdit->			setEnabled(true && pCLcamSelected->IsActivalable());

		if (g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->nSamples > 1)
		{
			if (g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_ROISset)
			{
				ui->m_measComp->show();
				this->ui->m_saveMeasure->setEnabled(true);
			}

			if (g_pFPGA_IFcore->m_CL_Applet->GetGrabTime() > 1)
				ui->m_progressBar->setValue(100);
			//else
			//	ui->m_progressBar->setValue(100);
		}

		this->ui->m_sbOfSetX->	setEnabled(true);
		this->ui->m_sbOfSetY->	setEnabled(true);
		this->ui->m_sbWidth->	setEnabled(true);
		this->ui->m_sbHeight->	setEnabled(true);
		this->ui->m_SetGeometry->setEnabled(true);
	}

	
	connect(ui->m_btnGrabContinuous,SIGNAL(clicked()), 			this, SLOT(slotFGGrabContinuous	()));
	connect(ui->m_btnGrabSingle,	SIGNAL(clicked()), 			this, SLOT(slotFGGrabSingle	()));
	connect(ui->m_btnGrabN,			SIGNAL(clicked()), 			this, SLOT(slotFGGrabDur()));
	connect(ui->m_btnGrabBuffer,	SIGNAL(clicked()), 			this, SLOT(slotFGGrabBuffer	()));

	slotUpdateGUIRB(0);
}


//grab only one image
void FPGA_IFMainWindow::slotFGGrabSingle()
{
	ui->m_measComp->hide();
	g_pFPGA_IFcore->m_CL_Applet->GetRB().clearMeasData(false);
	this->PlotData(false);
	if (isCameraRunning())
		stopGrabbing();

	ui->m_progressBar->setValue(0);

	pCLApplet->SetGrabCount(1);
	startGrabbing();
}

//Grab a defined number of images
void FPGA_IFMainWindow::slotFGGrabN()
{
	ui->m_measComp->hide();
	this->PlotData(false);
	g_pFPGA_IFcore->m_CL_Applet->GetRB().clearMeasData(false);
	ui->m_progressBar->setValue(0);
	if (isCameraRunning())
		stopGrabbing();
	//pCLApplet->SetGrabCount(qMax(ui->m_sbGrabN->value(),1));
	startGrabbing();
} 

//Start grabbing images for a predefined duration
void FPGA_IFMainWindow::slotFGGrabDur()
{
	if (isCameraRunning())
		stopGrabbing();

	//delete Data of last measurement
	this->PlotData(false);
	g_pFPGA_IFcore->m_CL_Applet->GetRB().clearMeasData(false);
	ui->m_measComp->hide();

	pCLApplet->SetGrabCount(-1);

	long timeMsec =		ui->m_timeEdit->time().hour()*3600*1000
						+	ui->m_timeEdit->time().minute()*60*1000
						+	ui->m_timeEdit->time().second()*1000;

	ui->m_progressBar->setValue(0);
	pCLApplet->SetGrabTime(timeMsec);
	startGrabbing();
}

//Start grabbing images continously
void FPGA_IFMainWindow::slotFGGrabContinuous()
{
	this->PlotData(false);
	MESSAGE("FPGA_IFMainWindow::slotFGGrabContinuous()");
	ui->m_tabView->setCurrentIndex(0);
	if (isCameraRunning())
	{
		stopGrabbing();
		if (g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_ROISset)
		{
			ui->m_measComp->show();
			ui->m_progressBar->setValue(100);
			this->ui->m_saveMeasure->setEnabled(true);
		}
	}
	else
	{
		pCLApplet->SetGrabCount(-1);
		pCLApplet->SetGrabTime(-1);

		g_pFPGA_IFcore->m_CL_Applet->GetRB().clearMeasData(false);
		startGrabbing();

		ui->m_measComp->hide();
		ui->m_progressBar->setValue(0);
	}
}

//Grab only so many images to fill the buffer once
void FPGA_IFMainWindow::slotFGGrabBuffer()
{
	this->PlotData(false);

	g_pFPGA_IFcore->m_CL_Applet->GetRB().clearMeasData(false);
	if (isCameraRunning())
		stopGrabbing();

	pCLApplet->SetGrabCount(qMax((int)pCLApplet->GetRB().GetSize(),1));
	startGrabbing();
	ui->m_measComp->hide();
	ui->m_progressBar->setValue(0);
}


//Draw image. Liveview, reference view (with/without overlay), live view for one roi only -> increased speed
void FPGA_IFMainWindow::DrawImage(FPGA_IF_Img &img, int index) //0 liveview 1-reference 2
{
	switch (index)
	{
		case  0:
			if(this->m_liveView)
			{
				if(!img.m_ImgDMA0.empty() && !ui->label_Image->isHidden())
				{
					QImage tempImg(static_cast<unsigned char*>(img.m_ImgDMA0.data),(int)img.m_ImgDMA0.cols, (int)img.m_ImgDMA0.rows, (int)img.m_ImgDMA0.step, QImage::Format_Indexed8);
	
					ui->label_Image->setScaledContents(true);
					ui->label_Image->setPixmap(QPixmap::fromImage(tempImg));
				}
				else
					cout << "Image Pointer not valid!" << endl;
			}
			break;
		case  1:
			if(!img.m_DMA0MatRef.empty())
			{
				if(!img.m_DMAInfoMatRef.empty())
				{
					QImage image( img.m_DMAInfoMatRef.data, (int)img.m_DMAInfoMatRef.cols, (int)img.m_DMAInfoMatRef.rows, (int)img.m_DMAInfoMatRef.step, QImage::Format_RGB888 );
					QImage tempImg = image.rgbSwapped();
					QPixmap content = QPixmap::fromImage(tempImg);
					item = RefScene->addPixmap(content);
					this->graphicsView->setScene(RefScene);
				}
				else
				{
					QImage tempImg( img.m_DMA0MatRef.data, (int)img.m_DMA0MatRef.cols, (int)img.m_DMA0MatRef.rows, (int)img.m_DMA0MatRef.step, QImage::Format_RGB888 );
					QPixmap content = QPixmap::fromImage(tempImg);
					item = RefScene->addPixmap(content);
					this->graphicsView->setScene(RefScene);
						//(item,Qt::KeepAspectRatio);
				}
			}
			else
			{
				
				RefScene->clear();
				this->graphicsView->setScene(RefScene);
				cout << "Image Pointer not valid!" << endl;
			}
			break;

		case  2:
			cv::Rect ROI;
			if(1)//this->m_liveView)
			{
				if (!img.m_ImgDMA0.empty() && !ui->label_Image->isHidden() && g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_ROISset && isCameraRunning())
				{
					cv::Mat CurrMat;
					ROI = cv::Rect(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getROIPosGrid(pCLApplet->GetROIId()).x,
								   g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getROIPosGrid(pCLApplet->GetROIId()).y,
								   g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getHeightROI(),
								   g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getWidthROI());
					
					if(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getROI((pCLApplet->GetROIId())).twoCircles)
						CurrMat = img.m_ImgDMA0(ROI).clone();
					else 
					{
						CurrMat = cv::Mat::zeros(ROI.size(),CV_8UC1);
						cv::putText(CurrMat,"Invalid ROI", cv::Point(10, (int)ROI.height/2),1,1,cv::Scalar(255,255,255),1);
					}
					QImage tempImg(static_cast<unsigned char*>(CurrMat.data),(int)CurrMat.cols, (int)CurrMat.rows, (int)CurrMat.step,QImage::Format_Indexed8);
					ui->label_Image_3->setScaledContents(true);
					//tempImg = tempImg.scaled(ui->label_Image_3->size(), Qt::KeepAspectRatio);
					ui->label_Image_3->setPixmap(QPixmap::fromImage(tempImg));
				}
			}
		break;
	}
}

//Clear current reference image
void FPGA_IFMainWindow::slotClearRefImg()
{
	g_pFPGA_IFcore->m_CL_Applet->GetRB().ClearRefImg();
	g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_ROISset = false;
	DrawImage(pCLApplet->GetRB().GetRefImg(),1);
}

//Save ROIS as XML only.Altohough... Probably you would always want to store a reference image instead of ROI positions only
void FPGA_IFMainWindow::slotSaveRois()
{
	QStringList filters;
	filters 	<< "xml files\t\t(*.xml)" ;

	QString path = g_pFPGA_IFcore->m_project.GetPathActive();
	QString	filePath = QDir::fromNativeSeparators(path);
	//MESSAGE2("Filepath for loading ROI file: ", filePath.toStdString());

	QFileDialog dialog	(this);
	dialog.setNameFilters	(filters);
	dialog.selectNameFilter(filters[0]);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setViewMode	(QFileDialog::Detail);
	dialog.setDirectory	(filePath);
	if (!dialog.exec())
		return ;

	QStringList selFile = dialog.selectedFiles();
	QString Filename = selFile[0];
	QDir		dir;

	if (!dir.exists(filePath))
		dir.mkpath(filePath);

	if(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.SaveRois(Filename.toStdString()))
		cout << "Saved current ROIs to "<<  Filename.toStdString() << endl;
	/*
	//Store refimage along with xml ROI data
	QString ImgName = Filename+"_assocRefImg.bmp";
	imwrite(ImgName.toStdString(),pCLApplet->GetRB().GetRefImg().m_DMA0MatRef);
	*/

	this->statusBar()->showMessage("Ready");
}

void FPGA_IFMainWindow::slotLoadRois()
{
	this->statusBar()->showMessage("Ready");
	QStringList filters;
	filters 	<< "xml files\t\t(*.xml)" ;

	QString path = g_pFPGA_IFcore->m_project.GetPathActive();
	QString	filePath = QDir::fromNativeSeparators(path);
	MESSAGE2("Filepath for loading ROI file: ", filePath.toStdString());

	QFileDialog dialog	(this);
	dialog.setNameFilters(filters);
	dialog.selectNameFilter(filters[0]);
	dialog.setAcceptMode	(QFileDialog::AcceptOpen);
	dialog.setViewMode	(QFileDialog::Detail);
	dialog.setDirectory	(filePath);
	dialog.setFileMode	(QFileDialog::ExistingFiles);
	if (!dialog.exec())
		return ;

	QStringList selFile = dialog.selectedFiles();
	QString Filename    = selFile[0];

	g_pFPGA_IFcore->m_CL_Applet->GetRB().ClearRefImg();
	
	g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.setROIs(g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.LoadRois(Filename.toStdString()));
	g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_ROISset = true;

	/*
	QString ImgName = Filename+"_assocRefImg.bmp";
	cv::Mat In = imread(ImgName.toStdString());
	if(In.empty())
		cout << "Associated image not found \n" << endl;
	else
	{
		pCLApplet->GetRB().SetRefImg(In);
		pCLApplet->GetRB().GetRefImg().m_DMAInfoMatRef = g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.m_VisResults(g_pFPGA_IFcore->m_CL_Applet->GetRB().GetRefImg().m_DMA0MatRef,g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myRef.getROIs());
		this->DrawImage(pCLApplet->GetRB().GetRefImg(), 1);
	}
	*/
	this->statusBar()->showMessage("Ready");
}

void FPGA_IFMainWindow::slotSaveMeasure()
{
	this->statusBar()->showMessage("Saving measurement to XML...");
	saveMeasXML();
	ui->m_measComp->hide();
	ui->m_progressBar->setValue(0);
	this->ui->m_saveMeasure->setEnabled(false);
	g_pFPGA_IFcore->m_CL_Applet->GetRB().clearMeasData(false);

	this->statusBar()->showMessage("Ready");
}

//Save the measurement results in XML format
void FPGA_IFMainWindow::saveMeasXML()
{
	
	QString tsmp = QString("%1").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz_"));
	MeasurementData measure = g_pFPGA_IFcore->m_CL_Applet->GetRB().getMeasData();

	QString path = g_pFPGA_IFcore->m_project.GetPath();
	QString Filename = path + "Measurement_" + tsmp + ".xml";
	cv::FileStorage fs(Filename.toStdString(), cv::FileStorage::WRITE);
	QString Header = "MeasurementData_" + tsmp;

	 //unsigned values cannot be saved!
    //First entry has to be a string followed by bracktes to indicate scope of node
	fs << Header.toStdString() << "{";
    fs << "Total_ROIS" << static_cast<int>( measure.nROIS);
    fs << "Total_Samples" << static_cast<int>( measure.nSamples);

	fs <<"Time_Stamps" << "{" ;
		for (int i = 0; i < measure.nSamples; i++)
		{
			string indx = to_string(static_cast<long long>(i));
			string dd = measure.measTstamp[i].toStdString();
			fs << (string("sampleNr") + "_" + indx + "_TimeStamp" ) << dd;
		}
    fs << "}";

    for (int i = 0; i < measure.nROIS; i++)
    {
		string indx = to_string(static_cast<long long>(i));

        fs    << (string("validROI") + "_" + indx) << measure.validROI[i];
        fs    << (string("leftROIImgCoordsx") + "_" + indx)<< measure.leftROIImgCoordsx[i];
        fs    << (string("leftROIImgCoordsy") + "_" + indx)<< measure.leftROIImgCoordsy[i];
        fs    << (string("rightROIImgCoordsx") + "_" + indx) << measure.rightROIImgCoordsx[i];
        fs    << (string("rightROIImgCoordsy") + "_" + indx) << measure.rightROIImgCoordsy[i];
        
        fs << (string("circleL_centROIx") + "_" + indx) << measure.circleL_centROIx[i];
        fs << (string("circleL_centROIy") + "_" + indx) << measure.circleL_centROIy[i];
        fs << (string("circleR_centROIx") + "_" + indx) << measure.circleR_centROIx[i];
        fs << (string("circleR_centROIy") + "_" + indx) << measure.circleR_centROIy[i];
        fs << (string("distance") + "_" + indx) << measure.distance[i];
    }
    fs << "}";

	//After xml file is written delete measurementdata from ram
	pCLApplet->GetRB().clearMeasData(false);
	

}

void FPGA_IFMainWindow::slotPlotAmpl(int ampl)
{
	pCLApplet->SetMaxAmp(ampl);
	int lastn = this->ROIPlot->getSamplesN();
	this->ROIPlot->setMaxDist(pCLApplet->GetMaxAmp());
	int maxY  = ampl;
	std::string yLabel = "Distance[PX]";
	std::string xLabel = "Last n samples";

	ROIPlot->setUpWindow(800,142,50,35,3,3,lastn, yLabel, xLabel, lastn, maxY);
	this->PlotData(false);
	ui->m_sb_expAmpl->repaint();
	ui->m_plotROI->repaint();
}

void FPGA_IFMainWindow::slotPlotN(int n)
{
	pCLApplet->SetNSamples(n);
	this->ROIPlot->setSamplesN(pCLApplet->GetNSamples());
	int maxY  = this->ROIPlot->getMaxDist();

	std::string yLabel = "Distance[PX]";
	std::string xLabel = "Last n samples";

	ROIPlot->setUpWindow(800, 142, 50, 35, 3, 3, pCLApplet->GetNSamples(), yLabel, xLabel, pCLApplet->GetNSamples(), maxY);
	
	this->PlotData(false);
	ui->m_sbNSamples->repaint();
	ui->m_plotROI->repaint();
}

void FPGA_IFMainWindow::PlotData(bool flag)
{
	int index	=	pCLApplet->GetROIId();
	int n		=   g_pFPGA_IFcore->m_CL_Applet->GetRB().getSamples();

	if(flag)
	{
		if(n>1)
		{
			float tmpDist = g_pFPGA_IFcore->m_CL_Applet->GetRB().getDist(index);
			this->ROIPlot->plotData(true, g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distancePlot, index);
		}
	}
	else
		this->ROIPlot->plotData(false, g_pFPGA_IFcore->m_CL_Applet->GetRB().m_myMeasure->distancePlot, index);

	cv::Mat currPlot = this->ROIPlot->getCurrPlot();

	QImage tempImg(static_cast<unsigned char*>(currPlot.data),currPlot.cols, currPlot.rows,QImage::Format_RGB888);
	
	ui->m_plotROI->setScaledContents(false);
	ui->m_plotROI->setPixmap(QPixmap::fromImage(tempImg));
}

void FPGA_IFMainWindow::slotCapRef()
{
	this->statusBar()->showMessage("Capture Reference Image...");
	RefScene->clear();
	this->graphicsView->setScene(RefScene);
	pCLApplet->GetRB().ClearRefImg();

	int num;
	if (isCameraRunning())
	{
		return;
	}
	else
	{
		num = pCLApplet->GetRB().GetActualImgNum()-abs(ui->m_slBuffer->value());
	}

	Mat Input = pCLApplet->GetRB().GetElement(num).m_ImgDMA0;
	
	//QMessageBox::warning(NULL, "No valid image in buffer", "Capture some images to fill buffer first");
	//return;
	
	cvtColor(Input,Input,CV_GRAY2BGR);
	
	FPGA_IF_Img *refPtr = &pCLApplet->GetRB().GetRefImg();
	refPtr->m_ImgDMA0 = Input;
	pCLApplet->GetRB().SetRefImg(refPtr, true);
	this->DrawImage(pCLApplet->GetRB().GetRefImg(),1);
	this->statusBar()->showMessage("Ready");

}

void FPGA_IFMainWindow::slotProjectPathSelect()
{
	QString dir = 
	QFileDialog::getExistingDirectory(this, tr("current project directory"),
                                                ui-> m_ProjectPath->text(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks); 
	if (!dir.isEmpty())
	{
		ui->m_ProjectPath->setText(dir);
		g_pFPGA_IFcore->m_project.SetPath(dir);
	}
}

void FPGA_IFMainWindow::slotProjectPath()
{
	g_pFPGA_IFcore->m_project.SetPath(ui->m_ProjectPath->text());
}

void FPGA_IFMainWindow::slotProjectIniSave()
{
	long timeMsec =		ui->m_timeEdit->time().hour()*3600*1000
						+	ui->m_timeEdit->time().minute()*60*1000
						+	ui->m_timeEdit->time().second()*1000;

	pCLApplet->SetGrabTime(timeMsec);

	FPGA_IFIniSelectionWindow iniSelectionWindow("SAVE");
	int nSelWindowRet = iniSelectionWindow.exec();

	if(nSelWindowRet && !iniSelectionWindow.getSelectedIni().isEmpty())
	{
		ui->m_ProjectInifile->setText(iniSelectionWindow.getSelectedIni());
		g_pFPGA_IFcore->m_project.SetPathIni(iniSelectionWindow.getSelectedIni());

		g_pFPGA_IFcore->WriteIni();
		g_pFPGA_IFcore->m_ini.writeFPGA_IFIni(iniSelectionWindow.getSelectedIni());
	}
}

void FPGA_IFMainWindow::slotProjectIniLoad(QString iniFilePath)
{
	if( g_pFPGA_IFcore->SelectIniFile() ){
		ui->m_ProjectInifile->setText(g_pFPGA_IFcore->m_ini.m_ini_filename);
		g_pFPGA_IFcore->ReadIni();
	}
}

void FPGA_IFMainWindow::slotCamShutter(int value)
{
	pCLcamSelected->SetShutter_us(value);
	pCLApplet->SetTrigger(true);
}


//Update GUI elements of project settings
void FPGA_IFMainWindow::slotUpdateGUIProject		()
{
	ui->m_ProjectInifile		->	blockSignals(true);	
	ui->m_ProjectPath			->	blockSignals(true);		
	ui->m_ProjectUser			->	blockSignals(true);		
	ui->m_ProjectUser_2			->	blockSignals(true);	
	ui->m_ProjectComment		->	blockSignals(true);	

	ui->m_Project_praxis		->	blockSignals(true);	
	ui->m_Project_Einzelmessung	->	blockSignals(true);

	ui->m_ProjectInifile		->	setText(g_pFPGA_IFcore->m_ini.m_ini_filename);
	ui->m_ProjectPath			->	setText(g_pFPGA_IFcore->m_project.GetPath());		
	ui->m_ProjectUser			->	setText(g_pFPGA_IFcore->m_project.GetUser1());
	ui->m_ProjectUser_2			->	setText(g_pFPGA_IFcore->m_project.GetUser2());
	
	ui->m_ProjectComment		->	setPlainText(g_pFPGA_IFcore->m_project.GetComment());
	ui->m_Project_Einzelmessung	->	setChecked(g_pFPGA_IFcore->m_project.GetMeasuremode() != FPGA_IF::manual);

	ui->m_ProjectInifile		->	blockSignals(false);	
	ui->m_ProjectPath			->	blockSignals(false);		
	ui->m_ProjectUser			->	blockSignals(false);		
	ui->m_ProjectUser_2			->	blockSignals(false);	
	ui->m_ProjectComment		->	blockSignals(false);	
	ui->m_Project_praxis		->	blockSignals(false);	
	ui->m_Project_Einzelmessung	->	blockSignals(false);
}

//Automatic or manual measurement?
void FPGA_IFMainWindow::slotProjectMessungTyp()
{
	if (ui->m_Project_praxis->isChecked())
		g_pFPGA_IFcore->m_project.SetMeasuremode(FPGA_IF::manual);
	else
		g_pFPGA_IFcore->m_project.SetMeasuremode(FPGA_IF::automatic);
}

void FPGA_IFMainWindow::slotProjectOK_Save	()
{
	// save
	slotFGBufferSave();
}

void FPGA_IFMainWindow::slotProjectComment	()
{
	g_pFPGA_IFcore->m_project.SetComment(ui->m_ProjectComment->toPlainText());

	// Validate comment text length to inform about too long text by red label text
	if( ui->m_ProjectComment->toPlainText().length() >= 130 )
	{
		ui->labelComment->setText("<font color='red'>Kommentar</font>");
	}
	else ui->labelComment->setText("<font color='black'>Kommentar</font>");
	
	ui->labelComment->setText("<font color='black'>Kommentar</font>");
}

//Set user info
void FPGA_IFMainWindow::slotProjectUser1	()
{
	g_pFPGA_IFcore->m_project.SetUser1(ui->m_ProjectUser->text());
}
//----------------------------------------------------------------

void FPGA_IFMainWindow::slotProjectUser2	()
{
	g_pFPGA_IFcore->m_project.SetUser2(ui->m_ProjectUser_2->text());
}

void FPGA_IFMainWindow::slotReferenceImageClear()
{
	pCLApplet->GetRB().ClearRefImg();
	RefScene->clear();
	this->graphicsView->setScene(RefScene);
}

void FPGA_IFMainWindow::slotReferenceImageShow			(bool value)
{
	if (!value)
		return;

	this->DrawImage(pCLApplet->GetRB().GetRefImg(),0);
}

void FPGA_IFMainWindow::slotLiveImageShow			(bool value)
{
	if (!value)
		return;

	this->DrawImage(pCLApplet->GetRB().GetLatestElement(),0);
	this->DrawImage(pCLApplet->GetRB().GetLatestElement(),2);
}

void FPGA_IFMainWindow::slotFGBufferLoad()
{
	this->statusBar()->showMessage("Load Buffer...");
	//QMessageBox::warning(NULL, "Not implemented yet", "Load as opencv mat!");
	QStringList filters;
	filters 	<< "Bitmap files\t\t(*.bmp)"
				<< "Portable Network files\t(*.png)"
				<< "TIFF files\t\t(*.tif)"
			/*<< "JPEG files\t\t(*.jpg)"
			<< "Portable Network files\t(*.png)"
			<< "TIFF files\t\t(*.tif)"*/;

	QString path = g_pFPGA_IFcore->m_project.GetPathActive();
	QString	filePath = QDir::fromNativeSeparators(path);
	MESSAGE2("Filepath for loading images: ", filePath.toStdString());

	QFileDialog dialog	(this);
	dialog.setNameFilters(filters);
	dialog.selectNameFilter(filters[0]);
	dialog.setAcceptMode	(QFileDialog::AcceptOpen);
	dialog.setViewMode	(QFileDialog::Detail);
	dialog.setDirectory	(filePath);
	dialog.setFileMode	(QFileDialog::ExistingFiles);
	if (!dialog.exec())
	{
		this->statusBar()->showMessage("Ready");
		return;
	}

	QStringList fileNamelist = dialog.selectedFiles();

	long imgcount = fileNamelist.count();
	if (!imgcount)
	{
		this->statusBar()->showMessage("Ready");
		return;
	}
		

	QString fname = fileNamelist[0];
		//#ifdef loadbuffer
	cv::Mat img = cv::imread(fname.toStdString());

	// generate ini file path out of saved images
	QFileInfo fInfo(fname);
	QString inifName = fInfo.absoluteFilePath().remove(fInfo.fileName()) + fInfo.baseName().mid(3, 23) + "__INI.ini";
	fInfo.setFile(inifName);

	bool reallocateCam = false;
	LPoint newImageSize = LPoint(img.rows, img.cols);
	//LPoint newImageSize = LPoint(img.data()->width(), img.data()->height());
	LPoint sensorSize = g_pFPGA_IFcore->GetpCamSelected()->GetSensorSize_px();
	LPoint difference = LPoint(sensorSize.x - newImageSize.x, sensorSize.y - newImageSize.y);

	if( img.rows != g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y ||
	    img.cols != g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x )
	{
		    int ret = QMessageBox::question(this, tr("Differing image size!"),
                                tr("The images you're trying to load have\n"
                                   "a differing image size to the camera!\n\n"
				   "Do you want to reallocate the camera?"),
				   QMessageBox::Ok | QMessageBox::Cancel);
		    if( ret == QMessageBox::Cancel )
			{
			    MESSAGE("Load images canceled!");
				this->statusBar()->showMessage("Ready");
			    return;
		    }
		    reallocateCam = true;
	}

	if( reallocateCam == true ){
		if( difference.x >= 0 || difference.y >= 0 ){
			slotCamActive(false);
						  
			g_pFPGA_IFcore->m_CL_Applet->DeInit();

			// Setup new camera parameters & calculate ideal offset	position
			g_pFPGA_IFcore->GetpCamSelected()->SetImageOffset(LPoint(0,0));
			g_pFPGA_IFcore->GetpCamSelected()->SetImageSize(newImageSize);
			g_pFPGA_IFcore->GetpCamSelected()->SetImageOffset(LPoint(difference.x/2 - 1,difference.y/2 - 1));

			//this->slotReferenceImageClear();
			/*
			if( fInfo.exists() == true ){
				//MESSAGE2("iniFName: ", inifName.toStdString());
				this->slotProjectIniLoad(inifName);
			}*/

			g_pFPGA_IFcore->m_CL_Applet->Init();

			slotCamActive(true);
		}
		else{
			MESSAGE("Camera alloctaion is not possible: The new image size is not supported!");
			QMessageBox::warning(this,"Reallocate Camera failed!",QString("The wanted image size is not supported!"));
			this->statusBar()->showMessage("Ready");
			return;
		}
	}

	QProgressDialog progress("Read images to buffer...", "Abort", 0, imgcount, this);
	progress.setWindowModality(Qt::WindowModal);
	progress.setMinimumDuration(0);
	
	// realloc RB
	pCLApplet->SetImageBuffer(imgcount);

	for (int frmnum = 0; frmnum < imgcount; frmnum++)
	{
		QString fname = fileNamelist[frmnum];
		cv::Mat img = cv::imread(fname.toStdString(),0);

		unsigned char * pData = (unsigned char *)img.data;
		int sizePData = sizeof(unsigned char) * img.rows * img.cols;
		memcpy((&pCLApplet->GetRB().GetElement(frmnum))->m_ImgDMA0.data, pData, sizePData);// = readBMP(fileNamelist[frmnum].toStdString(),0,0);
		progress.setValue(frmnum+1);
		if (progress.wasCanceled())
			break;
	}

	g_pFPGA_IFcore->m_CL_Applet->GetRB().SetActualImgNum(imgcount);
	g_pFPGA_IFcore->slotUpdateInternalData();
	this->statusBar()->showMessage("Ready");
	return;
}

//Save current image buffer
void FPGA_IFMainWindow::slotFGBufferSave()
{
	this->statusBar()->showMessage("Save Buffer...");
	Ringbuffer* rb =  &pCLApplet->GetRB();

	QString		filePath;
	ofstream	file;
	QChar		chr = '0';
	QString		fn;
	QDir		dir;
	QString		tsmp = QString("%1").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz_"));

	QProgressDialog progress("Write Buffer to disk...", "Abort", 0, rb->GetSize(), this);
	progress.setWindowModality(Qt::WindowModal);
	progress.setMinimumDuration(0);

	int count = 0;
	if (!count)
		count = ui->m_sbImagebufferSaveCount->value();
	if (!count)
		return ;
	if (count > (int)rb->GetSize())
		count = rb->GetSize();

	filePath = g_pFPGA_IFcore->m_project.GetPathActive();

	cout << "Filepath for saving buffers: " << filePath.toStdString() << "\n";

	if (!dir.exists(filePath))
		dir.mkpath(filePath);

	long act = rb->GetActualImgNum()-1;


	// referenz image data
	fn = filePath + tsmp + "_Referenz";
	// allways save Refimage
	cv::Mat refImgTmp = cv::Mat(cv::Size(g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x, g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y),CV_8UC1);
	refImgTmp.data= 	pCLApplet->GetRB().GetRefImg().m_ImgDMA0.data;
	if(!refImgTmp.empty())
	{
		imwrite((fn+".bmp").toStdString().c_str(),refImgTmp);
	}

	// all other image data
	for (int imgNr = act - count+1, i=0; imgNr <= act; imgNr++, i++)
	{
		fn = filePath + tsmp;
		fn += QString("_%1").arg(imgNr - (act - count+1), 5, 10, chr);


		cv::Mat refImgTmp	= cv::Mat(cv::Size(g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.x, g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size.y),CV_8UC1);
		refImgTmp.data		= 	rb->GetElement(imgNr).m_ImgDMA0.data;

		// write Image
		imwrite((fn+".bmp").toStdString().c_str(),refImgTmp);

		// write ROIs
		//rb->GetElement(imgNr).SaveCOGs(fn + ".cog");

		progress.setValue(i);

		if (progress.wasCanceled())
			break;
	}
	// write inifile to project path
	{
		fn = filePath + tsmp + "_INI.ini";
		g_pFPGA_IFcore->WriteIni();
		g_pFPGA_IFcore->m_ini.writeFPGA_IFIni(fn);
	}
	//debug() << "Save Buffer... ready!\n";
	this->statusBar()->showMessage("Ready");

	return ;
}

void FPGA_IFMainWindow::slotFGAverageImages(int value)
{
	cout << "Average: " << (1 << value) << endl;
}


void FPGA_IFMainWindow::slotFGThreshold	(int value)
{
	//ui->m_sbThreshold->setValue(g_pFPGA_IFcore->m_CL_Applet->GetThresholdMin());
	pCLApplet->SetThresholdMin(value); 

	this->statusBar()->showMessage("Calculating Threshold");

	if (!pCLApplet->GetRB().GetRefImg().m_DMAInfoMatRef.empty() && pCLApplet->GetRB().m_myRef.m_ROISset)
	{
		pCLApplet->GetRB().UpdateInfoView(pCLApplet->GetRB().m_myRef.m_threshPreview(pCLApplet->GetRB().GetRefImg().m_DMA0MatRef, pCLApplet->GetRB().m_myRef.getROIs(), value));
		pCLApplet->GetRB().UpdateInfoView(pCLApplet->GetRB().m_myRef.m_VisResults(pCLApplet->GetRB().GetRefImg().m_DMAInfoMatRef, pCLApplet->GetRB().m_myRef.getROIs(), value));
	}

	this->statusBar()->showMessage("Ready");

	this->DrawImage(pCLApplet->GetRB().GetRefImg(), 1);
	ui->m_tabView->setCurrentIndex(1);

}

//Set width of the ROIs with respect to limitations of the framgrabber
void FPGA_IFMainWindow::slotFGROIWidth	(int value)
{
	int modulo = g_pFPGA_IFcore->m_CL_Applet->GetModulo();
	int sizeX = value;
	if (sizeX >  MAXFPGAROISIZEX) sizeX = MAXFPGAROISIZEX;
	if (sizeX < 4) sizeX= 4;
	if (sizeX % modulo != 0) sizeX -= sizeX % modulo;
	pCLApplet->SetROIWidth(sizeX);
	//g_pFPGA_IFcore->slotUpdateInternalData();
	ui->m_sbROIWidth->setValue(sizeX);
	ui->m_sbROIWidth->repaint();
}

//Set height of the ROIs with respect to limitations of the framgrabber
void FPGA_IFMainWindow::slotFGROIHeight	(int value)
{

	int modulo = g_pFPGA_IFcore->m_CL_Applet->GetModulo();
	int sizeY = value;
	if (sizeY >  MAXFPGAROISIZEY) sizeY = MAXFPGAROISIZEY;
	if (sizeY < 4) sizeY = 4;
	if (sizeY % modulo != 0) sizeY -= sizeY % modulo;

	pCLApplet->SetROIHeight(sizeY);
	//g_pFPGA_IFcore->slotUpdateInternalData();
	ui->m_sbROIHeight->setValue(sizeY);
	ui->m_sbROIHeight->repaint();
}

//Set number of ROI to be displayed individually
void FPGA_IFMainWindow::slotFGROIId	(int value)
{
	pCLApplet->SetROIId(value);
	//this->ROIPlot->emptySampleList();
	if (pCLApplet->GetRB().m_myMeasure->distancePlot.size()>0)
		pCLApplet->GetRB().m_myMeasure->distancePlot[value].clear();
	this->PlotData(false);
}

//Set number of ROIS along x direction
void FPGA_IFMainWindow::slotFGROISx	(int value)
{
	if(pCLApplet->GetRB().m_myRef.getTotalY() * value > __MAX_ROIPAIRS__)
	{
		QMessageBox msgBox;
		msgBox.setText("Total of cells must not exceed 48!");
		msgBox.exec();
		int newVal = __MAX_ROIPAIRS__/pCLApplet->GetRB().m_myRef.getTotalY();
		ui->m_xROIs->setValue(newVal);
		ui->m_xROIs->repaint();
		pCLApplet->GetRB().m_myRef.setTotalX(newVal);
	}
	else
	{
		pCLApplet->GetRB().m_myRef.setTotalX(value);
		ui->m_xROIs->setValue(value);
		ui->m_xROIs->repaint();
	}
}


//Set number of ROIS along y direction
void FPGA_IFMainWindow::slotFGROISy	(int value)
{
	if(pCLApplet->GetRB().m_myRef.getTotalX() * value > __MAX_ROIPAIRS__)
	{
		QMessageBox msgBox;
		msgBox.setText("Total of cells must not exceed 48!");
		msgBox.exec();
		int newVal = __MAX_ROIPAIRS__/pCLApplet->GetRB().m_myRef.getTotalX();
		ui->m_yROIs->setValue(newVal);
		ui->m_yROIs->repaint();
		pCLApplet->GetRB().m_myRef.setTotalY(newVal);
	}
	else
	{
		pCLApplet->GetRB().m_myRef.setTotalY(value);
		ui->m_yROIs->setValue(value);
		ui->m_yROIs->repaint();
	}
}

//Update GAIN for multi tap cameras
void FPGA_IFMainWindow::slotCamBrightness(int value)
{
	//pCLcamSelected->m_gain = value;
	pCLcamSelected->SetGlobGain(val, value);
	g_pFPGA_IFcore->slotUpdateInternalData();
	//pCLcamSelected->SetTapGain(FPGA_IF::tapA, pCLcamSelected->m_gain);
	//pCLcamSelected->SetTapGain(FPGA_IF::tapB, pCLcamSelected->m_gain);
}

//Set the targeted framerate
void FPGA_IFMainWindow::slotCamFramerate(int value)
{

	disconnect(ui->m_slFrameRate,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));
	disconnect(ui->m_sbFramerate,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));

	pCLcamSelected->SetFramerate(value,val);
	//g_pFPGA_IFcore->slotUpdateInternalData();

	connect(ui->m_slFrameRate,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));
	connect(ui->m_sbFramerate,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamFramerate(int)));
}

//Offset of cropped image in x direction
void FPGA_IFMainWindow::slotCamOffsetX(int value)
{
	int modulo = __MODULO_MIKROTRON_DX_;
	int size = value;
	if (__MAX_MIKROTRON__ < pCLcamSelected->GetImageSize_px().x + size) size = __MAX_MIKROTRON__ - pCLcamSelected->GetImageSize_px().x;
	if (size < __MODULO_MIKROTRON_DX_ ) size = 0;
	if (size % modulo != 0) size -= size % modulo;
	
	disconnect(ui->m_sbOfSetX,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));

	LPoint curr;
	curr.x = size;
	curr.y = pCLcamSelected->GetImageOffset_px().y;

	pCLcamSelected->SetImageOffset(curr);
	//g_pFPGA_IFcore->slotUpdateInternalData();

	ui->m_sbOfSetX->setValue(size);
	ui->m_sbOfSetX->repaint();

	connect(ui->m_sbOfSetX,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));
}

//Offset of cropped image in y direction
void FPGA_IFMainWindow::slotCamOffsetY(int value)
{
	int modulo = __MODULO_MIKROTRON_Y_;
	int size = value;
	if (__MAX_MIKROTRON__ < pCLcamSelected->GetImageSize_px().y + size) size = __MAX_MIKROTRON__ - pCLcamSelected->GetImageSize_px().y;
	if (size < __MODULO_MIKROTRON_Y_ ) size = 0;
	if (size % modulo != 0) size -= size % modulo;

	disconnect(ui->m_sbOfSetY,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));

	LPoint curr;
	curr.x = pCLcamSelected->GetImageOffset_px().x;
	curr.y = size;

	pCLcamSelected->SetImageOffset(curr);
	//g_pFPGA_IFcore->slotUpdateInternalData();

	ui->m_sbOfSetY->setValue(size);
	ui->m_sbOfSetY->repaint();

	connect(ui->m_sbOfSetX,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamOffsetX(int)));
}

//Dimension of cropped image in x direction with respect to limitations of applet
void FPGA_IFMainWindow::slotCamWidth(int value)
{
	int modulo = __MODULO_MIKROTRON_W_;
	int size = value;
	if (__MAX_MIKROTRON__ < pCLcamSelected->GetImageOffset_px().x + size) size = __MAX_MIKROTRON__ - pCLcamSelected->GetImageOffset_px().x;
	if (size < __MODULO_MIKROTRON_W_) size = __MODULO_MIKROTRON_W_;
	if (size % modulo != 0) size -= size % modulo;

	disconnect(ui->m_sbWidth,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamWidth(int)));
	LPoint curr;
	curr.x = size;
	curr.y = pCLcamSelected->GetImageSize_px().y;
	pCLcamSelected->SetImageSize(curr);
	//g_pFPGA_IFcore->slotUpdateInternalData();

	ui->m_sbWidth->setValue(size);
	ui->m_sbWidth->repaint();

	connect(ui->m_sbWidth,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamWidth(int)));
}

//Dimension of cropped image in y direction with respect to limitations of applet
void FPGA_IFMainWindow::slotCamHeight(int value)
{
	int modulo = __MODULO_MIKROTRON_Y_;
	int size = value;
	if (__MAX_MIKROTRON__ < pCLcamSelected->GetImageOffset_px().y + size) size = __MAX_MIKROTRON__ - pCLcamSelected->GetImageOffset_px().y;
	if (size < __MODULO_MIKROTRON_Y_) size = __MODULO_MIKROTRON_Y_;
	if (size % modulo != 0) size -= size % modulo;

	disconnect(ui->m_sbHeight,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamHeight(int)));
	LPoint curr;
	curr.x = pCLcamSelected->GetImageSize_px().x;
	curr.y = size;
	pCLcamSelected->SetImageSize(curr);

	ui->m_sbHeight->setValue(size);
	ui->m_sbHeight->repaint();

	connect(ui->m_sbHeight,		SIGNAL(valueChanged(int)),		this, SLOT(slotCamHeight(int)));
}

//Tap offset for dual tap cams
void FPGA_IFMainWindow::slotCamTapOffset()
{
	pCLcamSelected->SetTapOffset(FPGA_IF::tapA, ui->m_sbTapOffsetA->value());
	pCLcamSelected->SetTapOffset(FPGA_IF::tapB, ui->m_sbTapOffsetB->value());
	//g_pFPGA_IFcore->slotUpdateInternalData();
}

//TRiggermode - not implemented 
void FPGA_IFMainWindow::slotFGTriggerMode(bool swt)
{
	pCLApplet->		SetTriggerMode(swt ? TrgPortArea::ExternSw_Trigger : TrgPortArea::GrabberControlled);
	//slotUpdateGUITriggerMode		(pCLApplet->GetTriggerMode());
}

//Statusbar - not implemented 
void FPGA_IFMainWindow::createStatusBar()
{
	this->statusBar()->showMessage(tr("ready"));
	this->statusBar()->setStyleSheet("background-color: rgb(230,230,230);");
}

//reallocate data structures for new image size
void FPGA_IFMainWindow::slotRefreshImgSize()
{
	MESSAGE("ReAlloc Applet with new size");

	g_pFPGA_IFcore->m_CL_Applet->m_DMA[0].sdma.size = pCLcamSelected->GetImageSize_px();
	g_pFPGA_IFcore->m_CL_Applet->SetImageBuffer(g_pFPGA_IFcore->m_CL_Applet->GetRB().GetBufferCount2Use());

	g_pFPGA_IFcore->slotUpdateInternalData();

	//slotCamActive(true);
}

//Live view active?
void FPGA_IFMainWindow::slotLiveView(bool act)
{
	this->m_liveView=act;
}

//Set values for blob analysis
	void FPGA_IFMainWindow::slotFGThresh(int value)
	{
		pCLApplet->GetRB().m_myRef.SetThresh(value);
	}
	void FPGA_IFMainWindow::slotFGConvexity(int value)
	{
		pCLApplet->GetRB().m_myRef.SetConvexity(value);
	}
	void FPGA_IFMainWindow::slotFGCircularity(int value)
	{
 		pCLApplet->GetRB().m_myRef.SetCircularity(value);
	}
	void FPGA_IFMainWindow::slotFGDistBetween(int value)
	{
		pCLApplet->GetRB().m_myRef.SetDistBetween(value);
	}
	void FPGA_IFMainWindow::slotFGMinArea(int value)
	{
		pCLApplet->GetRB().m_myRef.SetMinArea(value);
	}
	void FPGA_IFMainWindow::slotFGMaxArea(int value)
	{
		pCLApplet->GetRB().m_myRef.SetMaxArea(value);
	}