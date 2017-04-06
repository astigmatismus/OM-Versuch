/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "ROIAnalysis.h"

#pragma warning(disable:4996)

cROIEval::cROIEval() //Default Constructor
{
}

cROIEval::cROIEval(const cv::Mat &InputMat) //Default Constructor
{
    m_size   = InputMat.rows*InputMat.cols;
}

stats cROIEval::m_getStdDev (const cv::Mat &InputImg)
{
    //Fastest way to access matrix elements: use pointer structure
    
    unsigned char *data = (unsigned char*) InputImg.data;
    
    unsigned int    sum     = 0;
    unsigned int    sqSum   = 0;
    
    //Onepass standard deviation
    for (unsigned int i = 0; i<m_size; i++)
    {
        sum     += (*data);
        sqSum   += (*data) * (*data);
        
        data++;
    }
    
    m_statistics.s_mean    =   static_cast<double>(sum) / static_cast<double>(m_size);
    m_statistics.s_stdDev  =   sqrt(static_cast<double>(sqSum) / m_size - m_statistics.s_mean * m_statistics.s_mean);
    
    return m_statistics;
}

/*
//Very fast processing of ROIs on CPU using threads. - C++11 standard is used!! wont work "right out of the box" get c++11 support on windows!
void cROIEval::threadedCalc(cv::Mat InputImg, int thresh)
{
	
	ROIThreads = new cRoiThread[96];
	
	for (int i = 0;i< 96; i++)
	{

	}
    connect(workerThread, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();

	
    for (int i = 0; i < N_ROI; ++i)
    {
        t[i] = std::thread(&cROIEval::m_getCOG,this, InputImg, thresh);
    }
   //Join the threads with the main thread
   for (int i = 0; i < N_ROI; ++i)
   {
        t[i].join();
   }
  
}
 */

//Calculate the center of gravity (CoG) by setting pixels under threshold to zero and do weighted summation with gray values
//Basically do just the same as the Applet!
void cROIEval::m_getCOG    (cv::Mat InputImg, int thresh)
{
    unsigned int sX = 0;
    unsigned int sY = 0;
    unsigned int ss = 0;
    
    uchar val = 0;
    
    //Fastest way to access pixel without loosing adress information
    for (int i = 0; i < InputImg.rows; ++i)
    {
        uchar* pixel = InputImg.ptr<uchar>(i);  // point to first color in row
        for (int j = 0; j < InputImg.cols; ++j)
        {
            val      =   255- *pixel;
            if(val >= (255-thresh))
            {
                sX      +=  val * j;
                sY      +=  val * i;
                ss      +=  val;
            }
            pixel++;
        }
    }
    m_cog.x = (1./static_cast<double>(ss))* static_cast<double>(sX);
    m_cog.y = (1./static_cast<double>(ss))* static_cast<double>(sY);
}

cROIEval::~cROIEval(){}
