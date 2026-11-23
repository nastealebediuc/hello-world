#ifndef PRODUCTS
#define PRODUCTS
#include <bits/stdc++.h>
#include "magazin.h"
#include "category.h"
using namespace std;
ifstream readP("Products.txt");
fstream writeP;

Produs readProd() {
	Produs p;
	readP>>p.nume>>p.unit>>p.cod>>p.cantitate>>p.dataProdus.zi>>p.dataProdus.luna>>p.dataProdus.an;
	readP>>p.dataExpir.zi>>p.dataExpir.luna>>p.dataExpir.an>>p.pret;
	return p;
}

void writeProd(Produs p) {
	cout<<setw(25)<<left<<p.nume;
	cout<<"||  "<<setw(5)<<left<<p.unit<<" ||";
	cout<<" "<<setw(3)<<p.cod<<" ||   "<<
	setw(7)<<left<<setprecision(2)<<fixed<<p.cantitate<<" ||";
	showDatesNew(p); cout<<" "<<p.pret<<" mdl";
}

void writeProducts() {
	readP.seekg(0);
	cout<<setw(25)<<"========DENUMIREA========"<<"||"
	<<setw(7)<<"==UNIT=="<<"||"
	<<setw(5)<<"=COD="<<"||"
	<<setw(11)<<"=CANTITATE="<<"||"
	<<setw(14)<<"==PRODUS LA:=="<<"||"
	<<"===EXPIR LA:==||==PRET===";
	cout<<"\n";
	Produs prod;
	while (!readP.eof()) {
		prod=readProd();
		writeProd(prod);
		cout<<"\n";
	}
}

int totalDays(Date x){
    int t=0;
    t+=(x.an-2010)*365;
    t+=(x.luna-1)*30;
    t+=x.zi-1;
    return t;
}

int dateDifference(Date a, Date b){
    return (totalDays(b)-totalDays(a));
}

int sale(Produs x, Date c){
    int halfway=totalDays(x.dataProdus)+dateDifference(x.dataProdus, x.dataExpir)/2;
    int sfert=totalDays(x.dataExpir)-dateDifference(x.dataProdus, x.dataExpir)/4;
    if (totalDays(c)>totalDays(x.dataExpir)) return 100;
    else if (totalDays(c)>sfert) return 50;
    else if (totalDays(c)>halfway) return 20;
    else return 0;
}

float newPrice(Produs p, Date d){
    p.pret-=p.pret/100.0*sale(p, d);
    return p.pret;
}

string findCategory(Produs p){
    ifstream find("Category.txt");
    Category c;
    while (find>>c.cod>>c.nume){
        if (c.cod==p.cod) {find.close(); return c.nume; }
    }
    find.close();
    return "000";
}

void calculateSales(){
    fstream f; f.open("Sales.txt", ios::out);
    readP.seekg(0);
    Date currentdate;
    cout<<"Introduceti data de azi (DD MM YYYY): ";
    cin>>currentdate.zi>>currentdate.luna>>currentdate.an;
    Produs prod;
    while (!readP.eof()){
        prod=readProd();
        prod.cod=findCategory(prod);
        
        f<<setw(25)<<left<<prod.nume;
	    f<<"  "<<setw(5)<<left<<prod.unit<<" ";
	    f<<" "<<setw(15)<<prod.cod<<"    "<<
	    setw(7)<<left<<setprecision(2)<<fixed<<prod.cantitate<<" ";
    f<<"  ";
    if (prod.dataProdus.zi<10) f<<"0";
    f<<prod.dataProdus.zi<<" ";
    if (prod.dataProdus.luna<10) f<<"0";
    f<<prod.dataProdus.luna<<" "
    <<prod.dataProdus.an<<"    ";
    if (prod.dataExpir.zi<10) f<<"0";
    f<<prod.dataExpir.zi<<" ";
    if (prod.dataExpir.luna<10) f<<"0";
    f<<prod.dataExpir.luna<<" "
    <<prod.dataExpir.an<<"  ";
	   
	   
	   f<<" "<<prod.pret<<"\n";
    }
    f.close();
}

