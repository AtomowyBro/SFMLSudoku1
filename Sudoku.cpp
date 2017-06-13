#include "Sudoku.h"
#include "field.h"

using namespace std;

void mieszanie(int arr[], int n) // funkcja ktora miesza tablice by latwiej generowac mniejsze kwadraty sudoku
{
	int tab[9] = { 1,2,3,4,5,6,7,8,9 };
	for (int i = 8; i >= 0; --i)
	{
		int j = rand() % (i + 1);
		int temp = tab[i];
		tab[i] = tab[j];
		tab[j] = temp;
	}

	//po wymieszaniu przypisuje do przekazanej tablicy
	for (int i = 0; i<n; ++i)
		arr[i] = tab[i];
}


Sudoku::Sudoku(int nr)
{
	srand(nr);
	font.loadFromFile("arial.ttf");
	locked = sf::Color::Black;
	usable = sf::Color(126, 126, 126);
	used = sf::Color::Red;
	board[0][0].zmien_wybrane();
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			board[i][j].setpos(i*41+i/3, j*41+j/3); // powinno ustawiac pole w zalerznosci od [i][j]
		}
	}
	generaterandom();
	if (rozwiazsudoku())
	{
		cout << "ok\n";
	}
	losuj();
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			liczby[i][j].setFont(font);
			liczby[i][j].setCharacterSize(40);
			liczby[i][j].setStyle(sf::Text::Bold);
			liczby[i][j].setPosition(i * 41 + i / 3 + 8, j * 41 + j / 3 - 6);
			liczby[i][j].setFillColor(sf::Color::Black);
		}
	}
}

void Sudoku::zeruj()
{
	for (int i = 0;i<9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			board[i][j].domyslne();
		}
	}
}

void Sudoku::wczytywanie_hidden(int i, int j, int k)
{
	board[i][j].changehidden(k);
}

int Sudoku::shownvalue(int i, int y)
{
	return board[i][y].shownvalue();
}

void Sudoku::rozwiaz()
{
	for (int i = 0;i < 9;i++)
		for (int j = 0;j < 9;j++)
			board[i][j].rozwiaz();
}

void Sudoku::hiddenToShown()
{
	for (int i = 0;i < 9;i++)
		for (int j = 0;j < 9;j++)
			board[i][j].hiddenToShown();
}

bool Sudoku::zwyciestwo()
{
	int zwyciestwo = 1;
	for (int i = 0; i < 9;i++)
		for (int j = 0; j < 9;j++)
			if (board[i][j].shownvalue() != board[i][j].hiddenvalue())
				return false;
	return true;
}

bool Sudoku::czy_liczba_w_wierszu_widoczna(int wiersz, int y, int liczba)
{
	for (int kolumna = 0;kolumna < 9;kolumna++)
	{
		if (kolumna != y)
		{
			if (board[wiersz][kolumna].shownvalue() == liczba)
				return true;
		}
	}
	return false;
}

bool Sudoku::czy_liczba_w_kolumnie_widoczna(int x, int kolumna, int liczba)
{
	for (int wiersz = 0;wiersz < 9;wiersz++)
	{
		if (wiersz != x)
		{
			if (board[wiersz][kolumna].shownvalue() == liczba)
				return true;
		}
	}
	return false;
}

bool Sudoku::czy_liczba_w_kwadracie_widoczna(int poczatek_wiersz, int poczatek_kolumna, int liczba, int x, int y)
{
	for (int wiersz = 0;wiersz < 3;wiersz++)
	{
		for (int kolumna = 0; kolumna < 3;kolumna++)
		{
			if (wiersz != x&&kolumna != y)
				if (board[wiersz + poczatek_wiersz][kolumna + poczatek_kolumna].shownvalue() == liczba)
				{
					return true;
				}
		}
	}
	return false;
}

bool Sudoku::czy_mozna_widoczna(int wiersz, int kolumna, int liczba)
{
	return czy_liczba_w_wierszu_widoczna(wiersz, kolumna, liczba) || czy_liczba_w_kolumnie_widoczna(wiersz, kolumna, liczba) || czy_liczba_w_kwadracie_widoczna(wiersz - (wiersz % 3), kolumna - (kolumna % 3), liczba, wiersz % 3, kolumna % 3);
}

