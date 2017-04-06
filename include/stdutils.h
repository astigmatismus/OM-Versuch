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
#ifndef STDUTILS_H
#define	STDUTILS_H

#include <string>
#include <ios>		// namespace std::
#include <iomanip>
#include <iostream>	// cerr cout
#include <fstream>	// ofstream, instream
#include <sstream>	// namespace std::
#include <vector>
using namespace std;
// ---------------------------------------------------------------------------

template<class T>	void		Print				(const std::vector<T>			&v, std::string text = "Vector:");
//specializations:
template		void		Print<double>			(const std::vector<double>		&v, std::string text);
template		void		Print<float>			(const std::vector<float>		&v, std::string text);

template		void		Print<char>				(const std::vector<char>		&v, std::string text);
template		void		Print<short>			(const std::vector<short>		&v, std::string text);
template		void		Print<int>				(const std::vector<int>			&v, std::string text);
template		void		Print<long>				(const std::vector<long>		&v, std::string text);

template		void		Print<bool>				(const std::vector<bool>		&v, std::string text);

template		void		Print<unsigned char>	(const std::vector<unsigned char>	&v, std::string text);
template		void		Print<unsigned short>	(const std::vector<unsigned short>	&v, std::string text);
template		void		Print<unsigned int>		(const std::vector<unsigned int>	&v, std::string text);
template		void		Print<unsigned long>	(const std::vector<unsigned long>	&v, std::string text);
// ---------------------------------------------------------------------------

template <class T>	std::ostream&	operator<<		(std::ostream &s, const std::vector<T> &v);
//specializations:
template		std::ostream&	operator<<<double>	(std::ostream &s, const std::vector<double> &v);
template		std::ostream&	operator<<<int>		(std::ostream &s, const std::vector<int> &v);
template		std::ostream&	operator<<<bool>	(std::ostream &s, const std::vector<bool> &v);
// ---------------------------------------------------------------------------


#endif //STDUTILS_H
