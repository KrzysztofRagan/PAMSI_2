#pragma once
#include "kolejka.h"
#include "kopiec.h"
#include"Lista.cpp"

void dijkstra_macierz(int**,int*,int*,int*,int*);
void dijkstra_lista(List<int>*, int*, int*, int*, int*);
bool czy_sasiad(List<int>, int*);
void dijkstra_dla_listy(List<int>*, int *, int *, int *, int *);
