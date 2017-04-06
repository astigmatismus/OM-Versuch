/*
	infotag.cpp
	Milan Multi-Platform Imaging Language, an open source image processing library
	
	Copyright (C) 2006  	Tomy Rolo

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
	von der Free Software Foundation veroeffentlicht, weitergeben und/oder modifizieren, gemaeﬂ Version 2 der Lizenz.

	Die Veroeffentlichung dieses Programms erfolgt in der Hoffnung, daﬂ es Ihnen von Nutzen sein wird, aber OHNE 
	IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FUER EINEN BESTIMMTEN
	ZWECK. Details finden Sie in der GNU General Public License.

	Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht, 
	schreiben Sie an die Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA.


*/
#include <iostream>
#include <iomanip>
#include <sstream>
//#include <mdebug.h>

#include "infotag.h"

namespace IniMgmt
{

bool MInfoTag::toBool() const
{
	if (isBool(*this)) return (*(anyCast<bool>(&val)));
	else return false;
}

short MInfoTag::toShort() const
{
	if (isShort(*this)) return (*(anyCast<short>(&val)));
	else return 0;
}

unsigned short MInfoTag::toUShort() const
{
	if (isUShort(*this)) return (*(anyCast<unsigned short>(&val)));
	else return 0;
}

int MInfoTag::toInt() const
{
	if (isInt(*this)) return (*(anyCast<int>(&val)));
	else return 0;
}

unsigned int MInfoTag::toUInt() const
{
	if (isUInt(*this)) return (*(anyCast<unsigned int>(&val)));
	else return 0;
}

unsigned char MInfoTag::toUChar() const
{
        if (isUChar(*this)) return (*(anyCast<unsigned char>(&val)));
        else return 0;
}

char MInfoTag::toChar() const
{
        if (isChar(*this)) return (*(anyCast<char>(&val)));
        else return 0;
}

float MInfoTag::toFloat() const
{
	if (isFloat(*this)) return (*(anyCast<float>(&val)));
	else return 0.0;
}

double MInfoTag::toDouble() const
{
	if (isDouble(*this)) return (*(anyCast<double>(&val)));
	else return 0.0;
}

std::string MInfoTag::toString() const
{
	if (isString(*this)) return (*(anyCast<std::string>(&val)));
	else return "";
}

QString MInfoTag::toQString() const
{
        if (isQString(*this))
            return (*(anyCast<QString>(&val)));
        else if(isString(*this)) {
            return QString((*(anyCast<std::string>(&val))->c_str()));
        } else return "";
}

bool MInfoTag::equalKey(const std::string& rhsKey) const
{
	return (key == rhsKey);
}

bool MInfoTag::operator==(const MInfoTag& rhs)
{
	return (key == rhs.key) 
		&& (getType() == rhs.getType())
		&& (getValue() == rhs.getValue());
}

std::string MInfoTag::getValue() const
{
	if(isString(*this))
	{
		std::string value = *(anyCast<std::string>(&val));
		return value;
	}
	else if (isBool(*this))
	{
		std::string value = *(anyCast<bool>(&val)) ? "true" : "false";
		return value;
	}
	else if (isShort(*this))
	{
		short shortVal = *(anyCast<short>(&val));
		
		/// @todo use Int2String class 
		std::stringstream ss;
		ss << shortVal;
		std::string value = ss.str();		
		return value;		
	}
	else if (isUShort(*this))
	{
		unsigned short ushortVal = *(anyCast<unsigned short>(&val));
		
		/// @todo use Int2String class 
		std::stringstream ss;
		ss << ushortVal;
		std::string value = ss.str();		
		return value;		
	}
	else if (isInt(*this))
	{
		int intVal = *(anyCast<int>(&val));
		
		/// @todo use Int2String class 
		std::stringstream ss;
		ss << intVal;
		std::string value = ss.str();		
		return value;		
	}
	else if (isUInt(*this))
	{
		unsigned int uintVal = *(anyCast<unsigned int>(&val));
		
		/// @todo use Int2String class 
		std::stringstream ss;
		ss << uintVal;
		std::string value = ss.str();		
		return value;		
	}
	else if (isDouble(*this))
	{
		double doubleVal = *(anyCast<double>(&val));

		/// @todo use Double2String class 
		std::stringstream ss;
		ss << doubleVal;
		std::string value = ss.str();
		return value;
	}
	else if (isFloat(*this))
	{
		float floatVal = *(anyCast<float>(&val));

		/// @todo use Double2String class 
		std::stringstream ss;
		ss << floatVal;
		std::string value = ss.str();
		return value;
	}
	else
	{
		return "unknown type";
	}
}

std::string MInfoTag::getType() const
{
	if(isString(*this))
	{
		return "string";
	}
	else if (isBool(*this))
	{
		return "bool";
	}
	else if (isShort(*this))
	{
		return "short";		
	}
	else if (isUShort(*this))
	{
		return "unsigned short";		
	}
	else if (isInt(*this))
	{
		return "int";		
	}
	else if (isUInt(*this))
	{
		return "unsigned int";		
	}
	else if (isDouble(*this))
	{
		return "double";
	}
	else if (isFloat(*this))
	{
		return "float";
	}
	else
	{
		return "unknown";
	}
}

} // namespace milan
