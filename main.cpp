#include <bits/stdc++.h>
#include "magazin.h"
#include "products.h"
#include "category.h"
#include "afisari.h"
using namespace std;

int main()
{
    writeP.open("Products.txt", ios::app);
    writeC.open("Category.txt", ios::app);
    int optiune;
    
    do {
    cout<<"\nNOW ACCESSING: MAGAZIN\n";
    cout<<"=====MENU:=====\n";
    cout<<"1. Afisati toate produsele\n"<<"2. Afisati toate categoriile\n";
    cout<<"3. Adaugati un nou produs\n"<<"4. Adaugati o noua categorie\n";
    cout<<"5. Stergeti un produs\n"<<"6. Stergeti o categorie\n";
    cout<<"7. Modifica informatia unui produs\n"<<"8. Modifica informatia unei categorii\n";
    cout<<"9. Creati fisier cu preturile reduse\n"<<"10. Afisati produsele alfabetic dupa categorie\n";
    cout<<"11. Afisati cel mai ieftin/scump produs la data actuala\n"
    <<"12. Afisati valoarea totala a tuturor produselor in stoc\n";
    cout<<"0: EXIT MENU.\n";
    cout<<"Alegeti o optiune (introduceti numarul): ";
    cin>>optiune;
    switch (optiune){
        case 0: break;
        case 1: writeProducts(); break;
        case 2: writeCategories(); break;
        case 3: addProduct(); break;
        case 4: addCategory(); break;
        case 5: deleteProduct(); break;
        case 6: deleteCategory(); break;
        case 7: modifyProduct(); break;
        case 8: modifyCategory(); break;
        case 9: calculateSales(); cout<<"Fisier creat sub numele Sales.txt . Inchideti aplicatia pentru a finaliza procesul.\n"; break;
        case 10: afisFromCategory(); break;
        case 11: afisProdusMM(); break;
        case 12: afisTotalValue(); break;
       default: cout<<"ERROR! Optiunea introdusa nu exista.";
    }
    } while (optiune!=0);
    
    readP.close();
    readC.close();
    writeP.close();
    writeC.close();
    return 0;
}