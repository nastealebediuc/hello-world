#ifndef DATA_TYPES
#define DATA_TYPES
#include <bits/stdc++.h>
using namespace std;
struct Date{
    int zi, luna, an;
};

struct Produs{
    string nume, unit, cod;
    float cantitate, pret;
    Date dataProdus, dataExpir;
};

struct Category{
  string cod, nume;
};

void showDates(Produs p){
    cout<<"data producerii: ";
    if (p.dataProdus.zi<10) cout<<"0";
    cout<<p.dataProdus.zi<<".";
    if (p.dataProdus.luna<10) cout<<"0";
    cout<<p.dataProdus.luna<<"."
    <<p.dataProdus.an<<" data expirarii: ";
    if (p.dataExpir.zi<10) cout<<"0";
    cout<<p.dataExpir.zi<<".";
    if (p.dataExpir.luna<10) cout<<"0";
    cout<<p.dataExpir.luna<<"."
    <<p.dataExpir.an;
}

void showDatesNew(Produs p){
    cout<<"  ";
    if (p.dataProdus.zi<10) cout<<"0";
    cout<<p.dataProdus.zi<<".";
    if (p.dataProdus.luna<10) cout<<"0";
    cout<<p.dataProdus.luna<<"."
    <<p.dataProdus.an<<"  ||  ";
    if (p.dataExpir.zi<10) cout<<"0";
    cout<<p.dataExpir.zi<<".";
    if (p.dataExpir.luna<10) cout<<"0";
    cout<<p.dataExpir.luna<<"."
    <<p.dataExpir.an<<"  ||";
}



#endif