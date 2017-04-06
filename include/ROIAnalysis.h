/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef ROIANALYSIS_H_INCLUDED
#define ROIANALYSIS_H_INCLUDED


#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

#define N_ROI 96

typedef struct stats
{
    double s_stdDev;
    double s_mean;
} stats;

class cROIEval{
    
public:

							cROIEval();
							~cROIEval();
							cROIEval(const cv::Mat &InputImg);
    stats					m_getStdDev (const cv::Mat &InputImg);
    void					m_getCOG    (cv::Mat InputImg,int thresh);
    Point2f					getCogPt() {return m_cog;};

	// std::thread t[N_ROI];
	//void  threadedCalc(cv::Mat InputImg,int thresh);
    
private:

    stats					m_statistics;
    std::vector<Mat>		m_inputs;
    std::vector<Point2d>	m_cogs;
    Point2d					m_cog;
    unsigned int			m_witdthROI;        //Width of ROI
    unsigned int			m_heightROI;        //Height of ROI
    unsigned int			m_size;             //absolute size of ROI
    Mat						m_Input;         //Array containing all 48 ROIs
};

#endif