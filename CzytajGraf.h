#pragma once
#include "Generator.h"
#include "Lista.cpp"
#include <fstream>

List<int>* czytaj_jako_liste(std::string);
int **czytaj_macierz(std::string);
int czytaj_n(std::string);
int czytaj_krawedzie(std::string);
int czytaj_start(std::string);
