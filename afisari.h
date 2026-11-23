#ifndef AFISARI
#define AFISARI
#include <bits/stdc++.h>
#include "magazin.h"
#include "products.h"
using namespace std;

void afisFromCategory(){
    cout<<"Introduceti categoria: ";
    string cnume, cod; cin>>cnume;
    ifstream find("Category.txt");
    Category x;
    while (find>>x.cod>>x.nume){
        if (x.nume==cnume) cod=x.cod;
    }
    find.close(); readP.seekg(0);
    Produs c[50], aux;
    int n=0;
    while (!readP.eof()){
        aux=readProd();
        if (aux.cod==cod) { 
            c[n]=aux;
            n++;
        }
    }
    for (int i=0; i<n-1; i++){
        for (int j=i+1; j<n; j++){
            if (c[i].nume>c[j].nume) swap(c[i], c[j]);
        }
    }
    cout<<setw(25)<<"========DENUMIREA========"<<"||"
	<<setw(7)<<"==UNIT=="<<"||"
	<<setw(5)<<"=COD="<<"||"
	<<setw(11)<<"=CANTITATE="<<"||"
	<<setw(14)<<"==PRODUS LA:=="<<"||"
	<<"===EXPIR LA:==||==PRET===\n";
    for (int i=0; i<n; i++)
    {
        writeProd(c[i]); cout<<"\n";
    }
}

void afisProdusMM(){
    calculateSales();
    Produs pmax, pmin, p;
    pmax.pret=-1; pmin.pret=1000000;
    ifstream fin("Sales.txt");
    while (!fin.eof()){
        fin>>p.nume>>p.unit>>p.cod>>p.cantitate>>p.dataProdus.zi>>p.dataProdus.luna>>p.dataProdus.an
        >>p.dataExpir.zi>>p.dataExpir.luna>>p.dataExpir.an>>p.pret;
        if (p.pret>pmax.pret) pmax=p;
        else if (p.pret<pmin.pret) pmin=p;
    }
    cout<<"\nCel mai ieftin produs:\n";
    cout<<setw(25)<<left<<pmin.nume;
	cout<<"||  "<<setw(5)<<left<<pmin.unit<<" ||";
	cout<<" "<<setw(15)<<pmin.cod<<" ||   "<<
	setw(7)<<left<<setprecision(2)<<fixed<<pmin.cantitate<<" ||";
	showDatesNew(pmin); cout<<" "<<pmin.pret<<" mdl\n";
        
    cout<<"\nCel mai scump produs:\n";
    
    cout<<setw(25)<<left<<pmax.nume;
	cout<<"||  "<<setw(5)<<left<<pmax.unit<<" ||";
	cout<<" "<<setw(15)<<pmax.cod<<" ||   "<<
	setw(7)<<left<<setprecision(2)<<fixed<<pmax.cantitate<<" ||";
	showDatesNew(p); cout<<" "<<pmax.pret<<" mdl\n";
}

void afisTotalValue(){
    float total=0;
    Produs x;
    readP.seekg(0);
    while (!readP.eof()){
        x=readProd();
        total+=x.pret*x.cantitate;
    }
    cout<<"Valoarea totala a tuturor produselor din magazin: "<<total<<" mdl\n";
}

#endif