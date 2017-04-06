/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/

#include "ROIManager.h"
#include <QMessagebox>
#include <fstream>      // std::ofstream


#include "ROIAnalysis.h"

using namespace std;
using namespace cv;

#pragma warning(disable:4996)

cRefImg::cRefImg() //Default Constructor
{
    m_witdthROI     =       0;
    m_heightROI     =       0;
    m_witdthSubROI  =       0;
    m_heightSubROI  =       0;
    
    m_totalX        =       0;
    m_totalY        =       0;

	m_ROISset		=	false;
}

bool cRefImg::ReadIni		(MIniFile& ini)
{
	ini.getItem(INI_FG_CELLX	.toStdString(), this->m_totalX, 6);
	ini.getItem(INI_FG_CELLY	.toStdString(), this->m_totalY, 8);
	ini.getItem(INI_FG_THRESHINI.toStdString(), this->m_thresh, 0);
	ini.getItem(INI_FG_CONVINI	.toStdString(), this->m_Convexity, 0);
	ini.getItem(INI_FG_CIRCINI	.toStdString(), this->m_Circularity, 0);
	ini.getItem(INI_FG_DISTINI	.toStdString(), this->m_DistBetween, 0);
	ini.getItem(INI_FG_MINAREA	.toStdString(), this->m_MinArea, 0);
	ini.getItem(INI_FG_MAXAREA	.toStdString(), this->m_MaxArea, 0);
	return true;	     
}

bool cRefImg::WriteIni		(MIniFile& ini)
{
	ini.setItem((INI_FG_CELLX)	.toStdString(), this->getTotalX());
	ini.setItem((INI_FG_CELLY)	.toStdString(), this->getTotalY());
	ini.setItem(INI_FG_THRESHINI.toStdString(), this->GetThresh());
	ini.setItem(INI_FG_CONVINI	.toStdString(), this->GetConvexity());  
	ini.setItem(INI_FG_CIRCINI	.toStdString(), this->GetCircularity());
	ini.setItem(INI_FG_DISTINI	.toStdString(), this->GetDistBetween());
	ini.setItem(INI_FG_MINAREA	.toStdString(), this->GetMinArea());
	ini.setItem(INI_FG_MAXAREA	.toStdString(), this->GetMaxArea());
	return true;	     
}

//Get ROI Coordinates 
cv::Mat cRefImg::m_getROICoords(cv::Mat InputMat)
{
	m_ROIS.clear();
	if(InputMat.rows > 3000)
		m_setText = true;
	else
		m_setText = false;

    m_witdthROI     =       0;
    m_heightROI     =       0;
    m_spacing       =       0;

	int *CornerCoords = new int[(m_totalX+m_totalY)*2];
    
    CornerPoints  Corners  = m_getCorners(InputMat);
    m_getROIGrid	(Corners, InputMat.size(), CornerCoords);
    m_getROIArray	(InputMat, CornerCoords);
    
    for (int i = 0; i < m_ROIS.size(); i++)
    {
		//Sequentially perform blob analysis
		std::vector<cv::KeyPoint> circles = m_blobAnaysis(m_ROIS[i].Content);

		//only if there are two circles found declare ROI as valid  and evaluate ROIS
        if (circles.size()==2)
        {
            m_ROIS[i].twoCircles = true;

			if(circles[0].pt.x < circles[1].pt.x) //always first SubRoi left, second right!
			{
				m_ROIS[i].circleL_cent  =   cv::Point2f(circles[0].pt.x,circles[0].pt.y);
				m_ROIS[i].radiusLeft    =   circles[0].size;
				m_ROIS[i].circleR_cent  =   cv::Point2f(circles[1].pt.x,circles[1].pt.y);
				m_ROIS[i].radiusRight   =   circles[1].size;
			}
			else 
			{
				m_ROIS[i].circleL_cent  =   cv::Point2f(circles[1].pt.x,circles[1].pt.y);
				m_ROIS[i].radiusLeft    =   circles[1].size;
				m_ROIS[i].circleR_cent  =   cv::Point2f(circles[0].pt.x,circles[0].pt.y);
				m_ROIS[i].radiusRight   =   circles[0].size;
			}
				m_ROIS[i].distance      =   sqrt((m_ROIS[i].circleL_cent.x-m_ROIS[i].circleR_cent.x)*(m_ROIS[i].circleL_cent.x-m_ROIS[i].circleR_cent.x) +
                                             (m_ROIS[i].circleL_cent.y-m_ROIS[i].circleR_cent.y)*(m_ROIS[i].circleL_cent.y-m_ROIS[i].circleR_cent.y));  
        }
        else
        {
            m_ROIS[i].twoCircles = false;
            m_ROIS[i].circleL_cent  =   cv::Point2f(0,0);
            m_ROIS[i].radiusLeft    =   0;
            m_ROIS[i].circleR_cent  =   cv::Point2f(0,0);
            m_ROIS[i].radiusRight   =   0;
            m_ROIS[i].distance      =   0;
        } 
    }

	m_getSubROI(m_ROIS);

    m_GetStatistics(m_ROIS);
    
	delete[] CornerCoords;

	m_ROISset = true;

    return  m_VisResults(InputMat, m_ROIS,0);
}

