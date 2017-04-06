/*
	Copyright (C) 2016  	Nils Küpper

	h_da University of Applied Sciences
	Faculty of Mathematics and Science
	Dept. Computer Vision and Photonics

	Schoefferstr. 3
	D-64295 Darmstadt
	Germany

*/

#include <stdio.h>
#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QApplication>
#include "FPGA_Interface_Core.h"

int main(int argc, char* argv[], char* envp[])
{
	QApplication app(argc, argv);

	if (g_pFPGA_IFcore->Init())												//Intialize internal Data
	{
		std::cout << "Starting main aplication \n" << std::endl;
		g_pFPGA_IFcore->m_pFPGA_IFMainWindow	= new FPGA_IFMainWindow();
		g_pFPGA_IFcore->m_pFPGA_IFMainWindow->show();						//If initialization successfull - initialize main window
	}
	else 
		return 0;

    int dd = app.exec();													//Execute the application

	if (g_pFPGA_IFcore->DeInit())
	{
		delete g_pFPGA_IFcore->m_pFPGA_IFMainWindow;						//Free resources
		std::cout << "Main aplication quitted \n" << std::endl;
	}
	
	return dd;
}