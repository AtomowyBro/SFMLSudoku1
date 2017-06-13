#pragma once
#include "Sudoku.h"
#include "buttons.h"

class menu1
{
	sf::Font font;
	przycisk *wsk[5];
	sf::Text opcja[5];
	sf::Color text_color;
public:
	menu1(przycisk &wsk1, przycisk &wsk2, przycisk &wsk3, przycisk &wsk4, przycisk &wsk5);
	void drukuj(sf::RenderWindow & win);
	void zmien_aktywne(int x);
};