//Blob analysis for finding initial spots and adjust  the ROIs for the framegrabber
std::vector<cv::KeyPoint> cRefImg::m_blobAnaysis(cv::Mat &InputMat)
{
	cv::Point    ROICenter;
	unsigned int MinLenth       =   (std::numeric_limits<int>::max)();;
    unsigned int MinLenth2      =   (std::numeric_limits<int>::max)();;
    unsigned int Idx1           =   0;
    unsigned int Idx2           =   0;
    ROICenter.x                 =   static_cast<int>(InputMat.cols/2);
    ROICenter.y                 =   static_cast<int>(InputMat.rows/2);

    cv::SimpleBlobDetector::Params params;
    std::vector<cv::KeyPoint> foundDots;
    
    params.filterByArea			= true;         
	params.filterByCircularity	= true;
	params.filterByConvexity	= true;
	params.filterByInertia		= false;
	params.filterByColor		= false;
	
	params.minArea				= m_MinArea;
	params.maxArea				= m_MaxArea;             // max 500 pixels squared
    params.minThreshold			= m_thresh;
    params.maxThreshold			= 255;
	params.minCircularity		= static_cast<float>(m_Circularity / 100);
	params.minConvexity			= static_cast<float>(m_Convexity / 100);
	params.minDistBetweenBlobs	= m_DistBetween;

	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    // Detect blobs.
    detector->detect( InputMat, foundDots);
    
	unsigned int* distances    = new unsigned int[foundDots.size()];
	memset(distances, (std::numeric_limits<int>::max)(), foundDots.size()*sizeof(unsigned int));

    if (foundDots.size() > 2) // if more than two circles are found - return the closest ones!
    {
        for( size_t i = 0; i < foundDots.size(); i++ )
        {
			distances[i] = abs(ROICenter.x - foundDots[i].pt.x) + abs(ROICenter.y - foundDots[i].pt.y);
            if(distances[i]<MinLenth)
            {
                MinLenth        = distances[i];
                Idx1            = static_cast<int>(i);
            }
        }
        distances[Idx1]    = (numeric_limits<int>::max)();
        for( size_t i = 0; i < foundDots.size(); i++ )
        {
            if(distances[i]<MinLenth2)
            {
                MinLenth2 = distances[i];
                Idx2      = static_cast<int>(i);
            }
        }
        std::vector<cv::KeyPoint>   circles_out;
        circles_out.push_back(foundDots[Idx1]);
        circles_out.push_back(foundDots[Idx2]);
		delete [] distances;
        return circles_out;
    }
	else if(foundDots.size() < 2)  // if less than two circles are found - set roi as invalid!
	{
		cout << "ROI not valid!" <<  endl;
		std::vector<cv::KeyPoint>   circles_out;
		delete [] distances;
		return circles_out;
	}
 
	delete [] distances;

	return foundDots; //if exactly two spots are found- just return the result of blob analysis
}
 
//Create the grid with equidistant x and y values
void cRefImg::m_getROIGrid(CornerPoints &CornerPts, cv::Size InSize, int *GridCoords)
{
    unsigned int xyCounter  =    m_totalY+m_totalX;
   
	//this calculation crops the equidistant rois. a little flaw but considering the size of the image the worst case of 8 missed pixels is acceptable
    m_witdthROI     =   static_cast<unsigned int>((InSize.width/m_totalX));
    m_heightROI     =   static_cast<unsigned int>((InSize.height/m_totalY));
   
    for (unsigned int i = 0; i < m_totalX; i++)
    {
        int xIdx    = static_cast<int>(i * m_witdthROI);
        GridCoords[i] = xIdx;
    }
    for (unsigned int i = 0; i < m_totalY; i++)
    {
        int yIdx    = static_cast<int>(i * m_heightROI);
        GridCoords[i+xyCounter] = yIdx;
    }
    
}

//Divide the whole picture into ROI tiles. Fill the ROI-Struct with information
void cRefImg::m_getROIArray(cv::Mat &InputImg,  int *GridCoords)
{
    int idxY                =    -1;
    unsigned int ROI_ID     =    0;
    unsigned int idxX       =    0;
    unsigned int xyCounter  =    m_totalY+m_totalX;
    ROIInfo tempROI;

    for (unsigned int u= 0 ; u<m_totalX*m_totalY; u++)
    {
        if (u%m_totalX==0 )
        {
            idxY++;
            idxX = 0;
        }
        tempROI.ID            = ROI_ID;
        tempROI.Grid_Origin.x = GridCoords[idxX];
        tempROI.Grid_Origin.y = GridCoords[idxY + xyCounter];
        tempROI.height        = m_heightROI;
        tempROI.witdth        = m_witdthROI;
        
        cv::Rect CurrentROI(GridCoords[idxX], GridCoords[idxY + xyCounter], m_witdthROI-m_spacing, m_heightROI-m_spacing);
        tempROI.Content       =   InputImg(CurrentROI);
        
        m_ROIS.push_back(tempROI);
        
        idxX++;
        ROI_ID++;
    }
}

