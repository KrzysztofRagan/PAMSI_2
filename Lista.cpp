#pragma once
#include <iostream>

template <typename T>
struct Element {
	Element *next, *prev;
	T value;
	T krawedz;
	Element() {

	}

	Element(T value) {
		next = prev = nullptr;
		this->value = value;
	}
	Element(Element *prev, Element *next, T value,T krawedz) {
		this->prev = prev;
		this->next = next;
		this->value = value;
		this->krawedz = krawedz;
	}
};

template <typename T>
class List 
{
private:
	Element<T> *front, *back;
	int size;
	Element<T> *beginptr;
	Element<T> *endptr;
	int itcount = 0;
	int itcountEnd = 0;

public:
	List() {
		front = back = nullptr;
		size = 0;
	}


	int daj_size()
	{
		return size;
	}


	void pushfront(const T& newElement, const T& krawedz) {
		if (size == 0) {
			Element <T> *elem = new Element<T>(nullptr, nullptr, newElement,krawedz);
			front = elem;
			back = elem;
			size++;
		}

		else if (size > 0) {
			Element <T> *elem = new Element<T>(nullptr, front, newElement,krawedz);
			front->prev = elem;
			front = elem;
			size++;
		}
	};

	void pushback(const T& newElement, const T& krawedz) {
		if (size == 0) {
			Element <T> *elem = new Element<T>(nullptr, nullptr, newElement,krawedz);
			front = elem;
			back = elem;
			size++;
		}

		else if (size > 0) {
			Element <T> *elem = new Element<T>(back, nullptr, newElement,krawedz);
			back->next = elem;
			back = elem;
			size++;
		}

	};

	void insert(const T& newElement, int index) {
		if (size == (index - 1)) {
			pushback(newElement);
		}
		else if (size < (index - 1)) {
			std::cout << "Nie mo¿na wykonaæ." << std::endl;
		}
		else if (size >= index) {
			Element<T> *temp1 = front;
			Element<T> *temp2 = 0;

			for (int i = 0; i < (index - 1); i++) {
				//temp2 = temp1->next;
				//temp1 = temp2;
				temp2 = temp1;
				temp1 = temp1->next; //ustawic raczki elementow pomiedzy ktore insertujemy
			}
			Element <T> *elem = new Element<T>(nullptr, nullptr, newElement,0);
			temp2->next = elem;
			temp1->prev = elem;
			elem->next = temp1;
			elem->prev = temp2;
			size++; //Do sprawdzenia
		}
	}

	void remove(const T& element) {
		Element<T> remcount = element;
		for (int i = 0; i < element; i++) {

			if (front != nullptr) {
				Element<T> *newFront = front->next;
				//T remVal = front->value;
				delete front;
				front = newFront;
				newFront->prev = nullptr;
				size--;
				//std::cout << "Usunieto element" << std::endl;
			}
			//else
				//std::cout << "Nie usunieto elementu" << std::endl;
		}


	};


	bool search(int val)
	{
		Element<T> *temp1 = front;
		Element<T> *temp2 = 0;
		for (int i = 0; i < size; ++i)
		{
			if (val == temp1->value)return true;
			else
			{
				temp2 = temp1;
				temp1 = temp1->next;
			}
		}
		return false;
	}

	int daj_krawedz(int index)
	{
		if (size == (index + 1)) {
			std::cout << back->krawedz << std::endl;
			return back->krawedz;
		}
		else if (size < (index + 1)) {
			std::cout << "Nie ma takiego elementu." << std::endl;
		}
		else if (size > index) {
			Element<T> *temp1 = front;
			Element<T> *temp2 = 0;

			for (int i = 0; i < (index ); i++) {
				//temp2 = temp1->next;
				//temp1 = temp2;
				temp2 = temp1;
				temp1 = temp1->next;
			}
			//std::cout << temp1->krawedz << std::endl;
			return temp1->krawedz;
		}
		return index;
	}

	int daj_krawedz_danego_sasiada(int index)
	{
		Element<T> *temp1 = front;
		Element<T> *temp2 = 0;
		for (int i = 0; i < size; ++i)
		{
			if (index == temp1->value)return temp1->krawedz;
			else
			{
				temp2 = temp1;
				temp1 = temp1->next;
			}
		}
		std::cout << "NIE MA TAKIEGO SASIADA\n";
		return 0;
	}

	T& operator[] (int index) {
		//std::cout << "Wartosc elementu " << index << ":" << std::endl;
		if (size == (index + 1)) {
			std::cout << back->value << std::endl;
			return back->value;
		}
		else if (size < (index + 1)) {
			std::cout << "Nie ma takiego elementu." << std::endl;
		}
		else if (size > index) {
			Element<T> *temp1 = front;
			Element<T> *temp2 = 0;

			for (int i = 0; i < (index); i++) {
				//temp2 = temp1->next;
				//temp1 = temp2;
				temp2 = temp1;
				temp1 = temp1->next;
			}
			//std::cout << temp1->value << std::endl;
			return temp1->value;
		}
		return index;
	}

	void showcase() {
		Element<T> *temp = front;
		for (int i = 0; i < size; i++) {
			std::cout << "value: "<<temp->value << std::endl;
			std::cout << "krawedz: " << temp->krawedz << std::endl;
			temp = temp->next;
		}
	}


	struct Iterator {
		int itcount = 0;
		int itcountEnd = 0;

		Iterator begin() {
			if (itcount == 0) {
				beginptr = front;
				itcount++;
				return beginptr;
				beginptr = front->next;
			}
			else {
				return beginptr;
				if (beginptr->next != nullptr) {
					beginptr->next;
					itcount++;
				}
			}
		};

		Iterator end() {
			if (itcountEnd == 0) {
				beginptr = back;
				itcountEnd++;
				return beginptr;
				beginptr = back->prev;
			}
			else {
				return beginptr;
				if (beginptr->prev != nullptr) {
					beginptr->prev;
					itcountEnd++;
				}
			};
		};
		//constiterator cbegin() const {};
		//constiterator cend() const {};
	};
};