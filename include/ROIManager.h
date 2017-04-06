/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef ROIMANAGER_INCLUDED
#define ROIMANAGER_INCLUDED

using namespace std;

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <defines.h>
#include <inifile.h>

typedef struct CornerPoints
{
    cv::Point2f topLeft, topRight, bottomLeft, bottomRight;
    
}CornerPoints;

typedef struct ROIInfo
{
    bool            twoCircles;
    
    cv::Point       Grid_Origin;			//Topleft corner derived from equidistant grid with respect to img origin
    cv::Point       Origin;					//Top Left Corner of ROI with two dots with respect to Grid_Origin		this may be used to live display a single roi with two dots - maybe later
	cv::Point       OriginSubLeft;			//Top Left Corner of roi of left dot with respect to Grid_Origin		Used for visualization and intermittend results only!
	cv::Point       OriginSubRight;			//Top Left Corner of roi of right dot with respect to Grid_Origin		Used for visualization and intermittend results only!
	cv::Point       OriginSubLeftImg;		//Top Left Corner of roi of left dot with respect to img origin     Use this value for distance calculation!!!
	cv::Point       OriginSubRightImg;		//Top Left Corner of roi of right dot  with respect to img origin	Use this value for distance calculation!!!
    
	cv::Point       SubOffset;				//If selected roisize is smaller than Maximum roisize in applet,	an offset has to be added
    
    int				ID;						//ID of ROI
    int				witdth;					//Width of ROI
    int				height;					//Height of ROI
    int				SubWitdth;				//Width of ROI
    int				SubHeight;				//Height of ROI
    
	int				SubWitdthL;				//Width of individual ROI Left
    int				SubHeightL;				//Height of individual ROI Left
	int				SubWitdthR;				//Width of individual ROI right
    int				SubHeightR;				//Height of individual ROI right
    cv::Mat         Content;				//Original Image content in Cropped Region
    float           radiusLeft;				//avergae Radius of left circle
    float           radiusRight;			//avergae Radius of right circle
    cv::Point2f     circleL_cent;			//Center of left circle
    cv::Point2f     circleR_cent;			//Center of right circle
    float           distance;				//Distance of two points    
}ROIInfo;

typedef struct MeasurementData
{
    int nSamples;
    int nROIS;
    vector<int>					validROI;
	vector<QString>				measTstamp;
	vector<int>					leftROIImgCoordsx;          //Top Left Corner of roi of left dot with respect to img origin     Use this value for distance calculation!!!
    vector<int>					leftROIImgCoordsy;          //Top Left Corner of roi of left dot with respect to img origin     Use this value for distance calculation!!!
	vector<int>					rightROIImgCoordsx;         //Top Left Corner of roi of right dot  with respect to img origin	Use this value for distance calculation!!!
    vector<int>					rightROIImgCoordsy;         //Top Left Corner of roi of right dot  with respect to img origin	Use this value for distance calculation!!!
    vector<vector<float> >		circleL_centROIx;			//Center of left circle in ROI Coords
    vector<vector<float> >		circleL_centROIy;			//Center of right circle in ROI Coords
    vector<vector<float> >		circleR_centROIx;			//Center of left circle in ROI Coords
    vector<vector<float> >		circleR_centROIy;			//Center of right circle in ROI Coords
    vector<vector<double> >     distance;					//absolute distance of the centers of gravity
	vector<list<double> >		distancePlot;					//absolute distance of the centers of gravity
}MeasurementData;

class cRefImg{
    
public:
    cRefImg();
     ~cRefImg();

    //Public member Functions
    cv::Mat					m_getROICoords      (cv::Mat InputImg);
   
	void					clear				();
	std::vector<ROIInfo>	getROIs				()	{return m_ROIS;};
	void					setROIs				(std::vector<ROIInfo> input)	{ m_ROIS = input;};
	ROIInfo					getROI				(int index)		{return m_ROIS[index];};					
	cv::Point				getROIPosPairImg	(int index)	
												{
													cv::Point dd;
													dd.x = m_ROIS[index].Grid_Origin.x+m_ROIS[index].Origin.x;
													dd.y = m_ROIS[index].Grid_Origin.y+m_ROIS[index].Origin.y;
													return dd;
												};

	cv::Point				getROIPosGrid		(int index)	{return m_ROIS[index].Grid_Origin;};			

