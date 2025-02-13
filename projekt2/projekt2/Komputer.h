#pragma once

#include "Gracz.h"
#include "Plansza.h"

class Komputer : public Gracz
{
public:
	Komputer(int wartosc, Plansza& plansza);
	void Ruch() override;
};

