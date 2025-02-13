#pragma once

#include "Gracz.h"
#include "Plansza.h"

class Czlowiek : public Gracz
{
public:
	Czlowiek(int wartosc, Plansza& plansza);
	void Ruch() override;
};

