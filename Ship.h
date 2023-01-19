#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>

enum class ShipType {
            CORAZZATA,
            NAVE_SUPPORTO,
            SOTTOMARINO
        };


class Ship {
    
    public:
        Ship();
        int getColonnaInizio();
        int getRigaInizio();
        int getColonnaFine();
        int getRigaFine();
        int getRigaCentrale() const;
        int getColonnaCentrale() const;
        void setRigaCentrale( int RigaCentrale);
        void setColonnaCentrale( int ColonnaCentrale);
        std::vector<std::pair<int, int>> getCelleOccupate();
        void setCelleOccupate(std::vector<std::pair<int, int>> celleoccupate);
        ShipType GetType() const;
        void setType(ShipType type);
        void TakeHit();
        bool IsDestroyed() const;
        void SetSize(int size);
        int GetSize() const;
        int GetNumHits() const;
        void setOrizzontale();
        bool getOrizzontale()const;
        bool orizzontale;
        void printCelleOccupate();
        std::vector<std::pair<int, int>> celleoccupate;
        int RigaCentrale;
        int ColonnaCentrale;
        ShipType type_;
        void printShipInfo();
        class Invalid_Matrix_Position{};
        bool operator == (const Ship& s) const;
        bool operator != (const Ship& s) const;
        friend class Tab_dif;


    private:
        char colonnaInizio;
        int rigaInizio;
        char colonnaFine;
        int rigaFine;
        int riga;
        int size_;
        int health_;
        
        

};

#endif
