#include "kolejka.h"


std::pair<int, int> minimum(std::pair<int, int> *Arr)
{
	return *(Arr+0);  //as the minimum element is the root element in the max heap. //zwraca najlepszy wierzchołek
}

std::pair<int, int> extract_minimum(std::pair<int, int> *Arr, int *length) //kolejka bedzie kopcem, używam heapify i build heap aby stworzyć kolejke. Do wywolywania build heap potrzebna tablica sasiadow
{
	if (*length == 0)
	{
		std::cout << "Can’t remove element as queue is empty\n";
		return std::make_pair(-1,-1);
	}
	std::pair<int, int> min = *(Arr+0);
	*(Arr+0) = *(Arr+*length-1);
	*(Arr+*length-1) = std::make_pair(-1, -1);  //para zlozona z dwoch -1 bo to bedzie koniec tablicy teraz (dość prowiorycznie...)
	*length = *length - 1;
	heapify(Arr,*length,0);	
	return min;
}



