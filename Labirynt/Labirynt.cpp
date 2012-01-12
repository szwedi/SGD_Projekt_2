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

