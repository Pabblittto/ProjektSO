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
    int n = rand()%10 + 1;// zwraca iczbe od 1 do 10 
    sleep(n);// miasto wymusza chwilkę przerwy
}


int ISnumber(char*string){// zwraca 1 jeżeli to jedna liczba
    int good=1;// its good, its long number
    int lenght= strlen(string);

    for(int i=0;i<lenght;i++){
        if(!isdigit(string[i]))
            good=0;
    }

    return good;
}

void *PracaDlawatku(void* numer1){// numer to swój wałany numer
    int numer=*((int*)numer1);// rzutowanie numerku watku
    SAMOCHOD obiekt;
    int kierunek=0;// okresla na którą stronę mostu samochód jedzie
    int LewaLista,PrawaLista;// zmienne określające jaki samochód znajduje sie na samym początku kolejki
    while (1==1)
    {
        pthread_mutex_lock(&listowyMutex);
         LewaLista=lewy;
         PrawaLista=prawy;
        pthread_mutex_unlock(&listowyMutex);

        while(numer!=LewaLista && numer!=PrawaLista )// prawa lista i lewa lista określa numer watku ktory jest na samym poczatku
        {                    
           // printf("        Watek numer %d sprawdza numerki kture wynosza %d %d \n",numer,LewaLista,Prawalista);                           // jeżeli numer tego konkretnegon
            pthread_mutex_lock(&listowyMutex);
            lewy=PierwszyNaLiscie(PierwszeMiasto);
            prawy=PierwszyNaLiscie(DrugieMiasto);

            LewaLista=lewy;
            PrawaLista=prawy;
            pthread_mutex_unlock(&listowyMutex);
        }
        
        pthread_mutex_lock(&glownyMutex);// poniżej jest fragment kodu w którym można by umieścić symboliczny most-działania na wspólnej zmiennej
        pthread_mutex_lock(&listowyMutex);

        if (numer==LewaLista)// samochod byl po lewej stronie/ pierwszym miescie
        {
            obiekt=PoPList(&PierwszeMiasto); 
            kierunek=1;// samochód jedzie na prawą stronę mostu
            Pisz(numer,1);
        }
        else
        {
            obiekt=PoPList(&DrugieMiasto);
            kierunek=0;// samochód jedzie na lewą stronę mostu
            Pisz(numer,0);
        }

        if(kierunek==1)
            Add(&DrugieMiasto,obiekt.watek,obiekt.Numer);
        else
            Add(&PierwszeMiasto,obiekt.watek,obiekt.Numer);// jak robimy na zmiennych warunkowaych to można jakoś zostawić 

        pthread_mutex_unlock(&listowyMutex);


        lewy=PierwszyNaLiscie(PierwszeMiasto);
        prawy=PierwszyNaLiscie(DrugieMiasto);

        pthread_mutex_unlock(&listowyMutex);
        pthread_mutex_unlock(&glownyMutex);
        Town();// watek jest w miescie

        pthread_mutex_lock(&listowyMutex);// samochód ustawia się w kolejkę



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
       
    }
    
}