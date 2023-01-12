#include <iostream>
#include <vector>
#include <cstring>
#include "Tabella_difesa.h"
#include "Ship.h"

Coordinate::Coordinate(std::string r, int c)
           : riga {r}, colonna {c}
{   if(!isValid())
        throw Invalid_coordinate();
}

bool Coordinate::isValid()
{   bool ok = true;
    std::string available_characters = "abcdefghilmnABCDEFGHILMN";
    if(available_characters.find(riga) != std::string::npos)
        ok = true;
    else
        return false;
    if(colonna < 1 || colonna > 12)
        return false;
    else
        ok = true;
    return ok;
}

int Coordinate::rigaInt(char r)
{   int riga_int = (int)r;
    if(riga_int >= 97)
        riga_int -= 97;
    else
        riga_int -= 65;
//aggiusto coordinate per l, m, n perchè prima di esse ci sarebbero i caratteri j, k
        
    if(riga_int == 11 || riga_int == 12 ||riga_int == 13)
        riga_int -= 2;
    return riga_int;
}

Tab_dif::Tab_dif()
{   int const righe = 13;
    int const colonne = 13;
    std::string inizio = "";
    matrix.resize(righe, std::vector<std::string>(colonne, inizio));
    matrix[0][0] = "A";
    matrix[1][0] = "B";
    matrix[2][0] = "C";
    matrix[3][0] = "D";
    matrix[4][0] = "E";
    matrix[5][0] = "F";
    matrix[6][0] = "G";
    matrix[7][0] = "H";
    matrix[8][0] = "I";
    matrix[9][0] = "L";
    matrix[10][0] = "M";
    matrix[11][0] = "N";
    matrix[12][1] = "  1";
    matrix[12][2] = " 2";
    matrix[12][3] = " 3";
    matrix[12][4] = " 4";
    matrix[12][5] = " 5";
    matrix[12][6] = " 6";
    matrix[12][7] = " 7";
    matrix[12][8] = " 8";
    matrix[12][9] = " 9";
    matrix[12][10] = "10";
    matrix[12][11] = "11";
    matrix[12][12] = "12";
    for(int i = 0; i < 12; i++)
    {   for(int j = 1; j < 13; j++)
            matrix[i][j] = " ";
    }
}

std::string Tab_dif::getTab()
{   int const righe = 13;   
    int const colonne = 13;
    std::string tabella = "";
    for(int i = 0; i < righe; i ++)
    {   for(int j = 0; j < colonne; j++)
        {   if(matrix[i][j] == " ")
                tabella += matrix[i][j] + " " + " ";
            else
                tabella += matrix[i][j] + " ";
        }
        tabella += "\n";
    }
    return tabella;
}

void Tab_dif::Fill(int riga_poppa, int riga_prua, int colonna_poppa, int colonna_prua, std::string T, int dim)
{   if(riga_poppa == riga_prua)
    {   if(colonna_poppa - (dim-1) == colonna_prua)
        {   bool empty = true;
            for(int i = colonna_prua; i <= colonna_poppa; i++)
            {   if(matrix[riga_poppa][i] != " ")
                    throw Invalid_Matrix_Position();
            }
            if(empty)
            {   for(int i = colonna_prua; i <= colonna_poppa; i++)
                    matrix[riga_poppa][i] = " " + T;
            }
        }
        else if(colonna_poppa + (dim-1) == colonna_prua)
            {   bool empty = true;
                for(int i = colonna_poppa; i <= colonna_prua; i++)
                {   if(matrix[riga_poppa][i] != " ")
                        throw Invalid_Matrix_Position();
                }
                if(empty)
                {   for(int i = colonna_poppa; i <= colonna_prua; i++)
                        matrix[riga_poppa][i] = " " + T;
                }
            }
            else
                throw Invalid_Matrix_Position();
    }
    else if(colonna_poppa == colonna_prua)
        {   if(riga_poppa - (dim-1) == riga_prua)
            {   bool empty = true;
                for(int i = riga_prua; i <= riga_poppa; i++)
                {   if(matrix[i][colonna_poppa] != " ")
                        throw Invalid_Matrix_Position();
                }
                if(empty)
                {   for(int i = riga_prua; i <= riga_poppa; i++)
                        matrix[i][colonna_poppa] = " " + T;
                }
            }
            else if(riga_poppa + (dim-1) == riga_prua)
                {   bool empty = true;
                    for(int i = riga_poppa; i <= riga_prua; i++)
                    {   if(matrix[i][colonna_poppa] != " ")
                            throw Invalid_Matrix_Position();
                    }
                    if(empty)
                    {   for(int i = riga_poppa; i <= riga_prua; i++)
                            matrix[i][colonna_poppa] = " " + T;
                    }
                }
                else
                    throw Invalid_Matrix_Position();
        }
        else
            throw Invalid_Matrix_Position();
}