//Get the corners of input image defining the borders of the grid
CornerPoints cRefImg::m_getCorners(cv::Mat &InputImg)
{
    cv::Size frameDims = InputImg.size();
    CornerPoints Corners;
  
    Corners.topLeft.x      = 0;
    Corners.topLeft.y      = frameDims.height;
    Corners.topRight.x     = frameDims.width;
    Corners.topRight.y     = frameDims.height;
    Corners.bottomLeft.x   = 0;
    Corners.bottomLeft.y   = 0;
    Corners.bottomRight.x  = frameDims.width;
    Corners.bottomRight.y  = 0;

    return Corners;
}

//just as a test: get statistics about the initial spots
void cRefImg::m_GetStatistics(std::vector<ROIInfo> &ROIVec)
{
    float Distsum   =   0;
    float avgDist   =   0;
    
    float Radii     =   0;
    float avgRad    =   0;
    
    float maxRad    = (std::numeric_limits<float>::min)();
    float minRad    = (std::numeric_limits<float>::max)();
    
    float maxDist   = (std::numeric_limits<float>::min)();
    float minDist   = (std::numeric_limits<float>::max)();
    
    for (int i = 0; i < m_ROIS.size(); i++)
    {
        float minRadPair =  (m_ROIS[i].radiusRight < m_ROIS[i].radiusLeft)?m_ROIS[i].radiusRight:m_ROIS[i].radiusLeft;
        float maxRadPair =  (m_ROIS[i].radiusRight > m_ROIS[i].radiusLeft)?m_ROIS[i].radiusRight:m_ROIS[i].radiusLeft;
        
        if (    m_ROIS[i].distance < minDist) minDist = m_ROIS[i].distance;
        if (    m_ROIS[i].distance > maxDist) maxDist = m_ROIS[i].distance;
        if (    maxRadPair > maxRad) maxRad = maxRadPair;
        if (    minRadPair < minRad) minRad = minRadPair;

        Distsum    +=    m_ROIS[i].distance;
        Radii      +=    m_ROIS[i].radiusLeft+m_ROIS[i].radiusRight;
    }
    avgDist =   Distsum/m_ROIS.size();
    avgRad  =   Radii/(2*m_ROIS.size());
    
    printf("Average Distance = %.2f \n", avgDist);
    printf("Average Radius   = %.2f \n", avgRad);
    
    printf("Maximum Radius = %.2f \n", maxRad);
    printf("Minimum Radius = %.2f \n", minRad);
}

//adjust the ROIs with respect to the limitations given by the framgegrabber - parallelism!
void cRefImg::m_getSubROI(std::vector<ROIInfo> &ROIVec)
{
    unsigned int x_scale  = 4;
    unsigned int y_scale  = 7;

    unsigned int SubRoiW  = floor(m_witdthROI/x_scale);
	unsigned int SubRoiH =  floor(m_heightROI / y_scale);
    
    cv::Point centerSubRoi;

	cv::Point centerSubSubRoiL;
	cv::Point centerSubSubRoiR;

    cv::Point TopLeft;

	int modposxL;
	int modposxR;
	int modposyL;
	int modposyR;
	int modulo = __PARALLEL_MODULO__;
	
    for (int i = 0; i < m_ROIS.size(); i++)
    {
		if(m_ROIS[i].twoCircles == true)
		{
			centerSubRoi.x				= cvRound((m_ROIS[i].circleL_cent.x + m_ROIS[i].circleR_cent.x )/ 2);
			centerSubRoi.y				= cvRound((m_ROIS[i].circleL_cent.y + m_ROIS[i].circleR_cent.y )/ 2);
			TopLeft.x					= centerSubRoi.x - SubRoiW;
			TopLeft.y					= centerSubRoi.y - SubRoiH;
			m_ROIS[i].Origin			= TopLeft;
			m_ROIS[i].SubWitdth			= SubRoiW*2;
			m_ROIS[i].SubHeight			= SubRoiH*2;

			int tmpOrigSubLx			= floor(m_ROIS[i].circleL_cent.x - floor(m_witdthSubROI / 2));
			int tmpOrigSubRx			= floor(m_ROIS[i].circleR_cent.x - floor(m_witdthSubROI / 2));

			int tmpOrigSubLy			= floor(m_ROIS[i].circleL_cent.y - floor(m_heightSubROI / 2));
			int tmpOrigSubRy			= floor(m_ROIS[i].circleR_cent.y - floor(m_heightSubROI / 2));

			m_ROIS[i].OriginSubLeft.x	= tmpOrigSubLx;
			m_ROIS[i].OriginSubLeft.y	= tmpOrigSubLy;
		 
			m_ROIS[i].OriginSubRight.x	= tmpOrigSubRx;
			m_ROIS[i].OriginSubRight.y	= tmpOrigSubRy;

			//Set coordinates in img coordinate system and modulo for visual applets
			int tmpOrigSubLxImg			= tmpOrigSubLx+m_ROIS[i].Grid_Origin.x;
			int tmpOrigSubLyImg			= tmpOrigSubLy+m_ROIS[i].Grid_Origin.y;

			int tmpOrigSubRxImg			= tmpOrigSubRx+m_ROIS[i].Grid_Origin.x;
			int tmpOrigSubRyImg			= tmpOrigSubRy+m_ROIS[i].Grid_Origin.y;
			
			modposxL					=  tmpOrigSubLxImg  % modulo;
			modposxR					=  tmpOrigSubRxImg  % modulo;
			modposyL					=  tmpOrigSubLyImg  % modulo;
			modposyR					=  tmpOrigSubRyImg  % modulo;

			if (modulo == __PARALLEL_MODULO__ && modposxL == __PARALLEL_MODULO__-1)	
				modposxL = -1;
			if (modulo == __PARALLEL_MODULO__ && modposxR == __PARALLEL_MODULO__-1)	
				modposxR = -1;
			if (modulo == __PARALLEL_MODULO__ && modposyL == __PARALLEL_MODULO__-1)	
				modposyL = -1;
			if (modulo == __PARALLEL_MODULO__ && modposyR == __PARALLEL_MODULO__-1)	
				modposyR = -1;
				
			m_ROIS[i].OriginSubLeftImg.x = tmpOrigSubLxImg -modposxL;
			m_ROIS[i].OriginSubLeftImg.y = tmpOrigSubLyImg -modposyL;
		 
			m_ROIS[i].OriginSubRightImg.x = tmpOrigSubRxImg -modposxR;
			m_ROIS[i].OriginSubRightImg.y = tmpOrigSubRyImg -modposyR;

			int ROIdx = m_ROIS[i].OriginSubRightImg.x - m_ROIS[i].OriginSubLeftImg.x;
			int ROIdy = m_ROIS[i].OriginSubRightImg.y - m_ROIS[i].OriginSubLeftImg.y;
		}
		else
		{
			m_ROIS[i].Origin			= cvPoint(0,0);
			m_ROIS[i].SubWitdth			= 0;
			m_ROIS[i].SubHeight			= 0;

			m_ROIS[i].OriginSubLeft.x	= 0;
			m_ROIS[i].OriginSubLeft.y	= 0;
		 
			m_ROIS[i].OriginSubRight.x	= 0;
			m_ROIS[i].OriginSubRight.y	= 0;

			m_ROIS[i].OriginSubLeftImg.x = 0;
			m_ROIS[i].OriginSubLeftImg.y = 0;
		 
			m_ROIS[i].OriginSubRightImg.x = 0;
			m_ROIS[i].OriginSubRightImg.y = 0;

			int ROIdx = 0;
			int ROIdy = 0;
		}
    }

	//PrintOCV_COGData();
}

