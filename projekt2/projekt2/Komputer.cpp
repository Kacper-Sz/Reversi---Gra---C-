#include <iostream>
#include <windows.h>

#include "Komputer.h"

using namespace std;

Komputer::Komputer(int wartosc, Plansza& plansza):Gracz(wartosc, plansza) {}

// ruch komputera polega na wylosowaniu jednego z mozliwych ruchow
void Komputer::Ruch()
{
	plansza->Wypisz();

	Sleep(1000);

	auto mozliwe_ruchy = plansza->MozliweRuchy(symbol);

	if (mozliwe_ruchy.size() == 0)
	{
		cout << "Brak mozliwych ruchow" << endl;
		return;
	}

	int losowy_ruch = rand() % mozliwe_ruchy.size();
	int x = mozliwe_ruchy[losowy_ruch].first;
	int y = mozliwe_ruchy[losowy_ruch].second;

	plansza->WykonajRuch(x, y, symbol);
}