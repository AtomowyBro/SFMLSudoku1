#include "Sudoku.h"
#include "field.h"
#include "Menu.h"
#include "buttons.h"

int main()
{
	Sudoku plansza(time(NULL)%100);
	przycisk_nowa_gra p1(plansza);
	przycisk_wczytaj_gre p2(plansza);
	przycisk_zapisz_gre p3(plansza);
	przycisk_rozwiaz p4(plansza);
	przycisk_koniec p5;
	menu1 menu(p1, p2, p3, p4, p5);
	bool graj = false;
	bool wyjscie = false;
	int opcja = 0;
	int staraopcja = 0;
	while (!wyjscie)
	{
		sf::RenderWindow Menu(sf::VideoMode(400, 60 * 5), "Menu");

		sf::Font font;

		while (Menu.isOpen())
		{
			sf::Event Menu_event;

			menu.zmien_aktywne(staraopcja);
			int opcja = sf::Mouse::getPosition(Menu).y / 60;
			if (opcja < 0)
				opcja = 0;
			if (opcja >= 4)
				opcja = 4;
			staraopcja = opcja;
			menu.zmien_aktywne(opcja);

			while (Menu.pollEvent(Menu_event))
			{
				if (Menu_event.type == sf::Event::Closed)
				{
					Menu.close();
					wyjscie = true;
					graj = false;
				}
				if (Menu_event.type == sf::Event::MouseButtonPressed) //Proste menu z mozliwoscia wyboru trudnosci, bez trudnosci ustawiane jest po przeketnej
				{
					if (Menu_event.mouseButton.button == sf::Mouse::Left)
					{
						if (opcja == 0)
						{
							Menu.close();
							plansza.zeruj();
							plansza.generaterandom();
							plansza.rozwiazsudoku();
							plansza.losuj();
							graj = true;
						}
						if (opcja == 1)
						{
							Menu.close();
							//plansza.zeruj();
							wczytajbaze(plansza);
							graj = true;
						}
						if (opcja == 2)
						{
							zapiszbaze(plansza);
							graj = false;
						}
						if (opcja == 3)
						{
							Menu.close();
							graj = true;
							plansza.zeruj();
						}
						if (opcja == 4)
						{
							graj = false;
							wyjscie = true;
							Menu.close();
						}
					}
				}
			}
			Menu.clear();

			menu.drukuj(Menu);

			Menu.display();

		}
		if (graj)
		{
			sf::RenderWindow Okno(sf::VideoMode(9 * 41 - 1 + 2, 9 * 41 - 1 + 2), "Test");

			int stary_wiersz = 0;
			int stara_kolumna = 0;
			int wybrana_kolumna = 0;
			int wybrany_wiersz = 0;

			while (Okno.isOpen())
			{
				sf::Event zdarzenie;

				while (Okno.pollEvent(zdarzenie))
				{
					if (zdarzenie.type == sf::Event::Closed)
						Okno.close();

					if (zdarzenie.type == sf::Event::MouseButtonPressed) //kod skopiowany z przykladow k6
					{
						if (zdarzenie.mouseButton.button == sf::Mouse::Left)
						{
							plansza.zaznacz(stara_kolumna, stary_wiersz);
							int wiersz = sf::Mouse::getPosition(Okno).y / 41;
							int kolumna = sf::Mouse::getPosition(Okno).x / 41;
							wybrana_kolumna = kolumna;
							wybrany_wiersz = wiersz;
							plansza.zaznacz(kolumna, wiersz); // albo na odwrót - zale¿nie jak to sobie zdefiniowaliœcie
							stara_kolumna = kolumna;
							stary_wiersz = wiersz;
						}
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num1 || zdarzenie.key.code == sf::Keyboard::Numpad1))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 1);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num2 || zdarzenie.key.code == sf::Keyboard::Numpad2))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 2);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num3 || zdarzenie.key.code == sf::Keyboard::Numpad3))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 3);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num4 || zdarzenie.key.code == sf::Keyboard::Numpad4))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 4);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num5 || zdarzenie.key.code == sf::Keyboard::Numpad5))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 5);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num6 || zdarzenie.key.code == sf::Keyboard::Numpad6))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 6);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num7 || zdarzenie.key.code == sf::Keyboard::Numpad7))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 7);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num8 || zdarzenie.key.code == sf::Keyboard::Numpad8))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 8);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num9 || zdarzenie.key.code == sf::Keyboard::Numpad9))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 9);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && (zdarzenie.key.code == sf::Keyboard::Num0 || zdarzenie.key.code == sf::Keyboard::Numpad0))
					{
						plansza.change_value(wybrana_kolumna, wybrany_wiersz, 0);
					}
					if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::LBracket)
					{
						plansza.rozwiazsudoku();
						plansza.rozwiaz();
					}
					if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::RBracket)
					{
						plansza.perset_used();
					}
				}

				Okno.clear();

				plansza.drawboard(Okno);

				Okno.display();
			}
		}
	}
	

	return 0;
}