bool wrongDate(Date d){
    if (d.zi>30||d.zi<1) return 1;
    if (d.luna>12||d.luna<1) return 1;
    if (d.an<2010||d.an>9999) return 1;
    return 0;
}


void addProduct() {
	Produs p;
	cout<<"Introduceti datele noului produs:\n";
	cout<<"Nume: "; cin>>p.nume; cout<<"Unit. de masura: "; cin>>p.unit;
	cout<<"Codul categoriei: "; cin>>p.cod; cout<<"Cantitatea: "; cin>>p.cantitate;
	cout<<"Data producerii (DD MM YYYY): "; cin>>p.dataProdus.zi>>p.dataProdus.luna>>p.dataProdus.an;
	cout<<"Data expirarii (DD MM YYYY): "; cin>>p.dataExpir.zi>>p.dataExpir.luna>>p.dataExpir.an;
	cout<<"Pret: "; cin>>p.pret;
	if (dateDifference(p.dataProdus, p.dataExpir)<1) { cout<<"ERROR! Data invalida."; return; }
	if (wrongDate(p.dataProdus)||wrongDate(p.dataExpir)) { cout<<"ERROR! Data invalida."; return; }
	if (p.pret<0) { cout<<"ERROR! Pret invalid."; return; }
	Produs x; readP.seekg(0); while(!readP.eof()){
	    x=readProd();
	    if (x.nume==p.nume)  { cout<<"ERROR! Exista produs cu acest nume."; return; }
	}
	bool flag=0; string cod, cname;
	readC.seekg(0); while(!readC.eof()){
	    readC>>cod>>cname;
	    if (x.cod==cod) flag=1;
	}
	if (!flag) { cout<<"ERROR! Nu exista categorie cu acest cod."; return; }
	
	writeP<<"\n"<<p.nume<<" "<<p.unit<<" "<<p.cod<<" "<<p.cantitate<<" "<<p.dataProdus.zi<<" "<<p.dataProdus.luna;
	writeP<<" "<<p.dataProdus.an<<" "<<p.dataExpir.zi<<" "<<p.dataExpir.luna<<" "<<p.dataExpir.an<<" "<<p.pret;
	cout<<"Produs adaugat! Iesiti din program pentru a finaliza schimbarea.\n";
}

void deleteProduct() {
	string p;
	cout<<"Introduceti numele produsului: ";
	cin>>p;
	Produs x[100];
	int n=0;
	readP.seekg(0);
	bool flag=0;
	while (!readP.eof()) {
		x[n]=readProd();
		if (x[n].nume==p) flag=1;
		n++;
	}
	if (!flag) { cout<<"ERROR! Nu exista produs cu acest nume.\n"; return; }
	fstream add;
	add.open("Products.txt", ios::out);
     flag=0;
	for (int i=0; i<n; i++) {
		if (x[i].nume!=p) { add<<x[i].nume<<" "<<x[i].unit<<" "<<x[i].cod<<" "<<x[i].cantitate<<" "<<x[i].dataProdus.zi<<" "
			                     <<x[i].dataProdus.luna<<" "<<x[i].dataProdus.an<<" "<<x[i].dataExpir.zi<<" "<<x[i].dataExpir.luna<<" "
			                     <<x[i].dataExpir.an<<" "<<x[i].pret; if (n-i!=1&&(!(n-i==2&&flag==0))) add<<"\n";}
		else flag=1;
	}
	add.close();
	cout<<"Produs sters! Iesiti din program pentru a finaliza schimbarea.\n";
}

