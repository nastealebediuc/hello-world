#ifndef CATEGORY
#define CATEGORY
#include "magazin.h"
#include <bits/stdc++.h>
ifstream readC("Category.txt");
fstream writeC;

Category readCat(){
    Category c;
    readC>>c.cod>>c.nume;
    return c;
}

void writeCat(Category c){
    cout<<" "<<c.cod<<" || "<<c.nume;
}

void writeCategories(){
    readC.seekg(0);
    cout<<"=COD=||=DENUMIRE=\n";
    Category cat;
    while (!readC.eof()){
        cat=readCat();
        writeCat(cat);
        cout<<"\n";
    }
}

void addCategory(){
    Category c;
    cout<<"Introduceti datele pentru noua categorie:\n";
    cout<<"Cod: "; cin>>c.cod;
    cout<<"Denumire: "; cin>>c.nume;
    readC.seekg(0); Category x;
    while (!readC.eof()){
        x=readCat();
        if (x.cod==c.cod) { cout<<"ERROR! Exista categorie cu acest cod.\n"; return; }
        if (x.nume==c.nume) { cout<<"ERROR! Exista categorie cu acest nume.\n"; return; }
    }
    writeC<<"\n"<<c.cod<<" "<<c.nume;
    cout<<"Categorie adaugata! Iesiti din program pentru a finaliza schimbarea.\n";
}

void deleteCategory(){
    string c;
    cout<<"Introduceti numele categoriei: ";
    cin>>c;
    Category x[100]; int n=0;
    readC.seekg(0);
    bool check=0;
    while (!readC.eof()){
        x[n]=readCat();
        if (x[n].nume==c) check=1;
         n++;
    }
    if (!check) { cout<<"ERROR! Nu exista categorie cu acest nume."; return; }
    check=0;
    fstream add; add.open("Category.txt", ios::out);
    for (int i=0; i<n; i++){
        if (x[i].nume!=c) { add<<x[i].cod<<" "<<x[i].nume;
            if (n-i!=1&&(!(n-i==2&&check==0))) add<<"\n"; }
        else check=1;
    }
    add.close();
    cout<<"Categorie stersa! Iesiti din program pentru a finaliza schimbarea.\n";
}

void modifyCategory(){
    string cmod;
    cout<<"Introduceti numele categoriei: ";
    cin>>cmod;
    Category x[100]; int n=0;
    readC.seekg(0); bool check=0;
    while (!readC.eof()){
        x[n]=readCat();
        if (x[n].nume==cmod) check=1;
        n++;
    }
    if (!check) { cout<<"ERROR! Nu exista categorie cu acest nume."; return; }
    int op;
    cout<<"Ce doriti sa modificati?\n";
    cout<<"1. Codul\n2. Denumirea\n3. Ambele\n";
    cout<<"Introduceti nr. optiunii: "; 
    cin>>op;
    Category c;
    switch (op){
        case 1:
            cout<<"Introduceti noul cod: ";
            cin>>c.cod;
            break;
        case 2:
            cout<<"Introduceti noua denumire: ";
            cin>>c.nume;
            break;
        case 3:
            cout<<"Introduceti datele modificate: \n";
            cout<<"Cod: "; cin>>c.cod;
            cout<<"Denumire: "; cin>>c.nume;
            break;
        default: cout<<"ERROR! Optiune invalida, va rog incercati din nou."; return; 
    }
    readC.seekg(0); Category y;
    while (!readC.eof()){
        y=readCat();
        if (y.cod==c.cod) { cout<<"ERROR! Exista categorie cu acest cod.\n"; return; }
        if (y.nume==c.nume) { cout<<"ERROR! Exista categorie cu acest nume.\n"; return; }
    }
    fstream add; add.open("Category.txt", ios::out);
    for (int i=0; i<n; i++){
        if (x[i].nume!=cmod) add<<x[i].cod<<" "<<x[i].nume;
        else add<<c.cod<<" "<<c.nume;
        if (n-i!=1) add<<"\n";
    }
    add.close();
    cout<<"Categorie modificata! Iesiti din program pentru a finaliza schimbarea.\n";
}

#endif