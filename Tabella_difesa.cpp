

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <list>
#include "Tabella_difesa.h"
#include "Ship.h"

const static int ASCII_A = 65;
const static int ASCII_a = 97;

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
    if(riga_int >= ASCII_a)
        riga_int -= ASCII_a;
    else
        riga_int -= ASCII_A;
//aggiusto coordinate per l, m, n perchè prima di esse ci sarebbero i caratteri j, k
        
    if(riga_int == 11 || riga_int == 12 ||riga_int == 13)
        riga_int -= 2;
    return riga_int;
}

Tab_dif::Tab_dif()
{   int const righe = 13;
    int const colonne = 13;
    int const start_righe = 0, end_righe = 12;
    int const start_colonne = 1, end_colonne = 13;
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
    for(int i = start_righe; i < end_righe; i++)
    {   for(int j = start_colonne; j < end_colonne; j++)
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

void Tab_dif::initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2, std::ofstream& file)
{   const int coraz = 3;
    const int supp = 3;
    const int sott = 2;
    const int dim_coraz = 5;
    const int dim_supp = 3;
    const int dim_sott = 1;
    for(int i = 0; i < coraz; i++)
    {   std::string poppa = "", prua = "";
        std::string azione = "";
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
        
//stampo il posizionamento su file
        
        std::transform(poppa.begin(), poppa.end(), poppa.begin(), ::toupper);
        std::transform(prua.begin(), prua.end(), prua.begin(), ::toupper);
        azione = poppa + " " + prua;
        file << azione << std::endl;
        
//stampo le coordinate di prua e poppa della nave appena creata
        
        std::vector<std::pair<int, int>> celle_occupate_tmp;
        
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   
                celle_occupate_tmp.push_back(std::make_pair(i, j));
                std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
        
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
        
        if(i == 0)
        {   c1.setType(ShipType::CORAZZATA);
            c1.setRigaCentrale(riga_centrale);
            c1.setColonnaCentrale(colonna_centrale);
            c1.setCelleOccupate(celle_occupate_tmp);
            if(riga_poppa_int == riga_prua_int)
            {   c1.setOrizzontale();
                std::cout << "La corazzata 1 è piazzata\n";
            }
        } 
        else if(i == 1)
            {   c2.setType(ShipType::CORAZZATA);
                c2.setRigaCentrale(riga_centrale);
                c2.setColonnaCentrale(colonna_centrale);
                c2.setCelleOccupate(celle_occupate_tmp);
                if(riga_poppa_int == riga_prua_int)
                {   c2.setOrizzontale();
                    std::cout << "La corazzata 2 è piazzata\n";
                }
            } 
            else if(i == 2)
                {   c3.setType(ShipType::CORAZZATA);
                    c3.setRigaCentrale(riga_centrale);
                    c3.setColonnaCentrale(colonna_centrale);
                    c3.setCelleOccupate(celle_occupate_tmp);
                    if(riga_poppa_int == riga_prua_int)
                    {   c3.setOrizzontale();
                        std::cout << "La corazzata 3 è piazzata\n";
                    }
                }
    }
    for(int i = 0; i < supp; i++)
    {   std::string poppa = "", prua = "";
        std::string azione = "";
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
        std::transform(poppa.begin(), poppa.end(), poppa.begin(), ::toupper);
        std::transform(prua.begin(), prua.end(), prua.begin(), ::toupper);
        azione = poppa + " " + prua;
        file << azione << std::endl;
        std::vector<std::pair<int, int>> celle_occupate_tmp;
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   
                celle_occupate_tmp.push_back(std::make_pair(i, j));
                std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
        
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
        
//creo le 3 navi di supporto (manca da implementare la f virtuale)
        
        if(i == 0)
        {   s1.setType(ShipType::NAVE_SUPPORTO);
            s1.setRigaCentrale(riga_centrale);
            s1.setColonnaCentrale(colonna_centrale);
            s1.setCelleOccupate(celle_occupate_tmp);
            s1.SetSize(dim_supp);
            if(riga_poppa_int == riga_prua_int)
            {   s1.setOrizzontale();
                std::cout << "La supporto 1 è piazzata\n";
            }
            
        }
        else if(i == 1)
            {   s2.setType(ShipType::NAVE_SUPPORTO);
                s2.setRigaCentrale(riga_centrale);
                s2.setColonnaCentrale(colonna_centrale);
                s2.setCelleOccupate(celle_occupate_tmp);
                s2.SetSize(dim_supp);
                if(riga_poppa_int == riga_prua_int)
                {   s2.setOrizzontale();
                    std::cout << "La supporto 2 è piazzata\n";
                }
            }
            else if(i == 2)
                {   s3.setType(ShipType::NAVE_SUPPORTO);
                    s3.setRigaCentrale(riga_centrale);
                    s3.setColonnaCentrale(colonna_centrale);
                    s3.setCelleOccupate(celle_occupate_tmp);
                    s3.SetSize(dim_supp);
                    if(riga_poppa_int == riga_prua_int)
                    {   s3.setOrizzontale();
                        std::cout << "La supporto 3 è piazzata\n";
                    }
                    
                }
    }
    for(int i = 0; i < sott; i++)
    {   std::string poppa = "", prua = "";
        std::string azione = "";
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
        std::transform(poppa.begin(), poppa.end(), poppa.begin(), ::toupper);
        std::transform(prua.begin(), prua.end(), prua.begin(), ::toupper);
        azione = poppa + " " + prua;
        file << azione << std::endl;
        std::vector<std::pair<int, int>> celle_occupate_tmp;
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   
                celle_occupate_tmp.push_back(std::make_pair(i, j));
                std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }              
//creo i 2 sottomarini (manca da implementare la f virtuale)

        int riga_centrale = riga_poppa_int;
        int colonna_centrale = coord_poppa.getColonna();
        if(i == 0)
        {   e1.setType(ShipType::SOTTOMARINO);
            e1.setRigaCentrale(riga_centrale);
            e1.setColonnaCentrale(colonna_centrale);
            e1.setCelleOccupate(celle_occupate_tmp);
            e1.SetSize(dim_sott);
            if(riga_poppa_int == riga_prua_int)
            {   e1.setOrizzontale();
                std::cout << "Il sottomarino 1 è piazzato\n";
            }
        }
        else if(i == 1)
            {   e2.setType(ShipType::SOTTOMARINO);
                e2.setRigaCentrale(riga_centrale);
                e2.setColonnaCentrale(colonna_centrale);
                e2.setCelleOccupate(celle_occupate_tmp);
                e2.SetSize(dim_sott);
                if(riga_poppa_int == riga_prua_int)
                {   e2.setOrizzontale();
                    std::cout << "Il sottomarino 2 è piazzato\n";
                }
            }
    }
}

