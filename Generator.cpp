#pragma once
#include "Generator.h"
#include "Lista.cpp"
#include "Dijkstra.h"
using namespace std;

//GENERUJE MACIERZ SASIEDZTWA
int** generuj_graf_jako_macierz(int *gestosc, int *l_wezlow, int start)
{
	srand(time(NULL));

	ofstream graf;
	graf.open("graf.txt");

	int n = *l_wezlow;	

	int krawedzie = (*gestosc)*(*l_wezlow)*(*l_wezlow - 1)/200;  //ze wzoru

	graf << krawedzie << "	" << n << "	" << start<<"\n"; //nagłówek
	
	//deklaracja dynamicznej tablicy dwuwymiarowej i jej wypełnienie 0 (nie ma żadnych sąsiedztw, graf nie jest stworzony)

		int **macierz_sasiedztwa = new int *[n];

		for (int i = 0; i < n; ++i)
		{
			macierz_sasiedztwa[i] = new int[n];

			for (int j = 0; j < n; ++j)
			{
				macierz_sasiedztwa[i][j] = 0;
			}
		}

		for (int j = 0; j < n; ++j) // aby graf był spójny każdy wierzchołek dostaje conajmniej jedną krawędź
		{
			int poczatek, koniec, waga;
			poczatek = j;
			koniec = rand() % n;
			while (poczatek == koniec || macierz_sasiedztwa[poczatek][koniec] != 0)
			{
				koniec = rand() % n;
			}
			waga = rand() % (n / 2)+1;
			graf << poczatek << "	" << koniec << "	" << waga << "\n";
			macierz_sasiedztwa[poczatek][koniec] = waga;
			macierz_sasiedztwa[koniec][poczatek] = waga;

		}

		for (int i = 0; i < krawedzie - n; ++i) //w tej pętli wpisywane krawędzie 
		{
			int poczatek, koniec, waga;
			poczatek = rand() % n;
			koniec = rand() % n;
			while (poczatek == koniec || macierz_sasiedztwa[poczatek][koniec] != 0)
			{
				poczatek = rand() % n;
				koniec = rand() % n;
			}
			waga = rand() % (n / 2)+1;
			graf << poczatek << "	" << koniec << "	" << waga << "\n";
			macierz_sasiedztwa[poczatek][koniec] = waga;
			macierz_sasiedztwa[koniec][poczatek] = waga;
		}
		graf.close();

		return macierz_sasiedztwa;
}


//GENERUJE LISTE SASIEDZTWA
List <int>* generuj_graf_jako_liste(int *gestosc, int *l_wezlow, int start)
{

	srand(time(NULL));

	ofstream graf;

	int n = *l_wezlow;

	graf.open("graf.txt");

	int krawedzie = (*gestosc)*(*l_wezlow)*(*l_wezlow - 1) / 200;
	graf << "WYGENEROWANY GRAF O PARAMETRACH:\n";
	graf << krawedzie << "	" << n << "	" << start << "\n"; //nagłówek
	
	List <int>* lista_sasiedztwa = new List<int>[n];
		
		for (int j = 0; j < n; ++j) // aby graf był spójny każdy wierzchołek dostaje conajmniej jedną krawędź
		{
			int poczatek, koniec, waga;
			poczatek = j;
			koniec = rand() % n;
			while (poczatek == koniec || lista_sasiedztwa[poczatek].search(koniec) || (lista_sasiedztwa[koniec]).search(poczatek)) //czy_sasiad((lista_sasiedztwa[poczatek]),&koniec) || czy_sasiad((lista_sasiedztwa[koniec]), &poczatek))
			{
				koniec = rand() % n;
			}
			waga = rand() % (n / 2)+1;
			graf << poczatek << "	" << koniec << "	" << waga << "\n";
			(lista_sasiedztwa[poczatek]).pushback(koniec,waga);
			(lista_sasiedztwa[koniec]).pushback(poczatek, waga); 

		}

		int malo = krawedzie - *l_wezlow;

		for (int i = 0; i < malo; ++i) //w tej pętli wpisywane krawędzie 
		{
			int poczatek, koniec, waga;
			poczatek = rand() % n;
			koniec = rand() % n;
			while (poczatek == koniec || lista_sasiedztwa[poczatek].search(koniec) || (lista_sasiedztwa[koniec]).search(poczatek))
			{
				poczatek = rand() % n;
				koniec = rand() % n;
			}
			waga = rand() % (n / 2)+1;
			graf << poczatek << "	" << koniec << "	" << waga << "\n";
			(lista_sasiedztwa[poczatek]).pushback(koniec, waga);
			(lista_sasiedztwa[koniec]).pushback(poczatek, waga);
		}


		graf.close();

		return lista_sasiedztwa;
	
}

//POPRZEDNIA WERSJA ODCZYTU GRAFU Z PLIKU
/*   
List<int>* czytaj_jako_liste(int *krawedzie, int *l_wezlow, int* start)
{
	ifstream dane;
	dane.open("dane.txt");
	dane >> *krawedzie >> *l_wezlow >> *start;
	List <int>* lista_sasiedztwa = new List<int>[n];	

	for (int i = 0; i < *krawedzie; ++i) //w tej pętli wpisywane krawędzie 
	{
		int poczatek, koniec, waga;		
		dane >> poczatek >> koniec >> waga;
		(lista_sasiedztwa[poczatek]).pushback(koniec, waga);
		(lista_sasiedztwa[koniec]).pushback(poczatek, waga);
	}
	return lista_sasiedztwa;
}
int** czytaj_jako_macierz(int *krawedzie, int *l_wezlow, int* start)
{
	ifstream dane;
	dane.open("dane.txt");
	dane >> *krawedzie >> *l_wezlow >> *start;

	int **macierz_sasiedztwa = new int *[n];

	for (int i = 0; i < n; ++i)
	{
		macierz_sasiedztwa[i] = new int[n];

		for (int j = 0; j < n; ++j)
		{
			macierz_sasiedztwa[i][j] = 0;
		}
	}

	for (int j = 0; j < *krawedzie; ++j) // aby graf był spójny każdy wierzchołek dostaje conajmniej jedną krawędź
	{
		int poczatek, koniec, waga;
		dane >> poczatek >> koniec >> waga;
		macierz_sasiedztwa[poczatek][koniec] = waga;
		macierz_sasiedztwa[koniec][poczatek] = waga;

	}
	return macierz_sasiedztwa;
}

*/