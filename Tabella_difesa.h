//De Maria Giovanni

#ifndef TABDIF_H
#define TABDIF_H

#include <iostream>
#include <vector>
#include "Ship.h"
#include "Tabella_attacco.h"

class Tab_dif
{   public:
        Tab_dif();
        std::string getTab();
        void Fill(int riga_poppa, int riga_prua, int colonna_poppa, int colonna_prua, std::string T, int dim);
        void initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2);
        void auto_initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2);
        void delete_ships();
        void setMin(int r, int c);
        class Invalid_Matrix_Position{};
        void moveAndRepair(Ship& Ship,int NuovaRigaCentrale, int NuovaColonnaCentrale, Tab_dif const& tabella_difesa);
        void moveAndScan(Ship& Ship,int NuovaRigaCentrale, int NuovaColonnaCentrale, Tab_dif const& tabella_difesa, Tab_att& tabella_attacco, Tab_dif const& tabella_difesa_pc);
        void fire(Ship& ship, int RigaCasellaFuoco, int ColonnaCasellaFuoco, Tab_dif const& tabella_difesa, Tab_att& tabella_attacco, Tab_dif& tabella_difesa2);
        bool isOccupied(int r, int c);
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
