#include "Dijkstra.h"

#pragma once

#define INF 20000000


void dijkstra_macierz(int **macierz_sasiedztwa, int *poprzedniki, int *dojscie,int *wierzcholki,int *start)
{
	for (int i = 0; i < *wierzcholki; ++i)
	{
		*(dojscie + i) = INF;
		*(poprzedniki + i) = -1;
	}

	*(dojscie + *start) = 0;//koszt dojscia do startu to 0;

	//szukam sasiadow wierzchołka startowego i tworzę z nich tablicę par (do kopca)
	int *licznik = new int;

	for (int i = 0; i < *wierzcholki; ++i)
	{
		if (macierz_sasiedztwa[*start][i] != 0)*licznik+=1; //zliczam ilu ma sąsiadów
	}

	std::pair<int, int> *graf = new std::pair<int,int>[*wierzcholki];   //tablica która stanie się potem kopcem-kolejką priorytetową, priorytet to odległość od źródła

	for (int i = 0; i < *wierzcholki; ++i)
	{
		if (macierz_sasiedztwa[*start][i] != 0) // do tablicy graf wpisujemy ineksy sasiadow oraz ich odleglosci od wierzcholka w którym jestesmy
		{
			(graf+i)->first = i; 
			(graf + i)->second = macierz_sasiedztwa[*start][i];
		}
		else //wszystkie oprócz sąsiadów mają odległość=INF
		{
			(graf + i)->first = i;
			(graf + i)->second = INF;
		}
	}

	build_minheap(graf, wierzcholki); //tablica par graf jest teraz kopcem minimalnym, w korzeniu jest sasiad najblizszy źródłu

	*licznik = *wierzcholki;

	while (*licznik>0)
	{

		int najmniejszy = ((extract_minimum(graf, licznik)).first);  //kopiec na nowo stworzony, ostatni element to para minusjedynek, w najmniejszy mamy indeks najbliższego wierzchołka
		//licznik zmniejsza się o 1 wewnątrz extract_minimum
		for (int i = 0; i < *wierzcholki; ++i)
		{
			if (macierz_sasiedztwa[najmniejszy][i] != 0) //jesli istnieje krawedz
			{
				if(*(dojscie+i)>*(dojscie+najmniejszy)+ macierz_sasiedztwa[najmniejszy][i]) //relaksacja krawedzi
				{
					*(dojscie + i) = *(dojscie + najmniejszy) + macierz_sasiedztwa[najmniejszy][i];
					*(poprzedniki + i) = najmniejszy;
					for (int j = 0; j < *wierzcholki; ++j)
					{//dla tego sąsiada, którego rozważaliśmy musimy zaktualizować 
						if ((graf + j)->first == i)
						{
							(graf + j)->second = *(dojscie + i);  //w następnym obrocie bedziemy sciagac minimum, musimy zaktualizować koszty przejscia w kopcu a nastepnie
							heapify(graf, *licznik, 0); // przywrocic jego warunki, bo inaczej w korzeniu beda nieaktualne dane
						}
					}
				}
			}
		}
	}

}



void dijkstra_dla_listy(List<int>* lista_sasiedztwa, int *poprzedniki, int *dojscie, int *wierzcholki, int *start)
{
	
	for (int i = 0; i < *wierzcholki; ++i)
	{
		*(dojscie + i) = INF;
		*(poprzedniki + i) = -1;
	}

	*(dojscie + *start) = 0;

	//dodaj wszystkie wierzchołki do kolejki
	std::pair<int, int> *graf = new std::pair<int, int>[*wierzcholki]; //ta tablica będzie kopcem - kolejką priorytetową
	for (int i = 0; i < *wierzcholki; ++i)
	{
		if (lista_sasiedztwa[*start].search(i) != 0) // do tablicy graf wpisujemy ineksy sasiadow oraz ich odleglosci od wierzcholka w którym jestesmy
		{
			(graf + i)->first = i;
			(graf + i)->second = lista_sasiedztwa[*start].daj_krawedz_danego_sasiada(i);
		}
		else //wszystkie oprócz sąsiadów mają odległość=INF
		{
			(graf + i)->first = i;
			(graf + i)->second = INF;
		}
	}
	build_minheap(graf, wierzcholki); //tablica par graf jest teraz kopcem minimalnym, w korzeniu jest sasiad najblizszy źródłu

	int *licznik = new int;
	*licznik = *wierzcholki;

	while (*licznik > 0)
	{
		int najmniejszy = extract_minimum(graf, licznik).first;  //sciaga parę z korzenia kopca-te, gdzie second jest najmniejsze, a first to numer wierzcholka
		for (int i = 0; i < *wierzcholki; ++i)
		{
			if (lista_sasiedztwa[najmniejszy].search(i))
			{
				if (*(dojscie + i) > *(dojscie + najmniejszy) + lista_sasiedztwa[najmniejszy].daj_krawedz_danego_sasiada(i))
				{
					*(dojscie + i) = *(dojscie + najmniejszy) + lista_sasiedztwa[najmniejszy].daj_krawedz_danego_sasiada(i);
					*(poprzedniki + i) = najmniejszy;
					for (int j = 0; j < *wierzcholki; ++j)
					{//dla tego sąsiada, którego rozważaliśmy musimy zaktualizować 
						if ((graf + j)->first == i)
						{
							(graf + j)->second = *(dojscie + i);  //w następnym obrocie bedziemy sciagac minimum, musimy zaktualizować koszty przejscia w kopcu a nastepnie
							heapify(graf, *licznik, 0); // przywrocic jego warunki, bo inaczej w korzeniu beda nieaktualne dane
						}
					}
				}
			}
		}
	}
}


