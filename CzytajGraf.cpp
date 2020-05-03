#include "CzytajGraf.h"

using namespace std;

int ** czytaj_macierz(string nazwa)
{
	fstream plik;
	plik.open(nazwa);

	int *n = new int;
	int *krawedzie = new int;
	int *start = new int;
	int *poczatek = new int;
	int *koniec = new int;
	int *waga = new int;
	plik >> *krawedzie >> *n >> *start; //odczyt ilości wierzchołków, krawędzi i wierzchołka startowego

	int **macierz_sasiedztwa = new int* [*n];
	for (int i = 0; i < *n; ++i) //deklaracja dynamicznej tablicy dwuwymiarowej i jej wypełnienie 0 (nie ma żadnych sąsiedztw, graf nie jest stworzony)
	{
		macierz_sasiedztwa[i] = new int[*n];

		for (int j = 0; j < *n; ++j)
		{
			macierz_sasiedztwa[i][j] = 0;
		}
	}

	for (int i = 0; i < *krawedzie; ++i) //czytamy krawędzie
	{
		plik >> *poczatek >> *koniec >> *waga;
		macierz_sasiedztwa[*poczatek][*koniec] = *waga;
		macierz_sasiedztwa[*koniec][*poczatek] = *waga;
	}
	
	plik.close();

	delete n;
	delete start;
	delete poczatek;
	delete koniec;
	delete krawedzie;
	delete waga;
	return macierz_sasiedztwa;
}

List<int>* czytaj_jako_liste(string nazwa)
{

	fstream plik;
	plik.open(nazwa);

	int *n = new int;
	int *krawedzie = new int;
	int *start = new int;
	int *poczatek = new int;
	int *koniec = new int;
	int *waga = new int;
	
	//odczyt ilości wierzchołków, krawędzi i wierzchołka startowego
	
	plik >> *krawedzie >> *n >> *start;


	List <int>* lista_sasiedztwa = new List<int>[*n];

	for (int i = 0; i < *krawedzie; ++i) //w tej pętli wpisywane krawędzie 
	{
		plik >> *poczatek >> *koniec >> *waga;
		(lista_sasiedztwa[*poczatek]).pushback(*koniec, *waga);
		(lista_sasiedztwa[*koniec]).pushback(*poczatek, *waga);
	}
	plik.close();

	delete n;
	delete start;
	delete poczatek;
	delete koniec;
	delete krawedzie;
	delete waga;
	return lista_sasiedztwa;
}


int czytaj_krawedzie(string nazwa)
{
	fstream plik;
	plik.open(nazwa);
	int n;
	plik >> n;
	plik.close();
	return n;
}
int czytaj_n(string nazwa)
{
	fstream plik;
	plik.open(nazwa);
	int n;
	plik >> n >> n;
	plik.close();
	return n;
}
int czytaj_start(string nazwa)
{
	fstream plik;
	plik.open(nazwa);
	int n;
	plik >> n >> n >> n;
	plik.close();
	return n;
}