//Clear ROI data and flag
void cRefImg::clear						()
{
	m_ROIS.clear();
	m_ROISset = false;
}

//Visualize the results
cv::Mat  cRefImg::m_VisResults                (cv::Mat &InputImg, std::vector<ROIInfo> &ROIVec, int thresh)
{
    char *IDtext        = new char[10];
    char *DistText      = new char[10];
    char *avgDistText   = new char[10];
    char *maxAmpl       = new char[10];
    
    for (int i = 0; i<ROIVec.size(); i++)
    {		
		cv::line(InputImg, cv::Point(m_ROIS[i].Grid_Origin.x, 0), cv::Point(m_ROIS[i].Grid_Origin.x, InputImg.rows), cv::Scalar(0, 0, 0), 2);
		cv::line(InputImg, cv::Point(0, m_ROIS[i].Grid_Origin.y), cv::Point(InputImg.cols, m_ROIS[i].Grid_Origin.y), cv::Scalar(0, 0, 0), 2);

		if (m_ROIS[i].twoCircles)
        {			
			cv::Point centerL(cvRound(ROIVec[i].circleL_cent.x + ROIVec[i].Grid_Origin.x), cvRound(ROIVec[i].circleL_cent.y + ROIVec[i].Grid_Origin.y));
			cv::Point centerR(cvRound(ROIVec[i].circleR_cent.x + ROIVec[i].Grid_Origin.x), cvRound(ROIVec[i].circleR_cent.y + ROIVec[i].Grid_Origin.y));
            // int radiusL = cvRound(ROIVec[i].radiusLeft);
            // int radiusR = cvRound(ROIVec[i].radiusRight);
			// draw the circle center6
			cv::circle(InputImg, centerL, 1, cv::Scalar(0, 0, 255), -1, 8, 0);
			cv::circle(InputImg, centerR, 1, cv::Scalar(0, 0, 255), -1, 8, 0);

			if (m_setText==true)
			{
				sprintf(IDtext, "%i",  m_ROIS[i].ID);
				sprintf(DistText, "%.2f",  m_ROIS[i].distance);
            
				cv::putText(InputImg, "ROI ID: ", cv::Point(10 + ROIVec[i].Grid_Origin.x, 30 + ROIVec[i].Grid_Origin.y), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2, 8, false);
				cv::putText(InputImg, IDtext, cv::Point(120 + ROIVec[i].Grid_Origin.x, 30 + ROIVec[i].Grid_Origin.y), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 2, 8, false);
				cv::putText(InputImg, "Distance: ", cv::Point(10 + ROIVec[i].Grid_Origin.x, 60 + ROIVec[i].Grid_Origin.y), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2, 8, false);
				cv::putText(InputImg, DistText, cv::Point(180 + ROIVec[i].Grid_Origin.x, 60 + ROIVec[i].Grid_Origin.y), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 2, 8, false);
			}
			//these are the exact rois provided to the framegrabber!
			rectangle(InputImg, m_ROIS[i].OriginSubLeftImg, cv::Point(m_ROIS[i].OriginSubLeftImg.x + m_witdthSubROI, m_ROIS[i].OriginSubLeftImg.y + m_heightSubROI), cv::Scalar(255, 0, 200));
			rectangle(InputImg, m_ROIS[i].OriginSubRightImg, cv::Point(m_ROIS[i].OriginSubRightImg.x + m_witdthSubROI, m_ROIS[i].OriginSubRightImg.y + m_heightSubROI), cv::Scalar(255, 0, 200));
        }
        else
		{
			if (m_setText == true)
			{
				cv::putText(InputImg, "Circles not found - Error", cv::Point(80 + ROIVec[i].Grid_Origin.x, 100 + ROIVec[i].Grid_Origin.y), CV_FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2, 8, false);
			}
		}
    }
	cv::line(InputImg, cv::Point(InputImg.cols - 2, 0), cv::Point(InputImg.cols - 2, InputImg.rows), cv::Scalar(0, 0, 0), 2);
	cv::line(InputImg, cv::Point(0, InputImg.rows-2), cv::Point(InputImg.cols , InputImg.rows-2), cv::Scalar(0, 0, 0), 2);
	return InputImg;
}

