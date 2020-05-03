// PROJEKT_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include "Generator.h"
#include"kolejka.h"
#include"kopiec.h"
#include "Dijkstra.h"
#include <iostream>
#include "Lista.cpp"
#include "Czas.h"
#include "CzytajGraf.h"
using namespace std;
#define INF 20000000

int main()
{
	ofstream wyniki;
	wyniki.open("wyniki.txt");
	Czas czasDzialania;
	int *n, *gestosc;
	int *start;
	n = new int;
	start = new int;
	gestosc = new int;
	cout << "Hello World!\n";
	int gestosci[4] = { 25,50,75,100 };

	cout << "liczba wierzcholkow:\n";
	cin >> *n;
	cout << "gestosc w procentach:\n";
	cin >> *gestosc;
	cout << "wierzcholek startowy:\n";
	cin >> *start;

	
	
	int *poprzedniki = new int[*n];
	int *dojscie = new int[*n];
		
		
			wyniki << "\nmacierzowa\n";

			//for (int i = 0; i < 4; ++i)
			//{
				//*gestosc = gestosci[i];
				wyniki << "n= " << *n << "\n";
				wyniki << "gestosc: " << *gestosc << "%\n\n";
				/*
				*n = czytaj_n("graf.txt");
				*start = czytaj_start("graf.txt");
				*gestosc = 2 * czytaj_krawedzie("graf.txt") / (*n*(*n - 1));
				*/
				//for (int j = 0; j < 25; ++j)
				//{
					bool spojny = 0;
					cout << "GENERUJE GRAF\n";
					int **graf = /*czytaj_macierz("graf.txt");*/  generuj_graf_jako_macierz(gestosc, n, *start);
					//List <int>* graf = generuj_graf_jako_liste(gestosc, n, *start);

					czasDzialania.czasStart();
					dijkstra_macierz(graf, poprzedniki, dojscie, n, start);
					//dijkstra_lista(graf, poprzedniki, dojscie, n, start);
					//dijkstra_dla_listy(graf, poprzedniki, dojscie, n, start);
					czasDzialania.czasStop();

					for (int i = 0; i < *n; ++i)
					{
						if (*(dojscie + i) == INF)
						{
							cout << "\nGRAF NIESPOJNY\nlosuje ponownie\n";
							spojny = 0;
							break;
						}
						else spojny = 1;
					}

					while (!spojny) //jesli wylosujemy niespojny to losuje ponownie
					{

						graf = generuj_graf_jako_macierz(gestosc, n, *start);
						//graf = generuj_graf_jako_liste(gestosc, n, *start);
						czasDzialania.czasStart();
						dijkstra_macierz(graf, poprzedniki, dojscie, n, start);
						//dijkstra_dla_listy(graf, poprzedniki, dojscie, n, start);
						czasDzialania.czasStop();

						for (int i = 0; i < *n; ++i)
						{
							if (*(dojscie + i) == INF)
							{
								cout << "\nGRAF NIESPOJNY\nlosuje ponownie\n";
								spojny = 0;
								for (int i = 0; i < *n; ++i)
								{
									//for (int j = 0; j < graf[i].daj_size(); ++j)
									{
										//graf[i].remove(j);
									}
									//cout << "\nsasiedzi " << i << ":\n";
									//(graf + i)->showcase();
									delete[] graf[i];
								}
								delete[] graf;
								break;
							}
							else spojny = 1;
						}
					}

					wyniki << czasDzialania.czasWykonania() << "\n";
					/*
					cout << "koszty dojscia do wierzcholkow:\n";
					for (int i = 0; i < *n; ++i)
					{
						cout << i << " " << *(dojscie + i) << " \n";
					}
					cout << "Sciezka:\n";
					for (int i = 0; i < *n; ++i)
					{
						cout << i << " " << *(poprzedniki + i) << "\n";
					}
					*/
					for (int i = 0; i < *n; ++i)
					{
						//for (int j = 0; j < graf[i].daj_size(); ++j)
						{
							//graf[i].remove(j);
						}
						//cout << "\nsasiedzi " << i << ":\n";
						//(graf + i)->showcase();
						delete[] graf[i];
					}
					delete[] graf;

					//cout << i << " " << j << "\n";
				//}
				wyniki << "\n\n\n";
			//}

		delete[] poprzedniki;
		delete[] dojscie;
		delete n;
		delete start;
		delete gestosc;
		wyniki.close();
		return 0;	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
