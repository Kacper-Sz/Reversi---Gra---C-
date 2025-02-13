#pragma once

#include "Plansza.h"

class Gracz
{
protected:
	int symbol;
	Plansza* plansza;
public:
	Gracz(int wartosc, Plansza& plansza);

	virtual void Ruch();
};

