#include <iostream>

#include "Gracz.h"

using namespace std;

Gracz::Gracz(int wartosc, Plansza& plansza)
{
	this->symbol = wartosc;
	this->plansza = &plansza;
}

void Gracz::Ruch()
{
	cout << "to jest ruch gracza" << "\n";
}