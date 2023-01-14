#include <iostream>
#include <vector>
#include "Tabella_attacco.h"
#include "Tabella_difesa.h"
#include "Ship.h"

int main(void)
{   Tab_att a;
    Tab_dif d;
    Ship c1;
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
    d.initTab();
    std::cout << "\n";
    std::cout << "Tabella di difesa:\n";
    std::cout << d.getTab();
    std::cout << " le celle occupate dalla prima corazzata sono: " "\n";
    c1.printCelleOccupate();
}