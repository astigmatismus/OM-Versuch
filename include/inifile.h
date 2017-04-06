/*
	inifile.h
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
#ifndef INIFILE_H
#define INIFILE_H

#include <string>
#include <vector>
#include <QString>
#include "infotag.h"
#include "stringutils.h"



class MAny;


// Forward declarations
class QColor;
class QComboBox;
class QSpinBox;
class QDoubleSpinBox;
class QLabel;
class QLineEdit;
class QCheckBox;

/// Typedefs for MIniFile-iterators
typedef std::vector<IniMgmt::MInfoTag>::const_iterator	MIniFileConstIterator;
typedef std::vector<IniMgmt::MInfoTag>::iterator			MIniFileIterator;


class MIniFileIF
{
	public:
							MIniFileIF	(){}
		virtual 			~MIniFileIF	(){}		
		virtual void removeItem(const std::string& key) = 0;

		virtual bool getItem(const std::string& key, short&	value, short		defaultValue) = 0;
		virtual bool getItem(const std::string& key, unsigned short& value, unsigned short	defaultValue) = 0;
		virtual bool getItem(const std::string& key, int& value, int		defaultValue) = 0;
		virtual bool getItem(const std::string& key, unsigned int& value, unsigned int	defaultValue) = 0;
		virtual bool getItem(const std::string& key, long& value, long defaultValue) = 0;
		virtual bool getItem(const std::string& key, unsigned long&	value, unsigned long	defaultValue) = 0;
		virtual bool getItem(const std::string& key, float&	value, float defaultValue) = 0;
		virtual bool getItem(const std::string& key, double& value, double	defaultValue) = 0;
		virtual bool getItem(const std::string& key, char&	value, char	defaultValue) = 0;
		virtual bool getItem(const std::string& key, unsigned char&		value, unsigned char	defaultValue) = 0;
		virtual bool getItem(const std::string& key, bool& value, bool defaultValue) = 0;
		virtual bool getItem(const std::string& key, std::string& value, std::string defaultValue) = 0;
		virtual bool getItem(const std::string& key, QString& value, QString defaultValue) = 0;
		//virtual bool getItem(const std::string& key, milan::MCamModelTsang&	cam) = 0;
		virtual	bool getItem(const std::string& key, QColor&				color,	QColor			defaultColor) = 0;
		virtual bool getItem(const std::string& key, QComboBox*				pCombo, QString			defaultValue) = 0;
		virtual bool getItem(const std::string& key, QSpinBox*				pSpin,	int			defaultValue) = 0;
		virtual bool getItem(const std::string& key, QDoubleSpinBox*                    pSpin,	double			defaultValue) = 0;
		virtual bool getItem(const std::string& key, QLabel*                            pLabel, QString                 defaultValue) = 0;
		virtual bool getItem(const std::string& key, QCheckBox*                         pCheck, bool                    defaultValue) = 0;
		virtual bool getItem(const std::string& key, QLineEdit*                         pEdit,  QString                 defaultValue) = 0;

		virtual void setItem(const std::string& key, const short&			value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const unsigned short&	value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const int&			value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const unsigned int&	value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const long&		value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const unsigned long&	value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const float&		value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const double&		value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const char&		value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const unsigned char&	value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const bool&		value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const std::string&		value, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const QString&		value, bool flush = false) = 0;
		//virtual void setItem(const std::string& key, const milan::MCamModelTsang& cam, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const QColor&			color, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const QComboBox*		pCombo, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const QSpinBox*		pSpin, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const QDoubleSpinBox*	pSpin, bool flush = false) = 0;
		virtual void setItem(const std::string& key, const QLabel*              pLabel, bool flush = false)= 0;
		virtual void setItem(const std::string& key, const QLineEdit*           pEdit, bool flush = false)= 0;
		virtual void setItem(const std::string& key, const QCheckBox*           pCheck,bool flush = false)= 0;

		virtual int  getSubEntries	(const std::string& key, std::vector<std::string>& entries) = 0;
		virtual bool read		(const std::string& fileName) = 0;
		virtual bool write		(const std::string& fileName) = 0;
		virtual bool flush		() = 0;
		/*
		virtual bool readStereoMatrix(QString system, QString name, cv::Mat& mat) = 0;
		virtual bool readStereoVector(QString name, cv::Mat& mat) = 0;
		virtual bool writeStereoMatrix(QString system, QString name, cv::Mat mat) = 0;
		virtual bool writeStereoVector(QString name, cv::Mat mat) = 0;
		*/
};

class MIniFile : MIniFileIF
{
public:
						MIniFile	(const QString& fileName);
						~MIniFile	();

		bool			isValid		() const;


	// Convenience methods
public:
        IniMgmt::MInfoTag getItemA(const std::string& key, bool& ok);
        IniMgmt::MInfoTag getItemA(const std::string& key, const MAny& defaultValue, bool& ok);
public:
	