void Sudoku::druk_rozwiazywanie()
{
	{
		bool koniec = false;
		int i = 0;
		int j = 0;
		int starei; //pozwala nam zmienic bezpiecznie wartosc wybor w 2 polach
		int starej;
		while (!koniec)
		{
			starei = i;
			starej = j;
			system("cls");
			drukuj();
			unsigned char wybor = 7;
			cout << "Mozliwe akcje:" << endl << "=> pole nastepne \n<= pole poprzednie \n/\ pole wyzej \n\/ pole nizej \n1. Wpisz cyfre \n?. Wyswietl rozwiazanie \nESC Wyjscie\n";
			wybor = _getch();
			switch (wybor)
			{
			case 0: //klawisze specjalne (czasem zero czasem 224)
			case 224: //klawisze specjalne
				wybor = _getch();
				cout << wybor;
				switch (wybor)
				{
				case 75: //strza³ka w lewo
					j--; //zmniejszam o jeden po wcisniecu lewej strzalki
					break;
				case 77: //strza³ka w prawo
					j++; //zwiekszam o jeden po wcisnieciu prawej stralki
					break;
				case 72: //strzalka w gore
					i--;
					break;
				case 80:
					i++; //strzalka w dol
					break;
				}
				wybor = 0;
				break;
			case 27: //ESC
				koniec = true; //koncze petle i wracam do menu
				break;
			case '?': //2
				rozwiazsudoku();
				rozwiaz();
				break;
			case 49: //1
				wybor = _getch() - 48;
				if (wybor <= 9 && wybor >= 1)
				{
					board[i][j].zmien_value(wybor);
					board[i][j].shownvalueTohiddenvalue();
				}

				else
				{
					board[i][j].zmien_value(0);
					board[i][j].shownvalueTohiddenvalue();
				}
				if (wybor + 48 == 0 || wybor + 48 == 224)
					wybor = _getch();
				break;
			}
			if (i < 0)
				i = 0; // nie pozwalam wyjsc poza tablice
			else if (i > 8)
				i = 8;
			if (j < 0)
				j = 0; // nie pozwalam wyjsc poza tablice
			else if (j > 8)
				j = 8;
			board[starei][starej].zmien_wybrane();
			board[i][j].zmien_wybrane();
		}
	}
}

void Sudoku::interaktywny_druk()
{
	{
		bool koniec = false;
		int i = 0;
		int j = 0;
		int starei; //pozwala nam zmienic bezpiecznie wartosc wybor w 2 polach
		int starej;
		while (!koniec)
		{
			starei = i;
			starej = j;
			system("cls");
			drukuj();
			unsigned char wybor = 7;
			cout << "Mozliwe akcje:" << endl << "=> pole nastepne \n<= pole poprzednie \n/\ pole wyzej \n\/ pole nizej \n1. Wpisz cyfre \n?. Wyswietl rozwiazanie \nESC Wyjscie\n";
			wybor = _getch();
			switch (wybor)
			{
			case 0: //klawisze specjalne (czasem zero czasem 224)
			case 224: //klawisze specjalne
				wybor = _getch();
				cout << wybor;
				switch (wybor)
				{
				case 75: //strza³ka w lewo
					j--; //zmniejszam o jeden po wcisniecu lewej strzalki
					break;
				case 77: //strza³ka w prawo
					j++; //zwiekszam o jeden po wcisnieciu prawej stralki
					break;
				case 72: //strzalka w gore
					i--;
					break;
				case 80:
					i++; //strzalka w dol
					break;
				}
				wybor = 0;
				break;
			case 27: //ESC
				koniec = true; //koncze petle i wracam do menu
				break;
			case '?': //2
				rozwiaz();
				break;
			case 49: //1
				wybor = _getch() - 48;
				if (wybor <= 9 && wybor >= 1)
					board[i][j].zmien_value(wybor);
				else
					board[i][j].zmien_value(0);
				if (wybor + 48 == 0 || wybor + 48 == 224)
					wybor = _getch();
				break;
			}
			if (i < 0)
				i = 0; // nie pozwalam wyjsc poza tablice
			else if (i > 8)
				i = 8;
			if (j < 0)
				j = 0; // nie pozwalam wyjsc poza tablice
			else if (j > 8)
				j = 8;
			board[starei][starej].zmien_wybrane();
			board[i][j].zmien_wybrane();
		}
	}
	if (zwyciestwo())
		cout << "Wygrales\n";
	else
		cout << "Przegrales\n";
}


void Sudoku::losuj()
{
	int tablica[4];
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			mieszanie(tablica, 4);
			for (int k = 0;k < 4;k++)
			{
				board[3 * i + (tablica[k] / 3)][3 * j + (tablica[k] % 3)].permset();
			}
		}
	}
}

bool Sudoku::czy_mozna(int wiersz, int kolumna, int liczba)
{
	return !czy_liczba_w_wierszu(wiersz, liczba) && !czy_liczba_w_kolumnie(kolumna, liczba) && !czy_liczba_w_kwadracie(wiersz - (wiersz % 3), kolumna - (kolumna % 3), liczba);
}

bool Sudoku::czy_liczba_w_wierszu(int wiersz, int liczba)
{
	for (int kolumna = 0;kolumna < 9;kolumna++)
	{
		if (board[wiersz][kolumna].hiddenvalue() == liczba)
			return true;
	}
	return false;
}

bool Sudoku::czy_liczba_w_kolumnie(int kolumna, int liczba)
{
	for (int wiersz = 0;wiersz < 9;wiersz++)
	{
		if (board[wiersz][kolumna].hiddenvalue() == liczba)
			return true;
	}
	return false;
}

