#include <iostream>
#include <fstream>

#include "Plansza.h"

using namespace std;

// konstruktor
Plansza::Plansza(int wielkosc_planszy)
{
	//minimum 4 i zeby bylo parzyste -> zeby dalo sei latwo ustawic na srodu (bardziej sprawiedliwa plansza?)
	if (wielkosc_planszy < 4)
	{
		throw invalid_argument("rozmiar minimum 4");
	}
	else if (wielkosc_planszy % 2 != 0)
	{
		throw invalid_argument("rozmiar ma byc parzysty");
	}

	this->rozmiar = wielkosc_planszy;
	this->plansza = new int[wielkosc_planszy * wielkosc_planszy]();
}

// destruktor
Plansza::~Plansza()
{
	delete[] plansza;
}


// METODY
// zwracam rozmiar
int Plansza::RozmiarPlanszy()
{
	return rozmiar;
}

// wypisuje plansze
void Plansza::Wypisz()
{
	cout << endl;
	cout << "   ";
	for (int x = 0; x < rozmiar; x++)
	{
		cout << "  " << x + 1 << " ";
	}
	cout << endl;

	for (int y = 0; y < rozmiar; y++)
	{
		cout << "   ";
		for (int x = 0; x < rozmiar; x++)
		{
			cout << "+---";
		}
		cout << "+\n";


		cout << " " << y + 1 << " ";
		for (int x = 0; x < rozmiar; x++)
		{
			switch (this->plansza[y * rozmiar + x])
			{
			case 0:
				cout << "|   ";
				break;
			case 1:
				cout << "| O ";
				break;
			case 2:
				cout << "| X ";
				break;
			case 3:
				cout << "| ? ";
				break;
			default:
				break;
			}
		}
		cout << "|\n";
	}


	cout << "   ";
	for (int x = 0; x < rozmiar; x++)
	{
		cout << "+---";
	}

	cout << "+\n\n\n\n\n\n\n\n\n\n\n";
}

// zwracam wartosc pola
int Plansza::WartoscPola(int x, int y)
{
	if (x < 0 || x >= rozmiar || y < 0 || y >= rozmiar)
	{
		throw out_of_range("poza plansza");
	}
	return this->plansza[y * rozmiar + x];
}

void Plansza::WstawZnak(int x, int y, int wartosc)
{
	if (this->WartoscPola(x, y) == 3 || this->WartoscPola(x, y) == 0)
	{
		this->plansza[y * rozmiar + x] = wartosc;
	}
}

// ustawiam startowe wartosci
void Plansza::UstawienieStartowe()
{
	int srodek1 = (rozmiar / 2) - 1; //1
	int srodek2 = rozmiar / 2; //2

	// na srodku ustawiam 4 znaki kazdego gracza
	this->plansza[srodek1 * rozmiar + srodek1] = 1; // gracz 1 (O)
	this->plansza[srodek2 * rozmiar + srodek2] = 1; // gracz 1 (O)

	this->plansza[srodek2 * rozmiar + srodek1] = 2; // gracz 2 (X)
	this->plansza[srodek1 * rozmiar + srodek2] = 2; // gracz 2 (X)
}

// do zwracania wektora pustych pol
vector<pair<int, int>> Plansza::PustePola()
{
	// wektor par (x, y)
	vector<pair<int, int>> puste_pola;

	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			// tam gdzie wartosc jest 0 to tworze pare i dodaje do wektora
			if (this->WartoscPola(x, y) == 0)
			{
				puste_pola.push_back(make_pair(x, y));
			}
		}
	}
	return puste_pola;
}

// do zwracania wektora ktory ma wspolrzezne gdzie mozna postawic znak
vector<pair<int, int>> Plansza::MozliweRuchy(int symbol_gracza)
{
	vector<pair<int, int>> mozliwe_ruchy;

	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			// jesli ruch dozwolony to dodaje do wektora
			if (this->CzyRuchDozwolony(x, y, symbol_gracza))
			{
				mozliwe_ruchy.push_back(make_pair(x, y));
			}
		}
	}
	return mozliwe_ruchy;
}


// oznaczam te miejsca gdzie moge postawic znak
void Plansza::OznaczMozliweRuchy(int symbol_gracza)
{
	vector<pair<int, int>> mozliwe_ruchy = this->MozliweRuchy(symbol_gracza);

	// dla kazdego z mozliwych ruchow oznacz pole jako mozliwe
	for (const auto& ruch : mozliwe_ruchy)
	{
		int x = ruch.first;
		int y = ruch.second;
		// pole z mozliwoscia ruchu oznaczam jako 3
		//cout << "x: " << x << " y: " << y << endl;
		this->plansza[y * rozmiar + x] = 3;
	}
}

