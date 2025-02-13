#include <iostream>
#include <windows.h>

#include "Czlowiek.h"

using namespace std;

Czlowiek::Czlowiek(int wartosc, Plansza& plansza) :Gracz(wartosc, plansza) {}

void Czlowiek::Ruch()
{
    
	// oznaczam mozliwe ruchy
    plansza->OznaczMozliweRuchy(symbol);

	// dopiero wtedy wypisuje plansze
    plansza->Wypisz();

    Sleep(1000);

	// biore wspolrzedne od gracza dopoki nie poda dobrych
    while (true)
    {
        
        int x, y;

        cout << "podaj wspolrzedne x:" << endl;
        cin >> x;
        cout << "podaj wspolrzedne y:" << endl;
        cin >> y;

        // ZMNIEJSZAM O 1 BO W KODZIE OPERUJE NA INDEKSIE TABLICY
        x = x - 1;
        y = y - 1;

        // sprawdzam czy dozwolone jak tak to wykonuje ruch
        if (plansza->CzyRuchDozwolony(x, y, symbol))
        {
            plansza->WykonajRuch(x, y, symbol);
            break;
        }
        else
        {
            cout << "Ruch niedozwolony. Sprobuj ponownie." << endl;
        }
    }
	// przywrocam puste pola
    plansza->PrzywrocPustePola();
}