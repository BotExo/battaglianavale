#ifndef TABDIF_H
#define TABDIF_H

#include <iostream>
#include <vector>

class Tab_dif
{   public:
        Tab_dif();
        std::string getTab();
        void Fill(int riga_poppa, int riga_prua, int colonna_poppa, int colonna_prua, std::string T, int dim);
        void initTab();
        void delete_ships();
        void setMin(int r, int c);
        class Invalid_Matrix_Position{};
    private:
        std::vector<std::vector<std::string>> matrix;
};

class Coordinate
{   public:
        Coordinate(std::string r, int c);
        class Invalid_coordinate{};
        std::string getRiga()
        {   return riga;
        }
        int getColonna()
        {   return colonna;
        }
        int rigaInt(char r);
    private:
        std::string riga = "";
        int colonna = 0;
        bool isValid();
};

#endif