// zamieniam 3 na 0
void Plansza::PrzywrocPustePola()
{
	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			// przy przechodzeniu przez cala tablice sprawdzam czy jest 3 i zamieniam na 0
			if (this->plansza[y * rozmiar + x] == 3)
			{
				this->plansza[y * rozmiar + x] = 0; 
			}
		}
	}
}




// sprawdzenmie czy moge isc w danym kierunku
// x, y wspolrzedne; dx, dy okresla kierunek w ktorym bede sie poruszal; przeciwnik i symbol_gracza to symbole graczy zalezne od tego dla jakiego wywoluje funkcje
bool Plansza::CzyKierunekDozwolony(int x, int y, int dx, int dy, int przeciwnik, int symbol_gracza)
{
	// okreslam nowe wspolrzedne
	int nowy_x = x + dx;
	int nowy_y = y + dy;


	bool znaleziono_przeciwnika = false;

	// sprawdzam czy jestem na planszy i na nastepnym polu jest pionek przeciwnika
	while (nowy_x >= 0 && nowy_x < rozmiar && nowy_y >= 0 && nowy_y < rozmiar && this->WartoscPola(nowy_x, nowy_y) == przeciwnik)
	{
		// ide dalej w tym kierunku
		nowy_x += dx;
		nowy_y += dy;
		znaleziono_przeciwnika = true;
	}

	// jak znaleizono przeciwnika i jestem jeszcze na planszy ORAZ za przeciwnikiem jest pionek gracza to kierunek bedzei dozwolony
	return (znaleziono_przeciwnika && nowy_x >= 0 && nowy_x < rozmiar && nowy_y >= 0 && nowy_y < rozmiar && this->WartoscPola(nowy_x, nowy_y) == symbol_gracza);
}

// sprawdzam czy moge wykonac ruch
bool Plansza::CzyRuchDozwolony(int x, int y, int symbol_gracza)
{
	// jak jest poza plansza lub pole jest juz zajete to nie mozna robic ruchu
	if (x < 0 || x >= rozmiar || y < 0 || y >= rozmiar || this->WartoscPola(x, y) == 1 || this->WartoscPola(x, y) == 2)
	{
		return false;
	}

	// okreslam symbol przeciwnika
	int przeciwnik = 0;
	if (symbol_gracza == 1)
	{
		przeciwnik = 2;
	}
	else
	{
		przeciwnik = 1;
	}

	// ruch dozwolony jesli w jednym z 8 kierunkow mozna isc
	if (CzyKierunekDozwolony(x, y, -1, 0, przeciwnik, symbol_gracza)) return true; // lewo
	if (CzyKierunekDozwolony(x, y, 1, 0, przeciwnik, symbol_gracza)) return true;  // prawo
	if (CzyKierunekDozwolony(x, y, 0, -1, przeciwnik, symbol_gracza)) return true; // gora
	if (CzyKierunekDozwolony(x, y, 0, 1, przeciwnik, symbol_gracza)) return true;  // dol IDE DALEJ NA LISTE
	if (CzyKierunekDozwolony(x, y, -1, -1, przeciwnik, symbol_gracza)) return true; // lewo gora
	if (CzyKierunekDozwolony(x, y, 1, -1, przeciwnik, symbol_gracza)) return true;  // prawo gora
	if (CzyKierunekDozwolony(x, y, -1, 1, przeciwnik, symbol_gracza)) return true;  // lewo dol
	if (CzyKierunekDozwolony(x, y, 1, 1, przeciwnik, symbol_gracza)) return true;   // prawo dol

	// tak wygladaja osie do poruszania sie po planszy
	
	//        |
	//        |	
	//  ----- + ------>	
	//        |      x
	//       \./ y		  
	

	// nie ma dozwolonego ruchu
	return false;
}


// odwracam symbol gracza na planszy po zrobieniu ruchy
// x, y wspolrzedne; dx, dy okresla kierunek w ktorym bede sie poruszal; przeciwnik i symbol_gracza to symbole graczy zalezne od tego dla jakiego wywoluje funkcje
void Plansza::OdwrocPionki(int x, int y, int dx, int dy, int przeciwnik, int symbol_gracza)
{
	// okreslam nowe wspolrzedne zgodnie z kierunkiem
	int nowy_x = x + dx;
	int nowy_y = y + dy;

	// odwracam pionki przeciwnika na planszy po wykonanoi ruchu
	// dopoki jestem na planszy i na polu jest pionek przeciwnika to zamieniam na pionek gracza
	while (nowy_x >= 0 && nowy_x < rozmiar && nowy_y >= 0 && nowy_y < rozmiar && this->WartoscPola(nowy_x, nowy_y) == przeciwnik)
	{
		// this->WstawZnak(nowy_x, ny, symbol_gracza);
		// zmiieniam i ide dalej w tym kierunku
		this->plansza[nowy_y * rozmiar + nowy_x] = symbol_gracza;
		nowy_x += dx;
		nowy_y += dy;
	}
}