	cv::Point				getROIPosLeft		(int index)		{return m_ROIS[index].OriginSubLeftImg;};	
	cv::Point				getROIPosRight		(int index)		{return m_ROIS[index].OriginSubRightImg;};

	int						getHeightROI		()		{return m_ROIS[1].witdth;};
	int						getWidthROI			()		{return m_ROIS[1].height;};
	double					getDist				(int index){return m_ROIS[index].distance;};
	

	//setter/getter methoden
	void					setWidthSubROI		(int value)	{m_witdthSubROI = value;}
	void					setHeightSubROI		(int value)	{m_heightSubROI = value;}
	int						getWidthSubROI		()			{return m_witdthSubROI;}
	int						getHeightSubROI		()			{return m_heightSubROI;}
	
	void					setTotalX			(int value)	{m_totalX = value;}
	void					setTotalY			(int value)	{m_totalY = value;}
	unsigned int			getTotalX			()			{return m_totalX;}
	unsigned int			getTotalY			()			{return m_totalY;}
	unsigned int			getTotalROIs		()			{return m_totalY*m_totalX;}

	void					SetThresh			(int value)	{ m_thresh = value; }
	void					SetConvexity		(int value)	{ m_Convexity = value; }
	void					SetCircularity		(int value)	{ m_Circularity = value; }
	void					SetDistBetween		(int value)	{ m_DistBetween = value; }
	void					SetMinArea			(int value)	{ m_MinArea = value; }
	void					SetMaxArea			(int value)	{ m_MaxArea = value; }

	int						GetThresh			(){ return m_thresh; }
	int						GetConvexity		(){ return m_Convexity; }
	int						GetCircularity		(){ return m_Circularity; }
	int						GetDistBetween		(){ return m_DistBetween; }
	int						GetMinArea			(){ return m_MinArea; }
	int						GetMaxArea			(){ return m_MaxArea; }

	bool					m_ROISset;

	bool			cRefImg::ReadIni			(MIniFile& ini);
	bool			cRefImg::WriteIni			(MIniFile& ini);

	cv::Mat					m_VisResults		(cv::Mat &InputImg, std::vector<ROIInfo> &ROIVec, int thresh);
	cv::Mat					m_threshPreview		(const cv::Mat InputImg, const std::vector<ROIInfo> &ROIVec, int thresh);
	bool					SaveRois			(const std::string Filename);
	bool					PrintOCV_COGData	();
	std::vector<ROIInfo>	LoadRois			(const std::string Filename);

private:
		
	bool			m_setText;			
    unsigned int    m_witdthROI;        //Width of main ROI
    unsigned int    m_heightROI;        //Height of main ROI
    unsigned int    m_witdthSubROI;     //Width of refined ROI
    unsigned int    m_heightSubROI;     //Height of refined ROI

    unsigned int    m_totalX;           //number of ROIs in x direction
    unsigned int    m_totalY;           //number of ROIs in y direction
    unsigned int    m_spacing;          //space between roi tiles for visalization
	unsigned int    m_ROISubOffSet;     //space between roi tiles for visalization

	int				m_thresh;			//threshold for blob analysis
	int				m_Convexity;		//min Convexity for blob analysis
	int				m_Circularity;		//min Circularity for blob analysis
	int				m_DistBetween;		//min distance between for blob analysis
	int				m_MinArea;			//min area for blob analysis
	int				m_MaxArea;			//max area for blob analysis

    cv::Mat         m_ROIarray;         //Array containing all 48 ROIs
    cv::Mat         m_GlobalMask;       //Global Mask
    cv::Mat         m_Shading;          //Global shading Template
	cv::Mat         m_InputMats;        //Variable array of input mats for averaging
    
    CornerPoints    m_CornerCoords;     //Coordinates of the border
    std::vector<ROIInfo> m_ROIS;
    
    std::vector<cv::KeyPoint> m_blobAnaysis (cv::Mat &InputMat);
    CornerPoints    m_getCorners			(cv::Mat &InputImg);
	
    void			m_getROIGrid			(CornerPoints &CornerPts, cv::Size InSize, int *);
    void			m_getROIArray			(cv::Mat &InputImg,  int *GridCoords);
    void			m_getSubROI				(std::vector<ROIInfo> &ROIVec);
    int				m_readImages			(unsigned int, unsigned int );
    void			m_GetStatistics			(std::vector<ROIInfo> &ROIVec);
};

#endif