void Tab_dif::auto_initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2, std::ofstream& file)
{   const int coraz = 3;
    const int supp = 3;
    const int sott = 2;
    const int dim_coraz = 5;
    const int dim_supp = 3;
    const int dim_sott = 1;
    std::string possibili_righe = "ABCDEFGHILMN";
    std::srand(std::time(nullptr));
    std::vector<std::string> celle_occupate = {""};
    for(int i = 0; i < coraz; i++)
    {   std::string poppa = "", prua = "";
        std::string azione = "";
        bool done = false;
        while(!done)
        {   int random_riga = std::rand() % possibili_righe.length();
            int random_colonna = 0;
            do
            {   random_colonna = std::rand() % 13;
            }
            while(random_colonna == 0);
            std::string colonna_poppa_string = std::to_string(random_colonna);
            poppa = possibili_righe[random_riga] + colonna_poppa_string;
            int random_orizz_vert = std::rand() % 2;
            if(random_orizz_vert == 0 && random_colonna <= 8)
            {   std::string colonna_prua_string = std::to_string(random_colonna+4);
                prua = possibili_righe[random_riga] + colonna_prua_string;
                for(int j = 0; j < celle_occupate.size(); j++)
                {   std::string cella_da_verificare1 = poppa;
                    std::string colonna_2_string = std::to_string(random_colonna+1);
                    std::string cella_da_verificare2 = possibili_righe[random_riga] + colonna_2_string;
                    std::string colonna_3_string = std::to_string(random_colonna+2);
                    std::string cella_da_verificare3 = possibili_righe[random_riga] + colonna_3_string;
                    std::string colonna_4_string = std::to_string(random_colonna+3);
                    std::string cella_da_verificare4 = possibili_righe[random_riga] + colonna_4_string;
                    std::string cella_da_verificare5 = prua;
                    if(cella_da_verificare1 == celle_occupate[j] || cella_da_verificare2 == celle_occupate[j] || cella_da_verificare3 == celle_occupate[j] || cella_da_verificare4 == celle_occupate[j] || cella_da_verificare5 == celle_occupate[j])
                        break;
                    if(j == celle_occupate.size() - 1)
                    {   done = true;
                        celle_occupate.resize(celle_occupate.size()+5);
                        celle_occupate.push_back(cella_da_verificare1);
                        celle_occupate.push_back(cella_da_verificare2);
                        celle_occupate.push_back(cella_da_verificare3);
                        celle_occupate.push_back(cella_da_verificare4);
                        celle_occupate.push_back(cella_da_verificare5);
                    }
                }
            }
            else if(random_orizz_vert == 1 && random_riga <= 7)
                {   std::string colonna_prua_string = colonna_poppa_string;
                    prua = possibili_righe[random_riga+4] + colonna_prua_string;
                    for(int j = 0; j < celle_occupate.size(); j++)
                    {   std::string cella_da_verificare1 = poppa;
                        std::string cella_da_verificare2 = possibili_righe[random_riga+1] + colonna_poppa_string;
                        std::string cella_da_verificare3 = possibili_righe[random_riga+2] + colonna_poppa_string;
                        std::string cella_da_verificare4 = possibili_righe[random_riga+3] + colonna_poppa_string;
                        std::string cella_da_verificare5 = prua;
                        if(cella_da_verificare1 == celle_occupate[j] || cella_da_verificare2 == celle_occupate[j] || cella_da_verificare3 == celle_occupate[j] || cella_da_verificare4 == celle_occupate[j] || cella_da_verificare5 == celle_occupate[j])
                            break;
                        if(j == celle_occupate.size() - 1)
                        {   done = true;
                            celle_occupate.resize(celle_occupate.size()+5);
                            celle_occupate.push_back(cella_da_verificare1);
                            celle_occupate.push_back(cella_da_verificare2);
                            celle_occupate.push_back(cella_da_verificare3);
                            celle_occupate.push_back(cella_da_verificare4);
                            celle_occupate.push_back(cella_da_verificare5);
                        }
                    }
                }
        }
        azione = poppa + " " + prua;
        file << azione << std::endl;

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
        
//stampo le coordinate di prua e poppa della nave appena creata
        
        std::vector<std::pair<int, int>> celle_occupate_tmp;
        
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   
                celle_occupate_tmp.push_back(std::make_pair(i, j));
                std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }        
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
        
        if(i == 0)
        {   c1.setType(ShipType::CORAZZATA);
            c1.setRigaCentrale(riga_centrale);
            c1.setColonnaCentrale(colonna_centrale);
            c1.setCelleOccupate(celle_occupate_tmp);
            if(riga_poppa_int == riga_prua_int)
            {   c1.setOrizzontale();
            }
            std::cout << "La corazzata 1 è piazzata\n";

        } 
        else if(i == 1)
            {   c2.setType(ShipType::CORAZZATA);
                c2.setRigaCentrale(riga_centrale);
                c2.setColonnaCentrale(colonna_centrale);
                c2.setCelleOccupate(celle_occupate_tmp);
                if(riga_poppa_int == riga_prua_int)
                {   c2.setOrizzontale();
                }
                std::cout << "La corazzata 2 è piazzata\n";

            } 
            else if(i == 2)
                {   c3.setType(ShipType::CORAZZATA);
                    c3.setRigaCentrale(riga_centrale);
                    c3.setColonnaCentrale(colonna_centrale);
                    c3.setCelleOccupate(celle_occupate_tmp);
                    if(riga_poppa_int == riga_prua_int)
                    {   c3.setOrizzontale();
                    }
                    std::cout << "La corazzata 3 è piazzata\n";
                }
    }
    for(int i = 0; i < supp; i++)
    {   std::string poppa = "", prua = "";
        std::string azione = "";
        bool done = false;
        while(!done)
        {   int random_riga = std::rand() % possibili_righe.length();
            int random_colonna = 0;
            do
            {   random_colonna = std::rand() % 13;
            }
            while(random_colonna == 0);
            std::string colonna_poppa_string = std::to_string(random_colonna);
            poppa = possibili_righe[random_riga] + colonna_poppa_string;
            int random_orizz_vert = std::rand() % 2;
            if(random_orizz_vert == 0 && random_colonna <= 10)
            {   std::string colonna_prua_string = std::to_string(random_colonna+2);
                prua = possibili_righe[random_riga] + colonna_prua_string;
                for(int j = 0; j < celle_occupate.size(); j++)
                {   std::string cella_da_verificare1 = poppa;
                    std::string colonna_2_string = std::to_string(random_colonna+1);
                    std::string cella_da_verificare2 = possibili_righe[random_riga] + colonna_2_string;
                    std::string colonna_3_string = std::to_string(random_colonna+2);
                    std::string cella_da_verificare3 = prua;
                    if(cella_da_verificare1 == celle_occupate[j] || cella_da_verificare2 == celle_occupate[j] || cella_da_verificare3 == celle_occupate[j])
                        break;
                    if(j == celle_occupate.size() - 1)
                    {   done = true;
                        celle_occupate.resize(celle_occupate.size()+3);
                        celle_occupate.push_back(cella_da_verificare1);
                        celle_occupate.push_back(cella_da_verificare2);
                        celle_occupate.push_back(cella_da_verificare3);
                    }
                }
            }
            else if(random_orizz_vert == 1 && random_riga <= 9)
                {   std::string colonna_prua_string = colonna_poppa_string;
                    prua = possibili_righe[random_riga+2] + colonna_prua_string;
                    for(int j = 0; j < celle_occupate.size(); j++)
                    {   std::string cella_da_verificare1 = poppa;
                        std::string cella_da_verificare2 = possibili_righe[random_riga+1] + colonna_poppa_string;
                        std::string cella_da_verificare3 = prua;
                        if(cella_da_verificare1 == celle_occupate[j] || cella_da_verificare2 == celle_occupate[j] || cella_da_verificare3 == celle_occupate[j])
                            break;
                        if(j == celle_occupate.size() - 1)
                        {   done = true;
                            celle_occupate.resize(celle_occupate.size()+5);
                                           celle_occupate.push_back(cella_da_verificare1);
                            celle_occupate.push_back(cella_da_verificare2);
                            celle_occupate.push_back(cella_da_verificare3);
                        }
                    }
                }
        }
        azione = poppa + " " + prua;
        file << azione << std::endl;

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

        Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "S", dim_supp);
        
