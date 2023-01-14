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
    d.initTab(c1, c2, c3);
    std::cout << "\n";
    std::cout << "Tabella di difesa:\n";
    std::cout << d.getTab();
    std::cout << " la colonna centrale e': " "\n";
    //c1.setColonnaCentrale(9);
    
    std::cout << c1.getColonnaCentrale() << "\n";
    std::cout << " la riga centrale e': " "\n";
    //c1.setRigaCentrale(9);
    std::cout << c1.getRigaCentrale() << "\n";
    std::cout << " il tipo di nave e': " "\n";
    //c1.setType(ShipType::SOTTOMARINO);
    if (c1.GetType() == ShipType::CORAZZATA){
      std::cout << "corazzata" << "\n";
    }
    else if (c1.GetType() == ShipType::NAVE_SUPPORTO){
      std::cout << "nave supporto" << "\n";
    }
    else if (c1.GetType() == ShipType::SOTTOMARINO){
      std::cout << "sottomarino" << "\n";
    }

    
}