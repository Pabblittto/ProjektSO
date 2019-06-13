#ifndef FUNCTIONS_H
#define FUNCTIONS_H "FUNCTIONS_H"

#ifndef pthread_t
#include<pthread.h>
#endif
#include"list.h"


void Town();
int ISnumber(char*string);// zwraca 1 jeżeli string jest długą liczbą 
void *PracaDlawatku(void* numer);// funkcja którą wykonuja kazdy wątek 
void Pisz();// funkcja odpowiedzielana za pisanie informacji na ekranie 

int CzyPierwszyNaliscie(int numer, int stronaRzeki);// funkcja zwracajaca 1 jezeli samochod o danym numerze znajduje sie na pierwszym miejscu w kolejce
#endif