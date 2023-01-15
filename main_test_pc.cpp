#include <iostream>
#include <vector>
#include "Tabella_attacco.h"
#include "Tabella_difesa.h"
#include "Ship.h"

int main(void)
{   Tab_att a1, a2;
    Tab_dif d1, d2;
    Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
    Ship C1, C2, C3, S1, S2, S3, E1, E2;
    std::cout << "Tabella di attacco player:\n";
    std::cout << a1.getTab();
    std::cout << "\n";
    std::cout << "Tabella di difesa pleyer:\n";
    std::cout << d1.getTab();
    std::cout << "\n";
    std::cout << "Tabella di attacco pc:\n";
    std::cout << a2.getTab();
    std::cout << "\n";
    std::cout << "Tabella di difesa pc:\n";
    std::cout << d2.getTab();
    std::cout << "\n";
    d2.auto_initTab(nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
    std::cout << "\n";
    d1.initTab(C1, C2, C3, S1, S2, S3, E1, E2);
    std::cout << "\n";
    std::cout << "Tabella di difesa pleyer:\n";
    std::cout << d1.getTab();
    std::cout << "\n";
    std::cout << "Tabella di difesa pc:\n";
    std::cout << d2.getTab();
    std::cout << "\n";
}
