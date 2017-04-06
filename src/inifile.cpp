/*
	inifile.cpp
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
	von der Free Software Foundation veroeffentlicht, weitergeben und/oder modifizieren, gemaess Version 2 der Lizenz.

	Die Veroeffentlichung dieses Programms erfolgt in der Hoffnung, dass es Ihnen von Nutzen sein wird, aber OHNE 
	IRGENDEINE GARANTIE, sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FUER EINEN BESTIMMTEN
	ZWECK. Details finden Sie in der GNU General Public License.

	Sie sollten ein Exemplar der GNU General Public License zusammen mit diesem Programm erhalten haben. Falls nicht, 
	schreiben Sie an die Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA.

*/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

#include <QColor>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

#include <inifile.h>
#include <tree.h>


using namespace IniMgmt;
using namespace std;


MIniFile::MIniFile( const QString& fileName)
{
	this->m_valid		= false;
	this->m_changed		= false;

	this->m_name = fileName.toStdString();
	//this->read(m_name);

	this->m_application	= "Milan";
	this->m_version		= "1.0.0.0";
	this->m_organisation	= "h_da Hochschule Darmstadt";
}

MIniFile::~MIniFile()
{

}


bool MIniFile::read(const std::string& fileName)
{

	if (!fileName.empty())
		this->m_name = fileName;

	std::fstream f(this->m_name.c_str());			// file stream
	if (!f.is_open())
		return false;

	typedef std::string::size_type strPos;
	
	long depth, adepth;
	std::string line, line2;
	std::string group, group2;
	std::string key;

	depth = adepth = 0;
	while (std::getline(f, line))
	{
		line2 = trim(line);

		//this can't be a m_valid line
		if (line.size() < 2)
			continue;

		//a comment
		/// @todo check for comments that don't start at the beginning of the line
		if (line2[0] == '#')
			continue;

		// this line starts a new metagroup
		if (line2[0] == '[')
		{
			depth = 0;
			while(line[2*depth] != '[')
				depth++;

			if (depth <= adepth)
			{
				trimToken(group2, group, "/", "/", adepth - depth +1, 2);
				group = group2;
			}

			group += trim(line, "[] \t") + "/";
			adepth = depth;
			continue;		
		}

		strPos keyDelim = line.find("=");
		strPos typeDelim = line.rfind(":");
		
		if (keyDelim == std::string::npos || typeDelim == std::string::npos)
			continue;

		key = group + trim(line.substr(0, keyDelim));

		std::string value = trim(line.substr(keyDelim, typeDelim - keyDelim), "= \t");
		std::string type = trim(line.substr(typeDelim), ": \t");

		if (type == "bool")
		{
			insert(key, value == "true" ? true : false);
			key.clear();
			continue;
		}

		if (type == "int")
		{
			/// @todo use MInteger2String for conversion
			int iValue;
			std::stringstream s;
			s << value;
			s >> iValue;
			insert(key, iValue);
			key.clear();
			continue;
		}

		if (type == "unsigned int")
		{
			/// @todo use MInteger2String for conversion
			unsigned int uiValue;
			std::stringstream s;
			s << value;
			s >> uiValue;
			insert(key, uiValue);
			key.clear();
			continue;
		}

		if (type == "short")
		{
			/// @todo use MInteger2String for conversion
			short sValue;
			std::stringstream s;
			s << value;
			s >> sValue;
			insert(key, sValue);
			key.clear();
			continue;
		}

		if (type == "unsigned short")
		{
			/// @todo use MInteger2String for conversion
			unsigned short usValue;
			std::stringstream s;
			s << value;
			s >> usValue;
			insert(key, usValue);
			key.clear();
			continue;
		}
		
		if (type == "float")
		{
			/// @todo use MFloat2String for conversion
			float fValue;
			std::stringstream s;
			s << value;
			s >> fValue;
			insert(key, fValue);
			key.clear();
			continue;
		}

		if (type == "double")
		{
			/// @todo use MDouble2String for conversion
			double dValue;
			std::stringstream s;
			s << value;
			s >> dValue;
			insert(key, dValue);
			key.clear();
			continue;
		}

		if (type == "string")
		{
			insert(key, value);
			key.clear();
			continue;
		}
	}

	//std::cout << std::endl;
	return true;
}

