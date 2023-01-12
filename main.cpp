#include <iostream>
#include <vector>
#include "Tabella_attacco.h"
#include "Tabella_difesa.h"

int main(void)
{   Tab_att a;
    Tab_dif d;
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
}
