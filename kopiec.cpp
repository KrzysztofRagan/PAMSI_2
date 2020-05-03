#include <utility> 
#include "kopiec.h"
using namespace std;

void heapify(pair<int,int> *tab, int heap_size, int root) //potrzebujemy tablicy par, na pierwszym miejscu indeks na drugim waga krawedzi. Kopiec sortować bedzie po wagach
{
	int smallest = root; // Zakładamy że korzeń najmniejszy
	int l = 2 * root + 1; // left = 2*root + 1 
	int r = 2 * root + 2; // right = 2*root + 2 

	// Jeśli lewe dziecko wieksze 
	if (l < heap_size && tab[l].second < tab[smallest].second)
		smallest = l;

	// Jeśli prawe dziecko wieksze 
	if (r < heap_size && tab[r].second < tab[smallest].second)
		smallest = r;

	// Jeśli najwieksze to nie korzeń
	if (smallest != root)
	{
		SwapArr(tab, root, smallest); //Wartość najmniejsza idzie do korzenia

		// Rekursywnie należy sprawdzić, czy "stary" korzeń spełnia warunki kopca dla swoich "nowych" dzieci
		heapify(tab, heap_size, smallest);
	}

}
void build_minheap(pair<int,int> *Arr,int *N)
{
	for (int i = (*N / 2); i >= 1; i--)heapify(Arr, *N, i);
		
}

void SwapArr(pair<int,int> *tab, int a, int b) //swapuje komórki o indeksach a i b
{
	pair<int,int> *tmp = new pair<int,int>;
	*tmp = *(tab + a);
	*(tab + a) = *(tab + b);
	*(tab + b) = *tmp;
	delete tmp;
}