//Colorize pixels after adaptive thresholding
cv::Mat  cRefImg::m_threshPreview(const cv::Mat InputImg,const std::vector<ROIInfo> &ROIVec, int thresh)
{
	cv::Mat InputImgOut = InputImg.clone();
	unsigned int areaLeft		= 0;
	unsigned int areaRight		= 0;

	uchar valL = 0;
	uchar valR = 0;

	cv::Rect ROIleft, ROIright;
	cv::Mat tempLMat, tempRMat;

	//Go through all rois
	for (int idx = 0; idx < ROIVec.size(); idx++)
	{
		if (ROIVec[idx].twoCircles)
		{
			unsigned int sumLeft = 0;
			unsigned int sumRight = 0;

			//According to the statement in the Visual Applets Help regading the ROI Operator:
			//If the offset coordinates are valid but the Xlength and / or Ylength coordinates exceed the image boundaries, the operator will shrink ROI to the image boundaries.
			//We proceed accordingly and perform the local averaging only on pixels that are within the cropped image!

			int newDxR		=	m_witdthSubROI;
			int newDyR		=	m_heightSubROI;
			int newDxL		=	m_witdthSubROI;
			int newDyL		=	m_heightSubROI;
			int newOffsetRx =	ROIVec[idx].OriginSubRightImg.x;
			int newOffsetRy =	ROIVec[idx].OriginSubRightImg.y;
			int newOffsetLx =	ROIVec[idx].OriginSubLeftImg.x;
			int newOffsetLy =	ROIVec[idx].OriginSubLeftImg.y;

			//Widths not fitting - adjust ROI width
			if ((ROIVec[idx].OriginSubRightImg.x + m_witdthSubROI) >= (unsigned int)InputImgOut.cols)
			{	
				int x	= ROIVec[idx].OriginSubRightImg.x;
				int dx	= m_witdthSubROI;
				newDxR = m_witdthSubROI-((x + dx) - InputImgOut.cols);
			}

			if ((ROIVec[idx].OriginSubLeftImg.x + m_witdthSubROI) >= (unsigned int)InputImgOut.cols)
			{
				int x = ROIVec[idx].OriginSubLeftImg.x;
				int dx = m_witdthSubROI;
				newDxL = m_witdthSubROI - ((x + dx) - InputImgOut.cols);
			}

			//Heights not fitting - adjust ROI heights
			if ((ROIVec[idx].OriginSubRightImg.y + m_heightSubROI) >= (unsigned int)InputImgOut.rows)
			{
				int y = ROIVec[idx].OriginSubRightImg.y;
				int dy = m_heightSubROI;
				newDyR = m_heightSubROI - ((y + dy) - InputImgOut.rows);
			}

			if ((ROIVec[idx].OriginSubLeftImg.y + m_heightSubROI) >= (unsigned int)InputImgOut.rows)
			{
				int y = ROIVec[idx].OriginSubLeftImg.y;
				int dy = m_heightSubROI;
				newDxL = m_heightSubROI - ((y + dy) - InputImgOut.rows);
			}

			//x Offsets are out of image
			if (ROIVec[idx].OriginSubRightImg.x < 0 )
			{
				newOffsetRx = 0;
				newDxR = m_witdthSubROI-abs(ROIVec[idx].OriginSubRightImg.x);
			}
			if (ROIVec[idx].OriginSubLeftImg.x < 0)
			{
				newOffsetLx = 0;
				newDxL = m_witdthSubROI - abs(ROIVec[idx].OriginSubLeftImg.x);
			}

			//y Offsets are out of image
			if (ROIVec[idx].OriginSubRightImg.y < 0)
			{
				newOffsetRy = 0;
				newDyR = m_heightSubROI - abs(ROIVec[idx].OriginSubRightImg.y);
			}
			if (ROIVec[idx].OriginSubLeftImg.y < 0)
			{
				newOffsetLy = 0;
				newDyL = m_heightSubROI - abs(ROIVec[idx].OriginSubLeftImg.y);
			}

			int x = ROIVec[idx].OriginSubLeftImg.x;
			int y = ROIVec[idx].OriginSubLeftImg.y;
			int dx = m_witdthSubROI;
			int dy = m_heightSubROI;

			ROIleft = cv::Rect(	newOffsetLx,
								newOffsetLy,
								newDxL,
								newDyL);

			ROIright = cv::Rect( newOffsetRx,
									newOffsetRy,
									newDxR,
									newDyR);

			areaLeft = newDxL*newDyL;
			areaRight = newDxR*newDyR;

			//local copies of the input image
			
			tempLMat = InputImgOut(ROIleft).clone();
			tempRMat = InputImgOut(ROIright).clone();
			
			cvtColor(tempLMat, tempLMat, CV_RGB2GRAY);
			cvtColor(tempRMat, tempRMat, CV_RGB2GRAY);

			unsigned char* pixelLeft = (unsigned char*)tempLMat.data;
			unsigned char* pixelRight = (unsigned char*)(unsigned char*)tempRMat.data;

			for (int i = 0; i < tempLMat.rows*tempLMat.cols; ++i)
			{
				sumLeft += *pixelLeft;
				pixelLeft++;
			}

			for (int i = 0; i < tempRMat.rows*tempRMat.cols; ++i)
			{
				sumRight += *pixelRight;
				pixelRight++;
			}

			float avgGVLeft  = static_cast<float>(sumLeft / areaLeft);
			float avgGVRight = static_cast<float>(sumRight / areaRight);
		
			//looping once more in order to color in thresholded values
			//Adaptive threshold: mean of roi + threshold
			for (int i = 0; i < tempLMat.rows; ++i)
			{
				uchar* pixelLeft = tempLMat.ptr<uchar>(i);  // point to first color in row
				for (int j = 0; j < tempLMat.cols; ++j)
				{
					if (*pixelLeft <= (avgGVLeft - thresh))	
					{
						InputImgOut.at<cv::Vec3b>(i + newOffsetLy, j + newOffsetLx)[0] = 255;
						InputImgOut.at<cv::Vec3b>(i + newOffsetLy, j + newOffsetLx)[1] = 0;
						InputImgOut.at<cv::Vec3b>(i + newOffsetLy, j + newOffsetLx)[2] = 0;
					}
					pixelLeft++;
				}
			}

			for (int i = 0; i < tempRMat.rows; ++i)
			{
				uchar* pixelRight = tempRMat.ptr<uchar>(i);  // point to first color in row
				for (int j = 0; j < tempRMat.cols; ++j)
				{
					if (*pixelRight <= (avgGVRight - thresh))
					{
						InputImgOut.at<cv::Vec3b>(i + newOffsetRy, j + newOffsetRx)[0] = 255;
						InputImgOut.at<cv::Vec3b>(i + newOffsetRy, j + newOffsetRx)[1] = 0;
						InputImgOut.at<cv::Vec3b>(i + newOffsetRy, j + newOffsetRx)[2] = 0;
					}
					pixelRight++;
				}
			}
		
			/* //Compare CPU output to FPGA Output - in Case of ME4 no problems!
			cROIEval testSpot;
			testSpot.m_getCOG(tempLMat, avgGVLeft - thresh);
			cv::Point2f CPUPoint = testSpot.getCogPt();
			cout << "ID = " << idx << "\t left Pt x = " << CPUPoint.x << "\t  y = " << CPUPoint.y << "\n";
			testSpot.m_getCOG(tempRMat, avgGVRight - thresh);
			CPUPoint = testSpot.getCogPt();
			cout << "ID = " << idx << "\t right Pt x = " << CPUPoint.x << "\t  y = " << CPUPoint.y << "\n";
			*/
		}
	}
	return InputImgOut;
}