void modifyProduct() {
	string pmod; Produs Pmod;
	cout<<"Introduceti numele produsului: ";
	cin>>pmod;
	Produs x[100];
	int n=0;
	readP.seekg(0);
	bool flag=0;
	while (!readP.eof()) {
		x[n]=readProd();
		if (x[n].nume==pmod) { flag=1;
		    cout<<"Informatia curenta a produsului:\n";
		    cout<<x[n].nume<<" ("<<x[n].unit<<") "<<x[n].cod<<" cantitate: "<<x[n].cantitate<<" ";
	        showDates(x[n]); cout<<" pret: "<<x[n].pret<<" mdl\n";
	        Pmod=x[n];
		}
		n++;
	}
	if (!flag) { cout<<"ERROR! Nu exista produs cu acest nume.\n"; return; }
	Produs p=Pmod;
	int op;
	cout<<"Ce doriti sa modificati?\n"
	<<"1. Denumirea\n2. Unitatea de masura\n3. Codul categoriei\n4. Cantitatea\n"
	<<"5. Data producerii/expirarii\n6. Pretul\n7. Toate\nIntroduceti nr. optiunii: ";
	cin>>op;
	switch (op){
	    case 1: cout<<"Introduceti denumirea: "; cin>>p.nume; break;
	    case 2: cout<<"Introduceti unitatea: "; cin>>p.unit; break;
	    case 3: cout<<"Introduceti codul: "; cin>>p.cod; break;
	    case 4: cout<<"Introduceti cantitatea: "; cin>>p.cantitate; break;
	    case 5: cout<<"Introduceti data producerii (DD MM YYYY): ";
	        cin>>p.dataProdus.zi>>p.dataProdus.luna>>p.dataProdus.an;
	        cout<<"Data expirarii (DD MM YYYY): "; cin>>p.dataExpir.zi>>p.dataExpir.luna>>p.dataExpir.an; break;
	    case 6: cout<<"Introduceti pretul: "; cin>>p.pret; break;
	    case 7: cout<<"Introduceti datele modificate: \n";
	        cout<<"Nume: "; cin>>p.nume; cout<<"Unit. de masura: "; cin>>p.unit;
	        cout<<"Codul categoriei: "; cin>>p.cod; cout<<"Cantitatea: "; cin>>p.cantitate;
	        cout<<"Data producerii (DD MM YYYY): "; cin>>p.dataProdus.zi>>p.dataProdus.luna>>p.dataProdus.an;
	        cout<<"Data expirarii (DD MM YYYY): "; cin>>p.dataExpir.zi>>p.dataExpir.luna>>p.dataExpir.an;
            cout<<"Pret: "; cin>>p.pret; break;
        default: cout<<"ERROR! Optiune invalida, va rog incercati din nou.\n"; return;
	}
	if (dateDifference(p.dataProdus, p.dataExpir)<1) { cout<<"ERROR! Data invalida."; return; }
	if (wrongDate(p.dataProdus)||wrongDate(p.dataExpir)) { cout<<"ERROR! Data invalida."; return; }
	if (p.pret<0) { cout<<"ERROR! Pret invalid."; return; }
	Produs y; readP.seekg(0);
	while(!readP.eof()){
	    y=readProd();
	    if (y.nume==p.nume)  { cout<<"ERROR! Exista produs cu acest nume."; return; }
	}
	flag=0; string cod, cname;
	readC.seekg(0);
	while(!readC.eof()){
	    readC>>cod>>cname;
	    if (p.cod==cod) flag=1;
	}
	if (!flag) { cout<<"ERROR! Nu exista categorie cu acest cod."; return; }
	fstream add;
	add.open("Products.txt", ios::out);
	for (int i=0; i<n; i++) {
		if (x[i].nume!=pmod) add<<x[i].nume<<" "<<x[i].unit<<" "<<x[i].cod<<" "<<x[i].cantitate<<" "<<x[i].dataProdus.zi<<" "
			                        <<x[i].dataProdus.luna<<" "<<x[i].dataProdus.an<<" "<<x[i].dataExpir.zi<<" "<<x[i].dataExpir.luna<<" "
			                        <<x[i].dataExpir.an<<" "<<x[i].pret;
		else {
			add<<p.nume<<" "<<p.unit<<" "<<p.cod<<" "<<p.cantitate<<" "<<p.dataProdus.zi<<" "<<p.dataProdus.luna
			   <<" "<<p.dataProdus.an<<" "<<p.dataExpir.zi<<" "<<p.dataExpir.luna<<" "<<p.dataExpir.an<<" "<<p.pret;
		}
		if (n-i!=1) add<<"\n";
	}
	add.close();
	cout<<"Produs modificat! Iesiti din program pentru a finaliza schimbarea.\n";
}

#endif