//stampo le coordinate di prua e poppa della nave appena creata
        
        std::vector<std::pair<int, int>> celle_occupate_tmp;
        
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   
                celle_occupate_tmp.push_back(std::make_pair(i, j));
                std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
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
        
//creo le 3 navi di supporto
        
        if(i == 0)
        {   s1.setType(ShipType::NAVE_SUPPORTO);
            s1.setRigaCentrale(riga_centrale);
            s1.setColonnaCentrale(colonna_centrale);
            s1.setCelleOccupate(celle_occupate_tmp);
            s1.SetSize(dim_supp);
            if(riga_poppa_int == riga_prua_int)
            {   s1.setOrizzontale();
                std::cout << "La nave di supporto 1 è piazzata\n";
            }
            
        } 
        else if(i == 1)
            {   s2.setType(ShipType::NAVE_SUPPORTO);
                s2.setRigaCentrale(riga_centrale);
                s2.setColonnaCentrale(colonna_centrale);
                s2.setCelleOccupate(celle_occupate_tmp);
                s2.SetSize(dim_supp);
                if(riga_poppa_int == riga_prua_int)
                {   s2.setOrizzontale();
                    std::cout << "La nave di supporto 2 è piazzata\n";
                }
            } 
            else if(i == 2)
                {   s3.setType(ShipType::NAVE_SUPPORTO);
                    s3.setRigaCentrale(riga_centrale);
                    s3.setColonnaCentrale(colonna_centrale);
                    s3.setCelleOccupate(celle_occupate_tmp);
                    s3.SetSize(dim_supp);
                    if(riga_poppa_int == riga_prua_int)
                    {   s3.setOrizzontale();
                        std::cout << "La nave di supporto 3 è piazzata\n";
                    }
                }
    }
    for(int i = 0; i < sott; i++)
    {   std::string poppa = "", prua = "";
        std::string azione = "";
        bool done = false;
        while(!done)
        {   int random_riga = std::rand() % possibili_righe.length();
            int random_colonna = 0;
            do
            {   random_colonna = std::rand() % 13;
            }
            while(random_colonna == 0);
            std::string colonna_poppa_string = std::to_string(random_colonna);
            poppa = possibili_righe[random_riga] + colonna_poppa_string;
            prua = poppa;
            for(int j = 0; j < celle_occupate.size(); j++)
            {   if(poppa == celle_occupate[j])
                    break;
                if(j == celle_occupate.size() - 1)
                {   done = true;
                    celle_occupate.resize(celle_occupate.size()+1);
                    celle_occupate.push_back(poppa);
                }
            }
        }
        azione = poppa + " " + prua;
        file << azione << std::endl;

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

        Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "E", dim_sott);
        
