/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/


#ifndef FPGA_IF_CL_APPLETMIN_INCLUDED
#define FPGA_IF_CL_APPLETMIN_INCLUDED

#include "SiSo_AppletIF.h"
#include "defines.h"

class SiSo_AppletMin : public SiSo_AppletIF
{
	Q_OBJECT
public:
						SiSo_AppletMin	(FPGA_IF_Core& core);
	virtual				~SiSo_AppletMin	();
	
	virtual void		run				();
	virtual bool		Init			();
	virtual void		DeInit			();
	virtual void		Init_ThreadArgs	();
	virtual void		Param			();

	virtual bool		ReadIni			(MIniFile& ini);
	virtual bool		WriteIni		(MIniFile& ini);

	bool				SetImageBuffer	(long count);
	virtual void		SetTrigger		(bool swt);

	int					m_thresh_min;						//threshold for framegrabber


	int					m_ROIWidth;
	int					m_ROIHeight;
	int					m_ROIId;

	//Plot axes
	int					m_maxAmpl;
	int					m_NSamples;

	void				SetRoIs			();
	void				SetMainRoI		();


#ifdef __USE_COEFFICIENT_BUFFER__
	void				CoeffBuffParam	();
#endif

	//DMA Params
	LPoint				m_DMA0Size;
	LPoint				m_DMA1Size;
	LPoint				m_DMA2Size;
	
	virtual void		SetThresholdMin		(int thresh = -1);
	virtual int			GetThresholdMin		(){return this->m_thresh_min;}
	virtual void		SetROIWidth			(int width = -1);
	virtual inline int	GetROIWidth			(){return this->m_ROIWidth;}
	virtual void		SetROIHeight		(int height = -1);
	virtual inline int	GetROIHeight		(){return this->m_ROIHeight;}
	virtual void		SetROIId			(int Id = -1);
	virtual inline int	GetROIId			(){return this->m_ROIId;}
	virtual void		SetMaxAmp			(int ampl = -1);
	virtual inline int	GetMaxAmp			(){ return this->m_maxAmpl; }
	virtual void		SetNSamples			(int nSamp = -1);
	virtual inline int	GetNSamples			(){ return this->m_NSamples; }
	const char			*m_applet;
	virtual void		SetTriggerMode		(TrgPortArea::TriggerModeN triggermode);

protected slots:
	virtual void		Update				(int frm);
	virtual void		slotCalcMonitoring	();

public:
	void				iDMA0					();
	void				iDMA1					();
	void				iDMA2					();
};
//----------------------------------------------------------------

#endif //FPGA_IF_CL_APPLETCOG_INCLUDED