bool MIniFile::write(const std::string& fileName)
{
	if (!fileName.empty())
		this->m_name = fileName;

	std::ofstream f(this->m_name.c_str());			// file stream
	
	f << setprecision(17);						// Use full double precision for floating point output

	std::vector<MInfoTag>::iterator it;			// key iterator

	tree<std::string>			existingItems;	// tree struct
	tree<std::string>::iterator		loc;		// tree iterator
	tree<std::string>::sibling_iterator	sibIt, s2, ipos;		// Iterator which traverses only the nodes which are siblings of each other.
	
	// loop over all MInfoTag's to create a tree structure
	for (it = m_iniFile.begin(); it != m_iniFile.end(); ++it)
	{
		// split key into tokens
		std::vector< std::string > tokens;
		split(tokens, it->getKey(), "/");
		unsigned long t;
		sibIt = existingItems.begin();

		loc = find(existingItems.begin(), existingItems.end(), tokens[0]);
		if (loc == existingItems.end())		// insert token to tree
			sibIt = existingItems.insert(loc, tokens[0]);
		else
			sibIt = loc;

		// loop over all tokens to create all needed subkey's
		for (t = 1; t < tokens.size()-1; t++)
		{
			loc = find(existingItems.begin(sibIt), existingItems.end(sibIt), tokens[t]);
			if (loc == existingItems.end(sibIt))		// insert token to tree
				// all tokens followed by at least one child are appended at the end
				sibIt = existingItems.append_child(sibIt, tokens[t]);
			else
				sibIt = loc;
		}


		std::string value = it->getValue();
		std::string line;
//*		
		line = tokens.back();
		long dummyspace = 40 - 2* static_cast<long>(tokens.size()) - static_cast<long>(line.size());
		if (dummyspace > 0)
			line.append(dummyspace, ' ');
		line += "\t = " + value;
		dummyspace = 72 - 2* static_cast<long>(tokens.size()) - static_cast<long>(line.size());
		if (dummyspace > 0)
			line.append(dummyspace, ' ');
		line += "\t: " + it->getType();

		// all leaf tokens (having no childs) are prepended at the begining 
		// and moved down after the last sibling having no child. Then the tokens having childs follow.
		s2 = ipos = existingItems.prepend_child(sibIt, line);

		if (existingItems.number_of_children(sibIt) > 1)
		{
			for (ipos = existingItems.begin(sibIt); ipos != existingItems.end(sibIt); ++ipos)
			{
				if (ipos.number_of_children() > 0)
					break;
			}
			existingItems.move_before(ipos, s2);
		}
	}
	
	// loop over the tree and print items to stream (file)
	for (loc = existingItems.begin(); loc != existingItems.end(); ++loc)
	{
		if (existingItems.depth(loc) == 0)
			f << std::endl << "[" << (*loc) << "]" << std::endl;
		else if(loc.number_of_children() != 0)
			f << std::setw( existingItems.depth(loc)*2 ) << " " << "[" << (*loc) << "]" << std::endl;
		else
			f << std::setw( existingItems.depth(loc)*2 ) << " " << (*loc) << std::endl;
	}

	return true;	
}

void MIniFile::insert(const std::string& key, const MAny& value)
{
	if (!key.length())
		return;

	std::string fullKey;

	std::vector< std::string >tokens;
	split(tokens, key,"/");
	
	if (tokens.size() == 1)
		fullKey = "Globals/" + key;
	else
		fullKey	= key;

	// check if this key already exists in memory
	std::vector<MInfoTag>::iterator loc;
	for (loc = m_iniFile.begin(); loc != m_iniFile.end(); ++loc)
	{
		if (loc->equalKey(fullKey)) break;
	}
	// if it exists, change the associated value
	if (loc != m_iniFile.end()) loc->val = value;
	// else insert a new InfoTag
	else m_iniFile.push_back(MInfoTag(fullKey, value));
}

void MIniFile::removeItem(const std::string& key)
{	
	std::string fullKey;

	std::vector< std::string >tokens;
	split(tokens, key,"/");
	if (tokens.size() == 1)
		fullKey = "Globals/" + key;
	else
		fullKey	= key;

	std::vector<MInfoTag>::iterator loc;
	for (loc = m_iniFile.begin(); loc != m_iniFile.end(); ++loc)
	{
		if (loc->equalKey(fullKey)) {
			m_iniFile.erase(loc);
			break;
		}
	}
	
}