void Tab_dif::initTab()
{   const int coraz = 3;
    const int supp = 3;
    const int sott = 2;
    const int dim_coraz = 5;
    const int dim_supp = 3;
    const int dim_sott = 1;
    for(int i = 0; i < coraz; i++){
       std::string poppa = "", prua = "";
        std::cout << "ora siamo ad i: " << i <<"\n";
        std::cout << "Quali sono le coordinate per la corazzata " << i+1 <<"?\n";
        std::cin >> poppa;
        std::cin >> prua;

//creo le gli oggetti coordinate di poppa e prua

        std::string riga_poppa = poppa.substr(0,1);
        int colonna_poppa = std::stoi(poppa.substr(1));
        Coordinate coord_poppa(riga_poppa, colonna_poppa);
        std::string riga_prua = prua.substr(0,1);
        int colonna_prua = std::stoi(prua.substr(1));
        Coordinate coord_prua(riga_prua, colonna_prua);
        
//converto le lettere delle coordinate in indici interi per la tabella
        
        int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
        int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
        
//controllo che le coordinate siano valide, cioè che la nave sia in verticale o orizzontale e che tutte le caselle che occuperebbe sono libere e "posiziono" le lettere

        Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "C", dim_coraz);
        std::vector<int> celle_occupate_tmp{riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int k=riga_poppa_int; k<=riga_prua_int; k++)
            { for(int j=colonna_poppa; j<=colonna_prua; j++)
                {  std::cout<<"Le celle occupate sono riga: "<< k << " e colonna: "<< j <<"\n"; 
                }
        }
            
        std::cout<< celle_occupate_tmp.at(0) << " " << celle_occupate_tmp.at(1) << " " << celle_occupate_tmp.at(2) <<" "<< celle_occupate_tmp.at(3) <<std::endl;
        
//trovo le coordinate del centro della corazzata

        int riga_centrale = 0, colonna_centrale = 0;
        if(riga_poppa_int == riga_prua_int)
        {   riga_centrale = riga_poppa_int;
            colonna_centrale = (coord_poppa.getColonna() + coord_prua.getColonna()) / 2;
        }
        else
        {   colonna_centrale = coord_poppa.getColonna();
            riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
        }
        
//creo le 3 corazzate
        
        if(i == 0){
                Ship c1(ShipType::CORAZZATA, riga_centrale ,colonna_centrale, false, celle_occupate_tmp);
                if (riga_poppa_int == riga_prua_int){
                    c1.setOrizzontale();
                    std::cout << "La corazzata 1 è piazzata\n";
                }
            } else if(i == 1)
                {   
                    Ship c2(ShipType::CORAZZATA, riga_centrale ,colonna_centrale, false, celle_occupate_tmp);
                    if (riga_poppa_int == riga_prua_int){
                        c2.setOrizzontale();
                        std::cout << "La corazzata 2 è piazzata\n";
                    }
                } else if(i == 2){
                    Ship c3(ShipType::CORAZZATA, riga_centrale ,colonna_centrale, false, celle_occupate_tmp);
                    if (riga_poppa_int == riga_prua_int){
                            c3.setOrizzontale();
                            std::cout << "La corazzata 3 è piazzata\n";
                        }
            }   
    }
    for(int i = 0; i < supp; i++)
    {   std::string poppa = "", prua = "";
        std::cout << "Quali sono le coordinate per la nave di supporto " << i+1 <<"?\n";
        std::cin >> poppa;
        std::cin >> prua;
        std::string riga_poppa = poppa.substr(0,1);
        int colonna_poppa = std::stoi(poppa.substr(1));
        Coordinate coord_poppa(riga_poppa, colonna_poppa);
        std::string riga_prua = prua.substr(0,1);
        int colonna_prua = std::stoi(prua.substr(1));
        Coordinate coord_prua(riga_prua, colonna_prua);
        int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
        int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
        Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "S", dim_supp);
        std::vector<int> celle_occupate_tmp{riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int k=riga_poppa_int; k<=riga_prua_int; k++)
            { for(int j=colonna_poppa; j<=colonna_prua; j++)
                {  std::cout<<"Le celle occupate sono riga: "<< k << " e colonna: "<< j <<"\n"; 
                }
        }
        std::cout<< celle_occupate_tmp.at(0) << " " << celle_occupate_tmp.at(1) << " " << celle_occupate_tmp.at(2) <<" "<< celle_occupate_tmp.at(3) <<std::endl;
        