		void removeItem(const std::string& key);
		void clearItems(){m_iniFile.clear();}
        bool getItem(const std::string& key, short&					value, short			defaultValue);
        bool getItem(const std::string& key, unsigned short&		value, unsigned short	defaultValue);
        bool getItem(const std::string& key, int&					value, int				defaultValue);
        bool getItem(const std::string& key, unsigned int&			value, unsigned int		defaultValue);
        bool getItem(const std::string& key, long&					value, long				defaultValue);
        bool getItem(const std::string& key, unsigned long&			value, unsigned long	defaultValue);
        bool getItem(const std::string& key, float&					value, float			defaultValue);
        bool getItem(const std::string& key, double&				value, double			defaultValue);
        bool getItem(const std::string& key, char&					value, char				defaultValue);
        bool getItem(const std::string& key, unsigned char&			value, unsigned char	defaultValue);
        bool getItem(const std::string& key, bool&					value, bool				defaultValue);
        bool getItem(const std::string& key, std::string&			value,  std::string		defaultValue);
        bool getItem(const std::string& key, QString&				value,  QString			defaultValue);
		//bool getItem(const std::string& key, milan::MCamModelTsang&	cam);
        bool getItem(const std::string& key, QColor&				color,  QColor			defaultColor);
        bool getItem(const std::string& key, QComboBox*				pCombo, QString			defaultValue);
        bool getItem(const std::string& key, QSpinBox*				pSpin,  int			defaultValue);
        bool getItem(const std::string& key, QDoubleSpinBox*                    pSpin,  double			defaultValue);
        bool getItem(const std::string& key, QLabel*                            pLabel, QString                 defaultValue);
        bool getItem(const std::string& key, QCheckBox*                         pCheck, bool                    defaultValue);
        bool getItem(const std::string& key, QLineEdit*                         pEdit,  QString                 defaultValue);

		/*
		bool readStereoMatrix(QString system, QString name, cv::Mat& mat);
		bool readStereoVector(QString name, cv::Mat& mat);
		bool writeStereoMatrix(QString system, QString name, cv::Mat mat);
		bool writeStereoVector(QString name, cv::Mat mat);
		*/

		// Set functions
public:
        void setItem(const std::string& key, const MAny&			value, bool flush = false);
public:
        void setItem(const std::string& key, const short&			value, bool flush = false);
		void setItem(const std::string& key, const unsigned short&		value, bool flush = false);
        void setItem(const std::string& key, const int&				value, bool flush = false);
		void setItem(const std::string& key, const unsigned int&		value, bool flush = false);
        void setItem(const std::string& key, const long&			value, bool flush = false);
		void setItem(const std::string& key, const unsigned long&		value, bool flush = false);
        void setItem(const std::string& key, const float&			value, bool flush = false);
        void setItem(const std::string& key, const double&			value, bool flush = false);
        void setItem(const std::string& key, const char&			value, bool flush = false);
		void setItem(const std::string& key, const unsigned char&		value, bool flush = false);
        void setItem(const std::string& key, const bool&			value, bool flush = false);
		void setItem(const std::string& key, const std::string&			value, bool flush = false);
        void setItem(const std::string& key, const QString&			value, bool flush = false);
		//void setItem(const std::string& key, const milan::MCamModelTsang& cam,  bool flush = false);
        void setItem(const std::string& key, const QColor&			color, bool flush = false);
		void setItem(const std::string& key, const QComboBox*			pCombo, bool flush = false);
		void setItem(const std::string& key, const QSpinBox*			pSpin, bool flush = false);
		void setItem(const std::string& key, const QDoubleSpinBox*		pSpin, bool flush = false);
        void setItem(const std::string& key, const QLabel*                      pLabel, bool flush = false);
        void setItem(const std::string& key, const QLineEdit*                   pEdit, bool flush = false);
        void setItem(const std::string& key, const QCheckBox*                   pCheck,bool flush = false);


		/// @brief Return the subentries to the given key
		/// @param key The key for which the subentries are searched.
		/// @param entries A reference to a vector<string> in which the subentries are stored
		/// @return The number of subentries found
		/// Use this method to retrieve the number of keys under a given subkey.
		int getSubEntries(const std::string& key, std::vector<std::string>& entries);

		bool read	(const std::string& fileName = "");
		bool write	(const std::string& fileName = "");
		bool flush	(){this->write(m_name); return true;}

		// Iterator functions
		inline MIniFileConstIterator	getConstIterator() const {return m_iniFile.begin();}
		inline MIniFileIterator			getIterator	()	 {return m_iniFile.begin();}
		inline MIniFileConstIterator	end		() const {return m_iniFile.end();}
		inline MIniFileConstIterator	end		()	 {return m_iniFile.end();}


private:
	void insert(const std::string& key, const MAny& value);
//	void resolveHierarchy(const std::string& key, std::string& mg, std::string& g, std::string& k);
 
	bool					m_valid;
	bool					m_changed;
	std::string				m_name;

	std::vector<IniMgmt::MInfoTag> m_iniFile;

public:
	QString 				m_organisation;
	QString 				m_application;
	QString 				m_version;

};
#endif // INIFILE_H
