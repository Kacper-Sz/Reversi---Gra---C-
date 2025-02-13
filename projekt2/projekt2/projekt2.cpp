#include <iostream>

#include "Plansza.h"
#include "Gracz.h"
#include "Komputer.h"
#include "Czlowiek.h"
#include "Manager.h"

using namespace std;

int main()
{
	srand(time(NULL));

	Manager m;
	m.Rozgrywka();

	return 0;
}