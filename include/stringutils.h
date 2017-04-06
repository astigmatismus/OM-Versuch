/*
	stringutils.h
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

#ifndef MILAN_STRINGUTILS_H
#define MILAN_STRINGUTILS_H

#include <string>
#include <vector>

//namespace milan {
namespace IniMgmt{

std::string		getExtension	(const std::string& name);
std::string		trim			(const std::string& source, const char* delims = " \t");
void			split			(std::vector< std::string >& output, const std::string& input, const std::string& seperator);
void			trimToken		(	  std::string &output
									, const std::string& input
									, const std::string& seperator
									, const std::string& newseperator
									, int count = 1
									, int LR = 3);
//char* ChrToChr(char *str, char alt, char neu, char* delim = " \t\n");
std::string&	ChrToChr		(std::string &str, char alt, char neu, char* delim = " \t\n");
std::string		flPtToStr		(double dbl, int precision = 8, char c = '.');
std::string		flPtToStr		(float fl, int precision = 8, char c = '.');
int				strToInt		(const std::string& str);
double			strToDbl		(const std::string& str);
} // namespace milan

#endif // MILAN_STRINGUTILS_H