bool Sudoku::czy_liczba_w_kwadracie(int poczatek_wiersz, int poczatek_kolumna, int liczba)
{
	for (int wiersz = 0;wiersz < 3;wiersz++)
	{
		for (int kolumna = 0; kolumna < 3;kolumna++)
		{
			if (board[wiersz + poczatek_wiersz][kolumna + poczatek_kolumna].hiddenvalue() == liczba)
			{
				return true;
			}
		}
	}
	return false;
}

bool Sudoku::rozwiazsudoku()
{
	int wiersz, kolumna;
	if (!znajdz_puste(wiersz, kolumna))
	{
		return true;
	}
	for (int liczba = 1; liczba <= 9;liczba++)
	{
		if (czy_mozna(wiersz, kolumna, liczba))
		{
			board[wiersz][kolumna].changehidden(liczba);
			if (rozwiazsudoku())
			{
				return true;
			}
			else
			{
				board[wiersz][kolumna].changehidden(0);
			}

		}
	}
	return false;
}

bool Sudoku::znajdz_puste(int &wiersz, int &kolumna)
{
	for (wiersz = 0; wiersz < 9; wiersz++)
	{
		for (kolumna = 0; kolumna < 9; kolumna++)
		{
			if (!board[wiersz][kolumna].isused())
			{
				return true;
			}
		}
	}
	return false;
}

void Sudoku::play()
{

	generaterandom();
	if (rozwiazsudoku())
	{
		cout << "ok\n";
	}
	losuj();
	interaktywny_druk();
}

void set_color(int c) // pozwala na edycje kolorow w konsoli
{
	HANDLE uchwyt;
	uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(uchwyt, c);
}

void Sudoku::drukuj()
{
	int wybor;
	set_color(FOREGROUND_GREEN);
	for (int i = 0;i < 9;i++)
	{
		if (!(i % 3))
		{
			for (int i = 0;i < 17;i++)
				cout << "-";
			cout << endl;
		}
		for (int j = 0;j < 9;j++)
		{
			wybor = board[i][j].shownvalue();
			if (!(j % 3))
			{
				cout << "|";
			}
			if (board[i][j].czy_wybrane())
			{
				set_color(BACKGROUND_RED);
				if (wybor != 0)
				{
					cout << wybor;
				}
				else
				{
					cout << " ";
				}
				set_color(FOREGROUND_GREEN);
			}
			else
			{
				set_color(FOREGROUND_GREEN);
				if (wybor != 0)
				{
					if (czy_mozna_widoczna(i, j, wybor))
					{
						cout << "\a";
						set_color(FOREGROUND_BLUE);
						cout << wybor;
						set_color(FOREGROUND_GREEN);
					}
					else
						cout << wybor;
				}
				else
				{
					cout << " ";
				}
			}

		}
		cout << "|\n";
	}
	for (int i = 0;i < 17;i++)
		cout << "-";
	cout << endl;
}

void Sudoku::color_usable(int i, int j)
{
	liczby[i][j].setFillColor(usable);
}


void Sudoku::color_locked(int i, int j)
{
	liczby[i][j].setFillColor(locked);
}

void Sudoku::color_used(int i, int j)
{
	liczby[i][j].setFillColor(used);
}

void Sudoku::generaterandom()
{
	int pomieszana_lista[9];
	int l = 0;
	for (int k = 0; k < 3;k++)
	{
		mieszanie(pomieszana_lista, 9);
		for (int i = 0;i < 3;i++)
		{
			for (int j = 0; j < 3;j++)
			{
				board[3 * k + i][3 * k + j].changehidden(pomieszana_lista[l]);
				l++;
			}
		}
		l = 0;
	}
}
void Sudoku::change_value(int i, int j,int k)
{
	board[i][j].zmien_value(k);
}

bool Sudoku::czy_wybrane(int i, int j)
{
	return board[i][j].czy_wybrane();
}

void Sudoku::perset_used()
{
	for (int wiersz = 0; wiersz < 9; wiersz++)
	{
		for (int kolumna = 0; kolumna < 9; kolumna++)
		{
			board[wiersz][kolumna].shownvalueTohiddenvalue();
			if (board[wiersz][kolumna].isused())
				board[wiersz][kolumna].setperm();
		}
	}
}

void Sudoku::drawboard(sf::RenderWindow & win) // 
{
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			if (board[i][j].shownvalue() != 0)
				liczby[i][j].setString(std::to_string(board[i][j].shownvalue()));
			else
				liczby[i][j].setString(" ");
		}
	}
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			board[i][j].drawfield(win);
			if (!board[i][j].czy_wybrane())
				board[i][j].color_normal();
			else
				board[i][j].color_hovered();
		}
	}
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			if (!czy_mozna_widoczna(i, j, board[i][j].shownvalue()))
			{
				if (board[i][j].czy_locked())
				{
					liczby[i][j].setFillColor(locked);
					win.draw(liczby[i][j]);
				}
				else
				{
					liczby[i][j].setFillColor(usable);
					win.draw(liczby[i][j]);
				}
			}
			else
			{
				liczby[i][j].setFillColor(used);
				win.draw(liczby[i][j]);
			}
		}
	}
}

void Sudoku::zaznacz(int x, int y)
{
	board[x][y].zmien_wybrane();
}