//stampo le coordinate di prua e poppa della nave appena creata
        
        std::vector<std::pair<int, int>> celle_occupate_tmp;
        
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   
                celle_occupate_tmp.push_back(std::make_pair(i, j));
                std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }      
//creo i 2 sottomarini (manca da implementare la f virtuale)

        int riga_centrale = riga_poppa_int;
        int colonna_centrale = coord_poppa.getColonna();
        if(i == 0)
        {   e1.setType(ShipType::SOTTOMARINO);
            e1.setRigaCentrale(riga_centrale);
            e1.setColonnaCentrale(colonna_centrale);
            e1.setCelleOccupate(celle_occupate_tmp);
            e1.SetSize(dim_sott);
            if(riga_poppa_int == riga_prua_int)
            {   e1.setOrizzontale();
                std::cout << "Il sottomarino 1 è piazzato\n";
            }
        }
        else if(i == 1)
            {   e2.setType(ShipType::SOTTOMARINO);
                e2.setRigaCentrale(riga_centrale);
                e2.setColonnaCentrale(colonna_centrale);
                e2.setCelleOccupate(celle_occupate_tmp);
                e2.SetSize(dim_sott);
                if(riga_poppa_int == riga_prua_int)
                {   e2.setOrizzontale();
                    std::cout << "Il sottomarino 2 è piazzato\n";
                }
            }
    }
}

