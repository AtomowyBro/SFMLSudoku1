#include "field.h"


field::field()
{
	locked = false;
	hidden_value = 0;
	value = 0;
	wybrane = false;
	pole.setSize(sf::Vector2f(40, 40));
	normal = sf::Color::White;
	hovered = sf::Color (192, 192, 192);
}

bool field::czy_locked()
{
	return locked;
}

void field::setpos(int x, int y) //metoda potrzebna do zmiany pozycji pola
{
	pole.setPosition(x, y);
}

void field::domyslne()
{
	locked = false;
	hidden_value = 0;
	value = 0;
}

void field::shownvalueTohiddenvalue()
{
	hidden_value = value;
}

int field::shownvalue()
{
	return value;
}

void field::zmien_value(int x)
{
	if (!locked)
		value = x;
}

void field::rozwiaz()
{
	value = hidden_value;
}

void field::setperm()
{
	locked = true;
}

void field::permset()
{
	locked = true;
	value = hidden_value;
}

void field::zmien_wybrane()
{
	if (wybrane)
	{
		wybrane = false;
	}
	else
	{
		wybrane = true;
	}
}

bool field::czy_wybrane()
{
	if (wybrane)
		return true;
	return false;
}

int field::hiddenvalue()
{
	return hidden_value;
}

void field::showvalue()
{
	std::cout << value;
}

bool field::isused()
{
	if (hidden_value != 0)
		return true;
	else
		return false;
}

void field::changehidden(int x)
{
	hidden_value = x;
}

void field::changevalue(int x)
{
	value = x;
}

void field::color_hovered()
{
	pole.setFillColor(hovered);
}

void field::hiddenToShown()
{
	hidden_value = value;
}

void field::color_normal()
{
	pole.setFillColor(normal);
}

void field::drawfield(sf::RenderWindow & win) //?
{
	win.draw(pole);
}