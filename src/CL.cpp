/*
	CL.cpp
	Milan Mult i-Platform Imaging Language, an open source image processing library

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

#include "CL.h"
#include <stdio.h>
#include "defines.h"	// Makros MIN, MAX etc.
//----------------------------------------------------------------

void Fg_Error(Fg_Struct *fg)
{
	int		error;
	const char*	str	= Fg_getLastErrorDescription(fg);
	error		= Fg_getLastErrorNumber(fg);
	fprintf(stdout,"Fg_Error(%d): %s\n",error,str);
}
//----------------------------------------------------------------

CL_Serial::CL_Serial	()
{
	this->m_status		= 0;
	this->m_serialRef	= NULL;
	this->m_buffer[0]	= '\0';
	this->m_bufferSize	= 0;
	this->m_timeout		= 1000;
	this->m_lastchar	= '\0';
	this->m_board		= 0;
	this->m_port		= 0;
}
//----------------------------------------------------------------

CL_Serial::~CL_Serial	()
{
	this->Close();
}
//----------------------------------------------------------------

bool	CL_Serial::Open		(Fg_Struct* fg, ulong board, ulong port)
{
	if (!fg)
		return false;

	if (this->m_serialRef)
		this->Close();

	if ((this->m_status = clSerialInit(board+port, &this->m_serialRef)) < 0)
	{
		// Error
		QMessageBox::information(0, "CL seriell"
			, QString(	"Die serielle Schnittstelle (RS232)\n"
					"im CL-Port %1 des SiSo Boards %2\n"
					"kann nicht geöffnet werden!")
					.arg(port % 2 == 0 ? "A" : "B").arg(board/2));
		return false;
	}

	MESSAGE("CL_Serial::Open()");

	this->m_board		= board;
	this->m_port		= port;

	return true;
}
//----------------------------------------------------------------

bool	CL_Serial::Close	()
{
	if (!this->m_serialRef)
		return false;

	MESSAGE("CL_Serial::Close()");
	clFlushPort	(this->m_serialRef);
	clSerialClose	(this->m_serialRef);
	this->m_serialRef = NULL;
	this->m_board		= 0;
	this->m_port		= 0;
	return true;
}
//----------------------------------------------------------------

bool	CL_Serial::Write		(Fg_Struct* fg, QString cmd)
{

	int ConnectTry	= 0;
	int maxTry		= 10;

	if (!fg)
		return false;

	if (!this->m_serialRef)
	{
		QMessageBox::information(0, "CL seriell"
			, QString(	"Die serielle Schnittstelle (RS232)\n"
					"ist nicht geöffnet!"));
		return false;
	}

	this->m_bufferSize = MIN(2047, cmd.length());
	_snprintf_s(this->m_buffer, SiSoSerBufSize, this->m_bufferSize, "%s", cmd.toLatin1().data());

	//MESSAGE("CL_RS232 (" << (int)m_board << "," << ((m_port % 2) == 0 ? "A" : "B") << ") w: " << this->m_buffer);

	clFlushPort	(this->m_serialRef);

	if ((this->m_status = 
	clSerialWrite(	  this->m_serialRef
			, this->m_buffer
			, &this->m_bufferSize
			, this->m_timeout)
		) < 0)
	{
		clGetErrorText(this->m_status, this->m_buffer, &this->m_bufferSize);
		return false;
	}

	while(!this->Read(fg))	
	{
		ConnectTry++;
		Sleep(10); 
		std::cout << "Trying to connect to Camera: Try "<< ConnectTry << " / " << maxTry << std::endl;
		if(ConnectTry>=maxTry)
			return false;
	}

	return true;
}
//----------------------------------------------------------------

bool	CL_Serial::Read		(Fg_Struct* fg)
{
	if (!fg)
		return false;

	if (!this->m_serialRef)
	{
		QMessageBox::information(0, "CL seriell"
			, QString(	"Die serielle Schnittstelle (RS232)\n"
					"ist nicht geöffnet!"));
		return false;
	}

	memset(this->m_buffer, '\0', 2048);

	long pos = 0;
	this->m_bufferSize = 1;
	do 
	{
		if ((this->m_status = 
		clSerialRead(	  this->m_serialRef
				, &this->m_buffer[pos]
				, &this->m_bufferSize
				, this->m_timeout)
			) < 0)
		{
			clGetErrorText(this->m_status, this->m_buffer, &this->m_bufferSize);
			clFlushPort	(this->m_serialRef);
			return false;
		}
		pos++;
	}
	while (m_buffer[pos-1] != this->m_lastchar);

	clFlushPort	(this->m_serialRef);

	this->m_internalBuffer = this->m_buffer;
	
	//MESSAGE("CL_RS232 (" << (int)m_board << "," << ((m_port % 2) == 0 ? "A" : "B") << ") r: " << this->m_internalBuffer.simplified().toLatin1().data());
	//debug() << "CL_RS232 (" << (int)m_board << "," << ((m_port % 2) == 0 ? "A" : "B") << ") r: " << this->m_internalBuffer.simplified().toLatin1().data() << "\n";

	return true;
}


