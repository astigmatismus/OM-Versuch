/*
Copyright (C) 2016  	Nils Küpper

h_da University of Applied Sciences
Faculty of Mathematics and Science
Dept. Computer Vision and Photonics

Schoefferstr. 3
D-64295 Darmstadt
Germany

*/

#ifndef _POINT_H
#define _POINT_H

#include "Types.h"	// Types: BYTE, WORD etc
#include <math.h>	// ceil, floor
#include <ios>		// namespace std::
#include <sstream>	// namespace std::
#include <QString>

template<class T> 
class Point
{
public:
	T			x,y;

				Point			()
				{
					x = y = 0;
				}

				Point			(T _x, T _y)
				{
					x = _x;
					y = _y;
				}

				Point			(const Point<T> &p)
				{
					x = p.x;
					y = p.y;
				}

				~Point			()
				{}

	Point<T>&		Set(Point<T> p)
				{
					this->x = p.x;
					this->y = p.y;
					return *this;
				}
	Point<T>&		Set(T _x = 0, T _y = 0)
				{
					this->x = _x;
					this->y = _y;
					return *this;
				}
	Point<T>&		Clear()
				{
					return this->Set();
				}

	Point<T>&		Min			(const T x, const T y)
				{
					this->x = MIN(this->x, x);
					this->y = MIN(this->y, y);
					return *this;
				}

	Point<T>&		Max			(const T x, const T y)
				{
					this->x = MAX(this->x, x);
					this->y = MAX(this->y, y);
					return *this;
				}

	double			Betrag			()
				{
					return sqrt(SQR(this->x) + SQR(this->y));
				}

//=
	Point<T>&		operator=		(const T &p)
				{
					x = p;
					y = p;
					return *this;
				}
	Point<T>&		operator=		(const Point<T> &p)
				{
					x = p.x;
					y = p.y;
					return *this;
				}
	Point<T>&		operator=		(const std::string &s)
				{
					std::stringstream ss;
					ss << s;

					ss >> x >> y;
					return *this;
				}
	Point<T>&		operator=		(const QString &s)
				{
					std::stringstream ss;
					ss << s.toStdString();

					ss >> x >> y;
					return *this;
				}
	bool			operator==		(const Point<T> &p)
				{
					if ( (x == p.x) && (y == p.y) )
						return true;
					else
						return false;
				}
	bool			operator!=		(const Point<T> &p)
				{
					if ( *this == p )
						return false;
					else
						return true;
				}
	bool			operator<		(const Point<T> &p)
				{
					if ( (x < p.x) && (y < p.y) )
						return true;
					else
						return false;
				}
	bool			operator<=		(const Point<T> &p)
				{
					if ( (x <= p.x) && (y <= p.y) )
						return true;
					else
						return false;
				}
	bool			operator>		(const Point<T> &p)
				{
					if ( (x > p.x) && (y > p.y) )
						return true;
					else
						return false;
				}
	bool			operator>=		(const Point<T> &p)
				{
					if ( (x >= p.x) && (y >= p.y) )
						return true;
					else
						return false;
				}
//+
	Point<T>		operator+		(const Point<T> &p)
				{
					Point<T> n(*this);
					return n += p;
				}
	Point<T>		operator+		(const T p)
				{
					Point<T> n(*this);
					return n += p;
				}
	Point<T>&		operator+=		(const Point<T> &p)
				{
					x += p.x;
					y += p.y;
					return *this;
				}
	Point<T>&		operator+=		(const T p)
				{
					x += p;
					y += p;
					return *this;
				}
//-
	Point<T>		operator-		(const Point<T> &p)
				{
					Point<T> n(*this);
					return n -= p;
				}
	Point<T>		operator-		(const T p)
				{
					Point<T> n(*this);
					return n -= p;
				}
	Point<T>&		operator-=		(const Point<T> &p)
				{
					x -= p.x;
					y -= p.y;
					return *this;
				}
	Point<T>&		operator-=		(const T p)
				{
					x -= p;
					y -= p;
					return *this;
				}
//*
	Point<T>		operator*		(const Point<T> &p)
				{
					Point<T> n(*this);
					return n *= p;
				}
	Point<T>		operator*		(const T p)
				{
					Point<T> n(*this);
					return n *= p;
				}
	Point<T>&		operator*=		(const Point<T> &p)
				{
					x *= p.x;
					y *= p.y;
					return *this;
				}
	Point<T>&		operator*=		(const T p)
				{
					x *= p;
					y *= p;
					return *this;
				}
///
	Point<T>		operator/		(const Point<T> &p)
				{
					Point<T> n(*this);
					return n /= p;
				}
	Point<T>		operator/		(const T p)
				{
					Point<T> n(*this);
					return n /= p;
				}
	Point<T>&		operator/=		(const Point<T> &p)
				{
					if (p.x)	x /= p.x;
					if (p.y)	y /= p.y;
					return *this;
				}
	Point<T>&		operator/=		(const T p)
				{
					if (p)		x /= p;
					if (p)		y /= p;
					return *this;
				}

//  Casts
				operator Point<long>()
				{
					Point<long> lp;
					lp.x = (long)(this->x+0.5);
					lp.y = (long)(this->y+0.5);
					return lp;
				}
				operator Point<double>()
				{
					Point<double> dp;
					dp.x = (this->x);
					dp.y = (this->y);
					return dp;
				}