//Save the current ROI Data to an xml-File
bool cRefImg::SaveRois(const std::string Filename)
{
	cv::FileStorage fs(Filename, cv::FileStorage::WRITE);
	//unsigned values cannot be saved!
    //First entry has to be a string followed by bracktes to indicate scope of node
    fs << "ROIData" << "{";
    fs << "Total_ROIS" << static_cast<int>( m_ROIS.size());
    
    for (int i = 0; i < m_ROIS.size(); i++)
    {
		string indx = to_string(static_cast<long long>(i));

        fs    << (string("twoCircles") + "_" + indx) << m_ROIS[i].twoCircles ;
        fs    << (string("Grid_Origin") + "_" + indx)<< m_ROIS[i].Grid_Origin ;
        fs    << (string("Origin") + "_" + indx) << m_ROIS[i].Origin;
        fs    << (string("OriginSubLeft") + "_" + indx) << m_ROIS[i].OriginSubLeft;
        fs    << (string("OriginSubRight") + "_" + indx) << m_ROIS[i].OriginSubRight;
        fs    << (string("OriginSubLeftImg") + "_" + indx) << m_ROIS[i].OriginSubLeftImg;
        fs    << (string("OriginSubRightImg") + "_" + indx) << m_ROIS[i].OriginSubRightImg;
        fs    << (string("SubOffset") + "_" + indx) << m_ROIS[i].SubOffset;
        fs    << (string("ID") + "_" + indx) << m_ROIS[i].ID;
        fs    << (string("witdth") + "_" + indx) << m_ROIS[i].witdth;
        fs    << (string("height") + "_" + indx) << m_ROIS[i].height;
        fs    << (string("SubWitdth") + "_" + indx) << m_ROIS[i].SubWitdth;
        fs    << (string("SubHeight") + "_" + indx) << m_ROIS[i].SubHeight;
        fs    << (string("SubWitdthL") + "_" + indx) << m_ROIS[i].SubWitdthL;
        fs    << (string("SubHeightL") + "_" + indx) << m_ROIS[i].SubHeightL;
        fs    << (string("SubWitdthR") + "_" + indx) << m_ROIS[i].SubWitdthR;
        //fs    << (string("Content") + "_" + to_string(static_cast<long long>(i))) << m_ROIS[i].Content;
        //fs    << (string("localMask") + "_" + to_string(static_cast<long long>(i))) << m_ROIS[i].localMask;
        fs    << (string("radiusLeft") + "_" + indx) << m_ROIS[i].radiusLeft;
        fs    << (string("radiusRight") + "_" + indx) << m_ROIS[i].radiusRight;
        fs    << (string("circleL_cent") + "_" +indx) << m_ROIS[i].circleL_cent;
        fs    << (string("circleR_cent") + "_" + indx) << m_ROIS[i].circleR_cent;
        fs    << (string("distance") + "_" + indx) << m_ROIS[i].distance;
    }
    fs << "}";
	fs.release();

	return true;
}

