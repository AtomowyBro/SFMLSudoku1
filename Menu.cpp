#include "Menu.h"

menu1::menu1(przycisk &wsk1, przycisk &wsk2, przycisk &wsk3, przycisk &wsk4, przycisk &wsk5)
{
	font.loadFromFile("arial.ttf");
	text_color = sf::Color::Black;
	wsk[0] = &wsk1;
	wsk[1] = &wsk2;
	wsk[2] = &wsk3;
	wsk[3] = &wsk4;
	wsk[4] = &wsk5;
	for (int j = 0;j < 5;j++)
	{
		wsk[j]->pole.setPosition(0, j * 60);
		opcja[j].setFont(font);
		opcja[j].setCharacterSize(40);
		opcja[j].setStyle(sf::Text::Bold);
		opcja[j].setPosition(0, j * 60);
		opcja[j].setFillColor(sf::Color::Black);
		opcja[j].setString(wsk[j]->opcja);
	}
}


void menu1::drukuj(sf::RenderWindow & win)
{
	for (int j = 0;j < 5;j++)
	{
		if (wsk[j]->wybrane)
		{
			wsk[j]->pole.setFillColor(sf::Color (240, 240, 240));
			wsk[j]->drawboard(win);
		}
		else
		{
			wsk[j]->pole.setFillColor(sf::Color::White);
			wsk[j]->drawboard(win);
		}
	}
	for (int i = 0;i < 5;i++)
	{
		win.draw(opcja[i]);
	}
}

void menu1::zmien_aktywne(int x)
{
	if (wsk[x]->wybrane)
		wsk[x]->wybrane = false;
	else
		wsk[x]->wybrane = true;
}