#include <vector>
#include <algorithm>
#include <functional>      // For greater<int>( )
#include <cmath>

/*
Folgende Tabelle wird benötigt:
	unsigned short IndexLUTs[2][ROICOUNTX * ROICOUNTY][ROICOUNTX * ROICOUNTY];

Funktionsaufruf für die Generierung (immer im releas-modus laufen lassen, sonst langweilig):
	CreateIndexLUTs(&IndexLUTs[0][0][0], ROICOUNTX, ROICOUNTY);

Funktionsaufruf für den Import:
	char text[1024];
	sprintf(text, "C:/RoI_IndexLUTs_spiral_%02dx%02d.bin",  ROICOUNTX, ROICOUNTY);
	if (!ImportIndexLUTs(&IndexLUTs[0][0][0], ROICOUNTX, ROICOUNTY, text))
		Error("Import Index LUTs", __FILE__, __LINE__);
*/

using namespace std;

#define  PI 3.1415926535897932384626433832795

#define R2D (180./PI)
#define D2R (PI/180.)

struct Index
{
	int	icolrow;
	int	ispiral;
	int	R;
	double	A;
};

typedef vector <Index>	IndexVec;

bool lowerR (Index elem1, Index elem2 )
{
	return elem1.R < elem2.R;
}
bool lowerA (Index elem1, Index elem2 )
{
	return elem1.A < elem2.A;
}

bool lowerIcr (Index elem1, Index elem2 )
{
	return elem1.icolrow < elem2.icolrow;
}

void CreateIndexLUT(unsigned short *LUTa, unsigned short *LUTb, int nx, int ny, int start)
{
	IndexVec		indexlist;
	IndexVec::iterator	iter;
	Index			val;

	int x0, y0;
	x0 = start % nx;
	y0 = start / nx;

	double dx, dy;

	// radius und winkel fuer Kacheln abhaengig von der aktuellen Startkachel berechnen
	int spiral, posx, posy;
	for (spiral = 0; spiral < nx*ny; spiral++)
	{
		posx = spiral % nx;
		posy = spiral / ny;

		dx = posx - x0;
		dy = posy - y0;

		val.icolrow	= spiral;
		val.R		= (int)sqrt(dx * dx + dy * dy);
		val.A		= fmod((atan2(-dy, dx)*R2D + 360), 360);

		indexlist.push_back(val);
//		printf("%5d\t%5d\t%5d\t%+6.2lf\t%+6.2lf\t%5d\t%+7.2lf\n", spiral, posx, posy, dx, dy, val.R, val.A);
	}

//	printf("vectorsize: %5d\n", indexlist.size());

	// sortieren nach diskreten Radien
	stable_sort(indexlist.begin(), indexlist.end(), lowerR);
	//for ( iter = indexlist.begin( ) ; iter != indexlist.end( ) ; iter++ )
	//	printf("%5d\t%5d\t%7.2lf\n", (*iter).icolrow, (*iter).R, (*iter).A);


	// sortieren nach Winkeln innerhalb der jeweiligen Radiusklasse
	for (int radius = 0; radius < (int)(sqrt(nx*ny*2.)+1); radius++)
	{
		IndexVec::iterator	start = indexlist.end();
		IndexVec::iterator	stop  = indexlist.begin();

		for (iter = indexlist.begin(); iter != indexlist.end(); iter++)
			if ((*iter).R == radius)
			{
				start = iter;
				break;
			}
		for (iter = indexlist.begin(); iter != indexlist.end(); iter++)
			if ((*iter).R == radius+1)
			{
				stop = iter;
				break;
			}
		if (stop == indexlist.begin())
			stop = indexlist.end();
		if (start == indexlist.end())
			continue;

		partial_sort(start, stop, stop, lowerA );
	}

	int index = 0;
	for ( iter = indexlist.begin( ) ; iter != indexlist.end( ) ; iter++, index++)
	{
		LUTa[index] = (unsigned short)(*iter).icolrow;

		// in spiralfoermig sortierter Liste spiralen index linear ergaenzen
		(*iter).ispiral = index;
//		printf("%5d\t%5d\t%5d\t%7.2lf\n", (*iter).icolrow, (*iter).ispiral, (*iter).R, (*iter).A);
	}

	// umsortieren fuer Rueckweg
	stable_sort(indexlist.begin(), indexlist.end(), lowerIcr);

	index = 0;
	for ( iter = indexlist.begin( ) ; iter != indexlist.end( ) ; iter++, index++)
	{
		LUTb[index] = (unsigned short)(*iter).ispiral;
//		printf("%5d\t%5d\t%5d\t%7.2lf\n", (*iter).icolrow, (*iter).ispiral, (*iter).R, (*iter).A);
	}
}

void CreateIndexLUTs(unsigned short *LUTs, int nx, int ny)
{
	for (int starttile = 0; starttile < nx*ny; starttile++)
	{
		printf("%c%c%c%c%c%5d", 8, 8, 8, 8, 8, starttile);
		CreateIndexLUT(	&LUTs[starttile * nx*ny],		// Listeneinsprung fuer Hinweg
				&LUTs[starttile * nx*ny + nx*ny*nx*ny], // Listeneinsprung fuer Rueckweg
				nx, ny, starttile);
	}

	// save as text and as binary
	{
		char fnt[512], fnb[512];
		sprintf_s(fnt, 512, "C:/RoI_IndexLUTs_spiral_%02dx%02d.txt",  nx, ny);
		sprintf_s(fnb, 512, "C:/RoI_IndexLUTs_spiral_%02dx%02d.bin",  nx, ny);

		FILE *filet, *fileb;
		fopen_s(&filet, fnt, "w");
		fopen_s(&fileb, fnb, "wb");
		if (!filet || !fileb)
			return;

		// write as text
		for (int pos = 0; pos < 2*nx*ny*nx*ny; pos++)
		{
			fprintf(filet, "%5d\t", LUTs[pos]);
			if ((pos % (nx*ny)) == (nx*ny-1))
				fprintf(filet, "\n");
		}

		// write as binary
		fwrite(LUTs, sizeof(unsigned short), 2*nx*ny*nx*ny, fileb);

		fclose(filet);
		fclose(fileb);
	}
}

bool ImportIndexLUTs(unsigned short *LUTs, int nx, int ny, char *filename)
{
	FILE* file;
	fopen_s(&file, filename, "rb");
	if (!file)
		return false;

	int read;
	read = fread(LUTs, sizeof(unsigned short), 2*nx*ny*nx*ny, file);

	fclose(file);

	if (read != 2*nx*ny*nx*ny)
		return false;

	return true;
}