#ifdef txt //In case of txt output
void cRefImg::saveMeasTXT()
{
	QString		tsmp = QString("%1").arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz_"));
	MeasurementData measure = g_pFPGA_IFcore->m_CL_Applet->GetRB().getMeasData();

	QString path = g_pFPGA_IFcore->m_project.GetPath();
	QString Filename = path + "Measurement_" + tsmp + ".txt";
	QString Header = "MeasurementData_" + tsmp;

	ofstream fsOut ;
    
	fsOut.open(Filename.toStdString());//"/Users/nilskupper/Documents/writexml/res/measure.txt");

    if(fsOut.fail())
    {
        QMessageBox::warning(NULL, "File Saving Issue", "TXT-File could not be opened!");
        //return(false);
    }
    
	fsOut << Header.toStdString()/* date */ << "\n";
    fsOut << "Total ROIS "<< measure.nROIS << "\n";
    fsOut << "Total Samples " << measure.nSamples << "\n";
	fsOut << "Start Time Measurement " << tsmp.toStdString() << "\n";
    fsOut << "End Time Measurement " << -1 << "\n";
    
    //std::fixed << std::setprecision(8);
    
    for (int i = 0; i < measure.nROIS; i++)
    {
        fsOut << "RoiID " << i << "\n";
        
        fsOut << "Valid " << "\t" << "ROI Left x " << "\t" << "ROI Left y " << "\t" << "ROI Right x " <<  "ROI Right y" << "\n";
        
        
        fsOut << measure.validROI[i] << "\t" << /* measure.timestamp[i] <<*/ measure.leftROIImgCoordsx[i] << "\t" << measure.leftROIImgCoordsy[i]
        << "\t" <<measure.rightROIImgCoordsx[i] << "\t" << measure.rightROIImgCoordsy[i] <<"\n";
        
        fsOut << "Data at time " << "\n";
        
        fsOut << "#" << "\t" << "Lcogx" << "\t" << "Lcogy" << "\t" << "Rcogx" << "\t" << "Rcogy" <<  "\t" << "dist" <<  "\n";
        
        for (int j = 0; j < measure.nSamples; j++)
        {
            fsOut << j << "\t" << (double)measure.circleL_centROIx[i][j] << "\t" << (double)measure.circleL_centROIy[i][j] <<
            "\t" << (double)measure.circleR_centROIx[i][j] << "\t"  << (double)measure.circleR_centROIy[i][j] <<
            "\t"  <<(double)measure.distance[i][j] << "\n";
        }
    }
    fsOut.close();
}
#endif


