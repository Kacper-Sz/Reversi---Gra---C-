#pragma once

#include "Plansza.h"
#include "Gracz.h"

class Manager
{
private:
	Plansza* plansza;
	Gracz* gracz1;
	Gracz* gracz2;
public:
	Manager();
	~Manager();
	void Ustawienia(int rozmiar_planszy, int wybor, int& kto_teraz_zaczyna, char& g1, char& g2);
	void Rozgrywka();
};