void Tab_dif::setMin(int r, int c)
{   if(matrix[r][c] == " C")
        matrix[r][c] = " c";
    if(matrix[r][c] == " S")
        matrix[r][c] = " s";
    if(matrix[r][c] == " E")
        matrix[r][c] = " e";
}

void Tab_dif::moveAndRepair(Ship& ship,int NuovaRigaCentrale, int NuovaColonnaCentrale, Tab_dif const& tabella_difesa){
    std::vector<std::pair<int, int>> nuove_celle;
    for (int i = -1; i < -2; i++){
        for (int j = -1; j < -2; j++){
            if (matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " C" || matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " S" ||
                matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " E"){
                std::cout << "errore nel repair\n";
                throw Invalid_Matrix_Position();
            }
        }
    }
//gestione caso spostamento nave supporto orizzontale di una cella sola, verso dx o sx
    if(ship.orizzontale==true && (matrix[NuovaRigaCentrale][NuovaColonnaCentrale] == matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] ||
        matrix[NuovaRigaCentrale][NuovaColonnaCentrale] == matrix[ship.RigaCentrale][ship.ColonnaCentrale-1])){
            if(matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] == " S"){
                matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] = " ";
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale-1] = " S";
                nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale-1));}
                else{
                    matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] = " ";
                    matrix[NuovaRigaCentrale][NuovaColonnaCentrale-1] = " s";
                    nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale-1));
                }
            if(matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " S"){
                matrix[ship.RigaCentrale][ship.ColonnaCentrale] = " ";
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale] = " S";
                nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale));}
                else{
                    matrix[ship.RigaCentrale][ship.ColonnaCentrale] = " ";
                    matrix[NuovaRigaCentrale][NuovaColonnaCentrale] = " s";
                    nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale));
                }
            if(matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] == " S"){
                matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] = " ";
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale+1] = " S";
                nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale+1));}
                else{
                    matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] = " ";
                    matrix[NuovaRigaCentrale][NuovaColonnaCentrale+1] = " s";
                    nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale+1));
                }
    }



    else{
        
        if(ship.orizzontale==true && matrix[NuovaRigaCentrale][NuovaColonnaCentrale-1] == " " &&
         matrix[NuovaRigaCentrale][NuovaColonnaCentrale] == " " && matrix[NuovaRigaCentrale][NuovaColonnaCentrale+1] == " "){
            if(matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] == " S"){
                matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] = " ";
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale-1] = " S";
                nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale-1));}
                else{
                    matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] = " ";
                    matrix[NuovaRigaCentrale][NuovaColonnaCentrale-1] = " s";
                    nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale-1));
                }
            if(matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " S"){
                matrix[ship.RigaCentrale][ship.ColonnaCentrale] = " ";
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale] = " S";
                nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale));}
                else{
                    matrix[ship.RigaCentrale][ship.ColonnaCentrale] = " ";
                    matrix[NuovaRigaCentrale][NuovaColonnaCentrale] = " s";
                    nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale));
                }
            if(matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] == " S"){
                matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] = " ";
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale+1] = " S";
                nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale+1));}
                else{
                    matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] = " ";
                    matrix[NuovaRigaCentrale][NuovaColonnaCentrale+1] = " s";
                    nuove_celle.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale+1));
            }
            for (int i = -1; i < 2; i++)
            {
                int vitaextra = 0;
                if(matrix[NuovaRigaCentrale-1][NuovaColonnaCentrale+i]==" c"){

                    matrix[NuovaRigaCentrale-1][NuovaColonnaCentrale+i] = " C";

                } else if(matrix[NuovaRigaCentrale-1][NuovaColonnaCentrale+i]==" s"){
                    matrix[NuovaRigaCentrale-1][NuovaColonnaCentrale+i] = " S";
                }
                if(matrix[NuovaRigaCentrale+1][NuovaColonnaCentrale+i]==" c"){
                    matrix[NuovaRigaCentrale+1][NuovaColonnaCentrale+i] = " C";
                } else if(matrix[NuovaRigaCentrale+1][NuovaColonnaCentrale+i]==" s"){
                    matrix[NuovaRigaCentrale+1][NuovaColonnaCentrale+i] = " S";
                }

            }
            
        }
            else if (matrix[NuovaRigaCentrale-1][NuovaColonnaCentrale] == " " &&
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale] == " " && matrix[NuovaRigaCentrale+1][NuovaColonnaCentrale] == " "){
            if(matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] == " S"){
                matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] = " ";
                matrix[NuovaRigaCentrale-1][NuovaColonnaCentrale] = " S";}
                else{
                    matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] = " ";
                    matrix[NuovaRigaCentrale-1][NuovaColonnaCentrale] = " s";
                }
            if(matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " S"){
                matrix[ship.RigaCentrale][ship.ColonnaCentrale] = " ";
                matrix[NuovaRigaCentrale][NuovaColonnaCentrale] = " S";}
                else{
                    matrix[ship.RigaCentrale][ship.ColonnaCentrale] = " ";
                    matrix[NuovaRigaCentrale][NuovaColonnaCentrale] = " s";
                }
            if(matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] == " S"){
                matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] = " ";
                matrix[NuovaRigaCentrale+1][NuovaColonnaCentrale] = " S";}
                else{
                    matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] = " ";
                    matrix[NuovaRigaCentrale+1][NuovaColonnaCentrale] = " s";
            }

        }
        ship.RigaCentrale=NuovaRigaCentrale;
        ship.ColonnaCentrale=NuovaColonnaCentrale;
        ship.setCelleOccupate(nuove_celle);
    }
            
}

