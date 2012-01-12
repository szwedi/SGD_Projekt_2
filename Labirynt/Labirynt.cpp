// Labirynt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>

//deklaracja co ma sie wyswietlac
const char sciana = '#';
const char wolne = ' ';
const char CPOSS = '?';
const char droga = '+';
const char poczatek = 'S';
const char koniec = 'F';

// szerokosc, wysokosc
int width, height;
// labirynt
char *pMaze;
// poczatek/koniec punkty
int startx, starty, stopx, stopy;
// ilosc mozliwych pozycji
int nposibilities;

using namespace std;

// sprawdz wspolrzedne
bool czyzgodne(int x, int y)
{
	return (x>=1 && x<=width && y>=1 && y<=height);
}

//// =========================================================================
// zmiana pozycji na wspolrzedne
void Pos2Coord(int pos, int* x, int *y)
{
	*x = 1 + (pos % width);
	*y = 1 + (pos - (pos % width)) / width;
}

//// =========================================================================
// zwracanie zawartosci komorki
char GetCell(int x, int y)
{
	if (czyzgodne(x,y))
		return pMaze[(x-1) + (y-1)*width];
}

// =========================================================================
// ustalanie zawartosci komorki
void SetCell(int x, int y, char c)
{
	if (czyzgodne(x,y))
		pMaze[(x-1) + (y-1)*width] = c;
}

// =========================================================================
// zwracanie losowej liczby  
int GetRnd(int start, int stop)
{
	int res;
	if (start==stop)
		res = start;
	else
		res = start + (rand() * stop) / RAND_MAX;
	// wymus warunek  
	if (res>stop) res=stop;
	if (res<start) res=start;
	return res;
}

// =========================================================================
// wypisz labirynt
void DumpMaze()
{
	int y;
	char *pLine;

	pLine = new char[width+2];

	for (y=0; y<height; y++)
	{
		strncpy(pLine, pMaze + (y*width), width);               
		pLine[width] = 0;
		printf("%s \n", pLine);
	}
	delete[] pLine;
}

// =========================================================================
// zainicjuj labirynt
// wypelnij scianami
// 
void InitMaze()
{
	int x, y;

	// random
	srand( (unsigned)time( NULL ) );

	// tworzenie labiryntu 
	pMaze = new char[width*(height+1)];

	// set a row of safety 0\'s at the end for string functions safety
	for(x=0;x<width;x++)
		pMaze[x+height*width] = 0;

	//wypelnianie labiryntu scianami
	for (y=1; y<=height; y++)
		for (x=1; x<=width; x++)
			SetCell(x,y, sciana);

	//ustaw losowo mozliwy poczatek
	x = GetRnd(2, width-1);
	y = GetRnd(2, height-1);
	SetCell(x, y, CPOSS);
	nposibilities = 1;
}


// =========================================================================
//sprawdz mozliwosci pozycji i kierunki
//konwertuj komorke na cposs i zwieksz poss count
void CheckPosition(int x, int y, int dx, int dy)
{
	int tmpx, tmpy;

	//sprawdz czy komorka, sasiad i sasiad sasiada
	if (!czyzgodne(x,y) || !czyzgodne(x+dx, y+dy) || !czyzgodne(x+2*dx,y+2*dy) )
		return;

	// sprawdz sasiada
	tmpx=x+dx; tmpy=y+dy;
	if (GetCell(tmpx, tmpy) == CPOSS) return;
	if (!(GetCell(tmpx, tmpy) != wolne && 
		GetCell(tmpx-dy, tmpy-dx) != wolne && 
		GetCell(tmpx+dy, tmpy+dx) != wolne)) return;

	// sasiad sasiada
	tmpx += dx; tmpy += dy;
	if (!(GetCell(tmpx, tmpy) != wolne && 
		GetCell(tmpx-dy, tmpy-dx) != wolne && 
		GetCell(tmpx+dy, tmpy+dx) != wolne)) return;

	// zaznacz pozycje jako mozliwe
	// zwieksz poss
	SetCell(x+dx, y+dy, CPOSS);
	nposibilities++;
}


