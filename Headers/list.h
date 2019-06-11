#ifndef LIST_H
#define LIST_H "LIST_H"
#include<pthread.h>
#include <stdlib.h>

#ifndef SAMOCHOD
typedef struct Samochod{
   int Numer;
} SAMOCHOD;
#endif

#ifndef List
typedef struct list // lista watkow ktore maja pierwszenstwo- ma to zapobiegac zaglodzeniu
{
   struct Samochod Obiekt;
   struct list* next; // wskaźnik na następny obiekt w liscie 
} List;
#endif

#ifndef DANE_DO_WATKU
   typedef struct Dane{
      int numer;
      pthread_mutex_t* WskaznikNaMutex;
   } DANE_DO_WATKU;
#endif



void Add(List** poczatek,int numer);// dodaje watek do listy na sam koniec
void MoveToLast(List** poczatek,pthread_t* watek); // przesuwa watek z listy na koniec kolejki - tej samej listy
int NumberInList(List* pocztek,pthread_t* watek);// zwraca numer miejsca na którym znajduje się dany wątek 
int ElementsInList(List* poczatek);// zwraca liczbe elementow w liscie
SAMOCHOD PoPList(List** poczatek);// wywala pierwszy element z listy i cały obiekt na niego 

void WywalZKolejki(List** poczatek,int numerSamochodu);// wywala z listy dany numer samochodu
int CzyJestWLiscie(List* poczatek,int numerSamochodu);// funkcja okreslająca czy dany samochod jest w liscie, 0- fałsz , 1 prawda

int PierwszyNaLiscie(List* poczatek);// zwraca numer watku ktory jest pierwszy na liscie, jezeli lista jest pusta- zwraca -1

#endif