//POPRZEDNIA, NIEDZIALAJACA WERSJA FUNKCJI Z ALGORYTMEM DIJKSTRY DLA REPREZENTACJI MACIERZOWEJ
/*
void dijkstra_lista(List<int>* lista_sasiedztwa, int *poprzedniki, int *dojscie, int *wierzcholki, int *start)
{
	for (int i = 0; i < *wierzcholki; ++i)
	{
		*(dojscie + i) = INF;
		*(poprzedniki + i) = -1;
	}

	*(dojscie + *start) = 0;//koszt dojscia do startu to 0;

	//szukam sasiadow wierzchołka startowego i tworzę z nich tablicę par (do kopca)
	int *licznik = new int;

	std::pair<int, int> *graf = new std::pair<int, int>[*wierzcholki];   //tablica która stanie się potem kopcem-kolejką priorytetową, priorytet to odległość od źródła

	for (int i = 0; i < *wierzcholki; ++i)
	{				
			if (lista_sasiedztwa[*start].search(i)) // do tablicy graf wpisujemy ineksy sasiadow oraz ich odleglosci od wierzcholka w którym jestesmy
			{
				(graf + i)->first = i;
				(graf + i)->second = lista_sasiedztwa[*start].daj_krawedz_danego_sasiada(i);
			}
			else //wszystkie oprócz sąsiadów mają odległość=INF
			{
				(graf + i)->first = i;
				(graf + i)->second = INF;
			}		
	}

	(graf + *start)->second = 0;
	build_minheap(graf, wierzcholki); //tablica par graf jest teraz kopcem minimalnym, w korzeniu jest sasiad najblizszy źródłu
	
	for (int i = 0; i < *wierzcholki; ++i)
	{
		std::cout << std::endl << "KOPIEC" << i << ":\n" << (graf + i)->first << " " << (graf + i)->second;
	}
	std::cout << std::endl;

	*licznik = *wierzcholki;

	while (*licznik > 0)
	{

		int najmniejszy = ((extract_minimum(graf, licznik)).first);  //kopiec na nowo stworzony, ostatni element to para minusjedynek, w najmniejszy mamy indeks najbliższego wierzchołka
		//licznik zmniejsza się o 1 wewnątrz extract_minimum
		for (int i = 0; i < *wierzcholki; ++i)
		{
			std::cout << std::endl << "KOPIEC" << i << ":\n" << (graf + i)->first << " " << (graf + i)->second;
			std::cout << std::endl;
		}
		for (int i = 0; i < (lista_sasiedztwa[najmniejszy]).daj_size(); ++i) //tylko tyle obrotów ile sąsiadów najmniejszego
		{
			if (*(dojscie + i) > *(dojscie + najmniejszy) + (lista_sasiedztwa[najmniejszy]).daj_krawedz_danego_sasiada(i)) //relaksacja krawedzi
			{
				*(dojscie + i) = *(dojscie + najmniejszy) + (lista_sasiedztwa[najmniejszy]).daj_krawedz_danego_sasiada(i);
				*(poprzedniki + i) = najmniejszy;
				for (int j = 0; j < *wierzcholki; ++j)
				{
					if ((graf + j)->first == i)
					{
						(graf + j)->second = *(dojscie + i);  //w następnym obrocie bedziemy sciagac minimum, musimy zaktualizować koszty przejscia w kopcu a nastepnie
						heapify(graf, *licznik, 0);
					}					// przywrocic jego warunki, bo inaczej w korzeniu beda nieaktualne dane
					for (int i = 0; i < *wierzcholki; ++i)
					{
						std::cout << std::endl << "KOPIEC"<<i<<":\n" << (graf + i)->first << " " << (graf + i)->second;
						std::cout << std::endl;
					}
				}
			}
		}

		
	}
}
*/


//funkcja sprawdzajaca czy w danej liscie istnieje element o zadanej wartosci (czy istnieje sasiad)
bool czy_sasiad(List<int> lista, int* potencjalny_sasiad)
{
	int size = lista.daj_size();
	std::cout << "\nczy sasiad: "<<*potencjalny_sasiad;
	for (int i = 0; i < size; ++i)
	{
		std::cout <<std::endl<< i << " -ty elem listy:" << lista[i] << "\n";
			if (lista[i] == *potencjalny_sasiad)
			{
				std::cout << "JEST SASIAD\n";
				return 1;
			}
	}
	std::cout << "nie jest sasiad\n";
	return 0;
}