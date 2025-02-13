#include <iostream>


#include "Manager.h"
#include "Gracz.h"
#include "Komputer.h"
#include "Czlowiek.h"

#include <windows.h>

using namespace std;

Manager::Manager()
{
	this->plansza = NULL;
	this->gracz1 = NULL;
	this->gracz2 = NULL;
}

Manager::~Manager()
{
	delete plansza;
	delete gracz1;
	delete gracz2;
}

void Manager::Ustawienia(int rozmiar_planszy, int wybor, int& kto_teraz_zaczyna, char& g1, char& g2)
{
	this->plansza = new Plansza(rozmiar_planszy);
	switch (wybor)
	{
	case 1:
	{
		kto_teraz_zaczyna = 1;
		g1 = 'k';
		g2 = 'c';
		this->gracz1 = new Komputer(1, *plansza);
		this->gracz2 = new Czlowiek(2, *plansza);
		this->plansza->UstawienieStartowe();
		break;
	}
	case 2:
	{
		kto_teraz_zaczyna = 1;
		g1 = 'c';
		g2 = 'k';
		this->gracz1 = new Czlowiek(1, *plansza);
		this->gracz2 = new Komputer(2, *plansza);
		this->plansza->UstawienieStartowe();
		break;
	}
	case 3:
	{
		kto_teraz_zaczyna = 1;
		g1 = 'c';
		g2 = 'c';
		this->gracz1 = new Czlowiek(1, *plansza);
		this->gracz2 = new Czlowiek(2, *plansza);
		this->plansza->UstawienieStartowe();
		break;
	}
	case 4:
	{
		kto_teraz_zaczyna = 1;
		g1 = 'k';
		g2 = 'k';
		this->gracz1 = new Komputer(1, *plansza);
		this->gracz2 = new Komputer(2, *plansza);
		this->plansza->UstawienieStartowe();
		break;
	}
	case 5:
	{
		this->plansza->WczytajStanGry(kto_teraz_zaczyna, g1, g2);
		
		if (g1 == 'k')
		{
			this->gracz1 = new Komputer(1, *plansza);
		}
		else
		{
			this->gracz1 = new Czlowiek(1, *plansza);
		}

		if (g2 == 'k')
		{
			this->gracz2 = new Komputer(2, *plansza);
		}
		else
		{
			this->gracz2 = new Czlowiek(2, *plansza);
		}
		
		break;
	}
	default:
		cout << "Nie ma takiej opcji" << endl;
		break;
	}
}

void Manager::Rozgrywka()
{
	// domyslnie 8
	system("cls");
	int rozmiar = 8;
	int opcja;
	int kto_teraz_zaczyna;
	char g1, g2;
	cout << "REVERSI" << endl;
	cout << "Podaj opcje" << endl;
	cout << "1 - komputer vs gracz" << endl;
	cout << "2 - gracz vs komputer" << endl;
	cout << "3 - gracz vs gracz" << endl;
	cout << "4 - komputer vs komputer" << endl;
	cout << "5 - wczytaj gre" << endl;
	cin >> opcja;

	if (opcja != 5)
	{
		cout << "Podaj rozmiar" << endl;
		cin >> rozmiar;
	}
	this->Ustawienia(rozmiar, opcja, kto_teraz_zaczyna, g1, g2);

	char zapis;
	system("cls");

	while (true)
	{
		//this->plansza->Wypisz();
		//Sleep(1000);
		
		if(kto_teraz_zaczyna == 1)
		{
			this->plansza->Wypisz();
			// zapis jest przed postawieniem
			
			cout << "chcesz zpaisac gre? (t/n): " << endl;
			cin >> zapis;
			if (zapis == 't')
			{
				this->plansza->ZapiszStanGry(kto_teraz_zaczyna, g1, g2);
				cout << "GRA ZAPISANA" << endl;
			}

			Sleep(100);
			system("cls");
			Sleep(100);

			this->gracz1->Ruch();
			kto_teraz_zaczyna = 2;
			auto mozliwe_ruchy = plansza->MozliweRuchy(2);
			if (this->plansza->PustePola().size() == 0 || mozliwe_ruchy.size() == 0)
			{
				this->plansza->Wypisz();
				int gracz1_ilosc = 0;
				int gracz2_ilosc = 0;
				this->plansza->ZliczPionki(gracz1_ilosc, gracz2_ilosc);
				cout << "Gracz 1: " << gracz1_ilosc << " Gracz 2: " << gracz2_ilosc << endl;
				if (gracz1_ilosc > gracz2_ilosc)
				{
					cout << "Gracz 1 wygral" << endl;
				}
				else if (gracz1_ilosc < gracz2_ilosc)
				{
					cout << "Gracz 2 wygral" << endl;
				}
				else
				{
					cout << "Remis" << endl;
				}
				break;
			}
		}
		else
		{
			this->plansza->Wypisz();
			//Sleep(1000);
			
			cout << "chcesz zpaisac gre? (t/n): " << endl;
			cin >> zapis;
			if (zapis == 't')
			{
				//tu ma byc wyjatek try i catch
				this->plansza->ZapiszStanGry(kto_teraz_zaczyna, g1, g2);
				cout << "GRA ZAPISANA" << endl;
			}

			Sleep(100);
			system("cls");
			Sleep(100);

			this->gracz2->Ruch();
			kto_teraz_zaczyna = 1;
			auto mozliwe_ruchy = plansza->MozliweRuchy(1);
			if (this->plansza->PustePola().size() == 0 || mozliwe_ruchy.size() == 0)
			{
				this->plansza->Wypisz();
				int gracz1_ilosc = 0;
				int gracz2_ilosc = 0;
				this->plansza->ZliczPionki(gracz1_ilosc, gracz2_ilosc);
				cout << "Gracz 1: " << gracz1_ilosc << " Gracz 2: " << gracz2_ilosc << endl;
				if (gracz1_ilosc > gracz2_ilosc)
				{
					cout << "Gracz 1 wygral" << endl;
				}
				else if (gracz1_ilosc < gracz2_ilosc)
				{
					cout << "Gracz 2 wygral" << endl;
				}
				else
				{
					cout << "Remis" << endl;
				}
				break;
			}
		}
		
		
	}

	cout << "czy zaczac gre na nowo: tak-1\t koniec-cos innego tylko nie 1" << endl;
	cin >> opcja;
	if (opcja == 1)
	{
		this->Rozgrywka();
	}
	else
	{
		return;
	}
	return;	
}

