#ifndef TABATT_H
#define TABATT_H

#include <iostream>
#include <vector>
#include "Ship.h"

class Tab_att
{   public:
        Tab_att();
        std::string getTab();
        class Invalid_Matrix_Position{};
        void clearY();
        void insert(int r, int c, std::string s);
        class Invalid_Character{};
    private:
        std::vector<std::vector<std::string>> matrix;
};

#endif
