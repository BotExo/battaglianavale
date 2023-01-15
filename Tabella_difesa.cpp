//De Maria Giovanni

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <ctime>
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

void Tab_dif::initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2)
{   const int coraz = 3;
    const int supp = 3;
    const int sott = 2;
    const int dim_coraz = 5;
    const int dim_supp = 3;
    const int dim_sott = 1;
    for(int i = 0; i < coraz; i++)
    {   std::string poppa = "", prua = "";
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
        
//stampo le coordinate di prua e poppa della nave appena creata
        
        std::vector<int> celle_occupate_tmp {riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
        std::cout << "gli estremi sono: (" << celle_occupate_tmp.at(0) << ", " << celle_occupate_tmp.at(1) << ") (" << celle_occupate_tmp.at(2) << ", " << celle_occupate_tmp.at(3) << ")" << std::endl;
        
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
            if(riga_poppa_int == riga_prua_int)
            {   c1.setOrizzontale();
                std::cout << "La corazzata 1 è piazzata\n";
            }
        } 
        else if(i == 1)
            {   c2.setType(ShipType::CORAZZATA);
                c2.setRigaCentrale(riga_centrale);
                c2.setColonnaCentrale(colonna_centrale);
                if(riga_poppa_int == riga_prua_int)
                {   c2.setOrizzontale();
                    std::cout << "La corazzata 2 è piazzata\n";
                }
            } 
            else if(i == 2)
                {   c3.setType(ShipType::CORAZZATA);
                    c3.setRigaCentrale(riga_centrale);
                    c3.setColonnaCentrale(colonna_centrale);
                    if(riga_poppa_int == riga_prua_int)
                    {   c3.setOrizzontale();
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
        std::vector<int> celle_occupate_tmp {riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   std::cout<<"Le celle occupate sono riga: " << i << " e colonna: "<< j << "\n"; 
            }
        }
        std::cout << "gli estremi sono: (" << celle_occupate_tmp.at(0) << ", " << celle_occupate_tmp.at(1) << ") (" << celle_occupate_tmp.at(2) << ", " << celle_occupate_tmp.at(3) << ")" << std::endl;
        
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
            if(riga_poppa_int == riga_prua_int)
            {   s1.setOrizzontale();
                std::cout << "La supporto 1 è piazzata\n";
            }
            
        }
        else if(i == 1)
            {   s2.setType(ShipType::NAVE_SUPPORTO);
                s2.setRigaCentrale(riga_centrale);
                s2.setColonnaCentrale(colonna_centrale);
                if(riga_poppa_int == riga_prua_int)
                {   s2.setOrizzontale();
                    std::cout << "La supporto 2 è piazzata\n";
                }
            }
            else if(i == 2)
                {   s3.setType(ShipType::NAVE_SUPPORTO);
                    s3.setRigaCentrale(riga_centrale);
                    s3.setColonnaCentrale(colonna_centrale);
                    if(riga_poppa_int == riga_prua_int)
                    {   s3.setOrizzontale();
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
        std::vector<int> celle_occupate_tmp {riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int i = riga_poppa_int; i <= riga_prua_int; i ++)
        {   for(int j=colonna_poppa; j <= colonna_prua; j++)
            {   std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
        std::cout << "gli estremi sono: (" << celle_occupate_tmp.at(0) << ", " << celle_occupate_tmp.at(1) << ") (" << celle_occupate_tmp.at(2) << ", " << celle_occupate_tmp.at(3) << ")" << std::endl;
              
//creo i 2 sottomarini (manca da implementare la f virtuale)

        int riga_centrale = riga_poppa_int;
        int colonna_centrale = coord_poppa.getColonna();
        if(i == 0)
        {   e1.setType(ShipType::SOTTOMARINO);
            e1.setRigaCentrale(riga_centrale);
            e1.setColonnaCentrale(colonna_centrale);
            if(riga_poppa_int == riga_prua_int)
            {   e1.setOrizzontale();
                std::cout << "Il sottomarino 1 è piazzato\n";
            }
        }
        else if(i == 1)
            {   e2.setType(ShipType::SOTTOMARINO);
                e2.setRigaCentrale(riga_centrale);
                e2.setColonnaCentrale(colonna_centrale);
                if(riga_poppa_int == riga_prua_int)
                {   e2.setOrizzontale();
                    std::cout << "Il sottomarino 2 è piazzato\n";
                }
            }
    }
}

void Tab_dif::auto_initTab(Ship& c1, Ship& c2, Ship& c3, Ship& s1, Ship& s2, Ship& s3, Ship& e1, Ship& e2)
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
        
        std::vector<int> celle_occupate_tmp {riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
        std::cout << "gli estremi sono: (" << celle_occupate_tmp.at(0) << ", " << celle_occupate_tmp.at(1) << ") (" << celle_occupate_tmp.at(2) << ", " << celle_occupate_tmp.at(3) << ")" << std::endl;
        
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
            if(riga_poppa_int == riga_prua_int)
            {   c1.setOrizzontale();
            }
            std::cout << "La corazzata 1 è piazzata\n";

        } 
        else if(i == 1)
            {   c2.setType(ShipType::CORAZZATA);
                c2.setRigaCentrale(riga_centrale);
                c2.setColonnaCentrale(colonna_centrale);
                if(riga_poppa_int == riga_prua_int)
                {   c2.setOrizzontale();
                }
                std::cout << "La corazzata 2 è piazzata\n";

            } 
            else if(i == 2)
                {   c3.setType(ShipType::CORAZZATA);
                    c3.setRigaCentrale(riga_centrale);
                    c3.setColonnaCentrale(colonna_centrale);
                    if(riga_poppa_int == riga_prua_int)
                    {   c3.setOrizzontale();
                    }
                    std::cout << "La corazzata 3 è piazzata\n";
                }
    }
    for(int i = 0; i < supp; i++)
    {   std::string poppa = "", prua = "";
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
        
        std::vector<int> celle_occupate_tmp {riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
        std::cout << "gli estremi sono: (" << celle_occupate_tmp.at(0) << ", " << celle_occupate_tmp.at(1) << ") (" << celle_occupate_tmp.at(2) << ", " << celle_occupate_tmp.at(3) << ")" << std::endl;
        
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
            if(riga_poppa_int == riga_prua_int)
            {   s1.setOrizzontale();
                std::cout << "La nave di supporto 1 è piazzata\n";
            }
            
        } 
        else if(i == 1)
            {   s2.setType(ShipType::NAVE_SUPPORTO);
                s2.setRigaCentrale(riga_centrale);
                s2.setColonnaCentrale(colonna_centrale);
                if(riga_poppa_int == riga_prua_int)
                {   s2.setOrizzontale();
                    std::cout << "La nave di supporto 2 è piazzata\n";
                }
            } 
            else if(i == 2)
                {   s3.setType(ShipType::NAVE_SUPPORTO);
                    s3.setRigaCentrale(riga_centrale);
                    s3.setColonnaCentrale(colonna_centrale);
                    if(riga_poppa_int == riga_prua_int)
                    {   s3.setOrizzontale();
                        std::cout << "La nave di supporto 3 è piazzata\n";
                    }
                }
    }
    for(int i = 0; i < sott; i++)
    {   std::string poppa = "", prua = "";
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
        
        std::vector<int> celle_occupate_tmp {riga_poppa_int, colonna_poppa, riga_prua_int, colonna_prua};
        for(int i = riga_poppa_int; i <= riga_prua_int; i++)
        {   for(int j = colonna_poppa; j <= colonna_prua; j++)
            {   std::cout << "Le celle occupate sono riga: " << i << " e colonna: " << j << "\n"; 
            }
        }
        std::cout << "gli estremi sono: (" << celle_occupate_tmp.at(0) << ", " << celle_occupate_tmp.at(1) << ") (" << celle_occupate_tmp.at(2) << ", " << celle_occupate_tmp.at(3) << ")" << std::endl;
              
//creo i 2 sottomarini (manca da implementare la f virtuale)

        int riga_centrale = riga_poppa_int;
        int colonna_centrale = coord_poppa.getColonna();
        if(i == 0)
        {   e1.setType(ShipType::SOTTOMARINO);
            e1.setRigaCentrale(riga_centrale);
            e1.setColonnaCentrale(colonna_centrale);
            if(riga_poppa_int == riga_prua_int)
            {   e1.setOrizzontale();
                std::cout << "Il sottomarino 1 è piazzato\n";
            }
        }
        else if(i == 1)
            {   e2.setType(ShipType::SOTTOMARINO);
                e2.setRigaCentrale(riga_centrale);
                e2.setColonnaCentrale(colonna_centrale);
                if(riga_poppa_int == riga_prua_int)
                {   e2.setOrizzontale();
                    std::cout << "Il sottomarino 2 è piazzato\n";
                }
            }
    }
}

void Tab_dif::delete_ships(){
    int const start_righe = 0, end_righe = 12, start_colonne = 1, end_colonne = 13;
    for(int i = start_righe; i < end_righe; i++)
    {   for(int j = start_colonne; j < end_colonne; j++)
        {   if(matrix[i][j] == " e")
                matrix[i][j] = " ";
            if((j+4) < end_colonne && matrix[i][j] == " c" && matrix[i][j+1] == " c" && matrix[i][j+2] == " c" && matrix[i][j+3] == " c" && matrix[i][j+4] == " c")
            {   matrix[i][j] = matrix[i][j+1] = matrix[i][j+2] = matrix[i][j+3] = matrix[i][j+4] = " ";
            }
            if((i+4) < end_righe && matrix[i][j] == " c" && matrix[i+1][j] == " c" && matrix[i+2][j] == " c" && matrix[i+3][j] == " c" && matrix[i+4][j] == " c")
            {   matrix[i][j] = matrix[i+1][j] = matrix[i+2][j] = matrix[i+3][j] = matrix[i+4][j] = " ";
            }
            if((j+2) < end_colonne && matrix[i][j] == " s" && matrix[i][j+1] == " s" && matrix[i][j+2] == " s")
            {   matrix[i][j] = matrix[i][j+1] = matrix[i][j+2] = " ";
            }
            if((i+2) < end_righe && matrix[i][j] == " s" && matrix[i+1][j] == " s" && matrix[i+2][j] == " s")
            {   matrix[i][j] = matrix[i+1][j] = matrix[i+2][j] = " ";
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
    delete_ships();
}
