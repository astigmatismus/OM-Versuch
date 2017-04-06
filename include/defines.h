/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef DEFINES_H
#define DEFINES_H
//----------------------------------------------------------------
#pragma once
#include <iostream>
#include <iomanip>

#include "FPGA_InterfaceIniDefines.h"

#ifndef MIN
	#define	MIN(x,y) ( ((x) <  (y)) ?  (x) : (y))
#endif

#ifndef MAX
	#define	MAX(x,y) ( ((x) >  (y)) ?  (x) : (y))
#endif

#define	ABS(x)   ( ((x) <   0 ) ? (-x) : (x))
#define	SQR(x)   ( (x) * (x) )

#define MESSAGE(x) { \
		std::cout	<< std::setw(70) << std::left << __FILE__ \
				<< " (" << __LINE__ << ")\t" \
				<< x << std::endl << std::flush; }

#define MESSAGE2(x1, x2) { \
		std::cout	<< std::setw(70) << std::left << __FILE__ \
				<< " (" << __LINE__ << ")\t" \
				<< x1 << " " << x2 << std::endl << std::flush; }
// ---------------------------------------------------------------------------

#define CONDS
#undef CONDS

// ---------------------------------------------------------------------------

#define	PI		3.1415926535897932384626433832795
#define	PId2	1.5707963267948966192313216916398	// Pi/2
#define	R2D		57.295779513082320876798154814105	// 180/PI
#define D2R		0.017453292519943295769236907684886	// PI/180

#ifndef UINT32
typedef unsigned int UINT32;
#endif


#define __PARALLEL_MODULO__ 4		//This has to be set according to the used parallelism when setting rois in the applet
//#define		TRIGGER				//If special trigger modes should be supported or set - not fully implemented since freerun
//#define __SHOW_HFR__				//SISO Display for showing images. not bound to QT!
#define __MULTI_DMA_APPLET__		//Multi DMA - Actual Applet; Single DMA is for Displaying die image only - should be used for CPU only evaluation
//#define __ME5__					//define ME5 if ME5 Grabber is being used - otherwise the applet for ME4 plattform with JaiPulnix Cam is loaded 
//#define __USE_COEFFICIENT_BUFFER__	//Coefficient Buffer for using a predefined image instead of the live camera feed


#ifdef __MULTI_DMA_APPLET__			
	#define MAXDMA 3				//Maximum number of DMAs used- For now 3-> 0: Original Image 1:Raw CoG Positions 2: row-wise Histogram (not really used at this point - later autocalibration) 
#else
	#define MAXDMA 1
#endif

#define __MAX_ROIS__ 48  //Maximum number of rois as hardcoded in applet
// ---------------------------------------------------------------------------

#endif //DEFINES_H
