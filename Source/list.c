#include"../Headers/list.h"


void Add(List** poczatek,pthread_t* watek, int numer){
    
    List* PierwszyObiekt=*poczatek;


    if ((*poczatek)==NULL)// nie ma obietow na liscie 
    {
        (*poczatek)=calloc(1,sizeof(List));
        (*poczatek)->Obiekt.watek=watek;
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
        tmp->Obiekt.watek=watek;
        tmp->Obiekt.Numer=numer;
        (*poczatek)->next=tmp;
    }

    if(PierwszyObiekt!=NULL)
        *poczatek=PierwszyObiekt;
}


void MoveToLast(List** poczatek,pthread_t* watek){// wycian dany watek i przesuwa go na sam koniec kolejki/listy

    List* PierwszyObiekt=*poczatek;
    List* NowyPoczatek=*poczatek;// jezeli watek jest gdzieś w śrdoku listy to poczatek zostanie tam gdzie był


    if ((*poczatek)->Obiekt.watek==watek)
    {// jezeli poszukiwany watek jest na samym poczatku to go przesuwa na koniec i już
        NowyPoczatek=(*poczatek)->next;
        PierwszyObiekt->next=NULL;
        
        while((*poczatek)->next!=NULL)
        {
           *poczatek=(*poczatek)->next;
        }

        (*poczatek)->next=PierwszyObiekt;
        
    }
    else
    {// jezeli poszukiwany watek jest gdzies w srodku

        while((*poczatek)->next->Obiekt.watek!=watek)// jezeli kolejnym elementem nie jest element z poszukiwanym watkiem to szukaj dalej
        {
            (*poczatek) = (*poczatek)->next;
        }

        List* SzukanyElement=(*poczatek)->next;// ten element trzeba przeniesc na sam koniec
        SzukanyElement->next=NULL;
        
        (*poczatek)->next=(*poczatek)->next->next;

        while ((*poczatek)->next!=NULL)
        {
           (*poczatek)=(*poczatek)->next;
        }// tu jest znajdowany koniec listy 

        (*poczatek)->next=SzukanyElement;

    }

    (*poczatek)=NowyPoczatek;
}

int NumberInList(List* pocztek,pthread_t* watek){
    int Numer=1;
    while (pocztek->Obiekt.watek!=watek)
    {
        pocztek=pocztek->next;
        Numer++;
    }
    
    return Numer;
}

int ElementsInList(List* poczatek){
    int Numer=0;
    while (poczatek!=NULL)
    {
        poczatek=poczatek->next;
        Numer++;
    }
    return Numer;
}

SAMOCHOD PoPList(List** poczatek){
    List* NowyPoczatek=(*poczatek)->next;
    SAMOCHOD Zwracany=((*poczatek)->Obiekt);
    free(*poczatek);
    (*poczatek)=NowyPoczatek;
    return Zwracany;
}

int PierwszyNaLiscie(List* poczatek){

    if(poczatek!=NULL)
        return poczatek->Obiekt.Numer;
    else
        return -1;
        
}