// =========================================================================
// Generuj labirynt
void GenMaze()
{
	int pos, x, y, ix, iy;
	char *p;

	vector <int> sx; //pocz x
	vector <int> sy; //pocz y
	vector <int> fx; //kon x
	vector <int> fy; //kon y

	while (nposibilities>0)
	{
		// losuj pozycje
		pos = GetRnd(1, nposibilities);

		// znajdz najblizsza mozliwa pozycje
		//licz lewo gore za 1 i dol prawo za kon
		p = pMaze;
		while (pos-->0)
			p = strchr(++p, CPOSS); 

		pos = p - pMaze ;
		Pos2Coord(pos, &x, &y);

		// ustaw pozycje do sciezki
		// zmniejsz poss
		SetCell(x, y, wolne);
		nposibilities--;

		//wyklucz otaczajace mozliwe pozycje
		for(iy=y-1;iy<=y+1;iy++)
			for(ix=x-1;ix<=x+1;ix++)
				if (czyzgodne(ix, iy) && GetCell(ix, iy) == CPOSS)
				{
					SetCell(ix, iy, sciana);
					nposibilities--;
				}
		
		//ustaw nowa mozliwa pozycje otaczajaca kolejna pusta
		for(iy=y-1;iy<=y+1;iy++)
			for(ix=x-1;ix<=x+1;ix++)
				if (czyzgodne(ix, iy) && GetCell(ix, iy) == wolne)
				{
					CheckPosition(ix, iy,  0,  1);
					CheckPosition(ix, iy,  0, -1);
					CheckPosition(ix, iy,  1,  0);
					CheckPosition(ix, iy, -1,  0);
				} 
	}

	DumpMaze();

	int mozliwe;
	int wybrane;

	// ustaw poczatek
	y = height-1;
	for (x=1; x<=width; x++)
		if (GetCell(x,y) == wolne)
		{
			sx.push_back(x);
			sy.push_back(y+1);
		}
	cout << endl << "START wybieramy z dolnej sciany calego labiryntu" << endl;
	for (mozliwe = 1 ; mozliwe <= sx.size() ; mozliwe++)
		{
			cout << mozliwe << ": x= " << sx[mozliwe-1] << " y= " << sy[mozliwe-1] << "     ";
			if (!(mozliwe%3))
				cout << endl;
		}
	cout << endl;
	cout << "Gdzie zaczynamy: ";
	cin >> wybrane;
	cout << endl;

	startx = sx[wybrane-1];
	starty = sy[wybrane-1];
	SetCell(sx[wybrane-1],sy[wybrane-1],poczatek);

	// ustaw koniec
	y = 2;
	for (x=1; x<=width; x++)
		if (GetCell(x,y) == wolne)
		{
			fx.push_back(x);
			fy.push_back(y-1);
		}
	cout << "FINISH wybieramy z gornej sciany calego labiryntu" << endl;
	for (mozliwe = 1 ; mozliwe <= fx.size() ; mozliwe++)
		{
			cout << mozliwe << ": x= " << fx[mozliwe-1] << " y= " << fy[mozliwe-1] << "     ";
			if (!(mozliwe%3))
				cout << endl;
		}
	cout << endl;
	cout << "Gdzie konczymy: ";
	cin >> wybrane;
	cout << endl;

	SetCell(fx[wybrane-1],fy[wybrane-1],koniec);

}

//// =========================================================================
bool SolveMaze(int x, int y)
{
	char c;
	bool found;
	// odrzuc niedobre komorki
	if (!czyzgodne(x,y)) return false;

	// sprawdz zawartosc
	c = GetCell(x,y);
	switch (c)
	{
	case wolne:
	case poczatek:
		// ustaw jako sciezka
		if (c==poczatek)
			SetCell(x,y,poczatek);
		else
			SetCell(x,y,droga);

		// probuj we wszystkie strony az dojdziesz do konca
		found = 
			SolveMaze(x + 1, y) || SolveMaze(x, y - 1) || 
			SolveMaze(x - 1, y) || SolveMaze(x, y + 1);

		// przywroc oryginal jesli nie znajdziesz konca
		if (!found) 
			SetCell(x,y,c);

		return found;
		break;
	case koniec:
		// Bingo!!!
		return true;
		break;
	case droga:
	case sciana:
	default:
		// slepa uliczka
		return false;
		break;
	}
}

//// =========================================================================
int _tmain(int argc, _TCHAR* argv[])
{

	HANDLE okno = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size;
    size.X = 102;
    size.Y = 500;
    SetConsoleScreenBufferSize(okno, size);

	cout << "Podaj szerokosc labiryntu: ";
	cin >> width;
	cout << endl;
	cout << "Podaj wysokosc labiryntu: ";
	cin >> height;
	cout << endl;

	InitMaze();
	GenMaze();
	DumpMaze();
	system ("pause");
	SolveMaze(startx, starty);
	DumpMaze();
	system ("pause");
	return 0;
}
