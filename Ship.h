#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "Tabella_difesa.h"
#include <vector>

enum class ShipType {
            CORAZZATA,
            NAVE_SUPPORTO,
            SOTTOMARINO
        };


class Ship {
    private:
        char colonnaInizio;
        int rigaInizio;
        char colonnaFine;
        int rigaFine;
        int riga;
        int size_;
        int health_;
        
    public:
        Ship();
        Ship(ShipType type, char colonnaInizio, int rigaInizio, char colonnaFine, int rigaFine, bool orizzontale, std::vector<int> celleoccupate);
        Ship(ShipType type, int RigaCentrale, int ColonnaCentrale, bool orizzontale, std::vector<int> celleoccupate);
        int getColonnaInizio();
        int getRigaInizio();
        int getColonnaFine();
        int getRigaFine();
        int getRigaCentrale();
        int getColonnaCentrale();
        void setRigaCentrale(int RigaCentrale);
        void setColonnaCentrale(int ColonnaCentrale);
        std::vector<int> getCelleOccupate();
        void setCelleOccupate(std::vector<int> celleoccupate);
        ShipType GetType() const;
        void setType(ShipType type);
        void TakeHit();
        bool IsDestroyed() const;
        int GetSize() const;
        int GetNumHits() const;
        void setOrizzontale();
        bool getOrizzontale()const;
        bool orizzontale;
        void printCelleOccupate();
        std::vector<int> celleoccupate;
        int RigaCentrale;
        int ColonnaCentrale;
        ShipType type_;
        //void moveShip(Ship &ship, int middleX, int middleY, Tab_dif const& tabella_difesa);
        

};

#endif
