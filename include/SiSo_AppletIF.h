/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef FPGA_IF_CL_APPLETIF_INCLUDED
#define FPGA_IF_CL_APPLETIF_INCLUDED

class FPGA_IF_Core;

#define MAXFPGAROISIZEX	256	// Defines maximum size limitation for each ROI in case of FPGA calcualation
#define MAXFPGAROISIZEY	256

#pragma once
#include <QThread>
#include <CL.h>
#include <CoaXPress.h>
#include <defines.h>
#include <Ringbuffer.h>
#include <QTimer>
#include <inifile.h>
#include <QElapsedTimer>

typedef struct
{
	LPoint			size;
	int				byteWidth;
	dma_mem			*pmem;
	int				status[2];
	int				count;
}sDMA;

typedef struct DMAThreadArgs
{
public:
	QString			name;
	sDMA			sdma;
	int				dmaNr;
} DMAThreadArgs;


class SiSo_AppletIF : public QThread
{
	Q_OBJECT
public:
						SiSo_AppletIF		(FPGA_IF_Core& core);
	virtual				~SiSo_AppletIF		();
	FPGA_IF_Core&		m_core;
	virtual void		run					() = 0;
	virtual bool		Init				() = 0;
	virtual void		DeInit				() = 0;
	virtual void		Param				() = 0;
	virtual bool		ReadIni				(MIniFile& ini);
	virtual bool		WriteIni			(MIniFile& ini);
	QElapsedTimer		timer;
	bool				IsAllowedtoStart	(){return this->m_startallowed;}
	void				start				(Priority = InheritPriority)
											{		
												this->m_run = true;
												timer.start();
												emit timerstart();
												emit updateLiveGrab(true);
												QThread::start();
											}
	void				stop				()
											{
												this->m_run=false; 
												this->wait();
												this->Update(this->m_RB.GetActualImgNum());
											}

	virtual bool		ShowDoc				(QString name, bool show){return true;}
	bool				ConnectGrabBuffer	();
	bool				DisconnectGrabBuffer();
	virtual bool		SetImageBuffer		(long count) = 0;
	void				SetGrabCount		(long count){if (count < 0) count = -1; m_grabcount = count;}
	long				GetGrabCount		(){return m_grabcount;}
	void				SetGrabTime			(long duration){m_DurMSec = duration;}
	long				GetGrabTime			(){return m_DurMSec;}
	long				GetImageBufferCount	(){return (long)this->m_RB.GetSize();}
	virtual void		ProcessImages		(FPGA_IF_Img* imgs = NULL, bool showDLg = false, bool consoleOut = false){}
	virtual void		ProcessImagesMean	(){}

	TrgPortArea::TriggerModeN GetTriggerMode(){return this->m_TriggerMode;}
	virtual void		SetTriggerMode		(TrgPortArea::TriggerModeN triggermode) = 0;

	Fg_Struct*			GetFG				()const{return this->m_fg;}
	
	void				ChangeUpdateInterval(int time_ms){m_update_timer.setInterval(m_update_timer_ms = time_ms);}
	int					GetUpdateInterval	(){return m_update_timer_ms;}
	virtual void		SetTrigger			(bool swt) = 0;
	virtual void		SetRoIs				() = 0;
	virtual void		SetMainRoI			() = 0;
	int					GetModulo			(){return this->m_modulo;}
	virtual void		SetThresholdMin		(int thresh = -1) = 0;
	virtual int			GetThresholdMin		(){return 0;}
	
	virtual float		GetFramrate			(){return this->m_framerate;}
	void				SetFramrate			(float fps){this->m_framerate = fps;}

	virtual void		SetROIWidth			(int width = -1) = 0;
	virtual inline int	GetROIWidth			(){return -1;}

	virtual void		SetROIHeight		(int height = -1) = 0;
	virtual inline int	GetROIHeight		(){return -1;}

	virtual void		SetROIId			(int Id = -1) = 0;
	virtual inline int	GetROIId			(){return -1;}

	virtual void		SetMaxAmp			(int ampl = -1) = 0;
	virtual inline int	GetMaxAmp			(){ return -1; }

	virtual void		SetNSamples			(int nSamp = -1) = 0;
	virtual inline int	GetNSamples			(){ return -1; }

	Ringbuffer&			GetRB				(){return this->m_RB;}		

	bool				m_run;


	DMAThreadArgs		m_DMA[MAXDMA]; //protected
protected:
	bool				m_startallowed;
	bool				m_bufferconnected;

	QTimer				m_update_timer;
	int					m_update_timer_ms;

protected slots:
	virtual void		Update				(int frm = -1) = 0;
	virtual void		slotCalcMonitoring	() = 0;
	void				slottimerstart		();
	void				slottimerstop		();

signals:
	void				updateLiveGrab		(bool running);
	void				updateRingBufferCount(long ccount, long icount);
	void				updateImageView		(int imgnum);
	void				updateMeanImageView	();
	void				updateGUIFit		(int imgnum);
	void				updateMonitoring	(FPGA_IF_Img* imgs);
	void				timerstart			();
	void				timerstop			();

public:
	Fg_Struct*			m_fg;
protected:
	
	int					m_DMAsUsed;
	Ringbuffer			m_RB;
	long				m_grabcount;

	QTime				m_grabDuration;
	long				m_DurMSec;

	float				m_framerate;
	TrgPortArea::TriggerModeN m_TriggerMode;
	int					m_modulo;
	
	QString				m_hap;
	
};
//----------------------------------------------------------------

#endif //FPGA_IF_CL_APPLETIF_INCLUDED