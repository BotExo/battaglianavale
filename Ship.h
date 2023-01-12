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
        ShipType type_;
        int RigaCentrale;
        int ColonnaCentrale;
        bool orizzontale;
        std::vector<int> celleoccupate;

    public:
        Ship(ShipType type, char colonnaInizio, int rigaInizio, char colonnaFine, int rigaFine, bool orizzontale);
        Ship(ShipType type, int RigaCentrale, int ColonnaCentrale, bool orizzontale, std::vector<int> celleoccupate);
        int getColonnaInizio();
        int getRigaInizio();
        int getColonnaFine();
        int getRigaFine();
        int getRigaCentrale();
        int getColonnaCentrale();
        bool TakeDamage();
        void move();
        void Repair();
        void Reveal();
        bool IsSunk();
        ShipType GetType() const;
        void TakeHit();
        bool IsDestroyed() const;
        char GetSymbol();
        int GetSize() const;
        int GetNumHits() const;
        void setOrizzontale() const;
        //void moveShip(Ship &ship, int middleX, int middleY, Tab_dif const& tabella_difesa);
        

};

#endif