int MIniFile::getSubEntries(const std::string& key, std::vector<std::string>& entries) 
{
	int count = 0;
	
	// Remove all entries
	entries.clear();
	
	// add "Globals/" if necessary
	std::vector<std::string>	searchtokens;
	std::string			searchKey;
	split(searchtokens, key, "/");
	
	if (searchtokens.size() == 0)
		searchKey = "Globals/" + key;
	else
		searchKey = key;
	split(searchtokens, searchKey, "/");

	// run through the whole vector "m_iniFile" and search the searchkey
	MIniFileConstIterator loc;
	for (loc = m_iniFile.begin(); loc != m_iniFile.end(); ++loc)
	{
                std::vector<std::string> objTokens;
		split(objTokens, loc->getKey(), "/");

		if (objTokens.size() < searchtokens.size())
			continue;

		unsigned long t = 0;
		while(t < searchtokens.size())
		{
			if (objTokens[t] != searchtokens[t])
				break;
			t++;
		}

		// not all tokens from searchtokens are also in tokens 
		if (t != searchtokens.size())
			continue;

		// at this point we know that loc is a subkey from searchKey
		// If it is the first of its kind, the "subdir" is included in the entries
		// vector
		int n = static_cast<int>(searchtokens.size());
		if((int)objTokens.size() < n+1) continue;
                std::string candidate = objTokens[n];
		if(find(entries.begin(),entries.end(),candidate) == entries.end()) {
			entries.push_back(candidate);	
			++count;
		}
	}

	return count;
}


MInfoTag MIniFile::getItemA(const std::string& key, bool& ok)
{	
	std::string fullKey;
	MInfoTag tag;

	std::vector< std::string >tokens;
	split(tokens, key,"/");
	if (tokens.size() == 1)
		fullKey = "Globals/" + key;
	else
		fullKey	= key;

	std::vector<MInfoTag>::const_iterator loc;
	for (loc = m_iniFile.begin(); loc != m_iniFile.end(); ++loc)
	{
                if (loc->equalKey(fullKey)) {
                    ok = true;
                    return *loc;
                }
	}
        ok = false;
	return tag;
}

MInfoTag MIniFile::getItemA(const std::string& key, const MAny& defaultValue, bool& ok)
{
	std::string fullKey;
	MInfoTag tag;

	std::vector< std::string >tokens;
	split(tokens, key,"/");
	if (tokens.size() == 1)
		fullKey = "Globals/" + key;
	else
		fullKey	= key;

	std::vector<MInfoTag>::const_iterator loc;
	
	for (loc = m_iniFile.begin(); loc != m_iniFile.end(); ++loc)
	{
		if(loc->equalKey(fullKey)) break;
	}

        if (loc != m_iniFile.end()) {
            ok = true;
            return *loc;
        }
	else
	{
                MInfoTag newTag(fullKey, defaultValue);
                m_iniFile.push_back(newTag);
                ok = false;
                return newTag;
	}
}

bool MIniFile::getItem(const std::string& key, short& value, short defaultValue){
        bool ok;
        MInfoTag tag = getItemA(key,defaultValue,ok);
	value = tag.toShort();
        return ok;
}

bool MIniFile::getItem(const std::string& key, unsigned short& value, unsigned short defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toUShort();
    return ok;
}

bool MIniFile::getItem(const std::string& key, int& value, int defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toInt();
    return ok;
}

bool MIniFile::getItem(const std::string& key, unsigned int& value, unsigned int defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toUInt();
    return ok;
}

bool MIniFile::getItem(const std::string& key, long& value, long defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = (long)tag.toInt();
    return ok;
}

bool MIniFile::getItem(const std::string& key, unsigned long& value, unsigned long defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = (long)tag.toInt();
    return ok;
}

bool MIniFile::getItem(const std::string& key, float& value, float defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toFloat();
    return ok;
}

bool MIniFile::getItem(const std::string& key, double& value, double defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toDouble();
    return ok;
}

bool MIniFile::getItem(const std::string& key, char& value, char defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toChar();
    return ok;
}

bool MIniFile::getItem(const std::string& key, unsigned char& value, unsigned char defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toUChar();
    return ok;
}

bool MIniFile::getItem(const std::string& key, bool& value, bool defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    value = tag.toBool();
    return ok;
}

