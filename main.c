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

   if (ArgNum>3)
   {
      printf("Niepoprawna liczba argumentów!\n");
      return 1;
   }
   else// jezeli liczba argumentów jest prawidłowa
   {
     if(ArgNum>=2 && ISnumber(Args[1])!=1){// błędny argument
      printf("Zły argument! Podaj liczbę, lub jeżeli wywołujesz opcję \"-debug\" dodaj ją na samym końcu!");
      return 1;
     }

     if(ArgNum==3){// jezeli jest trzeci argument sprawdz czy to -debug
         if (strcmp(Args[2],"-debug")==0)
         {
             Debug=1;
         }
         else
         {
            printf("Drugi argument jest nie jest poprawny \n");
            return 1;
         }
     }
   }
   pthread_t Watki[atoi(Args[1])];// tworzenie tablicy watkow

   //printf("rozdzielanie watkow!\n");

   for (int i = 0; i < atoi(Args[1]); i++)
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
   lewy=PierwszyNaLiscie(PierwszeMiasto);
   prawy=PierwszyNaLiscie(DrugieMiasto);

   int wynik;
   for (int i = 0; i < atoi(Args[1]); i++)
   {
      int * arg= calloc(1,sizeof(*arg));
      *arg=i;
      wynik=pthread_create(&Watki[i],NULL,&PracaDlawatku,arg);

      if (wynik!=0){
      printf("Nie udalo sie utworzyc watku numer %d\n",i);   
      return 1; 
      }  
      
   }
   
   for (int i = 0; i < atoi(Args[1]); i++)
   {
     pthread_join(Watki[i],NULL);
   }
   

   return 0;
}