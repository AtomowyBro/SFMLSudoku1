#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>

class field
{
	bool locked; //Wygenerowana wartosc nie bedzie mogla zostac zmieniona
	int hidden_value; //ukryta wartosc poprawna
	int value; //wartosc wyswietlana
	bool wybrane; //pozwala podswietlic wybrane pole i zmienic wartosc
	sf::Color hovered, normal;
	sf::RectangleShape pole;
public:
	field();
	void changehidden(int); //zmiana wartosci poprawnej podczas generowania planszy
	void changevalue(int); //zmiana pojedynczych widzialnych pol planszy 
	bool isused(); //funkcja sprawdzajaca czy hidden_value zostalo ustalone
	void showvalue();
	int hiddenvalue();
	int shownvalue();
	void permset();
	void rozwiaz();
	void zmien_wybrane(); // pozwala nam poruszac sie po tablicy
	bool czy_wybrane(); //zwraca prawde jezeli wybrane == true
	bool czy_locked();
	void zmien_value(int x); // pozwalam zmienic jezeli locked == false
	void shownvalueTohiddenvalue();
	void hiddenToShown();
	void domyslne();
	void setpos(int x, int y);
	void color_hovered();
	void color_normal();
	void setperm();
	void drawfield(sf::RenderWindow & win);
};