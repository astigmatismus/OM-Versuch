/*
	infotag.h
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
	von der Free Software Foundation veroeffentlicht, weitergeben und/oder modifizieren, gemae� Version 2 der Lizenz.

	Die Veroeffentlichung dieses Programms erfolgt in der Hoffnung, da� es Ihnen von Nutzen sein wird, aber OHNE 
	IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FUER EINEN BESTIMMTEN
	ZWECK. Details finden Sie in der GNU General Public License.

	Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht, 
	schreiben Sie an die Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA.


*/
#ifndef INFOTAG_H
#define INFOTAG_H

#include <string>
#include <QString>
#include "any.h"

//namespace milan
//{
namespace IniMgmt
{
class MInfoTag
{

public:
	//construction / destruction
	MInfoTag() {}
	MInfoTag(const MInfoTag& tag) {key = tag.key; val = tag.val;}
	MInfoTag(const std::string& k, const MAny& v) {key = k; val = v;}
	MInfoTag(const std::string& k, const std::string& v) {key = k; val = v;}
	MInfoTag(const std::string& k, const char* v) {key = k; val = std::string(v);}
	MInfoTag(const std::string& k, short v) {key = k; val = v;}
	MInfoTag(const std::string& k, unsigned short v) {key = k; val = v;}
	MInfoTag(const std::string& k, int v) {key = k; val = v;}
	MInfoTag(const std::string& k, unsigned int v) {key = k; val = v;}
	MInfoTag(const std::string& k, bool v) {key = k; val = v;}
	MInfoTag(const std::string& k, float v) {key = k; val = v;}
	MInfoTag(const std::string& k, double v) {key = k; val = v;}
	MInfoTag(const std::string& k, unsigned char v) {key = k; val = v;}

	~MInfoTag() {}

	//Predicate funtions
	static bool isBool		(const MInfoTag& t) {return t.val.type() == typeid(bool);}
	static bool isShort		(const MInfoTag& t) {return t.val.type() == typeid(short);}
	static bool isUShort	(const MInfoTag& t) {return t.val.type() == typeid(unsigned short);}
	static bool isInt		(const MInfoTag& t) {return t.val.type() == typeid(int);}
	static bool isUInt		(const MInfoTag& t) {return t.val.type() == typeid(unsigned int);}
	static bool isFloat		(const MInfoTag& t) {return t.val.type() == typeid(float);}
	static bool isDouble	(const MInfoTag& t) {return t.val.type() == typeid(double);}
	static bool isString	(const MInfoTag& t) {return t.val.type() == typeid(std::string);}
    static bool isUChar     (const MInfoTag& t) {return t.val.type() == typeid(unsigned char);}
    static bool isChar      (const MInfoTag& t) {return t.val.type() == typeid(char);}
    static bool isQString   (const MInfoTag& t) {return t.val.type() == typeid(QString);}

	bool			toBool() const;
	short			toShort() const;
	unsigned short	toUShort() const;
	int				toInt() const;
	unsigned int	toUInt() const;
	float			toFloat() const;
	double			toDouble() const;
	std::string		toString() const;
    char            toChar() const;
    unsigned char   toUChar() const;
    QString         toQString() const;

	bool operator==(const MInfoTag& rhs);
	bool equalKey(const std::string& rhsKey) const;
	
	//output content to console
	//void retrieve();
	std::string getKey() const {return key;}
	std::string getValue() const;
	std::string getType() const;

	std::string key;
	MAny val;
}; // class MInfoTag

} // namespace milan

#endif // INFOTAG_H

