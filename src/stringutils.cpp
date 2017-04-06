/*
	stringutils.cpp
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
//
// @file stringutils.h
// @author Stephan Neser
// @date 05.09.2006

#include <stringutils.h>
#include <memory.h>
#include <sstream>
#include <algorithm>
namespace IniMgmt {

/// Return the extension of a string.
/// getExtension looks for the rightmost "." in the argument and returns all
/// characters right of it. For file names this should be the extension
/// @param name String to analyze.
/// @return returns the extension of the name without the dot, or an empty string
/// if any error occurs. 
std::string getExtension(const std::string& name)
{
	int i = (int)name.rfind(".");
	if(i == (int)std::string::npos) return std::string("");
	else if(i+1 < (int)name.size())
	{	// Don't try to extract an empty substring
		return name.substr(i+1,name.size()-i);
	} else return std::string("");
}
//------------------------------------------------------------------------------

/// Trim a string
/// trim removes the specified leading and trailing characters from a string.
/// @param source String to trim
/// @param delims Characters to remove, defaults to space and tab.
/// @return returns the trimmed string
std::string trim(const std::string& source, const char* delims)
{
	std::string result(source);
	std::string::size_type index = result.find_last_not_of(delims);
	if(index != std::string::npos) result.erase(++index);

	index = result.find_first_not_of(delims);
	if(index != std::string::npos) result.erase(0, index);
	else result.erase();
	
	return result;
}
//------------------------------------------------------------------------------

/// Split a string into tokens
/// split Tokenize a string. Delimiters are any chars of seperator. The tokens
/// are stored as strings in output. 
/// output will be empty if there are no matching delimiters in the input.
/// there is at least one token even if it is empty. 
/// @param output vector of strings containing the tokens
/// @param input The input string
/// @param seperator token delimiters
void split(std::vector< std::string >& output
		   , const std::string& input
		   , const std::string& seperator)
{
	using namespace std;

	typedef string::size_type StrPos;
	output.clear();
	vector <StrPos> delimPos;
	StrPos i;

	for (i = 0; i < input.size(); ++i)
	{
		for (StrPos j = 0; j < seperator.size(); ++j)
		{
			if(input[i] == seperator[j]) delimPos.push_back(i);
		}
	}
	delimPos.push_back(i);

	output.push_back(input.substr(0, delimPos[0]));

	for(i = 1; i < delimPos.size(); ++i)
		output.push_back(input.substr(delimPos[i-1]+1, delimPos[i] - (delimPos[i-1]+1)));
}
//------------------------------------------------------------------------------

void trimToken(	std::string &output
		, const std::string& input
		, const std::string& seperator
		, const std::string& newseperator
		, int count
		, int LR)
{
	std::vector< std::string >tokens;
	split(tokens, input, seperator);

	output.clear();

	long t, size;
	size = (long)tokens.size()-1;
	for (	t = ((LR & 1) ? count : 0); 
		t < ((LR & 2) ? (size - count) : size);
		t++)
	{
		output += tokens[t] + newseperator[0];
	}
	return;
}
//------------------------------------------------------------------------------

char* ChrToChr(char *str, char alt, char neu, char* delim)
{
	char *strchar = str;

	int pos = (int)strcspn( str, delim );

	for (int i = 0	; i < pos; i++)
	{
		if (strchar[i] == alt)
			strchar[i] = neu;
	}

	return str;
}
//------------------------------------------------------------------------------

std::string& ChrToChr(std::string &str, char alt, char neu, char* delim)
{
	int pos = (int)strcspn( str.c_str(), delim );

	for (int i = 0	; i < pos; i++)
	{
		if (str[i] == alt)
			str[i] = neu;
	}

	return str;
}
//------------------------------------------------------------------------------

/// Convert a double into a string
/// @param dbl double value to be converted to a string
/// @param precision the amount of post decimal positions
/// @return returns the double value as string
std::string flPtToStr(double dbl, int precision, char c){
	std::stringstream ss;
	ss.setf(std::ios::fixed, std::ios::floatfield);
	if(precision >= 0)
		ss.precision(precision);
	ss << dbl;
	std::string s;
	ss >> s;
	if(c != '.')
		std::replace(s.begin(), s.end(), '.', c);
	return s;
}

/// Convert a float into a string
/// @param dbl double value to be converted to a string
/// @param precision the amount of post decimal positions
/// @return returns the float value as string
std::string flPtToStr(float fl, int precision, char c){
	std::stringstream ss;
	ss.setf(std::ios::fixed, std::ios::floatfield);
	if(precision >= 0)
		ss.precision(precision);
	ss << fl;
	std::string s;
	ss >> s;
	if(c != '.')
		std::replace(s.begin(), s.end(), '.', c);
	return s;
}

int strToInt(const std::string& str){
	int nmbr;
	std::istringstream iss;
	iss.str(str);
	iss >> nmbr;
	return nmbr;
}

double strToDbl(const std::string& str){
	double nmbr;
	std::istringstream iss;
	iss.str(str);
	iss >> nmbr;
	return nmbr;
}

//------------------------------------------------------------------------------

} // namespace milan