//trovo le coordinate del centro della nave di supporto

        int riga_centrale = 0, colonna_centrale = 0;
        if(riga_poppa_int == riga_prua_int)
        {   riga_centrale = riga_poppa_int;
            colonna_centrale = (coord_poppa.getColonna() + coord_prua.getColonna()) / 2;
        }
        else
        {   colonna_centrale = coord_poppa.getColonna();
            riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
        }
        
/*creo le 3 navi di supporto (manca da implementare la f virtuale)*/
        
        if(i == 0){
                Ship s1(ShipType::NAVE_SUPPORTO, riga_centrale ,colonna_centrale, false, celle_occupate_tmp);
                if (riga_poppa_int == riga_prua_int){
                    s1.setOrizzontale();
                    std::cout << "La supporto 1 è piazzata\n";
                }
            } else if(i == 1)
                {   Ship s2(ShipType::NAVE_SUPPORTO, riga_centrale ,colonna_centrale, false, celle_occupate_tmp);
                    if (riga_poppa_int == riga_prua_int){
                        s2.setOrizzontale();
                        std::cout << "La supporto 2 è piazzata\n";
                    }
                } else if(i == 2){
                    Ship s3(ShipType::NAVE_SUPPORTO, riga_centrale ,colonna_centrale, false, celle_occupate_tmp);
                    if (riga_poppa_int == riga_prua_int){
                            s3.setOrizzontale();
                            std::cout << "La supporto 3 è piazzata\n";
                        }
            }   
    }
    for(int i = 0; i < sott; i++)
    {   std::string poppa = "", prua = "";
        std::cout << "Quali sono le coordinate per il sottomarino di esplorazione " << i+1 <<"?\n";
        std::cin >> poppa;
        std::cin >> prua;
        std::string riga_poppa = poppa.substr(0,1);
        int colonna_poppa = std::stoi(poppa.substr(1));
        Coordinate coord_poppa(riga_poppa, colonna_poppa);
        std::string riga_prua = prua.substr(0,1);
        int colonna_prua = std::stoi(prua.substr(1));
        Coordinate coord_prua(riga_prua, colonna_prua);
        int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
        int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
        Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "E", dim_sott);
        std::vector<int> celle_occupate_tmp{riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int k=riga_poppa_int; k<=riga_prua_int; k++)
            { for(int j=colonna_poppa; j<=colonna_prua; j++)
                {  std::cout<<"Le celle occupate sono riga: "<< k << " e colonna: "<< j <<"\n"; 
                }
        }
        std::cout<< celle_occupate_tmp.at(0) << " " << celle_occupate_tmp.at(1) << " " << celle_occupate_tmp.at(2) <<" "<< celle_occupate_tmp.at(3) <<std::endl;
        
              
/*creo i 2 sottomarini (manca da implementare la f virtuale)*/

        int riga_centrale = riga_poppa_int;
        int colonna_centrale = coord_poppa.getColonna();
        if(i == 0)
        {   Ship e1(ShipType::SOTTOMARINO, riga_centrale ,colonna_centrale, true, celle_occupate_tmp);
            if (riga_poppa_int == riga_prua_int)
            {
                e1.setOrizzontale();
                std::cout << "Il sottomarino 1 è piazzato\n";
            }
        }else if(i == 1)
            {   Ship e2(ShipType::SOTTOMARINO, riga_centrale ,colonna_centrale, false, celle_occupate_tmp);
                if (riga_poppa_int == riga_prua_int)
                {
                    e2.setOrizzontale();
                    std::cout << "Il sottomarino 2 è piazzato\n";
                }
        }
        
    }
}

std::string Coordinate::getRiga(){   
    return riga;
}

int Coordinate::getColonna(){
    return colonna;
}

Tab_dif Tab_dif::operator ==(Tab_dif const& m){
    ptr = new int* [13];
    for(int i =0;i<13;i++){
        for(int j=0;j<13;j++){
            matrix[i][j] = m.ptr[i][j];
        }
    }
    return *this;
}