/*
	Copyright (C) 2016  	Nils Küpper

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

*/
#include <SiSo_AppletIF.h>

SiSo_AppletIF::SiSo_AppletIF		(FPGA_IF_Core& core):m_core(core), m_RB(core)
{
	this->m_run				=	false;
	this->m_startallowed	=	false;
	this->m_bufferconnected	=	false;
	this->m_DMAsUsed		=	0;
	this->m_fg				=	NULL;
#ifdef _DEBUG
	this->m_update_timer_ms	=	200;
#else
	this->m_update_timer_ms	=	200;
#endif
	this->m_framerate		=	(float)1.;
	this->m_modulo			=	 __PARALLEL_MODULO__;
//	this->m_TriggerMode	= TrgPortArea::GrabberControlled;
}

//Free resources upoun shutdown
SiSo_AppletIF::~SiSo_AppletIF		()
{
	DisconnectGrabBuffer();
}
	

bool	SiSo_AppletIF::Init			()
{
	MESSAGE("SiSo_AppletIF::Init()");
	connect(&this->m_update_timer,	SIGNAL(timeout()),	this, SLOT(Update()));
	connect(this,			SIGNAL(timerstart()),	this, SLOT(slottimerstart()));//, Qt::BlockingQueuedConnection);
	connect(this,			SIGNAL(timerstop()),	this, SLOT(slottimerstop()));
	return true;
}


void	SiSo_AppletIF::DeInit			()
{
	MESSAGE("SiSo_AppletIF::DeInit()");
	disconnect(&this->m_update_timer,	SIGNAL(timeout()),	this, SLOT(Update()));
	disconnect(this,			SIGNAL(timerstart()),	this, SLOT(slottimerstart()));
	disconnect(this,			SIGNAL(timerstop()),	this, SLOT(slottimerstop()));
	DisconnectGrabBuffer();
}

//Read ini file
bool SiSo_AppletIF::ReadIni		(MIniFile& ini)
{
	this->GetRB().m_myRef.ReadIni(ini);
	return true;
}

//Write ini file
bool SiSo_AppletIF::WriteIni		(MIniFile& ini)
{
	this->GetRB().m_myRef.WriteIni(ini);
	return true;
}

//Start timer
void	SiSo_AppletIF::slottimerstart			()
{
	MESSAGE("Timer Start");
	m_update_timer.start(this->m_update_timer_ms); 
}

//Stop timer
void	SiSo_AppletIF::slottimerstop			()
{
	m_update_timer.stop(); 

	MESSAGE("Timer Stop");
	emit this->updateLiveGrab(false);
}

//Connect buffer - Create actual memory interface between DMA of FPGA and CPU
bool	SiSo_AppletIF::ConnectGrabBuffer			()
{

	this->DisconnectGrabBuffer();
	MESSAGE("ConnectGrabBuffer");

	int jj;
	int bytePerPixel = 1; //For now only grey value cameras are supported

	long	bufcount = this->m_RB.GetSize();
	FPGA_IF_Img	*imgs = &this->m_RB.GetElement(0);

	for (int dma = 0; dma < this->m_DMAsUsed; dma++)
	{
		long bufsize = imgs->GetByteSize(dma);
		// alloc user memory header
		if (	(this->m_DMA[dma].sdma.pmem = Fg_AllocMemHead( this->m_fg,bufsize * bufcount, bufcount))== NULL)
		{
			Fg_Error(this->m_fg);
			fprintf(stdout,"%d framebuffer could not be allocated\n",bufcount);
			return false;
		}
		else
			fprintf(stdout,"%d framebuffer allocated for port 0 ok\n",bufcount);
	}

	// connect user memory with header
	for (int imgbuf = 0; imgbuf < bufcount; imgbuf++)
	{
		imgs = &this->m_RB.GetElement(imgbuf);
		for (int dma = 0; dma < this->m_DMAsUsed; dma++)
		{
			long bufsize = imgs->GetByteSize(dma);
			jj = Fg_AddMem
				(
					this->m_fg, 
					imgs->GetBuffer(dma),
					bufsize, 
					imgbuf, 
					this->m_DMA[dma].sdma.pmem
				);

			if (jj <0) 
			fprintf(stderr, "error in Fg_AddMem: %s\n", Fg_getLastErrorDescription(this->m_fg));
			//else
			//printf("Allocated additional memory for %i Frames in DMA Port %i by Fg_AddMem:\n",jj,dma);
		}
	}

	this->m_bufferconnected = true;

	return true;
}

//Disconnect buffer - release memory interface interface between DMA of FPGA and CPU and free ressources
bool	SiSo_AppletIF::DisconnectGrabBuffer			()
{
	if (!this->m_bufferconnected)
		return true;

	MESSAGE("DisconnectGrabBuffer");
	
	for (int dma = 0; dma < this->m_DMAsUsed; dma++)
	{
		// disconnect user memory
		for(long i = 0; i < (long)this->m_RB.GetSize(); i++)
		{
			Fg_DelMem(this->m_fg, this->m_DMA[dma].sdma.pmem, i);
			if (dma == 0)
				this->m_RB.m_buffer.find(i)->second->m_ImgDMA0.release();
			if (dma == 1)
 				delete [] this->m_RB.m_buffer.find(i)->second->m_ImgDMA1Buffer;
			if (dma == 2)
 				delete [] this->m_RB.m_buffer.find(i)->second->m_ImgDMA2Buffer;
		}
		// Release of the memory header
		Fg_FreeMemEx(this->m_fg, this->m_DMA[dma].sdma.pmem);
	} 

	this->m_bufferconnected = false;
	return true;
}


