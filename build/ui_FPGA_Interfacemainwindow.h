/********************************************************************************
** Form generated from reading UI file 'FPGA_Interfacemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FPGA_INTERFACEMAINWINDOW_H
#define UI_FPGA_INTERFACEMAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FPGA_InterfaceMainWindow
{
public:
    QAction *action_Open_IniFile;
    QAction *actionNew_Measurement;
    QAction *action_Save_Current_Settings;
    QWidget *centralwidget;
    QFrame *line;
    QGroupBox *groupBox;
    QGroupBox *groupBox_5;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_5;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_24;
    QLabel *label_25;
    QSpinBox *m_sbROIId;
    QLabel *label_22;
    QSpinBox *m_sb_expAmpl;
    QSpinBox *m_sbNSamples;
    QFrame *frame;
    QLabel *m_plotROI;
    QGroupBox *groupBox_4;
    QTabWidget *m_tabView;
    QWidget *widget;
    QLabel *label_Image;
    QWidget *tab_2;
    QGraphicsView *graphicsView;
    QWidget *tab;
    QLabel *label_Image_3;
    QProgressBar *m_progressBar;
    QLabel *m_measComp;
    QGroupBox *groupBox_7;
    QTabWidget *tabWidget;
    QWidget *m_tabAllgemein;
    QGroupBox *groupBox_Project;
    QGridLayout *gridLayout;
    QLineEdit *m_ProjectInifile;
    QPushButton *m_ProjectIniLoad;
    QPushButton *m_ProjectIniSave;
    QGroupBox *groupBox_Path;
    QHBoxLayout *_2;
    QLineEdit *m_ProjectPath;
    QToolButton *m_ProjectPath_btn;
    QGroupBox *groupBox_Type;
    QHBoxLayout *_3;
    QRadioButton *m_Project_praxis;
    QRadioButton *m_Project_Einzelmessung;
    QGroupBox *groupBox_Person;
    QLabel *label_45;
    QLabel *label_46;
    QLabel *label;
    QLineEdit *m_ProjectUser;
    QLineEdit *m_ProjectUser_2;
    QLabel *labelComment;
    QTextEdit *m_ProjectComment;
    QPushButton *m_ProjectOK;
    QWidget *m_tabKamera;
    QLabel *label_5;
    QComboBox *m_cbCameraName;
    QLabel *label_6;
    QComboBox *m_cbBoard;
    QComboBox *m_cbPort;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *m_eSensortype;
    QLabel *label_9;
    QLineEdit *m_eNumberTaps;
    QGroupBox *groupBox_6;
    QGroupBox *groupBox_3;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *m_lTapGainMin;
    QLabel *m_lTapGainMax;
    QSpinBox *m_sbTapGainA;
    QSpinBox *m_sbTapGainB;
    QGroupBox *groupBox_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *m_lTapOffsetMin;
    QLabel *m_lTapOffsetMax;
    QSpinBox *m_sbTapOffsetA;
    QSpinBox *m_sbTapOffsetB;
    QCheckBox *m_cbCameraActive;
    QGroupBox *groupBox_OptionalCamParam;
    QGroupBox *groupBox_8;
    QWidget *gridLayoutWidget_7;
    QGridLayout *gridLayout_7;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_31;
    QLabel *label_32;
    QSpinBox *m_sbOfSetX;
    QSpinBox *m_sbOfSetY;
    QSpinBox *m_sbWidth;
    QSpinBox *m_sbHeight;
    QPushButton *m_SetGeometry;
    QGroupBox *groupBox_9;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayoutSettings;
    QLabel *label_15;
    QLabel *label_73;
    QLabel *label_23;
    QSlider *m_slBrightness;
    QSlider *m_slFrameRate;
    QSpinBox *m_sbShutter;
    QSpinBox *m_sbFramerate;
    QSpinBox *m_sbBrightness;
    QSlider *m_slShutter;
    QCheckBox *m_cbLive;
    QWidget *m_tabAnzAusw;
    QGroupBox *groupBox_RB;
    QFrame *line_14;
    QLabel *label_38;
    QSpinBox *m_sbSizeControlbuffer;
    QSlider *m_slBuffer;
    QSpinBox *m_sbBuffer;
    QFrame *line_16;
    QFrame *line_18;
    QLabel *m_lframeNum;
    QLabel *m_lFramerate;
    QSpinBox *m_sbThreshold;
    QLabel *label_100;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_29;
    QLabel *m_lTimestamp;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_6;
    QPushButton *m_btnGrabContinuous;
    QPushButton *m_btnGrabN;
    QPushButton *m_btnGrabSingle;
    QPushButton *m_btnGrabBuffer;
    QTimeEdit *m_timeEdit;
    QPushButton *m_saveMeasure;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_btnLoadBuffer;
    QPushButton *m_btnSaveBuffer;
    QLabel *label_86;
    QSpinBox *m_sbImagebufferSaveCount;
    QGroupBox *groupBox_Info;
    QLabel *m_lPegel;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_88;
    QLabel *label_98;
    QLabel *label_99;
    QSpacerItem *horizontalSpacer;
    QLabel *label_16;
    QLabel *label_14;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *m_sbROIHeight;
    QSpinBox *m_sbROIWidth;
    QSpinBox *m_yROIs;
    QSpinBox *m_xROIs;
    QLabel *label_2;
    QTabWidget *tabWidget_2;
    QWidget *AcquireRef;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_4;
    QPushButton *m_btn_RefImg_load;
    QPushButton *m_btn_Calc_ROIs;
    QPushButton *m_btn_Cap_Ref;
    QPushButton *m_btn_RefImg_clear;
    QPushButton *m_saveRois;
    QPushButton *m_loadRois;
    QWidget *tab_4;
    QWidget *gridLayoutWidget_8;
    QGridLayout *gridLayout_8;
    QLabel *label_37;
    QSpinBox *m_sbMaxArea;
    QSpinBox *m_sbDistBetween;
    QSpinBox *m_sbMinArea;
    QLabel *label_39;
    QLabel *label_35;
    QLabel *label_30;
    QLabel *label_89;
    QLabel *label_103;
    QLabel *label_34;
    QLabel *label_101;
    QSpinBox *m_sbThresh;
    QLabel *label_26;
    QSpinBox *m_sbCircularity;
    QSpinBox *m_sbConvexity;
    QLabel *label_21;
    QLabel *label_33;
    QLabel *label_36;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_3;
    QFrame *line_2;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *FPGA_InterfaceMainWindow)
    {
        if (FPGA_InterfaceMainWindow->objectName().isEmpty())
            FPGA_InterfaceMainWindow->setObjectName(QStringLiteral("FPGA_InterfaceMainWindow"));
        FPGA_InterfaceMainWindow->setEnabled(true);
        FPGA_InterfaceMainWindow->resize(1173, 896);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FPGA_InterfaceMainWindow->sizePolicy().hasHeightForWidth());
        FPGA_InterfaceMainWindow->setSizePolicy(sizePolicy);
        FPGA_InterfaceMainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        action_Open_IniFile = new QAction(FPGA_InterfaceMainWindow);
        action_Open_IniFile->setObjectName(QStringLiteral("action_Open_IniFile"));
        actionNew_Measurement = new QAction(FPGA_InterfaceMainWindow);
        actionNew_Measurement->setObjectName(QStringLiteral("actionNew_Measurement"));
        action_Save_Current_Settings = new QAction(FPGA_InterfaceMainWindow);
        action_Save_Current_Settings->setObjectName(QStringLiteral("action_Save_Current_Settings"));
        centralwidget = new QWidget(FPGA_InterfaceMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(766, 35, 20, 591));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 662, 1131, 181));
        groupBox_5 = new QGroupBox(groupBox);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(830, 20, 281, 151));
        groupBox_5->setMouseTracking(true);
        groupBox_5->setAcceptDrops(true);
        gridLayoutWidget_5 = new QWidget(groupBox_5);
        gridLayoutWidget_5->setObjectName(QStringLiteral("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(10, 20, 261, 121));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_18 = new QLabel(gridLayoutWidget_5);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_5->addWidget(label_18, 0, 2, 1, 1);

        label_19 = new QLabel(gridLayoutWidget_5);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_5->addWidget(label_19, 1, 2, 1, 1);

        label_20 = new QLabel(gridLayoutWidget_5);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_5->addWidget(label_20, 2, 2, 1, 1);

        label_24 = new QLabel(gridLayoutWidget_5);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_5->addWidget(label_24, 1, 4, 1, 1);

        label_25 = new QLabel(gridLayoutWidget_5);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_5->addWidget(label_25, 2, 4, 1, 1);

        m_sbROIId = new QSpinBox(gridLayoutWidget_5);
        m_sbROIId->setObjectName(QStringLiteral("m_sbROIId"));
        m_sbROIId->setMaximum(47);

        gridLayout_5->addWidget(m_sbROIId, 0, 3, 1, 1);

        label_22 = new QLabel(gridLayoutWidget_5);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_5->addWidget(label_22, 0, 4, 1, 1);

        m_sb_expAmpl = new QSpinBox(gridLayoutWidget_5);
        m_sb_expAmpl->setObjectName(QStringLiteral("m_sb_expAmpl"));

        gridLayout_5->addWidget(m_sb_expAmpl, 1, 3, 1, 1);

        m_sbNSamples = new QSpinBox(gridLayoutWidget_5);
        m_sbNSamples->setObjectName(QStringLiteral("m_sbNSamples"));

        gridLayout_5->addWidget(m_sbNSamples, 2, 3, 1, 1);

        frame = new QFrame(groupBox);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 22, 805, 147));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        m_plotROI = new QLabel(frame);
        m_plotROI->setObjectName(QStringLiteral("m_plotROI"));
        m_plotROI->setGeometry(QRect(2, 2, 801, 143));
        m_plotROI->setMargin(0);
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 20, 741, 620));
        groupBox_4->setMaximumSize(QSize(741, 620));
        m_tabView = new QTabWidget(groupBox_4);
        m_tabView->setObjectName(QStringLiteral("m_tabView"));
        m_tabView->setGeometry(QRect(10, 30, 722, 568));
        sizePolicy.setHeightForWidth(m_tabView->sizePolicy().hasHeightForWidth());
        m_tabView->setSizePolicy(sizePolicy);
        m_tabView->setMinimumSize(QSize(722, 568));
        m_tabView->setMaximumSize(QSize(722, 568));
        widget = new QWidget();
        widget->setObjectName(QStringLiteral("widget"));
        label_Image = new QLabel(widget);
        label_Image->setObjectName(QStringLiteral("label_Image"));
        label_Image->setGeometry(QRect(0, 0, 716, 544));
        label_Image->setMinimumSize(QSize(716, 539));
        label_Image->setMaximumSize(QSize(716, 544));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush2(QColor(255, 255, 220, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush1);
        label_Image->setPalette(palette);
        label_Image->setCursor(QCursor(Qt::CrossCursor));
        label_Image->setMargin(1);
        m_tabView->addTab(widget, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        graphicsView = new QGraphicsView(tab_2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 716, 542));
        graphicsView->setMouseTracking(true);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
        m_tabView->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_Image_3 = new QLabel(tab);
        label_Image_3->setObjectName(QStringLiteral("label_Image_3"));
        label_Image_3->setGeometry(QRect(0, 0, 716, 544));
        label_Image_3->setMinimumSize(QSize(716, 544));
        label_Image_3->setMaximumSize(QSize(716, 544));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush1);
        label_Image_3->setPalette(palette1);
        label_Image_3->setCursor(QCursor(Qt::CrossCursor));
        label_Image_3->setMargin(1);
        m_tabView->addTab(tab, QString());
        m_progressBar = new QProgressBar(groupBox_4);
        m_progressBar->setObjectName(QStringLiteral("m_progressBar"));
        m_progressBar->setEnabled(true);
        m_progressBar->setGeometry(QRect(12, 599, 716, 16));
        m_progressBar->setValue(0);
        m_progressBar->setTextVisible(false);
        m_measComp = new QLabel(groupBox_4);
        m_measComp->setObjectName(QStringLiteral("m_measComp"));
        m_measComp->setEnabled(true);
        m_measComp->setGeometry(QRect(320, 596, 151, 20));
        groupBox_7 = new QGroupBox(centralwidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(790, 20, 361, 620));
        groupBox_7->setMaximumSize(QSize(361, 620));
        tabWidget = new QTabWidget(groupBox_7);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(15, 30, 331, 581));
        tabWidget->setFocusPolicy(Qt::WheelFocus);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(true);
        m_tabAllgemein = new QWidget();
        m_tabAllgemein->setObjectName(QStringLiteral("m_tabAllgemein"));
        groupBox_Project = new QGroupBox(m_tabAllgemein);
        groupBox_Project->setObjectName(QStringLiteral("groupBox_Project"));
        groupBox_Project->setGeometry(QRect(10, 10, 301, 86));
        groupBox_Project->setMinimumSize(QSize(286, 0));
        groupBox_Project->setMaximumSize(QSize(350, 16777215));
        gridLayout = new QGridLayout(groupBox_Project);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_ProjectInifile = new QLineEdit(groupBox_Project);
        m_ProjectInifile->setObjectName(QStringLiteral("m_ProjectInifile"));
        m_ProjectInifile->setEnabled(true);
        m_ProjectInifile->setReadOnly(true);

        gridLayout->addWidget(m_ProjectInifile, 0, 0, 1, 2);

        m_ProjectIniLoad = new QPushButton(groupBox_Project);
        m_ProjectIniLoad->setObjectName(QStringLiteral("m_ProjectIniLoad"));

        gridLayout->addWidget(m_ProjectIniLoad, 1, 0, 1, 1);

        m_ProjectIniSave = new QPushButton(groupBox_Project);
        m_ProjectIniSave->setObjectName(QStringLiteral("m_ProjectIniSave"));

        gridLayout->addWidget(m_ProjectIniSave, 1, 1, 1, 1);

        groupBox_Path = new QGroupBox(m_tabAllgemein);
        groupBox_Path->setObjectName(QStringLiteral("groupBox_Path"));
        groupBox_Path->setGeometry(QRect(10, 100, 301, 56));
        groupBox_Path->setMinimumSize(QSize(286, 0));
        groupBox_Path->setMaximumSize(QSize(350, 16777215));
        _2 = new QHBoxLayout(groupBox_Path);
        _2->setObjectName(QStringLiteral("_2"));
        m_ProjectPath = new QLineEdit(groupBox_Path);
        m_ProjectPath->setObjectName(QStringLiteral("m_ProjectPath"));

        _2->addWidget(m_ProjectPath);

        m_ProjectPath_btn = new QToolButton(groupBox_Path);
        m_ProjectPath_btn->setObjectName(QStringLiteral("m_ProjectPath_btn"));

        _2->addWidget(m_ProjectPath_btn);

        groupBox_Type = new QGroupBox(m_tabAllgemein);
        groupBox_Type->setObjectName(QStringLiteral("groupBox_Type"));
        groupBox_Type->setGeometry(QRect(10, 160, 301, 43));
        groupBox_Type->setMinimumSize(QSize(286, 0));
        groupBox_Type->setMaximumSize(QSize(350, 16777215));
        groupBox_Type->setFlat(false);
        groupBox_Type->setCheckable(false);
        groupBox_Type->setChecked(false);
        _3 = new QHBoxLayout(groupBox_Type);
        _3->setObjectName(QStringLiteral("_3"));
        _3->setContentsMargins(-1, 3, -1, 3);
        m_Project_praxis = new QRadioButton(groupBox_Type);
        m_Project_praxis->setObjectName(QStringLiteral("m_Project_praxis"));

        _3->addWidget(m_Project_praxis);

        m_Project_Einzelmessung = new QRadioButton(groupBox_Type);
        m_Project_Einzelmessung->setObjectName(QStringLiteral("m_Project_Einzelmessung"));
        m_Project_Einzelmessung->setChecked(true);

        _3->addWidget(m_Project_Einzelmessung);

        groupBox_Person = new QGroupBox(m_tabAllgemein);
        groupBox_Person->setObjectName(QStringLiteral("groupBox_Person"));
        groupBox_Person->setGeometry(QRect(10, 210, 301, 281));
        groupBox_Person->setMinimumSize(QSize(286, 0));
        groupBox_Person->setMaximumSize(QSize(308, 16777215));
        label_45 = new QLabel(groupBox_Person);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(70, 21, 99, 21));
        label_46 = new QLabel(groupBox_Person);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(175, 21, 99, 21));
        label = new QLabel(groupBox_Person);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 45, 54, 20));
        m_ProjectUser = new QLineEdit(groupBox_Person);
        m_ProjectUser->setObjectName(QStringLiteral("m_ProjectUser"));
        m_ProjectUser->setGeometry(QRect(70, 45, 99, 20));
        m_ProjectUser_2 = new QLineEdit(groupBox_Person);
        m_ProjectUser_2->setObjectName(QStringLiteral("m_ProjectUser_2"));
        m_ProjectUser_2->setGeometry(QRect(175, 45, 99, 20));
        labelComment = new QLabel(groupBox_Person);
        labelComment->setObjectName(QStringLiteral("labelComment"));
        labelComment->setGeometry(QRect(10, 70, 54, 131));
        m_ProjectComment = new QTextEdit(groupBox_Person);
        m_ProjectComment->setObjectName(QStringLiteral("m_ProjectComment"));
        m_ProjectComment->setGeometry(QRect(70, 70, 204, 136));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_ProjectComment->sizePolicy().hasHeightForWidth());
        m_ProjectComment->setSizePolicy(sizePolicy1);
        m_ProjectComment->setFocusPolicy(Qt::WheelFocus);
        m_ProjectComment->setAutoFillBackground(false);
        m_ProjectComment->setAutoFormatting(QTextEdit::AutoBulletList);
        m_ProjectComment->setTabChangesFocus(true);
        m_ProjectComment->setLineWrapMode(QTextEdit::WidgetWidth);
        m_ProjectComment->setAcceptRichText(false);
        m_ProjectOK = new QPushButton(groupBox_Person);
        m_ProjectOK->setObjectName(QStringLiteral("m_ProjectOK"));
        m_ProjectOK->setGeometry(QRect(10, 220, 264, 38));
        tabWidget->addTab(m_tabAllgemein, QString());
        m_tabKamera = new QWidget();
        m_tabKamera->setObjectName(QStringLiteral("m_tabKamera"));
        label_5 = new QLabel(m_tabKamera);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(12, 12, 134, 20));
        m_cbCameraName = new QComboBox(m_tabKamera);
        m_cbCameraName->setObjectName(QStringLiteral("m_cbCameraName"));
        m_cbCameraName->setGeometry(QRect(50, 12, 251, 20));
        label_6 = new QLabel(m_tabKamera);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(11, 41, 31, 20));
        m_cbBoard = new QComboBox(m_tabKamera);
        m_cbBoard->setObjectName(QStringLiteral("m_cbBoard"));
        m_cbBoard->setGeometry(QRect(50, 41, 69, 20));
        m_cbPort = new QComboBox(m_tabKamera);
        m_cbPort->setObjectName(QStringLiteral("m_cbPort"));
        m_cbPort->setGeometry(QRect(170, 41, 69, 20));
        label_7 = new QLabel(m_tabKamera);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(146, 41, 30, 20));
        label_8 = new QLabel(m_tabKamera);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(11, 70, 49, 20));
        m_eSensortype = new QLineEdit(m_tabKamera);
        m_eSensortype->setObjectName(QStringLiteral("m_eSensortype"));
        m_eSensortype->setEnabled(false);
        m_eSensortype->setGeometry(QRect(66, 72, 41, 16));
        m_eSensortype->setMouseTracking(false);
        m_eSensortype->setFocusPolicy(Qt::NoFocus);
        m_eSensortype->setFrame(false);
        label_9 = new QLabel(m_tabKamera);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(112, 70, 22, 20));
        m_eNumberTaps = new QLineEdit(m_tabKamera);
        m_eNumberTaps->setObjectName(QStringLiteral("m_eNumberTaps"));
        m_eNumberTaps->setEnabled(false);
        m_eNumberTaps->setGeometry(QRect(140, 72, 21, 16));
        sizePolicy.setHeightForWidth(m_eNumberTaps->sizePolicy().hasHeightForWidth());
        m_eNumberTaps->setSizePolicy(sizePolicy);
        m_eNumberTaps->setFocusPolicy(Qt::NoFocus);
        m_eNumberTaps->setMaxLength(1);
        m_eNumberTaps->setFrame(false);
        groupBox_6 = new QGroupBox(m_tabKamera);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setEnabled(true);
        groupBox_6->setGeometry(QRect(10, 410, 301, 91));
        groupBox_6->setFlat(false);
        groupBox_6->setCheckable(false);
        groupBox_3 = new QGroupBox(groupBox_6);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(150, 15, 131, 66));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(5, 20, 16, 16));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(5, 45, 16, 16));
        m_lTapGainMin = new QLabel(groupBox_3);
        m_lTapGainMin->setObjectName(QStringLiteral("m_lTapGainMin"));
        m_lTapGainMin->setGeometry(QRect(80, 20, 45, 16));
        m_lTapGainMax = new QLabel(groupBox_3);
        m_lTapGainMax->setObjectName(QStringLiteral("m_lTapGainMax"));
        m_lTapGainMax->setGeometry(QRect(80, 40, 45, 16));
        m_sbTapGainA = new QSpinBox(groupBox_3);
        m_sbTapGainA->setObjectName(QStringLiteral("m_sbTapGainA"));
        m_sbTapGainA->setGeometry(QRect(20, 15, 61, 22));
        m_sbTapGainA->setWrapping(true);
        m_sbTapGainA->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbTapGainA->setAccelerated(true);
        m_sbTapGainA->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbTapGainB = new QSpinBox(groupBox_3);
        m_sbTapGainB->setObjectName(QStringLiteral("m_sbTapGainB"));
        m_sbTapGainB->setGeometry(QRect(20, 40, 61, 22));
        m_sbTapGainB->setWrapping(true);
        m_sbTapGainB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbTapGainB->setAccelerated(true);
        m_sbTapGainB->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        groupBox_2 = new QGroupBox(groupBox_6);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(5, 15, 131, 66));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(5, 20, 16, 16));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(5, 45, 16, 16));
        m_lTapOffsetMin = new QLabel(groupBox_2);
        m_lTapOffsetMin->setObjectName(QStringLiteral("m_lTapOffsetMin"));
        m_lTapOffsetMin->setGeometry(QRect(80, 20, 45, 16));
        m_lTapOffsetMax = new QLabel(groupBox_2);
        m_lTapOffsetMax->setObjectName(QStringLiteral("m_lTapOffsetMax"));
        m_lTapOffsetMax->setGeometry(QRect(80, 40, 45, 16));
        m_sbTapOffsetA = new QSpinBox(groupBox_2);
        m_sbTapOffsetA->setObjectName(QStringLiteral("m_sbTapOffsetA"));
        m_sbTapOffsetA->setGeometry(QRect(20, 15, 61, 22));
        m_sbTapOffsetA->setWrapping(true);
        m_sbTapOffsetA->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbTapOffsetA->setAccelerated(true);
        m_sbTapOffsetA->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbTapOffsetB = new QSpinBox(groupBox_2);
        m_sbTapOffsetB->setObjectName(QStringLiteral("m_sbTapOffsetB"));
        m_sbTapOffsetB->setGeometry(QRect(20, 40, 61, 22));
        m_sbTapOffsetB->setWrapping(true);
        m_sbTapOffsetB->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbTapOffsetB->setAccelerated(true);
        m_sbTapOffsetB->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_cbCameraActive = new QCheckBox(m_tabKamera);
        m_cbCameraActive->setObjectName(QStringLiteral("m_cbCameraActive"));
        m_cbCameraActive->setGeometry(QRect(260, 42, 51, 19));
        groupBox_OptionalCamParam = new QGroupBox(m_tabKamera);
        groupBox_OptionalCamParam->setObjectName(QStringLiteral("groupBox_OptionalCamParam"));
        groupBox_OptionalCamParam->setGeometry(QRect(10, 100, 301, 301));
        groupBox_8 = new QGroupBox(groupBox_OptionalCamParam);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 160, 281, 131));
        gridLayoutWidget_7 = new QWidget(groupBox_8);
        gridLayoutWidget_7->setObjectName(QStringLiteral("gridLayoutWidget_7"));
        gridLayoutWidget_7->setGeometry(QRect(10, 20, 261, 71));
        gridLayout_7 = new QGridLayout(gridLayoutWidget_7);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label_27 = new QLabel(gridLayoutWidget_7);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_7->addWidget(label_27, 0, 0, 1, 1);

        label_28 = new QLabel(gridLayoutWidget_7);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_7->addWidget(label_28, 1, 0, 1, 1);

        label_31 = new QLabel(gridLayoutWidget_7);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout_7->addWidget(label_31, 0, 2, 1, 1);

        label_32 = new QLabel(gridLayoutWidget_7);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_7->addWidget(label_32, 1, 2, 1, 1);

        m_sbOfSetX = new QSpinBox(gridLayoutWidget_7);
        m_sbOfSetX->setObjectName(QStringLiteral("m_sbOfSetX"));
        m_sbOfSetX->setWrapping(true);
        m_sbOfSetX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbOfSetX->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_sbOfSetX->setAccelerated(true);
        m_sbOfSetX->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbOfSetX->setMaximum(5120);
        m_sbOfSetX->setSingleStep(64);
        m_sbOfSetX->setValue(0);

        gridLayout_7->addWidget(m_sbOfSetX, 0, 1, 1, 1);

        m_sbOfSetY = new QSpinBox(gridLayoutWidget_7);
        m_sbOfSetY->setObjectName(QStringLiteral("m_sbOfSetY"));
        m_sbOfSetY->setWrapping(true);
        m_sbOfSetY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbOfSetY->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_sbOfSetY->setAccelerated(true);
        m_sbOfSetY->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbOfSetY->setMaximum(5120);
        m_sbOfSetY->setSingleStep(2);
        m_sbOfSetY->setValue(0);

        gridLayout_7->addWidget(m_sbOfSetY, 0, 3, 1, 1);

        m_sbWidth = new QSpinBox(gridLayoutWidget_7);
        m_sbWidth->setObjectName(QStringLiteral("m_sbWidth"));
        m_sbWidth->setWrapping(true);
        m_sbWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbWidth->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_sbWidth->setAccelerated(true);
        m_sbWidth->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbWidth->setMinimum(128);
        m_sbWidth->setMaximum(5120);
        m_sbWidth->setSingleStep(64);
        m_sbWidth->setValue(5120);

        gridLayout_7->addWidget(m_sbWidth, 1, 1, 1, 1);

        m_sbHeight = new QSpinBox(gridLayoutWidget_7);
        m_sbHeight->setObjectName(QStringLiteral("m_sbHeight"));
        m_sbHeight->setWrapping(true);
        m_sbHeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbHeight->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_sbHeight->setAccelerated(true);
        m_sbHeight->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbHeight->setMinimum(2);
        m_sbHeight->setMaximum(5120);
        m_sbHeight->setSingleStep(2);
        m_sbHeight->setValue(5120);

        gridLayout_7->addWidget(m_sbHeight, 1, 3, 1, 1);

        m_SetGeometry = new QPushButton(groupBox_8);
        m_SetGeometry->setObjectName(QStringLiteral("m_SetGeometry"));
        m_SetGeometry->setGeometry(QRect(10, 100, 261, 23));
        groupBox_9 = new QGroupBox(groupBox_OptionalCamParam);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(10, 20, 281, 131));
        gridLayoutWidget = new QWidget(groupBox_9);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 261, 99));
        gridLayoutSettings = new QGridLayout(gridLayoutWidget);
        gridLayoutSettings->setObjectName(QStringLiteral("gridLayoutSettings"));
        gridLayoutSettings->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayoutSettings->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(gridLayoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayoutSettings->addWidget(label_15, 0, 0, 1, 1);

        label_73 = new QLabel(gridLayoutWidget);
        label_73->setObjectName(QStringLiteral("label_73"));

        gridLayoutSettings->addWidget(label_73, 1, 0, 1, 1);

        label_23 = new QLabel(gridLayoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayoutSettings->addWidget(label_23, 2, 0, 1, 1);

        m_slBrightness = new QSlider(gridLayoutWidget);
        m_slBrightness->setObjectName(QStringLiteral("m_slBrightness"));
        m_slBrightness->setPageStep(1);
        m_slBrightness->setOrientation(Qt::Horizontal);

        gridLayoutSettings->addWidget(m_slBrightness, 1, 1, 1, 1);

        m_slFrameRate = new QSlider(gridLayoutWidget);
        m_slFrameRate->setObjectName(QStringLiteral("m_slFrameRate"));
        m_slFrameRate->setOrientation(Qt::Horizontal);

        gridLayoutSettings->addWidget(m_slFrameRate, 2, 1, 1, 1);

        m_sbShutter = new QSpinBox(gridLayoutWidget);
        m_sbShutter->setObjectName(QStringLiteral("m_sbShutter"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_sbShutter->sizePolicy().hasHeightForWidth());
        m_sbShutter->setSizePolicy(sizePolicy2);
        m_sbShutter->setWrapping(true);
        m_sbShutter->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbShutter->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_sbShutter->setAccelerated(true);
        m_sbShutter->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbShutter->setMaximum(1000000);
        m_sbShutter->setValue(1);

        gridLayoutSettings->addWidget(m_sbShutter, 0, 2, 1, 1);

        m_sbFramerate = new QSpinBox(gridLayoutWidget);
        m_sbFramerate->setObjectName(QStringLiteral("m_sbFramerate"));
        sizePolicy2.setHeightForWidth(m_sbFramerate->sizePolicy().hasHeightForWidth());
        m_sbFramerate->setSizePolicy(sizePolicy2);
        m_sbFramerate->setWrapping(true);
        m_sbFramerate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbFramerate->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_sbFramerate->setAccelerated(true);
        m_sbFramerate->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbFramerate->setMaximum(8888888);
        m_sbFramerate->setValue(1);

        gridLayoutSettings->addWidget(m_sbFramerate, 2, 2, 1, 1);

        m_sbBrightness = new QSpinBox(gridLayoutWidget);
        m_sbBrightness->setObjectName(QStringLiteral("m_sbBrightness"));
        sizePolicy2.setHeightForWidth(m_sbBrightness->sizePolicy().hasHeightForWidth());
        m_sbBrightness->setSizePolicy(sizePolicy2);
        m_sbBrightness->setLayoutDirection(Qt::LeftToRight);
        m_sbBrightness->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbBrightness->setMaximum(4);

        gridLayoutSettings->addWidget(m_sbBrightness, 1, 2, 1, 1);

        m_slShutter = new QSlider(gridLayoutWidget);
        m_slShutter->setObjectName(QStringLiteral("m_slShutter"));
        m_slShutter->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(84);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_slShutter->sizePolicy().hasHeightForWidth());
        m_slShutter->setSizePolicy(sizePolicy3);
        m_slShutter->setMinimumSize(QSize(84, 0));
        m_slShutter->setOrientation(Qt::Horizontal);

        gridLayoutSettings->addWidget(m_slShutter, 0, 1, 1, 1);

        m_cbLive = new QCheckBox(m_tabKamera);
        m_cbLive->setObjectName(QStringLiteral("m_cbLive"));
        m_cbLive->setGeometry(QRect(180, 72, 111, 17));
        tabWidget->addTab(m_tabKamera, QString());
        m_tabAnzAusw = new QWidget();
        m_tabAnzAusw->setObjectName(QStringLiteral("m_tabAnzAusw"));
        groupBox_RB = new QGroupBox(m_tabAnzAusw);
        groupBox_RB->setObjectName(QStringLiteral("groupBox_RB"));
        groupBox_RB->setGeometry(QRect(10, 7, 301, 249));
        groupBox_RB->setAutoFillBackground(false);
        line_14 = new QFrame(groupBox_RB);
        line_14->setObjectName(QStringLiteral("line_14"));
        line_14->setGeometry(QRect(5, 90, 281, 16));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);
        label_38 = new QLabel(groupBox_RB);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(206, 10, 53, 20));
        m_sbSizeControlbuffer = new QSpinBox(groupBox_RB);
        m_sbSizeControlbuffer->setObjectName(QStringLiteral("m_sbSizeControlbuffer"));
        m_sbSizeControlbuffer->setGeometry(QRect(204, 30, 70, 20));
        m_sbSizeControlbuffer->setMinimumSize(QSize(70, 0));
        m_sbSizeControlbuffer->setWrapping(true);
        m_sbSizeControlbuffer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbSizeControlbuffer->setAccelerated(true);
        m_sbSizeControlbuffer->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbSizeControlbuffer->setKeyboardTracking(false);
        m_sbSizeControlbuffer->setMaximum(1000000);
        m_sbSizeControlbuffer->setValue(1000000);
        m_slBuffer = new QSlider(groupBox_RB);
        m_slBuffer->setObjectName(QStringLiteral("m_slBuffer"));
        m_slBuffer->setGeometry(QRect(7, 52, 191, 16));
        m_slBuffer->setOrientation(Qt::Horizontal);
        m_sbBuffer = new QSpinBox(groupBox_RB);
        m_sbBuffer->setObjectName(QStringLiteral("m_sbBuffer"));
        m_sbBuffer->setGeometry(QRect(204, 50, 70, 20));
        m_sbBuffer->setMinimumSize(QSize(70, 0));
        m_sbBuffer->setWrapping(true);
        m_sbBuffer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbBuffer->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        m_sbBuffer->setAccelerated(true);
        m_sbBuffer->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        m_sbBuffer->setMaximum(8888888);
        m_sbBuffer->setValue(1234567);
        line_16 = new QFrame(groupBox_RB);
        line_16->setObjectName(QStringLiteral("line_16"));
        line_16->setGeometry(QRect(5, 163, 281, 16));
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);
        line_18 = new QFrame(groupBox_RB);
        line_18->setObjectName(QStringLiteral("line_18"));
        line_18->setGeometry(QRect(5, 210, 281, 16));
        line_18->setFrameShape(QFrame::HLine);
        line_18->setFrameShadow(QFrame::Sunken);
        m_lframeNum = new QLabel(groupBox_RB);
        m_lframeNum->setObjectName(QStringLiteral("m_lframeNum"));
        m_lframeNum->setGeometry(QRect(100, 19, 95, 15));
        m_lframeNum->setMinimumSize(QSize(90, 15));
        m_lframeNum->setMaximumSize(QSize(95, 15));
        QFont font;
        font.setFamily(QStringLiteral("MS Shell Dlg 2"));
        m_lframeNum->setFont(font);
        m_lframeNum->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_lFramerate = new QLabel(groupBox_RB);
        m_lFramerate->setObjectName(QStringLiteral("m_lFramerate"));
        m_lFramerate->setGeometry(QRect(85, 35, 110, 15));
        m_lFramerate->setMinimumSize(QSize(90, 15));
        m_lFramerate->setMaximumSize(QSize(110, 15));
        m_lFramerate->setFont(font);
        m_lFramerate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbThreshold = new QSpinBox(groupBox_RB);
        m_sbThreshold->setObjectName(QStringLiteral("m_sbThreshold"));
        m_sbThreshold->setGeometry(QRect(209, 222, 71, 20));
        m_sbThreshold->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        m_sbThreshold->setMinimum(0);
        m_sbThreshold->setMaximum(100);
        label_100 = new QLabel(groupBox_RB);
        label_100->setObjectName(QStringLiteral("label_100"));
        label_100->setGeometry(QRect(10, 222, 211, 20));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_100->setFont(font1);
        label_3 = new QLabel(groupBox_RB);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 19, 46, 13));
        label_4 = new QLabel(groupBox_RB);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 35, 61, 16));
        horizontalLayoutWidget = new QWidget(groupBox_RB);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 70, 271, 21));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 5, 0, 0);
        label_29 = new QLabel(horizontalLayoutWidget);
        label_29->setObjectName(QStringLiteral("label_29"));

        horizontalLayout->addWidget(label_29);

        m_lTimestamp = new QLabel(horizontalLayoutWidget);
        m_lTimestamp->setObjectName(QStringLiteral("m_lTimestamp"));
        m_lTimestamp->setFont(font);

        horizontalLayout->addWidget(m_lTimestamp);

        gridLayoutWidget_6 = new QWidget(groupBox_RB);
        gridLayoutWidget_6->setObjectName(QStringLiteral("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(10, 100, 271, 61));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        m_btnGrabContinuous = new QPushButton(gridLayoutWidget_6);
        m_btnGrabContinuous->setObjectName(QStringLiteral("m_btnGrabContinuous"));
        m_btnGrabContinuous->setCheckable(true);
        m_btnGrabContinuous->setChecked(false);

        gridLayout_6->addWidget(m_btnGrabContinuous, 0, 0, 1, 1);

        m_btnGrabN = new QPushButton(gridLayoutWidget_6);
        m_btnGrabN->setObjectName(QStringLiteral("m_btnGrabN"));
        m_btnGrabN->setCheckable(false);
        m_btnGrabN->setChecked(false);

        gridLayout_6->addWidget(m_btnGrabN, 1, 0, 1, 1);

        m_btnGrabSingle = new QPushButton(gridLayoutWidget_6);
        m_btnGrabSingle->setObjectName(QStringLiteral("m_btnGrabSingle"));

        gridLayout_6->addWidget(m_btnGrabSingle, 0, 1, 1, 1);

        m_btnGrabBuffer = new QPushButton(gridLayoutWidget_6);
        m_btnGrabBuffer->setObjectName(QStringLiteral("m_btnGrabBuffer"));

        gridLayout_6->addWidget(m_btnGrabBuffer, 0, 2, 1, 1);

        m_timeEdit = new QTimeEdit(gridLayoutWidget_6);
        m_timeEdit->setObjectName(QStringLiteral("m_timeEdit"));
        m_timeEdit->setMaximumTime(QTime(5, 0, 0));
        m_timeEdit->setMinimumTime(QTime(0, 0, 10));
        m_timeEdit->setCurrentSection(QDateTimeEdit::SecondSection);
        m_timeEdit->setDisplayFormat(QStringLiteral("HH:mm:ss"));
        m_timeEdit->setCurrentSectionIndex(2);
        m_timeEdit->setTime(QTime(0, 0, 10));

        gridLayout_6->addWidget(m_timeEdit, 1, 1, 1, 1);

        m_saveMeasure = new QPushButton(gridLayoutWidget_6);
        m_saveMeasure->setObjectName(QStringLiteral("m_saveMeasure"));
        m_saveMeasure->setEnabled(true);
        m_saveMeasure->setCheckable(false);
        m_saveMeasure->setAutoDefault(false);

        gridLayout_6->addWidget(m_saveMeasure, 1, 2, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(groupBox_RB);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 180, 271, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_btnLoadBuffer = new QPushButton(horizontalLayoutWidget_2);
        m_btnLoadBuffer->setObjectName(QStringLiteral("m_btnLoadBuffer"));

        horizontalLayout_2->addWidget(m_btnLoadBuffer);

        m_btnSaveBuffer = new QPushButton(horizontalLayoutWidget_2);
        m_btnSaveBuffer->setObjectName(QStringLiteral("m_btnSaveBuffer"));

        horizontalLayout_2->addWidget(m_btnSaveBuffer);

        label_86 = new QLabel(horizontalLayoutWidget_2);
        label_86->setObjectName(QStringLiteral("label_86"));

        horizontalLayout_2->addWidget(label_86);

        m_sbImagebufferSaveCount = new QSpinBox(horizontalLayoutWidget_2);
        m_sbImagebufferSaveCount->setObjectName(QStringLiteral("m_sbImagebufferSaveCount"));
        m_sbImagebufferSaveCount->setMinimumSize(QSize(40, 0));

        horizontalLayout_2->addWidget(m_sbImagebufferSaveCount);

        groupBox_Info = new QGroupBox(m_tabAnzAusw);
        groupBox_Info->setObjectName(QStringLiteral("groupBox_Info"));
        groupBox_Info->setGeometry(QRect(10, 446, 301, 101));
        groupBox_Info->setAutoFillBackground(false);
        m_lPegel = new QLabel(groupBox_Info);
        m_lPegel->setObjectName(QStringLiteral("m_lPegel"));
        m_lPegel->setGeometry(QRect(40, 70, 96, 16));
        m_lPegel->setFont(font);
        m_lPegel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gridLayoutWidget_2 = new QWidget(groupBox_Info);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(67, 190, 160, 80));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_3 = new QWidget(groupBox_Info);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 20, 281, 74));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_88 = new QLabel(gridLayoutWidget_3);
        label_88->setObjectName(QStringLiteral("label_88"));
        label_88->setMinimumSize(QSize(0, 15));
        label_88->setMaximumSize(QSize(80, 15));

        gridLayout_3->addWidget(label_88, 2, 0, 1, 1);

        label_98 = new QLabel(gridLayoutWidget_3);
        label_98->setObjectName(QStringLiteral("label_98"));
        label_98->setMinimumSize(QSize(0, 15));
        label_98->setMaximumSize(QSize(90, 15));

        gridLayout_3->addWidget(label_98, 0, 0, 1, 1);

        label_99 = new QLabel(gridLayoutWidget_3);
        label_99->setObjectName(QStringLiteral("label_99"));
        label_99->setMinimumSize(QSize(0, 15));
        label_99->setMaximumSize(QSize(60, 15));

        gridLayout_3->addWidget(label_99, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);

        label_16 = new QLabel(gridLayoutWidget_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_3->addWidget(label_16, 0, 5, 1, 1);

        label_14 = new QLabel(gridLayoutWidget_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_3->addWidget(label_14, 1, 5, 1, 1);

        label_17 = new QLabel(gridLayoutWidget_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_3->addWidget(label_17, 2, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 2, 1, 1, 1);

        m_sbROIHeight = new QSpinBox(gridLayoutWidget_3);
        m_sbROIHeight->setObjectName(QStringLiteral("m_sbROIHeight"));
        m_sbROIHeight->setMinimum(4);
        m_sbROIHeight->setMaximum(256);
        m_sbROIHeight->setSingleStep(4);
        m_sbROIHeight->setValue(128);

        gridLayout_3->addWidget(m_sbROIHeight, 1, 4, 1, 1);

        m_sbROIWidth = new QSpinBox(gridLayoutWidget_3);
        m_sbROIWidth->setObjectName(QStringLiteral("m_sbROIWidth"));
        m_sbROIWidth->setMinimum(4);
        m_sbROIWidth->setMaximum(256);
        m_sbROIWidth->setSingleStep(4);
        m_sbROIWidth->setValue(256);

        gridLayout_3->addWidget(m_sbROIWidth, 0, 4, 1, 1);

        m_yROIs = new QSpinBox(gridLayoutWidget_3);
        m_yROIs->setObjectName(QStringLiteral("m_yROIs"));

        gridLayout_3->addWidget(m_yROIs, 2, 4, 1, 1);

        m_xROIs = new QSpinBox(gridLayoutWidget_3);
        m_xROIs->setObjectName(QStringLiteral("m_xROIs"));

        gridLayout_3->addWidget(m_xROIs, 2, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 2, 3, 1, 1);

        tabWidget_2 = new QTabWidget(m_tabAnzAusw);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setEnabled(true);
        tabWidget_2->setGeometry(QRect(11, 264, 301, 179));
        tabWidget_2->setAutoFillBackground(false);
        tabWidget_2->setTabPosition(QTabWidget::North);
        AcquireRef = new QWidget();
        AcquireRef->setObjectName(QStringLiteral("AcquireRef"));
        gridLayoutWidget_4 = new QWidget(AcquireRef);
        gridLayoutWidget_4->setObjectName(QStringLiteral("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(10, 10, 281, 141));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_4->setContentsMargins(0, 0, 6, 0);
        m_btn_RefImg_load = new QPushButton(gridLayoutWidget_4);
        m_btn_RefImg_load->setObjectName(QStringLiteral("m_btn_RefImg_load"));

        gridLayout_4->addWidget(m_btn_RefImg_load, 0, 0, 1, 1);

        m_btn_Calc_ROIs = new QPushButton(gridLayoutWidget_4);
        m_btn_Calc_ROIs->setObjectName(QStringLiteral("m_btn_Calc_ROIs"));

        gridLayout_4->addWidget(m_btn_Calc_ROIs, 1, 0, 1, 1);

        m_btn_Cap_Ref = new QPushButton(gridLayoutWidget_4);
        m_btn_Cap_Ref->setObjectName(QStringLiteral("m_btn_Cap_Ref"));

        gridLayout_4->addWidget(m_btn_Cap_Ref, 0, 1, 1, 1);

        m_btn_RefImg_clear = new QPushButton(gridLayoutWidget_4);
        m_btn_RefImg_clear->setObjectName(QStringLiteral("m_btn_RefImg_clear"));

        gridLayout_4->addWidget(m_btn_RefImg_clear, 1, 1, 1, 1);

        m_saveRois = new QPushButton(gridLayoutWidget_4);
        m_saveRois->setObjectName(QStringLiteral("m_saveRois"));

        gridLayout_4->addWidget(m_saveRois, 2, 0, 1, 1);

        m_loadRois = new QPushButton(gridLayoutWidget_4);
        m_loadRois->setObjectName(QStringLiteral("m_loadRois"));

        gridLayout_4->addWidget(m_loadRois, 2, 1, 1, 1);

        tabWidget_2->addTab(AcquireRef, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayoutWidget_8 = new QWidget(tab_4);
        gridLayoutWidget_8->setObjectName(QStringLiteral("gridLayoutWidget_8"));
        gridLayoutWidget_8->setGeometry(QRect(10, 0, 281, 152));
        gridLayout_8 = new QGridLayout(gridLayoutWidget_8);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 0, 0, 0);
        label_37 = new QLabel(gridLayoutWidget_8);
        label_37->setObjectName(QStringLiteral("label_37"));

        gridLayout_8->addWidget(label_37, 4, 3, 1, 1);

        m_sbMaxArea = new QSpinBox(gridLayoutWidget_8);
        m_sbMaxArea->setObjectName(QStringLiteral("m_sbMaxArea"));
        m_sbMaxArea->setMaximum(10000);

        gridLayout_8->addWidget(m_sbMaxArea, 5, 2, 1, 1);

        m_sbDistBetween = new QSpinBox(gridLayoutWidget_8);
        m_sbDistBetween->setObjectName(QStringLiteral("m_sbDistBetween"));
        m_sbDistBetween->setMaximum(1000);
        m_sbDistBetween->setValue(10);

        gridLayout_8->addWidget(m_sbDistBetween, 3, 2, 1, 1);

        m_sbMinArea = new QSpinBox(gridLayoutWidget_8);
        m_sbMinArea->setObjectName(QStringLiteral("m_sbMinArea"));
        m_sbMinArea->setMaximum(10000);

        gridLayout_8->addWidget(m_sbMinArea, 4, 2, 1, 1);

        label_39 = new QLabel(gridLayoutWidget_8);
        label_39->setObjectName(QStringLiteral("label_39"));

        gridLayout_8->addWidget(label_39, 5, 3, 1, 1);

        label_35 = new QLabel(gridLayoutWidget_8);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout_8->addWidget(label_35, 4, 0, 1, 1);

        label_30 = new QLabel(gridLayoutWidget_8);
        label_30->setObjectName(QStringLiteral("label_30"));

        gridLayout_8->addWidget(label_30, 2, 3, 1, 1);

        label_89 = new QLabel(gridLayoutWidget_8);
        label_89->setObjectName(QStringLiteral("label_89"));
        label_89->setMinimumSize(QSize(0, 15));
        label_89->setMaximumSize(QSize(80, 15));

        gridLayout_8->addWidget(label_89, 2, 0, 1, 1);

        label_103 = new QLabel(gridLayoutWidget_8);
        label_103->setObjectName(QStringLiteral("label_103"));
        label_103->setMinimumSize(QSize(0, 15));
        label_103->setMaximumSize(QSize(85, 15));

        gridLayout_8->addWidget(label_103, 1, 0, 1, 1);

        label_34 = new QLabel(gridLayoutWidget_8);
        label_34->setObjectName(QStringLiteral("label_34"));

        gridLayout_8->addWidget(label_34, 3, 0, 1, 1);

        label_101 = new QLabel(gridLayoutWidget_8);
        label_101->setObjectName(QStringLiteral("label_101"));
        label_101->setMinimumSize(QSize(0, 15));
        label_101->setMaximumSize(QSize(90, 15));

        gridLayout_8->addWidget(label_101, 0, 0, 1, 1);

        m_sbThresh = new QSpinBox(gridLayoutWidget_8);
        m_sbThresh->setObjectName(QStringLiteral("m_sbThresh"));
        m_sbThresh->setMinimum(0);
        m_sbThresh->setMaximum(255);
        m_sbThresh->setSingleStep(1);
        m_sbThresh->setValue(255);

        gridLayout_8->addWidget(m_sbThresh, 0, 2, 1, 1);

        label_26 = new QLabel(gridLayoutWidget_8);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_8->addWidget(label_26, 1, 3, 1, 1);

        m_sbCircularity = new QSpinBox(gridLayoutWidget_8);
        m_sbCircularity->setObjectName(QStringLiteral("m_sbCircularity"));
        m_sbCircularity->setMinimum(0);
        m_sbCircularity->setMaximum(100);
        m_sbCircularity->setValue(60);

        gridLayout_8->addWidget(m_sbCircularity, 2, 2, 1, 1);

        m_sbConvexity = new QSpinBox(gridLayoutWidget_8);
        m_sbConvexity->setObjectName(QStringLiteral("m_sbConvexity"));
        m_sbConvexity->setMinimum(0);
        m_sbConvexity->setMaximum(100);
        m_sbConvexity->setSingleStep(1);
        m_sbConvexity->setValue(60);

        gridLayout_8->addWidget(m_sbConvexity, 1, 2, 1, 1);

        label_21 = new QLabel(gridLayoutWidget_8);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_8->addWidget(label_21, 0, 3, 1, 1);

        label_33 = new QLabel(gridLayoutWidget_8);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout_8->addWidget(label_33, 3, 3, 1, 1);

        label_36 = new QLabel(gridLayoutWidget_8);
        label_36->setObjectName(QStringLiteral("label_36"));

        gridLayout_8->addWidget(label_36, 5, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_5, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_6, 2, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_7, 3, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_8, 4, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        gridLayout_8->addLayout(horizontalLayout_3, 5, 1, 1, 1);

        tabWidget_2->addTab(tab_4, QString());
        tabWidget->addTab(m_tabAnzAusw, QString());
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(30, 645, 1101, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        FPGA_InterfaceMainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FPGA_InterfaceMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        FPGA_InterfaceMainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(FPGA_InterfaceMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1173, 21));
        FPGA_InterfaceMainWindow->setMenuBar(menubar);

        retranslateUi(FPGA_InterfaceMainWindow);

        m_tabView->setCurrentIndex(2);
        tabWidget->setCurrentIndex(2);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FPGA_InterfaceMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FPGA_InterfaceMainWindow)
    {
        FPGA_InterfaceMainWindow->setWindowTitle(QApplication::translate("FPGA_InterfaceMainWindow", "FPGA Interface", 0));
        action_Open_IniFile->setText(QApplication::translate("FPGA_InterfaceMainWindow", "&Open Settings", 0));
        actionNew_Measurement->setText(QApplication::translate("FPGA_InterfaceMainWindow", "New Measurement", 0));
        action_Save_Current_Settings->setText(QApplication::translate("FPGA_InterfaceMainWindow", "&Save Current Settings", 0));
        groupBox->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Plot Info", 0));
        groupBox_5->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Individual ROI Info", 0));
        label_18->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Display Info For ROI ", 0));
        label_19->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Max.Expected Ampl.", 0));
        label_20->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Display Last ", 0));
        label_24->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Pixel", 0));
        label_25->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Samples", 0));
        label_22->setText(QApplication::translate("FPGA_InterfaceMainWindow", "ID", 0));
        m_plotROI->setText(QApplication::translate("FPGA_InterfaceMainWindow", "TextLabel", 0));
        groupBox_4->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Image Display", 0));
        label_Image->setText(QApplication::translate("FPGA_InterfaceMainWindow", "TextLabel", 0));
        m_tabView->setTabText(m_tabView->indexOf(widget), QApplication::translate("FPGA_InterfaceMainWindow", "LiveView", 0));
        m_tabView->setTabText(m_tabView->indexOf(tab_2), QApplication::translate("FPGA_InterfaceMainWindow", "Reference Image", 0));
        label_Image_3->setText(QApplication::translate("FPGA_InterfaceMainWindow", "TextLabel", 0));
        m_tabView->setTabText(m_tabView->indexOf(tab), QApplication::translate("FPGA_InterfaceMainWindow", "Individual ROI", 0));
        m_measComp->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Measurement Completed!", 0));
        groupBox_7->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Interface ", 0));
        groupBox_Project->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Measurement-Inifile", 0));
        m_ProjectIniLoad->setText(QApplication::translate("FPGA_InterfaceMainWindow", "&Load", 0));
        m_ProjectIniSave->setText(QApplication::translate("FPGA_InterfaceMainWindow", "&Save", 0));
        groupBox_Path->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Project Path", 0));
        m_ProjectPath_btn->setText(QApplication::translate("FPGA_InterfaceMainWindow", "...", 0));
        groupBox_Type->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Measurement", 0));
        m_Project_praxis->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Automatic", 0));
        m_Project_Einzelmessung->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Manual", 0));
        groupBox_Person->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Additional Info", 0));
        label_45->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Name", 0));
        label_46->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Surname", 0));
        label->setText(QApplication::translate("FPGA_InterfaceMainWindow", "User", 0));
        labelComment->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Comment", 0));
        m_ProjectComment->setDocumentTitle(QString());
        m_ProjectComment->setHtml(QApplication::translate("FPGA_InterfaceMainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
        m_ProjectOK->setText(QApplication::translate("FPGA_InterfaceMainWindow", "All settings are correct. Save current configuration", 0));
        tabWidget->setTabText(tabWidget->indexOf(m_tabAllgemein), QApplication::translate("FPGA_InterfaceMainWindow", "Genereal", 0));
        label_5->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Name", 0));
        label_6->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Board", 0));
        label_7->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Port", 0));
        label_8->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Sensortyp", 0));
        m_eSensortype->setText(QApplication::translate("FPGA_InterfaceMainWindow", "CMOS", 0));
        label_9->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Taps", 0));
        m_eNumberTaps->setText(QApplication::translate("FPGA_InterfaceMainWindow", "0", 0));
        groupBox_6->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "DualTap Settings", 0));
        groupBox_3->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Tap-Gain", 0));
        label_12->setText(QApplication::translate("FPGA_InterfaceMainWindow", "A", 0));
        label_13->setText(QApplication::translate("FPGA_InterfaceMainWindow", "B", 0));
        m_lTapGainMin->setText(QApplication::translate("FPGA_InterfaceMainWindow", ">0", 0));
        m_lTapGainMax->setText(QApplication::translate("FPGA_InterfaceMainWindow", "<max", 0));
        groupBox_2->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Tap-Offset", 0));
        label_10->setText(QApplication::translate("FPGA_InterfaceMainWindow", "A", 0));
        label_11->setText(QApplication::translate("FPGA_InterfaceMainWindow", "B", 0));
        m_lTapOffsetMin->setText(QApplication::translate("FPGA_InterfaceMainWindow", ">0", 0));
        m_lTapOffsetMax->setText(QApplication::translate("FPGA_InterfaceMainWindow", "<max", 0));
        m_cbCameraActive->setText(QApplication::translate("FPGA_InterfaceMainWindow", "&active", 0));
        groupBox_OptionalCamParam->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Image Parameters", 0));
        groupBox_8->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Frame Geometry", 0));
        label_27->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Offset X", 0));
        label_28->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Width", 0));
        label_31->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Offset Y", 0));
        label_32->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Height", 0));
        m_sbOfSetX->setSuffix(QString());
        m_sbOfSetY->setSuffix(QString());
        m_sbWidth->setSuffix(QString());
        m_sbHeight->setSuffix(QString());
        m_SetGeometry->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Set New geometry!", 0));
        groupBox_9->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Acquisition Settings", 0));
        label_15->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Shutter", 0));
        label_73->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Gain", 0));
        label_23->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Framerate", 0));
        m_sbShutter->setSuffix(QApplication::translate("FPGA_InterfaceMainWindow", "\302\265s", 0));
        m_sbFramerate->setSuffix(QString());
        m_cbLive->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Live View Full Size", 0));
        tabWidget->setTabText(tabWidget->indexOf(m_tabKamera), QApplication::translate("FPGA_InterfaceMainWindow", "Camera", 0));
        groupBox_RB->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "Ringbuffer", 0));
        label_38->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Ringbuffer", 0));
        m_sbBuffer->setSuffix(QString());
        m_lframeNum->setText(QApplication::translate("FPGA_InterfaceMainWindow", "123456789012", 0));
        m_lFramerate->setText(QApplication::translate("FPGA_InterfaceMainWindow", "200.00Hz (5.00ms)", 0));
        m_sbThreshold->setSpecialValueText(QApplication::translate("FPGA_InterfaceMainWindow", "Optimize!", 0));
        label_100->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Threshold for FPGA measurement ", 0));
        label_3->setText(QApplication::translate("FPGA_InterfaceMainWindow", "FameId", 0));
        label_4->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Framerate", 0));
        label_29->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Timestamp:", 0));
        m_lTimestamp->setText(QApplication::translate("FPGA_InterfaceMainWindow", "2009-11-30  15:53:21:123", 0));
        m_btnGrabContinuous->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Live Start", 0));
        m_btnGrabN->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Measure For ", 0));
        m_btnGrabSingle->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Grab 1", 0));
        m_btnGrabBuffer->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Grab Buffer", 0));
        m_saveMeasure->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Save Results", 0));
        m_btnLoadBuffer->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Load", 0));
        m_btnSaveBuffer->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Save Buffer", 0));
        label_86->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Last", 0));
        groupBox_Info->setTitle(QApplication::translate("FPGA_InterfaceMainWindow", "ROI Info", 0));
        m_lPegel->setText(QString());
        label_88->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Grid ", 0));
        label_98->setText(QApplication::translate("FPGA_InterfaceMainWindow", "ROI Width:", 0));
        label_99->setText(QApplication::translate("FPGA_InterfaceMainWindow", "ROI Height:", 0));
        label_16->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Pixel", 0));
        label_14->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Pixel", 0));
        label_17->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Cells", 0));
        label_2->setText(QApplication::translate("FPGA_InterfaceMainWindow", "x", 0));
        m_btn_RefImg_load->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Load Reference", 0));
        m_btn_Calc_ROIs->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Calculate ROIs", 0));
        m_btn_Cap_Ref->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Reference From Buffer", 0));
        m_btn_RefImg_clear->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Delete Reference", 0));
        m_saveRois->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Save ROIs", 0));
        m_loadRois->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Load ROIs", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(AcquireRef), QApplication::translate("FPGA_InterfaceMainWindow", "Reference Image", 0));
        label_37->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Pixel", 0));
        label_39->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Pixel", 0));
        label_35->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Minimum Area:", 0));
        label_30->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Percent", 0));
        label_89->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Min. Circularity:", 0));
        label_103->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Min. Convexity:", 0));
        label_34->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Min. Distance Between Dots:", 0));
        label_101->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Threshold:", 0));
        label_26->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Percent", 0));
        label_21->setText(QApplication::translate("FPGA_InterfaceMainWindow", "GV", 0));
        label_33->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Pixel", 0));
        label_36->setText(QApplication::translate("FPGA_InterfaceMainWindow", "Maximum Area:", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("FPGA_InterfaceMainWindow", "Parameters Reference Image", 0));
        tabWidget->setTabText(tabWidget->indexOf(m_tabAnzAusw), QApplication::translate("FPGA_InterfaceMainWindow", "Measurement", 0));
    } // retranslateUi

};

namespace Ui {
    class FPGA_InterfaceMainWindow: public Ui_FPGA_InterfaceMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FPGA_INTERFACEMAINWINDOW_H