void Tab_dif::moveAndScan(Ship& ship,int NuovaRigaCentrale, int NuovaColonnaCentrale, Tab_dif const& tabella_difesa, Tab_att& tabella_attacco, Tab_dif const& tabella_difesa2){
    if(tabella_difesa.matrix[NuovaRigaCentrale][NuovaColonnaCentrale] != " "){
                    std::cout << "errore nel moveandscan" << std::endl;
                    throw Invalid_Matrix_Position();
                    
    }
    std::vector<std::pair<int, int>> nuova_cella;
    if(tabella_difesa.matrix[NuovaRigaCentrale][NuovaColonnaCentrale] == " "){
        matrix[NuovaRigaCentrale][NuovaColonnaCentrale] = " E";
        matrix[ship.RigaCentrale][ship.ColonnaCentrale] = " ";
        nuova_cella.push_back(std::make_pair(NuovaRigaCentrale, NuovaColonnaCentrale));


    }
    
    for (int i = -2; i < 3; i++)
    {
        for (int j = -2; j < 3; j++)
        {
            if(NuovaRigaCentrale+i>=0 && NuovaRigaCentrale+i<11 && NuovaColonnaCentrale+j>0 && NuovaColonnaCentrale+j<13){
            if(tabella_difesa2.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " S" ){
                tabella_attacco.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] = " Y";
            }else
            if(tabella_difesa2.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " s" ){
                tabella_attacco.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] = " X";
            }else
            if(tabella_difesa2.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " C" ){
                tabella_attacco.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] = " Y";
            }else
            if(tabella_difesa2.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " c" ){
                tabella_attacco.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] = " X";
            }else
            if(tabella_difesa2.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] == " E" ){
                tabella_attacco.matrix[NuovaRigaCentrale+i][NuovaColonnaCentrale+j] = " Y";
            }
            }
        }
        
    }
    ship.RigaCentrale=NuovaRigaCentrale;
    ship.ColonnaCentrale=NuovaColonnaCentrale;
    ship.setCelleOccupate(nuova_cella);
}

