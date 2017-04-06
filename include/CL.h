/*
	CL.h
	Milan Multi-Platform Imaging Language, an open source image processing library

	Copyright (C) 2008  	Harald Kloess

				h_da University of Applied Sciences
				Faculty of Mathematics and Science
				Dept. Computer Vision and Photonics

				Schoefferstr. 3
				D-64295 Darmstadt
				Germany

	This program is free software; you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software Foundation version 2 of the License

	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
	even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
	Public License for more details.

	You should have received a copy of the GNU General Public License along with this program; if not, write
	to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA

	Dieses Programm ist freie Software. Sie koennen es unter den Bedingungen der GNU General Public License, wie
	von der Free Software Foundation veroeffentlicht, weitergeben und/oder modifizieren, gemaess Version 2 der Lizenz.

	Die Veroeffentlichung dieses Programms erfolgt in der Hoffnung, dass es Ihnen von Nutzen sein wird, aber OHNE
	IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FUER EINEN BESTIMMTEN
	ZWECK. Details finden Sie in der GNU General Public License.

	Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht,
	schreiben Sie an die Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA.
*/

#ifndef CL_INCLUDED
#define CL_INCLUDED
//----------------------------------------------------------------

#include <QString>
#include <QMessagebox>
#include "defines.h"

#ifndef __CL_SISO__

// includes for SiliconSoftware framegrabber
#include "fgrab_prototyp.h"
#include "fgrab_struct.h"
#include "fgrab_define.h"
#include "clser.h"

// Prototypes
void Fg_Error(Fg_Struct *fg);



namespace CameraGrayAreaBase 
{
	enum DvalMode 
	{
		DVAL_Enabled	= 1,
		DVAL_Disabled	= 0
	};
	enum CLformat 
	{
		SingleTap8Bit	= 0,
		SingleTap10Bit	= 1,
		SingleTap12Bit	= 2,
		SingleTap14Bit	= 3,
		SingleTap16Bit	= 4,
		DualTap8Bit	= 5,
		DualTap10Bit	= 6,
		DualTap12Bit	= 7
	};
}

namespace SYNC 
{
	enum m_t_SyncModeType
	{
		SyncToMin = 0,
		SyncToMax = 1
	};
}

namespace Histogram 
{
	enum m_t_AutoSyncMode {
		EoL	= 0,
		EoF	= 1
	};
}

namespace ImageBufferMultiRoI 
{
	enum m_e_ModeType {
		FreeRun	= 0,
		WaitAfterImage	= 1,
		WaitAfterRoI	= 2
	};
}

namespace TrgPortArea 
{
	enum TriggerModeN {
		GrabberControlled	= 1,
		ExternSw_Trigger	= 2
	};
	enum EnableN {
		OFF	= 0,
		ON	= 1,
		NOTSET	=-1
	};
	enum ImageTrgInSourceN {
		InSignal0	= 0,
		InSignal1	= 1,
		InSignal2	= 2,
		InSignal3	= 3,
		SoftwareTrigger	= 4
	};
	enum PolarityN {
		HighActive	= 0,
		LowActive	= 1
	};
	enum CCsourceN {
		Exsync	= 0,
		ExsyncInvert	= 1,
		Hdsync	= 2,
		HdsyncInvert	= 3,
		Flash	= 4,
		FlashInvert	= 5,
		Clk	= 6,
		Gnd	= 7,
		Vcc	= 8
	};
}


namespace ImageNumber 
{
	enum SingleShotMode 
	{
		Off	= 0,
		On	= 1
	};
}

//Camera Link Functionality

class CL_Serial
{
public:
				CL_Serial	();
				~CL_Serial	();

private:
	long			m_status;

	void*  			m_serialRef;  		//Contains a reference pointer to the serial interface.
	uint			m_bufferSize; 		//Number of data to transfer.
	uint 			m_timeout; 			//Timeout in ms.
	QString			m_internalBuffer;
	char			m_lastchar;
	ulong			m_board, m_port;

public:
#define	SiSoSerBufSize	2048
	char			m_buffer[SiSoSerBufSize];	//pointer to the data buffer

	bool			Open		(Fg_Struct* fg, ulong board, ulong port);
	bool			Close		();
	bool			Write		(Fg_Struct* fg, QString cmd);
	bool			Read		(Fg_Struct* fg);
	void			SetLastChar	(char chr){this->m_lastchar = chr;}
	QString&		GetBuffer	(){return this->m_internalBuffer;}
	QString			GetBufferSimple	()
					{
						return this->m_internalBuffer.simplified();
					}
	bool			GetBufferInt	(int &val)	
					{
						bool ok;
						int tmp;
						tmp = this->m_internalBuffer.simplified().section(' ',0, -2).toInt(&ok);
						if (ok) val = tmp;
						return ok;
					}
	bool			GetBufferFloat	(float &val)
					{
						bool ok;
						float tmp;
						tmp = this->m_internalBuffer.simplified().section(' ',0, -2).toFloat(&ok);
						if (ok) val = tmp;
						return ok;
					}

};
//----------------------------------------------------------------
#else

#define Fg_Struct void

#endif //__CL_SISO__
//----------------------------------------------------------------

#endif //CL_INCLUDED
