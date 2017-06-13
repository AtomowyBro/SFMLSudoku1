#include "buttons.h"
#include "field.h"
#include "Sudoku.h"


void zapiszbaze(Sudoku &tab) //zapisuje linia po linii wszystkie cechy wszystkich struktor do pliku w folderze z projektem
{
	std::fstream zapisz;
	zapisz.open("baza.txt", std::ios::out);
	for (int i = 0; i < 9;i++)
	{
		for (int j = 0; j < 9;j++)
		{
			zapisz << tab.shownvalue(i, j);
		}
		zapisz << std::endl;
	}
	zapisz.close();
	zapisz.clear();
}

void wczytajbaze(Sudoku &tab)
{
	std::ifstream wczytaj;
	wczytaj.open("baza.txt", std::ios::in);

	if (!wczytaj.good())
	{
		std::cout << "Plik nie istnieje" << std::endl;
		system("pause");
		exit(0);
	}

	std::string aktualna_linia;
	int nr_linii = 1;
	int temp = 0;
	int wiersz_sudoku[9];

	for (int i = 0;i < 9;i++)
	{
		std::getline(wczytaj, aktualna_linia);
		for (int j = 0; j < 9;j++)
		{
			temp = aktualna_linia[j] - 48;
			tab.wczytywanie_hidden(i, j, temp);
		}
	}
	tab.rozwiaz();
	tab.perset_used();

	wczytaj.close();
	wczytaj.clear();
}

std::string przycisk::podaj_opcje()
{
	return opcja;
}

void przycisk::wywolaj()
{
	;
}

przycisk::przycisk()
{
	opcja = "Nazwa";
	wybrane = false;
	pole.setSize(sf::Vector2f(400, 60));
	normal = sf::Color::White;
	hovered = sf::Color(240, 240, 240);
}

przycisk_rozwiaz::przycisk_rozwiaz(Sudoku &tab)
{
	opcja = "Rozwiaz";
	this->tab = &tab;
}

void przycisk_rozwiaz::wywolaj()
{
	tab->zeruj();
	tab->druk_rozwiazywanie();
}

przycisk_nowa_gra::przycisk_nowa_gra(Sudoku &tab)
{
	opcja = "Nowa Gra";
	this->tab = &tab;
	wybrane = true;
};

void przycisk_nowa_gra::wywolaj()
{
	system("cls");
	tab->zeruj();
	tab->play();
}

przycisk_wczytaj_gre::przycisk_wczytaj_gre(Sudoku &tab)
{
	opcja = "Wczytaj Gre";
	this->tab = &tab;
}

void przycisk_wczytaj_gre::wywolaj()
{
	wczytajbaze(*tab);
	tab->interaktywny_druk();
}

przycisk_zapisz_gre::przycisk_zapisz_gre(Sudoku &tab)
{
	opcja = "Zapisz Gre";
	this->tab = &tab;
}

void przycisk_zapisz_gre::wywolaj()
{
	zapiszbaze(*tab);
}

przycisk_koniec::przycisk_koniec()
{
	opcja = "Koniec";
}

void przycisk_koniec::wywolaj(bool &koniec)
{
	koniec = true;
}

void przycisk::drawboard(sf::RenderWindow & win)
{
	win.draw(pole);
}