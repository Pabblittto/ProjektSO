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

    extern List* DrugaKolejka;
    extern List* PierwszaKolejka;

    extern int lewy;
    extern int prawy;

    extern pthread_mutex_t glownyMutex;
    extern pthread_mutex_t listowyMutex;
    extern pthread_mutex_t pisanieMutex;
    extern pthread_mutex_t miastowyMutex;
    extern pthread_mutex_t zmienneMutex;

    extern int NumerNaMoscie;
    extern int KierunakJazdy;

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
    int StronaRzeki=1;// zmienna określająca po której stronie rzeki znajduje sie samochód, na dole jest funkcja określająca, po kótrj sie znajduje 
                // jezeli strona rzeki jest =0 to jest po lewej stronie, pierwszej stronie
    
     pthread_mutex_lock(&pisanieMutex);
    if(CzyJestWLiscie(PierwszaKolejka,numer)==1)// jak samochod jest jednak po lewej straonie to zmien
        StronaRzeki=0;// jak 0 to znaczy ze po lewej stronie , jak 1 to znaczy że po prawej stronie 
    pthread_mutex_unlock(&pisanieMutex);

    while (1==1)
    {
        
        pthread_mutex_lock(&glownyMutex);// poniżej jest fragment kodu w którym można by umieścić symboliczny most-działania na wspólnej zmiennej
        
        pthread_mutex_lock(&listowyMutex);
        pthread_mutex_lock(&pisanieMutex);
            if (StronaRzeki==0)// samochód jest po lewej stronie, wywal go z kolejki pierwszej
                WywalZKolejki(&PierwszaKolejka,numer);
            else
                WywalZKolejki(&DrugaKolejka,numer);
        pthread_mutex_unlock(&pisanieMutex);
        pthread_mutex_unlock(&listowyMutex);
        

        // w tym momencie samochód jest na moście
        pthread_mutex_lock(&pisanieMutex);
        pthread_mutex_lock(&zmienneMutex);
            NumerNaMoscie=numer;
            KierunakJazdy=StronaRzeki;// kierunak jazdy jest równy stronie rzeki PONIEWAŻ stronaRzeki=0 to jest po lewej stronie i jedzie w prawo
        pthread_mutex_unlock(&zmienneMutex);
        pthread_mutex_unlock(&pisanieMutex);


        pthread_mutex_lock(&pisanieMutex);// mutex na pisanie żeby nie było błędów bufora wyjścia
            Pisz();
        pthread_mutex_unlock(&pisanieMutex);

        sleep(1);// pauza na 1 sekunde żeby jechał przez most

        pthread_mutex_lock(&pisanieMutex);
        pthread_mutex_lock(&zmienneMutex);
            NumerNaMoscie=-1;// nie ma nikogo na moscie
        pthread_mutex_unlock(&zmienneMutex);
        pthread_mutex_unlock(&pisanieMutex);

        pthread_mutex_unlock(&glownyMutex);// samochod opuszcza most


        pthread_mutex_lock(&pisanieMutex);
        pthread_mutex_lock(&miastowyMutex);
        if (StronaRzeki==0)// jeżeli samochód był po lewej stronie rzeki to teraz jest po prawej stronie rzeki
        {
            StronaRzeki=1;
            Add(&DrugieMiasto,numer);// samochód tuz po tym jak opuści most jedzie do miasta
        }
        else
        {
            StronaRzeki=0;// samochód był po prawej stronie i wjachał na lewą stronę rzeki
            Add(&PierwszeMiasto,numer);
        }
        pthread_mutex_unlock(&miastowyMutex);
        pthread_mutex_unlock(&pisanieMutex);


        pthread_mutex_lock(&pisanieMutex);// mutex na pisanie żeby nie było błędów bufora wyjścia
            Pisz();
        pthread_mutex_unlock(&pisanieMutex);

        Town();// watek jest w miescie
        // samochód wyjechał z miasta i jedzie do kolejki przed most

        pthread_mutex_lock(&pisanieMutex);
        pthread_mutex_lock(&listowyMutex);// samochód wyjezdza z miasta i jedzie do kolejki
        if(StronaRzeki==0)// jak samochód jest po lewej stronie
        {
            pthread_mutex_lock(&miastowyMutex);
                WywalZKolejki(&PierwszeMiasto,numer);
            pthread_mutex_unlock(&miastowyMutex);

            Add(&PierwszaKolejka,numer);// podjachał do kolejki
        }
        else
        {
            pthread_mutex_lock(&miastowyMutex);
                WywalZKolejki(&DrugieMiasto, numer);
            pthread_mutex_unlock(&miastowyMutex);

            Add(&DrugaKolejka, numer);
        }
        pthread_mutex_unlock(&listowyMutex);
        pthread_mutex_unlock(&pisanieMutex);


        pthread_mutex_lock(&pisanieMutex);// mutex na pisanie żeby nie było błędów bufora wyjścia
            Pisz();
        pthread_mutex_unlock(&pisanieMutex);

    }

}

