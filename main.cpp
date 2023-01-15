#include <iostream>
#include <vector>
#include "Tabella_attacco.h"
#include "Tabella_difesa.h"
#include "Ship.h"

int main()
{   Tab_att a;
    Tab_dif d;
    Ship c1;
    Ship c2;
    Ship c3;
    Ship s1;
    Ship s2;
    Ship s3;
    Ship e1;
    Ship e2;
    /*Ship c2(ShipType::NAVE_SUPPORTO, 0, 0, 0, 0, false,  {0, 1, 2, 3});
    Ship c3(ShipType::CORAZZATA, 0, 0, 0, 0, false,  {0, 1, 2, 3});
    Ship s1(ShipType::CORAZZATA, 0, 0, 0, 0, false,  {0, 1, 2, 3});
    Ship s2(ShipType::NAVE_SUPPORTO,  0, 0, 0, 0, false, {0, 1, 2, 3});
    Ship s3(ShipType::NAVE_SUPPORTO,  0, 0, 0, 0, false, {0, 1, 2, 3});
    Ship e1(ShipType::NAVE_SUPPORTO, 0, 0, 0, 0, false,  {0, 1, 2, 3});
    Ship e2(ShipType::SOTTOMARINO, 0, 0, 0, 0, false,  {0, 1, 2, 3});*/
    std::cout << "Tabella di attacco:\n";
    std::cout << a.getTab();
    std::cout << "\n";
    std::cout << "Tabella di difesa:\n";
    std::cout << d.getTab();
    std::cout << "\n";
    d.initTab(c1, c2, c3, s1, s2, s3, e1, e2);
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

    
}