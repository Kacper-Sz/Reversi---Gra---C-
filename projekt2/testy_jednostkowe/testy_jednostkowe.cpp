#include "pch.h"
#include "CppUnitTest.h"

#include "../projekt2/Czlowiek.h"
#include "../projekt2/Gracz.h"
#include "../projekt2/Komputer.h"
#include "../projekt2/Manager.h"
#include "../projekt2/Plansza.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace testyjednostkowe
{
	TEST_CLASS(testyjednostkowe)
	{
	public:
		
		TEST_METHOD(RozmiarPlanszy)
		{
			Plansza p(8);
			Assert::AreEqual(8, p.RozmiarPlanszy());

			Plansza p2(10);
			Assert::AreEqual(10, p2.RozmiarPlanszy());

			Plansza p3(12);
			Assert::AreEqual(12, p3.RozmiarPlanszy());

			Plansza p4(4);
			Assert::AreEqual(4, p4.RozmiarPlanszy());

			try
			{
				Plansza p5(3);
				Assert::Fail();
			}
			catch (const invalid_argument& e)
			{
				Assert::AreEqual("rozmiar minimum 4", e.what());
			}

			try
			{
				Plansza p6(11);
				Assert::Fail();
			}
			catch (const invalid_argument& e)
			{
				Assert::AreEqual("rozmiar ma byc parzysty", e.what());
			}

		}

		TEST_METHOD(WartoscPola)
		{
			Plansza p(8);
			for (int y = 0; y < 8; y++)
			{
				for (int x = 0; x < 8; x++)
				{
					Assert::AreEqual(0, p.WartoscPola(x, y));
				}
			}

			Plansza p2(10);
			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 10; x++)
				{
					Assert::AreEqual(0, p2.WartoscPola(x, y));
				}
			}

			Plansza p3(4);
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					Assert::AreEqual(0, p3.WartoscPola(x, y));
				}
			}

			try
			{
				p3.WartoscPola(12, 1);
				Assert::Fail();
			}
			catch (const out_of_range& e)
			{
				Assert::AreEqual("poza plansza", e.what());
			}
		}

		TEST_METHOD(WstawianieZnaku)
		{
			Plansza p(8);
			p.WstawZnak(3, 3, 1);
			Assert::AreEqual(1, p.WartoscPola(3, 3));
			p.WstawZnak(4, 4, 2);
			Assert::AreEqual(2, p.WartoscPola(4, 4));
			p.WstawZnak(5, 5, 1);
			Assert::AreEqual(1, p.WartoscPola(5, 5));
			p.WstawZnak(6, 6, 3);
			Assert::AreEqual(3, p.WartoscPola(6, 6));
		}

		TEST_METHOD(UstawienieStartowae)
		{
			Plansza p(8);
			p.UstawienieStartowe();
			Assert::AreEqual(1, p.WartoscPola(3, 3));
			Assert::AreEqual(1, p.WartoscPola(4, 4));
			Assert::AreEqual(2, p.WartoscPola(4, 3));
			Assert::AreEqual(2, p.WartoscPola(3, 4));

			Plansza p2(4);
			p2.UstawienieStartowe();
			Assert::AreEqual(1, p2.WartoscPola(1, 1));
			Assert::AreEqual(1, p2.WartoscPola(2, 2));
			Assert::AreEqual(2, p2.WartoscPola(1, 2));
			Assert::AreEqual(2, p2.WartoscPola(2, 1));
		}

		TEST_METHOD(PustePola)
		{
			Plansza p(8);
			auto puste = p.PustePola();
			Assert::IsTrue(64 == puste.size());
			Plansza p2(10);
			auto puste2 = p2.PustePola();
			Assert::IsTrue(100 == puste2.size());
			Plansza p3(4);
			auto puste3 = p3.PustePola();
			Assert::IsTrue(16 == puste3.size());

			p.UstawienieStartowe(); // uzywam juz tej funkcji bo sprawdzilaej ja wczesniej
			auto puste4 = p.PustePola();
			Assert::IsTrue(60 == puste4.size());
			p2.UstawienieStartowe();
			auto puste5 = p2.PustePola();
			Assert::IsTrue(96 == puste5.size());
		}

		TEST_METHOD(MozliweRuchy)
		{
			Plansza p(8);
			p.UstawienieStartowe();
			auto mozliwe = p.MozliweRuchy(1);
			Assert::IsTrue(4 == mozliwe.size());
			auto mozliwe2 = p.MozliweRuchy(2);
			Assert::IsTrue(4 == mozliwe2.size());
			
			Plansza p2(4);
			auto mozliwe3 = p2.MozliweRuchy(1);
			Assert::IsTrue(0 == mozliwe3.size());
			auto mozliwe4 = p2.MozliweRuchy(2);
			Assert::IsTrue(0 == mozliwe4.size());
		}

		TEST_METHOD(PrzywrocPuste)
		{
			Plansza p(8);
			p.UstawienieStartowe();
			p.WstawZnak(1, 1, 3);
			p.WstawZnak(2, 2, 3);
			p.WstawZnak(3, 3, 3);
			p.WstawZnak(4, 4, 3);
			p.PrzywrocPustePola();

			auto puste = p.PustePola();
			Assert::IsTrue(60 == puste.size());

			p.WstawZnak(1, 1, 3);
			p.WstawZnak(2, 2, 3);
			p.WstawZnak(3, 3, 3);
			p.WstawZnak(2, 4, 3);
			p.WstawZnak(5, 5, 2);
			p.WstawZnak(6, 1, 1);
			p.PrzywrocPustePola();
			auto puste2 = p.PustePola();
			Assert::IsTrue(58 == puste2.size());
		}

		TEST_METHOD(OznaczMozliwe)
		{
			Plansza p(4);
			p.UstawienieStartowe();
			p.OznaczMozliweRuchy(1);
			Assert::AreEqual(3, p.WartoscPola(2, 0));
			Assert::AreEqual(3, p.WartoscPola(3, 1));
			Assert::AreEqual(3, p.WartoscPola(0, 2));
			Assert::AreEqual(3, p.WartoscPola(1, 3));

			Plansza p2(4);
			p2.UstawienieStartowe();
			p2.WykonajRuch(2, 0, 1);
			p2.WykonajRuch(1, 0, 2);
			p2.OznaczMozliweRuchy(1);
			
			Assert::AreEqual(3, p2.WartoscPola(0, 0));
			Assert::AreEqual(3, p2.WartoscPola(0, 1));
			Assert::AreEqual(3, p2.WartoscPola(0, 2));
			Assert::AreEqual(3, p2.WartoscPola(0, 3));
		}

		TEST_METHOD(WykonanieRuchu) // w funkcji wykonaj ruch sprawdzam tez sprawdzanie kierunkow, odwracania
		{
			Plansza p(4);
			p.UstawienieStartowe();
			p.WykonajRuch(2, 0, 1);
			Assert::AreEqual(1, p.WartoscPola(2, 0));
			Assert::AreEqual(1, p.WartoscPola(2, 1));
			Assert::AreEqual(1, p.WartoscPola(2, 2));
			Assert::AreEqual(1, p.WartoscPola(1, 1));
			Assert::AreEqual(2, p.WartoscPola(1, 2));
		}

		TEST_METHOD(Zliczanie) // w funkcji wykonaj ruch sprawdzam tez sprawdzanie kierunkow, odwracania
		{
			Plansza p(4);
			p.UstawienieStartowe();
			p.WykonajRuch(2, 0, 1);
			Assert::AreEqual(1, p.WartoscPola(2, 0));
			Assert::AreEqual(1, p.WartoscPola(2, 1));
			Assert::AreEqual(1, p.WartoscPola(2, 2));
			Assert::AreEqual(1, p.WartoscPola(1, 1));
			Assert::AreEqual(2, p.WartoscPola(1, 2));

			int gracz1 = 0;
			int gracz2 = 0;
			p.ZliczPionki(gracz1, gracz2);
			Assert::AreEqual(4, gracz1);
			Assert::AreEqual(1, gracz2);

		}
	};
}