void Pisz(){// jeżeli kierunek =1 to znaczy że samochód jedzie na prawo
    

    if(Debug==0){// program został uruchomiony bez motywu -debug

   // pthread_mutex_lock(&miastowyMutex);
   // pthread_mutex_lock(&listowyMutex);
   // pthread_mutex_lock(&zmienneMutex);
    //pthread_mutex_lock(&pisanieMutex);
        if (KierunakJazdy==0)// jak samochów na moscie jedzie w prawo
        printf("A-%d %d>>> [>> %d >>] <<<%d %d-B \n",ElementsInList(PierwszeMiasto),ElementsInList(PierwszaKolejka),NumerNaMoscie,ElementsInList(DrugaKolejka),ElementsInList(DrugieMiasto));
        else
        printf("A-%d %d>>> [<< %d <<] <<<%d %d-B \n",ElementsInList(PierwszeMiasto),ElementsInList(PierwszaKolejka),NumerNaMoscie,ElementsInList(DrugaKolejka),ElementsInList(DrugieMiasto));
    //pthread_mutex_unlock(&miastowyMutex);
   // pthread_mutex_unlock(&listowyMutex);
   // pthread_mutex_unlock(&pisanieMutex);
    //pthread_mutex_unlock(&zmienneMutex);
    }
    else
    {// jest włączony motyw -debug

    //pthread_mutex_lock(&miastowyMutex);
    char* WskaznikDrugieMiasto=ListaSamochodow(DrugieMiasto);
    char* WskaznikPierwszeMiasto=ListaSamochodow(PierwszeMiasto);
    //pthread_mutex_unlock(&miastowyMutex);

    //pthread_mutex_lock(&listowyMutex);
    char* WskaznikPierwszaKolejka=ListaSamochodow(PierwszaKolejka);
    char* WskaznikDrugaKolejka=ListaSamochodow(DrugaKolejka);
    //pthread_mutex_unlock(&listowyMutex);

    //pthread_mutex_lock(&zmienneMutex);
    //pthread_mutex_lock(&pisanieMutex);
       if (KierunakJazdy==0)// jak samochów na moscie jedzie w prawo
        printf("A-[%s] [%s]>>> [>> %d >>] <<<[%s] [%s]-B \n",WskaznikPierwszeMiasto,WskaznikPierwszaKolejka,NumerNaMoscie,WskaznikDrugaKolejka,WskaznikDrugieMiasto);
        else
        printf("A-[%s] [%s]>>> [<< %d <<] <<<[%s] [%s]-B \n",WskaznikPierwszeMiasto,WskaznikPierwszaKolejka,NumerNaMoscie,WskaznikDrugaKolejka,WskaznikDrugieMiasto);
    //pthread_mutex_unlock(&pisanieMutex);
    //pthread_mutex_unlock(&zmienneMutex);


    free(WskaznikPierwszeMiasto);
    free(WskaznikPierwszaKolejka);
    free(WskaznikDrugieMiasto);
    free(WskaznikDrugaKolejka);

    }
    
}