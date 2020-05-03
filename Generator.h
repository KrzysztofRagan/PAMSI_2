#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Lista.cpp"

/*
Moduł generujący plik tekstowy, w którym zapisany jest graf oraz sam graf

Do wyboru: gęstość grafu, liczba węzłów, reprezentacja grafu (jako lista sąsiedztwa lub macierz sąsiedztwa)

*/


int** generuj_graf_jako_macierz(int* , int* ,int );
List <int>* generuj_graf_jako_liste(int*, int*, int);
//int** czytaj_jako_macierz(int*, int*, int);
//List <int>* czytaj_jako_liste(int*, int*, int);