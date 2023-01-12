#ifndef TABDIF_H
#define TABDIF_H

#include <iostream>
#include <vector>
#include "Ship.h"

class Tab_dif
{   public:
        Tab_dif();
        std::string getTab();
        void Fill(int riga_poppa, int riga_prua, int colonna_poppa, int colonna_prua, std::string T, int dim);
        void initTab();
        class Invalid_Matrix_Position{};
        Tab_dif operator ==(Tab_dif const& m);
    private:
        int **ptr;
        std::vector<std::vector<std::string>> matrix;
};

class Coordinate
{   public:
        Coordinate(std::string r, int c);
        class Invalid_coordinate{};
        std::string getRiga();
        int getColonna();
        int rigaInt(char r);
        int getRiga_poppa() const;
        int getRiga_prua() const;
        int riga_poppa;
        int riga_prua;
        
    private:
        std::string riga = "";
        int colonna = 0;
        bool isValid();
};

#endif
