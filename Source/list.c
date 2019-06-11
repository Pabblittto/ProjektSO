#include"../Headers/list.h"


void Add(List** poczatek, int numer){
    
    List* PierwszyObiekt=*poczatek;


    if ((*poczatek)==NULL)// nie ma obietow na liscie 
    {
        (*poczatek)=calloc(1,sizeof(List));
       // (*poczatek)->Obiekt.watek=watek;
        (*poczatek)->next=NULL;
        (*poczatek)->Obiekt.Numer=numer;
    }
    else // sa obiekty na liscie 
    {
        while ((*poczatek)->next!=NULL) // dobra tu wywala bledy
        {
            (*poczatek)=(*poczatek)->next;
        }
        List* tmp= calloc(1,sizeof(List));

        tmp->next=NULL;
       // tmp->Obiekt.watek=watek;
        tmp->Obiekt.Numer=numer;
        (*poczatek)->next=tmp;
    }

    if(PierwszyObiekt!=NULL)
        *poczatek=PierwszyObiekt;
}


// void MoveToLast(List** poczatek,pthread_t* watek){// wycian dany watek i przesuwa go na sam koniec kolejki/listy

//     List* PierwszyObiekt=*poczatek;
//     List* NowyPoczatek=*poczatek;// jezeli watek jest gdzieś w śrdoku listy to poczatek zostanie tam gdzie był


//     if ((*poczatek)->Obiekt.watek==watek)
//     {// jezeli poszukiwany watek jest na samym poczatku to go przesuwa na koniec i już
//         NowyPoczatek=(*poczatek)->next;
//         PierwszyObiekt->next=NULL;
        
//         while((*poczatek)->next!=NULL)
//         {
//            *poczatek=(*poczatek)->next;
//         }

//         (*poczatek)->next=PierwszyObiekt;
        
//     }
//     else
//     {// jezeli poszukiwany watek jest gdzies w srodku

//         while((*poczatek)->next->Obiekt.watek!=watek)// jezeli kolejnym elementem nie jest element z poszukiwanym watkiem to szukaj dalej
//         {
//             (*poczatek) = (*poczatek)->next;
//         }

//         List* SzukanyElement=(*poczatek)->next;// ten element trzeba przeniesc na sam koniec
//         SzukanyElement->next=NULL;
        
//         (*poczatek)->next=(*poczatek)->next->next;

//         while ((*poczatek)->next!=NULL)
//         {
//            (*poczatek)=(*poczatek)->next;
//         }// tu jest znajdowany koniec listy 

//         (*poczatek)->next=SzukanyElement;

//     }

//     (*poczatek)=NowyPoczatek;
// }

// int NumberInList(List* pocztek,pthread_t* watek){
//     int Numer=1;
//     while (pocztek->Obiekt.watek!=watek)
//     {
//         pocztek=pocztek->next;
//         Numer++;
//     }
    
//     return Numer;
// }

int ElementsInList(List* poczatek){ // zwraca ilość elementów w liście
    int Numer=0;
    while (poczatek!=NULL)
    {
        poczatek=poczatek->next;
        Numer++;
    }
    return Numer;
}

SAMOCHOD PoPList(List** poczatek){ // wywala pierwszy samochów z listy
    List* NowyPoczatek=(*poczatek)->next;
    SAMOCHOD Zwracany=((*poczatek)->Obiekt);
    free(*poczatek);
    (*poczatek)=NowyPoczatek;
    return Zwracany;
}

int PierwszyNaLiscie(List* poczatek){// numer piwrszego samochodu na liscie

    if(poczatek!=NULL)
        return poczatek->Obiekt.Numer;
    else
        return -1;
        
}


void WywalZKolejki(List** poczatek,int numerSamochodu){

    List* PierwszyObiekt=*poczatek;
    List* NowyPoczatek=*poczatek;// jezeli watek jest gdzieś w śrdoku listy to poczatek zostanie tam gdzie był

    if ((*poczatek)->Obiekt.Numer==numerSamochodu)
        {// jezeli poszukiwany numer jest na samym poczatku
            NowyPoczatek=(*poczatek)->next;
            
        }
    else
        {// jezeli poszukiwany watek jest gdzies w srodku

            while((*poczatek)->next->Obiekt.Numer!=numerSamochodu)// jezeli kolejnym elementem nie jest element z poszukiwanym watkiem to szukaj dalej
            {
                (*poczatek) = (*poczatek)->next;
            }            
            
            (*poczatek)->next=(*poczatek)->next->next;// tu jest pomijany element pomiędzy 


        }

    (*poczatek)=NowyPoczatek;



}

int CzyJestWLiscie(List* poczatek,int numerSamochodu){// funkcja okreslająca czy dany samochod jest w liscie, 0- fałsz , 1 prawda
int wynik=0;// na poczatku wynik jest z góry fałszem

    if (poczatek==NULL)// lista pusta to raczej go nie ma w tej liscie
        return wynik;
    
    


    while (poczatek->Obiekt.Numer!=numerSamochodu)// jeżeli dany obiekt nie jest poszukiwanym obiektem to lec dalej 
    {
        poczatek=poczatek->next;
    }
    // tu albo znalazło taki obiekt albo przeszło po wszystkich elementah na liście 
    // więc....:

    if(poczatek->Obiekt.Numer==numerSamochodu)
    wynik=1;

    return wynik;
}