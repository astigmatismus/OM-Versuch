/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "RB_Plot.h"

#pragma warning(disable:4996)

CV_plot::CV_plot() //Default Constructor
{
}

//default constructor with default plotting parameters
CV_plot::CV_plot(const int width, const int height,const int offsetx, const int offsety, const int divx,const int divy, const int samples, const string ylabel, const string xlabel, int xmax, int ymax)
{
    
    int  xypos  = 20; //Spacing from top of window for max y label
    
    m_maxX      = static_cast<float>(xmax);
    m_maxY      = static_cast<float>(ymax);
    m_samplesN  = samples;
    m_offsetx   = offsetx;
    m_offsety   = offsety;
    m_witdthW   = width;
    m_heightW   = height;
    
    m_witdth    = m_witdthW - offsetx;
    m_height    = m_heightW - offsety;
    
    m_gridx     = divx;
    m_gridy     = divy;
    
    int dx      = static_cast<int>(m_witdth/m_gridx);
    int dy      = static_cast<int>(m_height/m_gridy);
    
    m_mask      = cv::Mat(m_heightW,m_witdthW,CV_8UC1);
    m_bg        = cv::Mat(m_heightW,m_witdthW,CV_8UC3);
    m_PlotWindow= cv::Mat(m_heightW,m_witdthW,CV_8UC3);
    
    m_PlotWindow.setTo(cv::Scalar(255,255,255));
    m_bg.setTo(cv::Scalar(0,255,0));
    m_mask.setTo(0);
                       
    cv::Point vertT(0,m_height);
    cv::Point vertB(0,0);
    
    cv::Point horL(offsetx,0);
    cv::Point horR(m_witdth+offsetx,0);
    
    //Set max/min axis values
    char *maxXStr      = new char[10];
    char *maxYStr      = new char[10];
    
    sprintf(maxXStr, "%i",  0);
    sprintf(maxYStr, "%i",  ymax);
    
    //cv::putText(m_PlotWindow, maxYStr , cv::Point((int)m_offsetx/-10,10),1 , 1, cvScalar(255,0,0));
    cv::putText(m_PlotWindow, maxXStr , cv::Point((int)m_witdthW-xypos,m_height+m_offsety/4),1 , 1, cvScalar(255,0,0));
    
    //set vertical lines and x axis description
    for(unsigned int i=0;i<=m_gridx; i++)
    {
        int pos = i*dx + offsetx-1;
        vertT.x = pos;
        vertB.x = pos;
        cv::line(m_PlotWindow, vertB, vertT, Scalar(0,0,0),1);
        
        sprintf(maxXStr, "%i", -1*( xmax - xmax*(i*dx)/(m_witdth)));
        
        cv::putText(m_PlotWindow, maxXStr , cv::Point(vertT.x,m_height+m_offsety/4),1 , 1, cvScalar(255,0,0));
    }
    
    //Set y-label
    cv::Mat yLabelMat = cv::Mat(offsetx-1,m_height,CV_8UC3);
    yLabelMat.setTo(cv::Scalar(255,255,255));
    
    cv::putText(yLabelMat, ylabel , cv::Point(0,(int)offsetx/3),1 , 1, cvScalar(0,0,10));
    flip(yLabelMat,yLabelMat,1);
    yLabelMat=yLabelMat.t();
    
    yLabelMat.copyTo(m_PlotWindow(cv::Rect(0,0,yLabelMat.cols,yLabelMat.rows)));
    
    //set horizontal lines and y axis description
    for(unsigned int i=0;i<=m_gridy; i++)
    {
        int pos =	i*dy;
        horR.y	=	pos;
        horL.y	=	pos;
        cv::line(m_PlotWindow, horR, horL, Scalar(0,0,0));
        
        sprintf(maxYStr, "%i",  static_cast<float>(ymax - (1.0*ymax*(i*dy)/m_height)));
        
        cv::putText(m_PlotWindow, maxYStr , cv::Point((int)(m_offsetx/2.5),horR.y),1 , 1, cvScalar(255,0,0));
    }
    
    //Set x-label
    cv::putText(m_PlotWindow, xlabel , cv::Point((int)m_witdth/2,(int)m_height+offsety/2),1 , 1, cvScalar(0,0,10));
    
    delete maxYStr;
    delete maxXStr;
}


