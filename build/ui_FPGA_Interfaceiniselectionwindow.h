/********************************************************************************
** Form generated from reading UI file 'FPGA_Interfaceiniselectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FPGA_INTERFACEINISELECTIONWINDOW_H
#define UI_FPGA_INTERFACEINISELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_FPGA_InterfaceIniSelectionWindow
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QLabel *m_label_text;
    QSpacerItem *horizontalSpacer;
    QLabel *m_label_Version;
    QFrame *line;
    QGridLayout *gridLayout;
    QComboBox *m_cbIniFile;
    QToolButton *m_tbSelectIniFile;
    QFrame *line_2;
    QGridLayout *gridLayout_2;
    QPushButton *m_btnLoad;
    QPushButton *m_btnStd;
    QSpacerItem *spacerItem;
    QPushButton *m_btnCancel;

    void setupUi(QDialog *FPGA_InterfaceIniSelectionWindow)
    {
        if (FPGA_InterfaceIniSelectionWindow->objectName().isEmpty())
            FPGA_InterfaceIniSelectionWindow->setObjectName(QStringLiteral("FPGA_InterfaceIniSelectionWindow"));
        FPGA_InterfaceIniSelectionWindow->resize(455, 120);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FPGA_InterfaceIniSelectionWindow->sizePolicy().hasHeightForWidth());
        FPGA_InterfaceIniSelectionWindow->setSizePolicy(sizePolicy);
        FPGA_InterfaceIniSelectionWindow->setMinimumSize(QSize(455, 120));
        FPGA_InterfaceIniSelectionWindow->setMaximumSize(QSize(600, 120));
        FPGA_InterfaceIniSelectionWindow->setLayoutDirection(Qt::LeftToRight);
        FPGA_InterfaceIniSelectionWindow->setSizeGripEnabled(false);
        gridLayout_4 = new QGridLayout(FPGA_InterfaceIniSelectionWindow);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_label_text = new QLabel(FPGA_InterfaceIniSelectionWindow);
        m_label_text->setObjectName(QStringLiteral("m_label_text"));
        sizePolicy.setHeightForWidth(m_label_text->sizePolicy().hasHeightForWidth());
        m_label_text->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(m_label_text, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);

        m_label_Version = new QLabel(FPGA_InterfaceIniSelectionWindow);
        m_label_Version->setObjectName(QStringLiteral("m_label_Version"));

        gridLayout_3->addWidget(m_label_Version, 0, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        line = new QFrame(FPGA_InterfaceIniSelectionWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_cbIniFile = new QComboBox(FPGA_InterfaceIniSelectionWindow);
        m_cbIniFile->setObjectName(QStringLiteral("m_cbIniFile"));
        m_cbIniFile->setEditable(false);

        gridLayout->addWidget(m_cbIniFile, 0, 0, 1, 1);

        m_tbSelectIniFile = new QToolButton(FPGA_InterfaceIniSelectionWindow);
        m_tbSelectIniFile->setObjectName(QStringLiteral("m_tbSelectIniFile"));

        gridLayout->addWidget(m_tbSelectIniFile, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout, 2, 0, 1, 1);

        line_2 = new QFrame(FPGA_InterfaceIniSelectionWindow);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_2, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_btnLoad = new QPushButton(FPGA_InterfaceIniSelectionWindow);
        m_btnLoad->setObjectName(QStringLiteral("m_btnLoad"));

        gridLayout_2->addWidget(m_btnLoad, 0, 0, 1, 1);

        m_btnStd = new QPushButton(FPGA_InterfaceIniSelectionWindow);
        m_btnStd->setObjectName(QStringLiteral("m_btnStd"));

        gridLayout_2->addWidget(m_btnStd, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(51, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(spacerItem, 0, 2, 1, 1);

        m_btnCancel = new QPushButton(FPGA_InterfaceIniSelectionWindow);
        m_btnCancel->setObjectName(QStringLiteral("m_btnCancel"));

        gridLayout_2->addWidget(m_btnCancel, 0, 3, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 4, 0, 1, 1);


        retranslateUi(FPGA_InterfaceIniSelectionWindow);

        QMetaObject::connectSlotsByName(FPGA_InterfaceIniSelectionWindow);
    } // setupUi

    void retranslateUi(QDialog *FPGA_InterfaceIniSelectionWindow)
    {
        FPGA_InterfaceIniSelectionWindow->setWindowTitle(QApplication::translate("FPGA_InterfaceIniSelectionWindow", "FPGA-Interface: Choose initialisation file", 0));
        m_label_text->setText(QApplication::translate("FPGA_InterfaceIniSelectionWindow", "Choose initialisation file", 0));
        m_label_Version->setText(QApplication::translate("FPGA_InterfaceIniSelectionWindow", "Version: 0.0", 0));
        m_tbSelectIniFile->setText(QApplication::translate("FPGA_InterfaceIniSelectionWindow", "...", 0));
        m_btnLoad->setText(QApplication::translate("FPGA_InterfaceIniSelectionWindow", "&Load", 0));
        m_btnStd->setText(QApplication::translate("FPGA_InterfaceIniSelectionWindow", "&Default", 0));
        m_btnCancel->setText(QApplication::translate("FPGA_InterfaceIniSelectionWindow", "&Cancle", 0));
    } // retranslateUi

};

namespace Ui {
    class FPGA_InterfaceIniSelectionWindow: public Ui_FPGA_InterfaceIniSelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FPGA_INTERFACEINISELECTIONWINDOW_H