bool MIniFile::getItem(const std::string& key, std::string& value, std::string defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    if(ok) {
        if(MInfoTag::isQString(tag))
            value = tag.toQString().toStdString();
        else if(MInfoTag::isString(tag))
            value = tag.toString();
    } else {
        value = defaultValue;
    }

    return ok;
}

bool MIniFile::getItem(const std::string& key, QString& value, QString defaultValue){
    bool ok;
    MInfoTag tag = getItemA(key,defaultValue,ok);
    if(ok) {
        if(MInfoTag::isQString(tag))
            value = tag.toQString();
        else if(MInfoTag::isString(tag))
            value = QString(tag.toString().c_str());
    } else {
        value = defaultValue;
    }
    return ok;
}

// Set functions

void MIniFile::setItem(const std::string& key, const MAny& value, bool flush){
	this->insert (key, value);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const short& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const unsigned short& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const int& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const unsigned int& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const long& value, bool flush){  
	MInfoTag tag(key, (int)value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const unsigned long& value, bool flush){  
	MInfoTag tag(key, (int)value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const float& value, bool flush){
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}
void MIniFile::setItem(const std::string& key, const double& value, bool flush){
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const char& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const unsigned char& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const bool& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const std::string& value, bool flush){  
	MInfoTag tag(key, value);
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

void MIniFile::setItem(const std::string& key, const QString& value, bool flush){  
	MInfoTag tag(key, value.toStdString());
	this->setItem(key,tag.val);
	if (flush) this->write(m_name);
}

/*
bool MIniFile::getItem(const std::string& key, milan::MCamModelTsang& cam) {
	bool ok = true;
	cv::Mat K(3,3,CV_64FC1);
	
	// Camera matrix
	K.at<double>(1,0) = 0.0; K.at<double>(2,0) = 0.0; K.at<double>(0,1) = 0.0;
	K.at<double>(2,1) = 0.0; K.at<double>(2,2) = 1.0;

	ok = ok && getItem("CamModelTsang/"+key+"/K00",  K.at<double>(0,0),1.0 );  // fx
	ok = ok && getItem("CamModelTsang/"+key+"/K11",  K.at<double>(1,1),1.0 );  // fy
	ok = ok && getItem("CamModelTsang/"+key+"/K02",  K.at<double>(0,2),0.0 );  // Cx
	ok = ok && getItem("CamModelTsang/"+key+"/K12",  K.at<double>(1,2),0.0 );  // Cy
	cam.setCameraMatrix(K);
	
	// This items are optional!
	cv::Mat dc(8,1,CV_64FC1);
	ok = ok && getItem("CamModelTsang/"+key+"/K1",   dc.at<double>(0,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/K2",   dc.at<double>(1,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/K3",   dc.at<double>(2,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/B1",   dc.at<double>(3,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/B2",   dc.at<double>(4,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/K4",   dc.at<double>(5,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/K5",   dc.at<double>(6,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/K6",   dc.at<double>(7,0),0.0);
	cam.setDistCoeffs(dc);

	cv::Mat vr(3,1,CV_64FC1);
	ok = ok && getItem("CamModelTsang/"+key+"/R0",  vr.at<double>(0,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/R1",   vr.at<double>(1,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/R2",   vr.at<double>(2,0),0.0);
	cam.settVec(vr);
	
	cv::Mat vt(3,1,CV_64FC1);
	ok = ok && getItem("CamModelTsang/"+key+"/T0",   vt.at<double>(0,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/T1",   vt.at<double>(1,0),0.0);
	ok = ok && getItem("CamModelTsang/"+key+"/T2",   vt.at<double>(2,0),0.0);
	cam.setrVec(vt);
	
	double sx = 0,sy = 0; int w = 0, h = 0;
	ok = ok && getItem("CamModelTsang/"+key+"/SX",   sx,0.005);
	ok = ok && getItem("CamModelTsang/"+key+"/SY",   sy,0.005);
	ok = ok && getItem("CamModelTsang/"+key+"/W",	 w,1024);
	ok = ok && getItem("CamModelTsang/"+key+"/H",	 h,768);
	cam.setSx(sx);
	cam.setSx(sy);
	cam.setWidth(w);
	cam.setHeight(h);
	return ok;
}



void MIniFile::setItem(const std::string& key, const milan::MCamModelTsang& cam,  bool flush) {
	
	cv::Mat K(3,3,CV_64FC1);
	K = cam.cameraMatrix();
	setItem("CamModelTsang/"+key+"/K00",  K.at<double>(0,0) );  // fx
	setItem("CamModelTsang/"+key+"/K11",  K.at<double>(1,1) );	 // fy
	setItem("CamModelTsang/"+key+"/K02",  K.at<double>(0,2) );  // Cx
	setItem("CamModelTsang/"+key+"/K12",  K.at<double>(1,2) );  // Cy
	
	cv::Mat dc(8,1,CV_64FC1);
	dc = cam.distCoeffs();
	setItem("CamModelTsang/"+key+"/K1",   dc.at<double>(0,0));
	setItem("CamModelTsang/"+key+"/K2",   dc.at<double>(1,0));
	setItem("CamModelTsang/"+key+"/K3",   dc.at<double>(2,0));
	setItem("CamModelTsang/"+key+"/B1",   dc.at<double>(3,0));
	setItem("CamModelTsang/"+key+"/B2",   dc.at<double>(4,0));
	if(dc.rows > 5) {
		setItem("CamModelTsang/"+key+"/K4",   dc.at<double>(5,0));
		setItem("CamModelTsang/"+key+"/K5",   dc.at<double>(6,0));
		setItem("CamModelTsang/"+key+"/K6",   dc.at<double>(7,0));
	} else {
		setItem("CamModelTsang/"+key+"/K4",  0);
		setItem("CamModelTsang/"+key+"/K5",  0);
		setItem("CamModelTsang/"+key+"/K6",  0);
	}
	cv::Mat vr(3,1,CV_64FC1);
	vr = cam.rVec();
	setItem("CamModelTsang/"+key+"/R0",   vr.at<double>(0,0));
	setItem("CamModelTsang/"+key+"/R1",   vr.at<double>(1,0));
	setItem("CamModelTsang/"+key+"/R2",   vr.at<double>(2,0));
	
	cv::Mat vt(3,1,CV_64FC1);
	vt = cam.tVec();
	setItem("CamModelTsang/"+key+"/T0",   vt.at<double>(0,0));
	setItem("CamModelTsang/"+key+"/T1",   vt.at<double>(1,0));
	setItem("CamModelTsang/"+key+"/T2",   vt.at<double>(2,0));

	setItem("CamModelTsang/"+key+"/SX",  cam.sx());
	setItem("CamModelTsang/"+key+"/SY",  cam.sy());
	setItem("CamModelTsang/"+key+"/W",	 cam.width());
	setItem("CamModelTsang/"+key+"/H",   cam.height());

	if (flush) this->write(m_name);
	
}

bool MIniFile::readStereoMatrix(QString system, QString name, cv::Mat& mat) {
	mat = cv::Mat(3,3,CV_64F);
	std::string stdSystem = system.toStdString();
	std::string stdName = name.toStdString();

	bool ok = true;
	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/00",mat.at<double>(0,0),0.0);
	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/01",mat.at<double>(0,1),0.0);
	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/02",mat.at<double>(0,2),0.0);

	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/10",mat.at<double>(1,0),0.0);
	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/11",mat.at<double>(1,1),0.0);
	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/12",mat.at<double>(1,2),0.0);

	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/20",mat.at<double>(2,0),0.0);
	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/21",mat.at<double>(2,1),0.0);
	ok = ok && getItem("StereoData/"+stdSystem+"/"+stdName+"/22",mat.at<double>(2,2),0.0);
	return ok;
}

bool MIniFile::readStereoVector(QString name, cv::Mat& mat) {
	mat = cv::Mat(3,1,CV_64F);
	bool ok = true;
	ok = ok && getItem("StereoData/"+name.toStdString()+"/T/0",mat.at<double>(0,0),0.0);
	ok = ok && getItem("StereoData/"+name.toStdString()+"/T/1",mat.at<double>(1,0),0.0);
	ok = ok && getItem("StereoData/"+name.toStdString()+"/T/2",mat.at<double>(2,0),0.0);
	return ok;
}

bool MIniFile::writeStereoMatrix(QString system, QString name, cv::Mat mat) {
	if(mat.cols < 3 || mat.rows < 3) {
		return false;
	}	
	std::string Stdsystem = system.toStdString();
	std::string Stdname = name.toStdString();

	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/00",mat.at<double>(0,0));
	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/01",mat.at<double>(0,1));
	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/02",mat.at<double>(0,2));

	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/10",mat.at<double>(1,0));
	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/11",mat.at<double>(1,1));
	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/12",mat.at<double>(1,2));

	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/20",mat.at<double>(2,0));
	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/21",mat.at<double>(2,1));
	setItem("StereoData/"+Stdsystem+"/"+Stdname+"/22",mat.at<double>(2,2));
	return true;
}

bool MIniFile::writeStereoVector(QString name, cv::Mat mat) {
	if(mat.cols < 1 || mat.rows < 3) {
		return false;
	}	
	setItem("StereoData/"+name.toStdString()+"/T/0",mat.at<double>(0,0));
	setItem("StereoData/"+name.toStdString()+"/T/1",mat.at<double>(1,0));
	setItem("StereoData/"+name.toStdString()+"/T/2",mat.at<double>(2,0));
	return true;
}
*/
void MIniFile::setItem(const std::string& key,	const QColor& color,  bool flush) {
	color.toRgb();
	setItem(key+"/r",   color.red() );
	setItem(key+"/g",   color.green());
	setItem(key+"/b",   color.blue());
	setItem(key+"/a",	color.alpha());
	if (flush) this->write(m_name);
}

bool MIniFile::getItem(const std::string& key,	QColor& color, QColor defaultColor) {
	bool ok = true;
	int r=0,g=0,b=0,a=0;
	ok = ok && getItem(key+"/r",   r, defaultColor.red());
	ok = ok && getItem(key+"/g",   g, defaultColor.green());
	ok = ok && getItem(key+"/b",   b, defaultColor.blue());
	ok = ok && getItem(key+"/a",   a, defaultColor.alpha());
	color.fromRgb(r,g,b,a);
	return ok;


}

void MIniFile::setItem(const std::string& key, const QComboBox* pCombo, bool flush) {
	setItem(key,pCombo->currentText(),flush);
}

bool MIniFile::getItem(const std::string& key, QComboBox*	pCombo, QString defaultValue) {
	bool ok = true;
	QString s;
	ok = getItem(key,s,defaultValue);
	int i = pCombo->findText(s);
	pCombo->setCurrentIndex(i);
	return ok;
}

void MIniFile::setItem(const std::string& key, const QSpinBox* pSpin, bool flush) {
	setItem(key,pSpin->value(),flush);
}

bool MIniFile::getItem(const std::string& key, QSpinBox* pSpin, int defaultValue) {
	bool ok;
        int i;
        ok = getItem(key,i,defaultValue);
        pSpin->setValue(i);
	return ok;
}

void MIniFile::setItem(const std::string& key, const QDoubleSpinBox* pSpin, bool flush) {
	setItem(key,pSpin->value(),flush);
}

bool MIniFile::getItem(const std::string& key, QDoubleSpinBox* pSpin, double defaultValue) {
	bool ok;
        double d;
        ok = getItem(key,d,defaultValue);
        pSpin->setValue(d);
	return ok;
}

void MIniFile::setItem(const std::string& key, const QLabel* pLabel, bool flush) {
        setItem(key,pLabel->text(),flush);
}

bool MIniFile::getItem(const std::string& key, QLabel* pLabel, QString defaultValue) {
        bool ok;
        QString s;
        ok = getItem(key,s,defaultValue);
        pLabel->setText(s);
        return ok;
}

void MIniFile::setItem(const std::string& key, const QLineEdit* pEdit, bool flush) {
        setItem(key,pEdit->text(),flush);
}

bool MIniFile::getItem(const std::string& key, QLineEdit* pEdit, QString defaultValue) {
        bool ok;
        QString s;
        ok = getItem(key,s,defaultValue);
        pEdit->setText(s);
        return ok;
}

void MIniFile::setItem(const std::string& key, const QCheckBox* pCheck, bool flush) {
        if(pCheck->isChecked())
            setItem(key,true,flush);
        else
            setItem(key,false,flush);
}

bool MIniFile::getItem(const std::string& key, QCheckBox* pCheck, bool defaultValue) {
        bool ok;
        bool val;
        ok = getItem(key,val,defaultValue);
        pCheck->setChecked(val);
        return ok;
}


		
		
