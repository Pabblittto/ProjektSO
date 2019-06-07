#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "Headers/list.h"
#include "Headers/functions.h"

   List* ListaGlodzenia=NULL;// lista okreslajaca kto powinien przejechac przez most wczesniej-- to sie moze przydac wprzy zmiennych warunkowcy 
   List* PierwszeMiasto=NULL;
   List* DrugieMiasto=NULL;
   int lewy;
   int prawy;

   pthread_mutex_t glownyMutex = PTHREAD_MUTEX_INITIALIZER;
   pthread_mutex_t listowyMutex = PTHREAD_MUTEX_INITIALIZER;
   int Debug=0;// zmienna okreslajaca czy program zostal uruchomiony z -debug

int main(int ArgNum,char* Args[]) {
   srand(time(NULL));

   if (ArgNum!=2)
   {
      printf("Nieprawidłowa liczba argumnetów!\n");
      return 1;
   }
   else// jezeli został podany tylko jeden argument
   {
     if(ISnumber(Args[1])!=1){// błędnu argument
      printf("Zły argument! Podaj liczbę");
      return 1;
     }
   }
   pthread_t Watki[atoi(Args[1])];// tworzenie tablicy watkow

   //printf("rozdzielanie watkow!\n");

   for (size_t i = 0; i < atoi(Args[1]); i++)
   {
      
      int losowa=rand()%2;

      if (losowa==0)// losowe rozmieszczenie samochodow/watkow w miastach
      {
         Add(&PierwszeMiasto,&Watki[i],i);
         Add(&ListaGlodzenia,&Watki[i],i);
      }
      else
      {
         Add(&DrugieMiasto,&Watki[i],i);
         Add(&ListaGlodzenia,&Watki[i],i);
      }
      
   }
   // watki rozmieszczone teraz czas na nieskonczonego while-a
   lewy=PierwszyNaLiscie(PierwszeMiasto);
   prawy=PierwszyNaLiscie(DrugieMiasto);

   int wynik;
   for (int i = 0; i < atoi(Args[1]); i++)
   {
      int * arg= calloc(1,sizeof(*arg));
      *arg=i;
      wynik=pthread_create(&Watki[i],NULL,&PracaDlawatku,arg);

      if (wynik!=0){
      printf("nie udalo sie utworzyc watku %d\n",i);   
      return 1; 
      }  
      
   }
   
   for (int i = 0; i < atoi(Args[1]); i++)
   {
     pthread_join(Watki[i],NULL);
   }
   

   return 0;
}