// jedna funkcja co wykonuje caly ruch
void Plansza::WykonajRuch(int x, int y, int symbol_gracza)
{
	// sprawdzam czy ruch jest dozwolony
	// czyli czy w ktoryms z 8 kierunkow moge isc
	if (!this->CzyRuchDozwolony(x, y, symbol_gracza))
	{
		cout << "ruch niedozwolony, sprobuj ponownie" << endl;
		return;
	}

	// okreslam symbol przeciwnika
	int przeciwnik = 0;

	if (symbol_gracza == 1)
	{
		przeciwnik = 2;
	}
	else
	{
		przeciwnik = 1;
	}

	// sprawdzam kazdy z 8 kierunkow
	// jak tak to zmieniam znaki na tej lini
	// 1. lewo
	if (CzyKierunekDozwolony(x, y, -1, 0, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, -1, 0, przeciwnik, symbol_gracza);
	}
	// 2. prawo
	if (CzyKierunekDozwolony(x, y, 1, 0, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, 1, 0, przeciwnik, symbol_gracza);
	}
	// 3. gora
	if (CzyKierunekDozwolony(x, y, 0, -1, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, 0, -1, przeciwnik, symbol_gracza);
	}
	// 4. dol
	if (CzyKierunekDozwolony(x, y, 0, 1, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, 0, 1, przeciwnik, symbol_gracza);
	}
	// 5. lewo gora
	if (CzyKierunekDozwolony(x, y, -1, -1, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, -1, -1, przeciwnik, symbol_gracza);
	}
	// 6. prawo gora
	if (CzyKierunekDozwolony(x, y, 1, -1, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, 1, -1, przeciwnik, symbol_gracza);
	}
	// 7. lewo dol
	if (CzyKierunekDozwolony(x, y, -1, 1, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, -1, 1, przeciwnik, symbol_gracza);
	}
	// 8. prawo dol
	if (CzyKierunekDozwolony(x, y, 1, 1, przeciwnik, symbol_gracza))
	{
		OdwrocPionki(x, y, 1, 1, przeciwnik, symbol_gracza);
	}

	// stawiam znak gracza na planszy
	this->WstawZnak(x, y, symbol_gracza);
}

// zliczam pionki do sprawdzenia kto wygral
void Plansza::ZliczPionki(int& gracz1_ilosc, int& gracz2_ilosc) {
	gracz1_ilosc = 0;
	gracz2_ilosc = 0;

	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			if (this->WartoscPola(x, y) == 1)
			{
				gracz1_ilosc++;
			}
			else if (this->WartoscPola(x, y) == 2)
			{
				gracz2_ilosc++;
			}
		}
	}
}

// zapisuje stan gry do pliku
void Plansza::ZapiszStanGry(int kto_teraz_zaczyna, char g1, char g2)
{
	//otwieram plik
	ofstream plik("../stan_gry.txt");

	if (!plik)
	{
		throw invalid_argument("nie mozna otworzyc");
	}

	//gracz 1, gracz 2, kto teraz zaczyna, rozmiar planszy i plansza
	plik << g1 << endl;
	plik << g2 << endl;
	plik << kto_teraz_zaczyna << endl;
	plik << rozmiar << endl;

	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			plik << this->WartoscPola(x, y) << " ";
		}
		plik << endl;
	}

	plik.close();
}

// wczytuje stan gry z pliku
void Plansza::WczytajStanGry(int& kto_teraz_zaczyna, char& g1, char& g2)
{
	ifstream plik("../stan_gry.txt");

	if (!plik)
	{
		throw invalid_argument("nie mozna otworzyc");
	}

	//gracz 1, gracz 2, kto teraz zaczyna, rozmiar planszy i plansza
	plik >> g1;
	plik >> g2;
	plik >> kto_teraz_zaczyna;

	int nowy_rozmiar;
	plik >> nowy_rozmiar;

	delete[] plansza;

	this->rozmiar = nowy_rozmiar;
	this->plansza = new int[nowy_rozmiar * nowy_rozmiar]();

	for (int y = 0; y < rozmiar; y++)
	{
		for (int x = 0; x < rozmiar; x++)
		{
			plik >> this->plansza[y * rozmiar + x];
		}
	}

	plik.close();
}