//Carlo Bottaro
#ifndef TABDIF_H
#define TABDIF_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Ship.h"
#include "Tabella_attacco.h"

class Tab_dif
{   public:
        Tab_dif(); //costruttore
        std::string getTab(); //metodo stampa della griglia
        void Fill(int riga_poppa, int riga_prua, int colonna_poppa, int colonna_prua, std::string T, int dim);  //metodo per aggiungere le navi alla griglia
        void initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2, std::ofstream& file); //metodo per inizializzare la griglia
        void auto_initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2, std::ofstream& file); //metodo per inizializzare la griglia del pc
        void delete_ship(Ship& s); //metodo per eliminare la nave affondata
        void setMin(int r, int c); //metodo per settare il carattere da maiuscolo a minuscolo se colpito
        class Invalid_Matrix_Position{}; //eccezione per la posizione nella griglia
        void moveAndRepair(Ship& ship,int NuovaRigaCentrale, int NuovaColonnaCentrale, Tab_dif const& tabella_difesa, Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2); //metodo per spostare la nave di supporto e riparare le navi alleate vicine
        void moveAndScan(Ship& ship,int NuovaRigaCentrale, int NuovaColonnaCentrale, Tab_dif const& tabella_difesa, Tab_att& tabella_attacco, Tab_dif const& tabella_difesa2); //metodo per spostare il sottomarino e scansionare le navi nemiche vicine
        void fire(Ship& ship, int RigaCasellaFuoco, int ColonnaCasellaFuoco, Tab_dif const& tabella_difesa, Tab_att& tabella_attacco, Tab_dif& tabella_difesa2, Ship& avv1, Ship& avv2, Ship& avv3, Ship& avv4, Ship& avv5, Ship& avv6, Ship& avv7, Ship& avv8); //metodo per sparare con la corazzata
        bool isOccupied(int r, int c); //metodo per vedere se la casella e' occupata
    private:
        std::vector<std::vector<std::string>> matrix; //matrice della griglia
};

class Coordinate
{   public:
        Coordinate(std::string r, int c); //costruttore
        class Invalid_coordinate{}; //eccezione per la posizione nella griglia
        std::string getRiga() //metodo get per la riga
        {   return riga;
        }
        int getColonna() //metodo get per la colonna
        {   return colonna;
        }
        int rigaInt(char r); //metodo per convertire la riga da char a int
    private:
        std::string riga = ""; //riga
        int colonna = 0; //colonna
        bool isValid(); //metodo per vedere se la posizione e' valida
};

#endif