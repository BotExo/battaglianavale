//De Maria Giovanni
#ifndef TABATT_H
#define TABATT_H

#include <iostream>
#include <vector>

class Tab_att
{   public:
        Tab_att();//costruttore
        std::string getTab();//metodo stampa della griglia
        class Invalid_Matrix_Position{};//eccezione per la posizione nella griglia
        void clearY();//metodo per cancellare le Y
        void clearXO();//metodo per cancellare le X e le O
        void insert(int r, int c, std::string s);//metodo per inserire nella griglia una X, una O o una Y
        class Invalid_Character{};//eccezione per il carattere inserito
        friend class Tab_dif; //classe amica per poter accedere ai metodi e alle variabili private
    private:
        std::vector<std::vector<std::string>> matrix;  //matrice della griglia
};

#endif