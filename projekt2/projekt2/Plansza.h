#pragma once

#include <vector>

using namespace std;

class Plansza
{
private:
	int rozmiar;
	int* plansza;
public:
	// na pewno potrzebuje konstruktora i destruktora
	Plansza(int rozmiar);
	~Plansza();

	int RozmiarPlanszy(); // OK

	void Wypisz();
	int WartoscPola(int x, int y); //OK
	void WstawZnak(int x, int y, int wartosc); //OK
	void UstawienieStartowe(); //OK

	vector<pair<int, int>> PustePola(); //OK
	vector<pair<int, int>> MozliweRuchy(int symbol_gracza); //OK

	void OznaczMozliweRuchy(int symbol_gracza); //OK
	void PrzywrocPustePola(); //OK

	bool CzyRuchDozwolony(int x, int y, int symbol_gracza);
	bool CzyKierunekDozwolony(int x, int y, int dx, int dy, int przeciwnik, int symbol_gracza);

	void OdwrocPionki(int x, int y, int dx, int dy, int przeciwnik, int symbol_gracza);
	void WykonajRuch(int x, int y, int symbol_gracza);

	void ZliczPionki(int& gracz1_ilosc, int& gracz2_ilosc);

	void ZapiszStanGry(int kto_teraz_zaczyna, char g1, char g2);
	void WczytajStanGry(int& kto_teraz_zaczyna, char& g1, char& g2);
};

