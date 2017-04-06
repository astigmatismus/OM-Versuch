/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef ROIPLOT_H_INCLUDED
#define ROIPLOT_H_INCLUDED

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <list>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class CV_plot{
    
public:
						CV_plot();
						~CV_plot();
						CV_plot				(const int width, const int height,const int offsetx, const int offsety, const int divx,const int divy, const int samples, const string ylabel, const string xlabel, int xmax, int ymax);
    void				setUpWindow			(const int width, const int height,const int offsetx, const int offsety, const int divx,const int divy, const int samples, const string ylabel, const string xlabel, int xmax, int ymax);
	void				plotData(bool dd, std::vector<std::list<double>>	& samples, const int roiIdx);
    cv::Mat				getCurrPlot			();
	//void				emptySampleList		(){m_samples.clear();};
	void				setSamplesN			(int n) {m_samplesN = n;};
	void				setMaxDist			(int maxD) {m_maxY = (float)maxD;};
	int					getSamplesN			() {return m_samplesN;};
	float				getMaxDist			() {return m_maxY;};
    
private:
    cv::Mat				m_bg;				//bg
    cv::Mat             m_mask;				//mask
    cv::Mat             m_PlotWindow;		//Container for plot
    //std::list<double>   m_samples;			//list of distances
    unsigned int		m_gridx;			//Width of ROI
    unsigned int		m_gridy;			//Height of ROI
    unsigned int		m_offsetx;
    unsigned int		m_offsety;
    unsigned int		m_witdth;			//Width of PlotROI
    unsigned int		m_height;			//Height of PlotROI
    unsigned int		m_witdthW;			//Width of PlotROI
    unsigned int		m_heightW;			//Height of PlotROI
    int					m_samplesN;         //absolute size of PlotROI
    float				m_maxX;
    float				m_maxY;
};


#endif