//Set up the plot window
void CV_plot::setUpWindow(const int width, const int height,const int offsetx, const int offsety, const int divx,const int divy, const int samples, const string ylabel, const string xlabel, int xmax, int ymax)
{
    
    int  xypos  = 20; //Spacing from top of window for max y label
    
    m_maxX      = static_cast<float>(xmax);
    m_maxY      = static_cast<float>(ymax);
    m_samplesN  = samples;
    m_offsetx   = offsetx;
    m_offsety   = offsety;
    m_witdthW   = width;
    m_heightW   = height;
    
    m_witdth    = m_witdthW - offsetx;
    m_height    = m_heightW - offsety;
    
    m_gridx     = divx;
    m_gridy     = divy;
    
    double dx      = floor(1.0*m_witdth/m_gridx);
    double dy      = floor(1.0*m_height/m_gridy);
   
    m_mask      = cv::Mat(m_heightW,m_witdthW,CV_8UC1);
    m_bg        = cv::Mat(m_heightW,m_witdthW,CV_8UC3);
    m_PlotWindow= cv::Mat(m_heightW,m_witdthW,CV_8UC3);
    
    m_PlotWindow.setTo(cv::Scalar(255,255,255));
    m_bg.setTo(cv::Scalar(0,255,0));
    m_mask.setTo(0);
                       
    cv::Point vertT(0,m_height-2);
    cv::Point vertB(0,0);
    
    cv::Point horL(offsetx,0);
    cv::Point horR(m_witdth+offsetx,0);
    
    //Set max/min axis values
    
    char *maxXStr      = new char[10];
    char *maxYStr      = new char[10];
    
    sprintf(maxXStr, "%i",  0);
    sprintf(maxYStr, "%i",  ymax);
    
    //cv::putText(m_PlotWindow, maxYStr , cv::Point((int)m_offsetx/-10,10),1 , 1, cvScalar(255,0,0));
 
    
    //set vertical lines and x axis description
    for(unsigned int i=0;i<=m_gridx; i++)
    {
        int pos = static_cast<int>(floor(i*dx + offsetx-1));
        vertT.x = pos;
        vertB.x = pos;
        cv::line(m_PlotWindow, vertB, vertT, Scalar(0,0,0),1);
        
        sprintf(maxXStr, "%i", static_cast<int>(-1*( xmax - xmax*(i*dx)/(m_witdth))));
        
        cv::putText(m_PlotWindow, maxXStr , cv::Point(vertT.x,m_height+m_offsety/3),1 , 1, cvScalar(0,0,255));
    }
	cv::putText(m_PlotWindow, maxXStr , cv::Point((int)m_witdthW-xypos,m_height+m_offsety/3),1 , 1, cvScalar(0,0,255));
    
    //Set y-label
    cv::Mat yLabelMat = cv::Mat(offsetx-1,m_height,CV_8UC3);
    yLabelMat.setTo(cv::Scalar(255,255,255));
    
    cv::putText(yLabelMat, ylabel , cv::Point(0,(int)offsetx/3),1 , 1, cvScalar(0,0,10));
    flip(yLabelMat,yLabelMat,1);
    yLabelMat=yLabelMat.t();
    
    yLabelMat.copyTo(m_PlotWindow(cv::Rect(0,0,yLabelMat.cols,yLabelMat.rows)));
    
    //set horizontal lines and y axis description
    for(unsigned int i=0;i<=m_gridy; i++)
    {
        int pos = static_cast<int>(ceil(i*dy));
        
        horR.y = pos;
        horL.y = pos;
        cv::line(m_PlotWindow, horR, horL, Scalar(0,0,0));
        
        sprintf(maxYStr, "%i",  static_cast<int>(floor(ymax - (1.0*ymax*(i*dy)/m_height))));
        
        cv::putText(m_PlotWindow, maxYStr , cv::Point((int)(m_offsetx/2.5),horR.y),1 , 1, cvScalar(0,0,255));
    }
    
    //Set x-label
    cv::putText(m_PlotWindow, xlabel , cv::Point((int)(m_witdth/2),m_height+(int)(offsety/1.5)),1 , 1, cvScalar(0,0,10));
    
    delete maxYStr;
    delete maxXStr;
}

//Get the latest plot as image
cv::Mat CV_plot::getCurrPlot()
{
    cv::Mat plot;
    m_PlotWindow.copyTo(plot);
    m_bg.copyTo(plot, m_mask);
    return plot;
}

//Update the plot
void CV_plot::plotData(bool dd, std::vector<std::list<double>>	& samples, const int roiIdx)
{
    m_mask.setTo(0);
	/*
	if (!dd)
	{
		samples[roiIdx].clear();
	}
	*/
	if (samples[roiIdx].size()<1)
		return;
    
	int k = 2;

	static cv::Point curPt(0,0);
	static cv::Point prePt(0,0);
    
	curPt.y = static_cast<int>(m_height - 3 - *samples[roiIdx].begin()*(m_height - 2) / m_maxY);
	curPt.x= m_offsetx;
	prePt = curPt;

	for (std::list<double>::iterator it = samples[roiIdx].begin(); it != samples[roiIdx].end(); ++it)
	{
		//Plot everything
		//int j = (m_offsetx+1)+(m_witdth-2)*((double)k/m_samples.size());
		//Plot a last samples
		
		unsigned int j = static_cast<int>(ceil(m_offsetx+1+(m_witdth)*((double)k/(m_samplesN))));
		unsigned int i = static_cast<int>(floor(m_height-3 - *it*(m_height-2)/m_maxY));
		curPt = Point(j,i);

		if(i < m_heightW && i > 0 && j > 00 &&j < m_witdthW)
			m_mask.at<uchar>(i,j)= 255;
        
		cv::line(m_mask, curPt, prePt, 255);
		prePt = curPt;
		k++;
	}
}

CV_plot::~CV_plot()
{
}
