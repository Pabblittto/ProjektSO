#include "../Headers/functions.h"

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<pthread.h>
#include "../Headers/list.h"

  extern List* PierwszeMiasto;
  extern List* DrugieMiasto;
  extern int lewy;
  extern int prawy;

  extern pthread_mutex_t glownyMutex;
  extern pthread_mutex_t listowyMutex;

  extern int Debug;// zmienna okreslajaca czy program zostal odpalony z -debug

void Town(){
    int n = rand() %10 + 1;// zwraca iczbe od 1 do 10 
    sleep(n);// miasto wymusza chwilkę przerwy
}


int ISnumber(char*string){// returns 1 if string is long number
    int good=1;// its good, its long number
    int lenght= strlen(string);

    for(int i=0;i<lenght;i++){
        if(!isdigit(string[i]))
            good=0;
    }

    return good;
}

void *PracaDlawatku(void* numer1){// numer to swój wałany numer
    int numer=*((int*)numer1);
    SAMOCHOD obiekt;
    while (1==1)
    {
        pthread_mutex_lock(&listowyMutex);
        int LewaLista=lewy;
        int Prawalista=prawy;
        pthread_mutex_unlock(&listowyMutex);

        while(numer!=LewaLista && numer!=Prawalista )// prawa lista i lewa lista określa numer watku ktory jest na samym poczatku
        {                                               // jeżeli numer tego konkretnegon
            pthread_mutex_lock(&listowyMutex);
            LewaLista=lewy;
            Prawalista=prawy;
            pthread_mutex_unlock(&listowyMutex);
        }

        // trzeba usunac obiekt listy 

        
        pthread_mutex_lock(&glownyMutex);
        pthread_mutex_lock(&listowyMutex);

        if (numer==LewaLista)// samochod byl po lewej stronie/ pierwszym miescie
        {
            obiekt=PoPList(&PierwszeMiasto); 
            Pisz(numer,1);
            Add(&DrugieMiasto,obiekt.watek,obiekt.Numer);
            lewy=PierwszyNaLiscie(PierwszeMiasto);
        }
        else
        {
            obiekt=PoPList(&DrugieMiasto);
            Pisz(numer,0);
            Add(&PierwszeMiasto,obiekt.watek,obiekt.Numer);
            prawy=PierwszyNaLiscie(DrugieMiasto);
        }
        pthread_mutex_unlock(&listowyMutex);
        pthread_mutex_unlock(&glownyMutex);
        Town();// watek jest w miescie, nie ważne w którym 
    }

}

void Pisz(int numer,int kierunek){// jeżeli kierunek =1 to znaczy że samochód jedzie na prawo
    if(Debug==0){// program został uruchomiony bez motywu -debug
        if (kierunek==1)
        printf("A-%d %d>>> [>> %d >>] <<<%d %d-B \n",ElementsInList(PierwszeMiasto),PierwszyNaLiscie(PierwszeMiasto),numer,PierwszyNaLiscie(DrugieMiasto),ElementsInList(DrugieMiasto));
        else
        printf("A-%d %d>>> [<< %d <<] <<<%d %d-B \n",ElementsInList(PierwszeMiasto),PierwszyNaLiscie(PierwszeMiasto),numer,PierwszyNaLiscie(DrugieMiasto),ElementsInList(DrugieMiasto));
    }
    else
    {
        /* code */
    }
    
}