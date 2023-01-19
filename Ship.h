//Marco Bettin
#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>

enum class ShipType { //enumerazione per il tipo di nave
            CORAZZATA, 
            NAVE_SUPPORTO, 
            SOTTOMARINO
        };


class Ship {
    
    public:
        Ship();//costruttore
        int getColonnaInizio();//metodi get per la colonna di inizio della nave
        int getRigaInizio();//metodi get per la riga di inizio della nave
        int getColonnaFine();//metodi get per la colonna di fine della nave
        int getRigaFine();//metodi get per la riga di fine della nave
        int getRigaCentrale() const; //metodi get per la riga centrale della nave
        int getColonnaCentrale() const; //metodi get per la colonna centrale della nave
        void setRigaCentrale( int RigaCentrale); //metodi set per la riga centrale della nave
        void setColonnaCentrale( int ColonnaCentrale); //metodi set per la colonna centrale della nave
        std::vector<std::pair<int, int>> getCelleOccupate(); //metodo get ritornare il vettore di pair di celle occupate
        void setCelleOccupate(std::vector<std::pair<int, int>> celleoccupate); //metodo set per settare il vettore di pair di celle occupate
        void printCelleOccupate(); //metodo per stampare le celle occupate
        ShipType GetType() const; //metodo get per il tipo di nave
        void setType(ShipType type); //metodo set per il tipo di nave
        ShipType type_; //variabile per il tipo di nave
        void TakeHit(); //metodo per prendere un colpo
        bool IsDestroyed() const; //metodo per vedere se la nave e' distrutta
        void SetSize(int size); //metodo set per la dimensione della nave
        int GetSize() const; //metodo get per la dimensione della nave
        int GetNumHits() const; //metodo get per la vita rimasta alla nave
        void setOrizzontale(); //metodo set per settare la nave in orizzontale
        bool getOrizzontale()const; //metodo get per vedere se la nave e' in orizzontale
        bool orizzontale; //variabile booleana per vedere se la nave e' in orizzontale
        
        std::vector<std::pair<int, int>> celleoccupate; //vettore di pair di celle occupate
        int RigaCentrale; //variabile per la riga centrale della nave
        int ColonnaCentrale; //variabile per la colonna centrale della nave
        
        void printShipInfo(); //metodo per stampare alcuni parametri della nave
        void setHealth(int h); //metodo set per la vita della nave
        class Invalid_Matrix_Position{}; //classe eccezione per la posizione nella matrice


    private:
        char colonnaInizio; //variabile per la colonna di inizio della nave
        int rigaInizio; //variabile per la riga di inizio della nave
        char colonnaFine; //variabile per la colonna di fine della nave
        int rigaFine; //variabile per la riga di fine della nave
        int size_; //variabile per la dimensione della nave
        int health_; //variabile per la vita della nave
        
        

};

#endif