//Test output - opencv output equal to fpga Output?
bool cRefImg::PrintOCV_COGData()
{
	QString path = "";
	QString Filename = "C:/Users/RB/Desktop/cogs.txt";

	std::ofstream fsOut;

	fsOut.open(Filename.toStdString());//"/Users/nilskupper/Documents/writexml/res/measure.txt");

	if (fsOut.fail())
	{
		QMessageBox::warning(NULL, "File Saving Issue", "TXT-File could not be opened!");
		//return(false);
	}

	fsOut << "Total ROIS " << m_ROIS.size() << "\n";

	for (int i = 0; i < m_ROIS.size(); i++)
	{
		if (m_ROIS[i].twoCircles == true)
		{
			double centerSubRoiXRight = m_ROIS[i].circleR_cent.x + m_ROIS[i].Grid_Origin.x;
			double centerSubRoiYRight = m_ROIS[i].circleR_cent.y + m_ROIS[i].Grid_Origin.y;

			double centerSubRoiXLeft = m_ROIS[i].circleL_cent.x + m_ROIS[i].Grid_Origin.x;;
			double centerSubRoiYLeft = m_ROIS[i].circleL_cent.y + m_ROIS[i].Grid_Origin.y;;

			fsOut <<"index = " << i << "Spt Right X " << centerSubRoiXRight << "\n";
			fsOut <<"index = " << i << "Spt Right Y " << centerSubRoiYRight << "\n";

			fsOut << "index = " << i << "Spt Left X " << centerSubRoiXLeft << "\n";
			fsOut << "index = " << i << "Spt Left Y " << centerSubRoiYLeft << "\n";

			double Distx = (centerSubRoiXRight)-(centerSubRoiXLeft);
			double Disty = (centerSubRoiYRight)-(centerSubRoiYLeft);

			double dist = sqrt(Distx*Distx + Disty*Disty);

			fsOut << "index = " << i << "dist " << dist << "\n";

			/*
			m_ROIS[i].OriginSubLeftImg.x = tmpOrigSubLxImg - modposxL;
			m_ROIS[i].OriginSubLeftImg.y = tmpOrigSubLyImg - modposyL;

			m_ROIS[i].OriginSubRightImg.x = tmpOrigSubRxImg - modposxR;
			m_ROIS[i].OriginSubRightImg.y = tmpOrigSubRyImg - modposyR;

			*/
		}
	}
	fsOut.close();

	return true;
}

//Load previous ROI data from XML-File - Test whether old resolution fits to current resolution should be implemented
std::vector<ROIInfo> cRefImg::LoadRois(const std::string Filename)
{
	cv::FileStorage fs(Filename, cv::FileStorage::READ);
	std::vector<ROIInfo> RoisVec;
    cv::FileNode fn = fs["ROIData"];
    if (fn.empty())
    {
		fs.release();
		QMessageBox::warning(NULL, "File not found", "No ROIS.xml File found!");
        return RoisVec;
    }
    int size;
    fn["Total_ROIS"] >> size;
    RoisVec.resize(size);
    
    for (int i = 0; i < size; i++)
    {
		string indx = to_string(static_cast<long long>(i));

        fn[(string("twoCircles") + "_" + indx)] >> RoisVec[i].twoCircles ;
        fn[(string("Grid_Origin") + "_" +indx)] >> RoisVec[i].Grid_Origin ;
        fn[(string("Origin") + "_" + indx)] >> RoisVec[i].Origin;
        fn[(string("OriginSubLeft") + "_" + indx)] >> RoisVec[i].OriginSubLeft;
        fn[(string("OriginSubRight") + "_" + indx)] >> RoisVec[i].OriginSubRight;
        fn[(string("OriginSubLeftImg") + "_" + indx)] >> RoisVec[i].OriginSubLeftImg;
        fn[(string("OriginSubRightImg") + "_" + indx)] >> RoisVec[i].OriginSubRightImg;
        fn[(string("SubOffset") + "_" + indx)] >> RoisVec[i].SubOffset;
        fn[(string("ID") + "_" + indx)] >> RoisVec[i].ID;
        fn[(string("witdth") + "_" + indx)] >> RoisVec[i].witdth;
        fn[(string("height") + "_" + indx)] >> RoisVec[i].height;
        fn[(string("SubWitdth") + "_" + indx)] >> RoisVec[i].SubWitdth;
        fn[(string("SubHeight") + "_" + indx)] >> RoisVec[i].SubHeight;
        fn[(string("SubWitdthL") + "_" + indx)] >> RoisVec[i].SubWitdthL;
        fn[(string("SubHeightL") + "_" + indx)] >> RoisVec[i].SubHeightL;
        fn[(string("SubWitdthR") + "_" + indx)] >> RoisVec[i].SubWitdthR;
        //fs    << (string("Content") + "_" + indx) << m_RoisOut[i].Content;
        //fs    << (string("localMask") + "_" + indx) << m_RoisOut[i].localMask;
        fn[(string("radiusLeft") + "_" + indx) ] >> RoisVec[i].radiusLeft;
        fn[(string("radiusRight") + "_" + indx) ] >> RoisVec[i].radiusRight;
        fn[(string("circleL_cent") + "_" + indx)] >> RoisVec[i].circleL_cent;
        fn[(string("circleR_cent") + "_" + indx)] >> RoisVec[i].circleR_cent;
        fn[(string("distance") + "_" + indx) ] >> RoisVec[i].distance;
    }
	fs.release();
	
	return RoisVec;
}

cRefImg::~cRefImg()
{

}