void Tab_dif::fire(Ship& ship, int RigaCasellaFuoco, int ColonnaCasellaFuoco, Tab_dif const& tabella_difesa, Tab_att& tabella_attacco, Tab_dif& tabella_difesa2){
    if(tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " C" || tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " c"){
            if((tabella_difesa2.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] == " C") ||
                    (tabella_difesa2.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] == " E") || (tabella_difesa2.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] == " S")){
                    tabella_attacco.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] = " X";
                    if (tabella_difesa2.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] == " C"){
                        tabella_difesa2.setMin(RigaCasellaFuoco, ColonnaCasellaFuoco);
                        }
                    if (tabella_difesa2.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] == " S"){
                        tabella_difesa2.setMin(RigaCasellaFuoco, ColonnaCasellaFuoco);
                        }   
                    if (tabella_difesa2.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] == " E"){
                        tabella_difesa2.setMin(RigaCasellaFuoco, ColonnaCasellaFuoco);
                        }
                   
            }
        else{
             tabella_attacco.matrix[RigaCasellaFuoco][ColonnaCasellaFuoco] = " O";
        }
    }
        else{
        std::cout << "errore nel fire" << std::endl;
        throw Invalid_Matrix_Position();
        
        }
}

bool Tab_dif::isOccupied(int r, int c)
{   bool occupied = false;
    if(matrix[r][c] == " C" || matrix[r][c] == " c" || matrix[r][c] == " S" || matrix[r][c] == " s" || matrix[r][c] == " E")
        occupied = true;
    return occupied;
}
        
void Tab_dif::delete_ships(Ship& ship, Tab_dif& tabella_difesa, std::list<Ship> &lista_navi){
    if (tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " e")
    {
        lista_navi.remove(ship);
        tabella_difesa.matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] = " ";
    }
    
    if(ship.orizzontale==false){
        if( tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " c" && tabella_difesa.matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] == " c" &&
            tabella_difesa.matrix[ship.RigaCentrale+2][ship.ColonnaCentrale] == " c" && tabella_difesa.matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] == " c" &&
            tabella_difesa.matrix[ship.RigaCentrale-2][ship.ColonnaCentrale] == " c"){
            
              tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] = tabella_difesa.matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] =
               tabella_difesa.matrix[ship.RigaCentrale-2][ship.ColonnaCentrale] = tabella_difesa.matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] = tabella_difesa.matrix[ship.RigaCentrale+2][ship.ColonnaCentrale] = " ";
            lista_navi.remove(ship);
            }
        if( tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " s" && tabella_difesa.matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] == " s" &&
            tabella_difesa.matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] == " s"){
              tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] = tabella_difesa.matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] = tabella_difesa.matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] = " ";
            lista_navi.remove(ship);        
            }
    }
    else{
        if( tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " c" && tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] == " c" &&
            tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale+2] == " c" && tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] == " c" && 
            tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale-2] == " c"){
              tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] = tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] = tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale-2] =
               tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] = tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale+2] = " ";
            lista_navi.remove(ship);
            }
        if( tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] == " s" && tabella_difesa.matrix[ship.RigaCentrale+1][ship.ColonnaCentrale] == " s" &&
            tabella_difesa.matrix[ship.RigaCentrale-1][ship.ColonnaCentrale] == " s"){
              tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale] = tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale-1] = tabella_difesa.matrix[ship.RigaCentrale][ship.ColonnaCentrale+1] = " ";
            lista_navi.remove(ship);        
        }
  }
}