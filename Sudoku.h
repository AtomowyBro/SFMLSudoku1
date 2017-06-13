#pragma once
#include "field.h"



class Sudoku
{
	sf::Font font;
	field board[9][9]; //plansza sudoku 9 x 9
	sf::Text liczby[9][9];
	sf::Color locked, usable, used;
public:
	Sudoku(int nr); //konstruktor planszy ktory generuje plansze w zaleznosci od nr gry
	void generaterandom(); //generujemy 3 macierze 3x3
	void drukuj(); //drukujemy plansze
	void play();
	bool rozwiazsudoku(); // na podstawie wygenerowanych macierzy 3x3 rozwiazujemy sudoku
	bool znajdz_puste(int &wiersz, int &kolumna); //przeszukuje tablice w poszukiwaniu nie zapisanych pol
	bool czy_liczba_w_wierszu(int wiersz, int liczba);
	bool czy_liczba_w_kolumnie(int kolumna, int liczba);
	bool czy_liczba_w_kwadracie(int poczatek_wiersz, int poczatek_kolumna, int liczba);
	bool czy_mozna(int wiersz, int kolumna, int liczba);
	void losuj(); // wybieram 4 miejsca w macierzach 3x3
	void interaktywny_druk(); // ulepszam metode drukuj i daje mozliwosc edycji pojedynczych pol
	void rozwiaz();
	bool zwyciestwo();
	bool czy_liczba_w_wierszu_widoczna(int wiersz, int y, int liczba);
	bool czy_liczba_w_kolumnie_widoczna(int x, int kolumna, int liczba);
	bool czy_liczba_w_kwadracie_widoczna(int poczatek_wiersz, int poczatek_kolumna, int liczba, int x, int y);
	bool czy_mozna_widoczna(int wiersz, int kolumna, int liczba);
	void druk_rozwiazywanie();
	int shownvalue(int i, int y);
	void wczytywanie_hidden(int i, int j, int k);
	void hiddenToShown();
	void zeruj();
	void zaznacz(int x, int y);
	void drawboard(sf::RenderWindow & win); //?
	void color_locked(int i, int j);
	void color_usable(int i, int j);
	void color_used(int i, int j);
	void change_value(int i, int j, int k);
	bool czy_wybrane(int i, int j);
	bool czy_mozna();
	void perset_used();
};

