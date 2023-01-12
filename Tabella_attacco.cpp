#include <iostream>
#include <vector>
#include "Tabella_attacco.h"

Tab_att::Tab_att()
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

std::string Tab_att::getTab()
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

void Tab_att::clearY()
{   int const start_righe = 0, end_righe = 12;
    int const start_colonne = 1, end_colonne = 13;
    for(int i = start_righe; i < end_righe; i++)
    {   for(int j = start_colonne; j < end_colonne; j++)
        {   if(matrix[i][j] == " Y")
                matrix[i][j] = " ";
        }   
    }
}

void Tab_att::clearXO()
{   int const start_righe = 0, end_righe = 12;
    int const start_colonne = 1, end_colonne = 13;
    for(int i = start_righe; i < end_righe; i++)
    {   for(int j = start_colonne; j < end_colonne; j++)
        {   if(matrix[i][j] == " X" || matrix[i][j] == " O")
                matrix[i][j] = " ";
        }   
    }
}

void Tab_att::insert(int r, int c, std::string s)
{   int const start_righe = 0, end_righe = 12;
    int const start_colonne = 1, end_colonne = 13;
    if(r < start_righe || r > end_righe || c < start_colonne || c > end_colonne)
        throw Invalid_Matrix_Position();
    std::string available_characters = "OYX";
    if(available_characters.find(s) != std::string::npos)
        matrix[r][c] = " " + s;
    else
        throw Invalid_Character();
}
