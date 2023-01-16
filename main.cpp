#include <iostream>
#include <vector>
#include "Tabella_attacco.h"
#include "Tabella_difesa.h"
#include "Ship.h"

int main()
{   Tab_att a;
    Tab_dif d;
    Tab_att apc;
    Tab_dif dpc;
    Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
    Ship c1, c2, c3, s1, s2, s3, e1, e2;
    std::cout << "Tabella di attacco:\n";
    std::cout << a.getTab();
    std::cout << "\n";
    std::cout << "Tabella di difesa:\n";
    std::cout << d.getTab();
    std::cout << "\n";
    d.initTab(c1, c2, c3, s1, s2, s3, e1, e2);
    dpc.auto_initTab(nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
    std::cout << "\n";
    std::cout << "Tabella di difesa:\n";
    std::cout << d.getTab();
    std::cout << "Informazioni sulla prima corazzata: \n";
    c1.printShipInfo();
    std::cout << c1.orizzontale << "\n";
    std::cout << "Informazioni sulla seconda corazzata: \n";
    c2.printShipInfo();
    std::cout << "Informazioni sulla terza corazzata: \n";
    c3.printShipInfo();
    std::cout << "Informazioni sulla prima nave supporto: \n";
    s1.printShipInfo();
    std::cout << "Informazioni sulla seconda nave supporto: \n";
    s2.printShipInfo();
    std::cout << "Informazioni sulla terza nave supporto: \n";
    s3.printShipInfo();
    std::cout << "Informazioni sul primo sottomarino: \n";
    e1.printShipInfo();
    std::cout << "Informazioni sul secondo sottomarino: \n";
    e2.printShipInfo();
    d.fire(c1, 7, 7, d, a, dpc);
    std::cout << "Tabella di difesa player: \n";
    std::cout << d.getTab();
    std::cout << "Tabella di difesa pc:\n";
    std::cout << dpc.getTab();
    std::cout << "Tabella di attacco player:\n";
    std::cout << a.getTab();
    d.moveAndRepair(s1, 7, 7, d);
    std::cout << d.getTab();
    s1.printCelleOccupate();
}