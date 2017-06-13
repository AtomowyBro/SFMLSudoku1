#pragma once
#include "field.h"
#include "Sudoku.h"


void wczytajbaze(Sudoku &tab);
void zapiszbaze(Sudoku &tab);
class przycisk
{
public:
	sf::Color hovered, normal;
	sf::RectangleShape pole;
	Sudoku *tab;
	std::string opcja;
	bool wybrane;
	przycisk();
	virtual void wywolaj();
	virtual std::string podaj_opcje();
	void drawboard(sf::RenderWindow & win);
};

class przycisk_rozwiaz
	:public przycisk
{
public:
	przycisk_rozwiaz(Sudoku &tab);
	void wywolaj();
};

class przycisk_nowa_gra
	: public przycisk
{
public:
	przycisk_nowa_gra(Sudoku &tab);
	void wywolaj();
};

class przycisk_wczytaj_gre
	:public przycisk
{
public:
	przycisk_wczytaj_gre(Sudoku &tab);
	void wywolaj();
};

class przycisk_zapisz_gre
	:public przycisk
{
public:
	przycisk_zapisz_gre(Sudoku &tab);
	void wywolaj();
};

class przycisk_koniec
	:public przycisk
{
public:
	przycisk_koniec();
	void wywolaj(bool &koniec);
};