				operator QString()
				{
					return QString("%1 %2").arg(this->x).arg(this->y);
				}

				operator std::string()
				{
					return ((QString)*this).toStdString();
				}

				operator const char*()
				{
					return ((std::string)*this).c_str();
				}
				
	Point<long>		Ceil()
				{
					return Point<long>((long)ceil((T)this->x), (long)ceil((T)this->y));
				}
	Point<long>		Floor()
				{
					return Point<long>((long)floor((T)this->x), (long)floor((T)this->y));
				}

	T			GetxMulty()
				{
					return this->x * this->y;
				}

	Point<T>&		Snap2Modulo	(T modulo)
				{
					if (!modulo)
						return *this;

					if (	typeid(T) == typeid(double))
					{
						this->x -= fmod((double)this->x, modulo);
						this->y -= fmod((double)this->y, modulo);
					}
					else if ( typeid(T) == typeid(float) )
					{
						this->x -= fmod((float)this->x, modulo);
						this->y -= fmod((float)this->y, modulo);
					}
					else
					{
						this->x -= this->x % modulo;
						this->y -= this->y % modulo;
					}

					return *this;
				}
	T			hypot()
				{
					return _hypot(this->x, this->y);
				}
};
// ---------------------------------------------------------------------------

template <class T>
std::ostream&		operator<<	(std::ostream &s, Point<T> &p)
{
	s << "\t" << setw(10) << setprecision(5) << fixed << p.x 
	  << " "  << setw(10) << setprecision(5) << fixed << p.y ;// << endl;
	return s;
}
// ---------------------------------------------------------------------------

template <class T>
std::istream&		operator>>	(std::istream &s, Point<T> &p)
{
	s >> p.x >> p.y;
	return s;
}
// ---------------------------------------------------------------------------

template <class T>
Point<T>		operator<<	(Point<T> &p, std::string &s)
{
	std::stringstream ss;
	ss << s;

	ss >> p.x >> p.y;
	return p;
}
// ---------------------------------------------------------------------------


// unsigned
typedef Point<BYTE>		BPoint;
typedef Point<WORD>		WPoint;
typedef Point<DWORD>		DWPoint;

// floating
typedef Point<double>		dPoint;
typedef Point<float>		fPoint;

// signed
typedef Point<char>		CPoint;
typedef Point<short>	SPoint;
typedef Point<int>		IPoint;
typedef Point<long>		LPoint;

#endif // eyeView_POINT_H