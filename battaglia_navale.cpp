#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "Tabella_attacco.h"
#include "Tabella_difesa.h"
#include "Ship.h"

class Invalid_comand{};

int main(int argc, char* argv[])
{   if(argc != 2)
        throw Invalid_comand();
    std::string partita = argv[1];
    if(partita != "pc" && partita != "cc")
        throw Invalid_comand();
    if(partita == "pc")
    {   Tab_att a1, a2;
        Tab_dif d1, d2;
        Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
        Ship C1, C2, C3, S1, S2, S3, E1, E2;
        d2.auto_initTab(nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
        std::cout << "\n";
        d1.initTab(C1, C2, C3, S1, S2, S3, E1, E2);
        std::cout << "\n";
        std::cout << "tabelle player:\n";
        std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
        std::cout << "Tabelle pc:\n";
        std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
        const int turni = 30;
        for(int i = 0; i < turni; i++)
        {   
            std::cout << "turno " << i+1 << std::endl;
            std::string possibili_righe = "ABCDEFGHILMN";
        
//azione player
            
            bool finished = true;
            do
            {   std::string selezione = "", bersaglio = "";
                std::cout << "Qual è la prossima mossa?\n";
                std::cin >> selezione;
                std::cin >> bersaglio;
                if(selezione == "XX" && selezione == bersaglio)
                {   std::cout << "Tabella difesa:\n" << d1.getTab() << std::endl;
                    std::cout << "Tabella attacco:\n" << a1.getTab() << std::endl;
                    finished = false;
                }
                else if(selezione == "AA" && selezione == bersaglio)
                {   a1.clearY();
                    finished = false;
                }
                else
                {   std::string riga_selezione = selezione.substr(0,1);
                    int colonna_selezione = std::stoi(selezione.substr(1));
                    Coordinate coord_selezione(riga_selezione, colonna_selezione);
                    std::string riga_bersaglio = bersaglio.substr(0,1);
                    int colonna_bersaglio = std::stoi(bersaglio.substr(1));
                    Coordinate coord_bersaglio(riga_bersaglio, colonna_bersaglio);
                    int riga_selezione_int = coord_selezione.rigaInt(coord_selezione.getRiga()[0]);
                    int riga_bersaglio_int = coord_bersaglio.rigaInt(coord_bersaglio.getRiga()[0]);
                
//controllo che la selezione sia valida
                
                    if(riga_selezione_int != C1.getRigaCentrale() && colonna_selezione != C1.getColonnaCentrale() && riga_selezione_int != C2.getRigaCentrale() && colonna_selezione != C2.getColonnaCentrale() && riga_selezione_int != C3.getRigaCentrale() && colonna_selezione != C3.getColonnaCentrale() && riga_selezione_int != S1.getRigaCentrale() && colonna_selezione != S1.getColonnaCentrale() && riga_selezione_int != S2.getRigaCentrale() && colonna_selezione != S2.getColonnaCentrale() && riga_selezione_int != S3.getRigaCentrale() && colonna_selezione != S3.getColonnaCentrale() && riga_selezione_int != E1.getRigaCentrale() && colonna_selezione != E1.getColonnaCentrale() && riga_selezione_int != E2.getRigaCentrale() && colonna_selezione != E2.getColonnaCentrale())
                    {   std::cout << "Selezione non valida\n";
                        finished = false;
                    }
                
//eseguo azione
                
                    else if(riga_selezione_int == C1.getRigaCentrale() && colonna_selezione == C1.getColonnaCentrale())
                    {   d1.fire(C1, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2);
                        d2.delete_ships();
                    }
                    else if(riga_selezione_int == C2.getRigaCentrale() && colonna_selezione == C2.getColonnaCentrale())
                    {   d1.fire(C2, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2);
                        d2.delete_ships();
                    }
                    else if(riga_selezione_int == C3.getRigaCentrale() && colonna_selezione == C3.getColonnaCentrale())
                    {   d1.fire(C3, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2);
                        d2.delete_ships();
                    }
                    else if(riga_selezione_int == S1.getRigaCentrale() && colonna_selezione == S1.getColonnaCentrale())
                    {   d1.moveAndRepair(S1, riga_bersaglio_int, colonna_bersaglio, d1);
                    }
                    else if(riga_selezione_int == S2.getRigaCentrale() && colonna_selezione == S2.getColonnaCentrale())
                    {   d1.moveAndRepair(S2, riga_bersaglio_int, colonna_bersaglio, d1);
                    }
                    else if(riga_selezione_int == S3.getRigaCentrale() && colonna_selezione == S3.getColonnaCentrale())
                    {   d1.moveAndRepair(S3, riga_bersaglio_int, colonna_bersaglio, d1);
                    }
                    else if(riga_selezione_int == E1.getRigaCentrale() && colonna_selezione == E1.getColonnaCentrale())
                    {   d1.moveAndScan(E1, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2);
                    }
                    else if(riga_selezione_int == E2.getRigaCentrale() && colonna_selezione == E2.getColonnaCentrale())
                    {   d1.moveAndScan(E2, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2);
                    }
                }
            }
            while(!finished);
            
//azione pc
           
           int riga_selezione = 0, colonna_selezione = 0, riga_bersaglio = 0, colonna_bersaglio = 0;
           std::string riga_selezione_string = "", colonna_selezione_string = "", riga_bersaglio_string = "", colonna_bersaglio_string  = "";
           std::vector<std::vector<int>> celle_centrali;
           int colonne_vector = 2, righe_vector = 8, inizio = 0;
           celle_centrali.resize(righe_vector, std::vector<int>(colonne_vector, inizio));
           for(int i = 0; i < righe_vector; i++)
           {    for(int j = 0; j < colonne_vector; j++)
                    celle_centrali[i][j] = 0;
           }
           int dim_vector = 0;
           if(!nave1.IsDestroyed())
           {    celle_centrali[0][0] = nave1.getRigaCentrale();
                celle_centrali[0][1] = nave1.getColonnaCentrale();
                dim_vector = 1;
           }
           if(!nave2.IsDestroyed())
           {    celle_centrali[1][0] = nave2.getRigaCentrale();
                celle_centrali[1][1] = nave2.getColonnaCentrale();
                dim_vector = 2;
           }
           if(!nave3.IsDestroyed())
           {    celle_centrali[2][0] = nave3.getRigaCentrale();
                celle_centrali[2][1] = nave3.getColonnaCentrale();
                dim_vector = 3;
           }
           if(!naves1.IsDestroyed())
           {    celle_centrali[3][0] = naves1.getRigaCentrale();
                celle_centrali[3][1] = naves1.getColonnaCentrale();
                dim_vector = 4;
           }
           if(!naves2.IsDestroyed())
           {    celle_centrali[4][0] = naves2.getRigaCentrale();
                celle_centrali[4][1] = naves2.getColonnaCentrale();
                dim_vector = 5;
           }
           if(!naves3.IsDestroyed())
           {    celle_centrali[5][0] = naves3.getRigaCentrale();
                celle_centrali[5][1] = naves3.getColonnaCentrale();
                dim_vector = 6;
           }
           if(!navesott1.IsDestroyed())
           {    celle_centrali[6][0] = navesott1.getRigaCentrale();
                celle_centrali[6][1] = navesott1.getColonnaCentrale();
                dim_vector = 7;
           }
           if(!navesott2.IsDestroyed())
           {    celle_centrali[7][0] = navesott2.getRigaCentrale();
                celle_centrali[7][1] = navesott2.getColonnaCentrale();
                dim_vector = 8;
           }
           bool ok = false;
           int random_ship;
           do
           {    std::srand(std::time(0));
                random_ship = std::rand() % dim_vector;
                riga_bersaglio = std::rand() % 12;
                colonna_bersaglio = std::rand() % 11 +1;
                if(celle_centrali[random_ship][0] != 0 && celle_centrali[random_ship][1] != 0)
                    ok = true; 
                riga_selezione = celle_centrali[random_ship][0];
                colonna_selezione = celle_centrali[random_ship][1];
                riga_selezione_string = possibili_righe[riga_selezione];
                colonna_selezione_string = std::to_string(colonna_selezione);
                riga_bersaglio_string = possibili_righe[riga_bersaglio];
                colonna_bersaglio_string = std::to_string(colonna_bersaglio);
                if(riga_selezione == nave1.getRigaCentrale() && colonna_selezione == nave1.getColonnaCentrale())
                {   d2.fire(nave1, riga_bersaglio, colonna_bersaglio, d2, a2, d1);
                    d1.delete_ships();
                }
                else if(riga_selezione == nave2.getRigaCentrale() && colonna_selezione == nave2.getColonnaCentrale())
                {   d2.fire(nave2, riga_bersaglio, colonna_bersaglio, d2, a2, d1);
                    d1.delete_ships();
                }
                else if(riga_selezione == nave3.getRigaCentrale() && colonna_selezione == nave3.getColonnaCentrale())
                {   d2.fire(nave3, riga_bersaglio, colonna_bersaglio, d2, a2, d1);
               d1.delete_ships();
                }
                else if(riga_selezione == naves1.getRigaCentrale() && colonna_selezione == naves1.getColonnaCentrale())
                {   if(naves1.getOrizzontale())
                    {   if((colonna_bersaglio+1) < 13 && (colonna_bersaglio-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio, colonna_bersaglio+1) && !d2.isOccupied(riga_bersaglio, colonna_bersaglio-1))
                                d2.moveAndRepair(naves1, riga_bersaglio, colonna_bersaglio, d2);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                    else
                    {   if((riga_bersaglio+1) < 12 && (riga_bersaglio-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio+1, colonna_bersaglio) && !d2.isOccupied(riga_bersaglio-1, colonna_bersaglio))
                                d2.moveAndRepair(naves1, riga_bersaglio, colonna_bersaglio, d2);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                }
                else if(riga_selezione == naves2.getRigaCentrale() && colonna_selezione == naves2.getColonnaCentrale())
                {   if(naves2.getOrizzontale())
                    {   if((colonna_bersaglio+1) < 13 && (colonna_bersaglio-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio, colonna_bersaglio+1) && !d2.isOccupied(riga_bersaglio, colonna_bersaglio-1))
                                d2.moveAndRepair(naves2, riga_bersaglio, colonna_bersaglio, d2);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                    else
                    {   if((riga_bersaglio+1) < 12 && (riga_bersaglio-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio+1, colonna_bersaglio) && !d2.isOccupied(riga_bersaglio-1, colonna_bersaglio))
                                d2.moveAndRepair(naves2, riga_bersaglio, colonna_bersaglio, d2);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                }
                else if(riga_selezione == naves3.getRigaCentrale() && colonna_selezione == naves3.getColonnaCentrale())
                {   if(naves3.getOrizzontale())
                    {   if((colonna_bersaglio+1) < 13 && (colonna_bersaglio-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio, colonna_bersaglio+1) && !d2.isOccupied(riga_bersaglio, colonna_bersaglio-1))
                                d2.moveAndRepair(naves3, riga_bersaglio, colonna_bersaglio, d2);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                    else
                    {   if((riga_bersaglio+1) < 12 && (riga_bersaglio-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio+1, colonna_bersaglio) && !d2.isOccupied(riga_bersaglio-1, colonna_bersaglio))
                                d2.moveAndRepair(naves3, riga_bersaglio, colonna_bersaglio, d2);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                }
                else if(riga_selezione == navesott1.getRigaCentrale() && colonna_selezione == navesott1.getColonnaCentrale())
                {   if(!d2.isOccupied(riga_bersaglio, colonna_bersaglio))
                        d2.moveAndScan(navesott1, riga_bersaglio, colonna_bersaglio, d2, a2, d1);
                    else
                        ok = false;
                }
                else if(riga_selezione == navesott2.getRigaCentrale() && colonna_selezione == navesott2.getColonnaCentrale())
                {   if(!d2.isOccupied(riga_bersaglio, colonna_bersaglio))
                        d2.moveAndScan(navesott2, riga_bersaglio, colonna_bersaglio, d2, a2, d1);
                    else
                        ok = false;
                }
           }
           while(!ok || colonna_bersaglio == 0);
           
           
//verifica azione
           
           std::cout << "azione pc:\n" << riga_selezione_string << colonna_selezione_string << " " << riga_bersaglio_string << colonna_bersaglio_string << std::endl;
            }
            std::cout << "tabelle player:\n";
            std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
            std::cout << "Tabelle pc:\n";
            std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
    }
    else
    {   Tab_att a1, a2;
        Tab_dif d1, d2;
        Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
        Ship C1, C2, C3, S1, S2, S3, E1, E2;
        d2.auto_initTab(nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        d1.auto_initTab(C1, C2, C3, S1, S2, S3, E1, E2);
        std::cout << "\n";
        std::cout << "tabelle pc1:\n";
        std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
        std::cout << "Tabelle pc2:\n";
        std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
        const int turni = 100;
        for(int i = 0; i < turni; i++)
        {   std::string possibili_righe = "ABCDEFGHILMN";
            std::cout << "turno " << i+1 << std::endl;
            int colonne_vector = 2, righe_vector = 8, inizio = 0;

//azione pc1
           
           int riga_selezione1 = 0, colonna_selezione1 = 0, riga_bersaglio1 = 0, colonna_bersaglio1 = 0;
           std::string riga_selezione_string1 = "", colonna_selezione_string1 = "", riga_bersaglio_string1 = "", colonna_bersaglio_string1  = "";
           std::vector<std::vector<int>> celle_centrali1;
           celle_centrali1.resize(righe_vector, std::vector<int>(colonne_vector, inizio));
           for(int i = 0; i < righe_vector; i++)
           {    for(int j = 0; j < colonne_vector; j++)
                    celle_centrali1[i][j] = 0;
           }
           int dim_vector1 = 0;
           if(!C1.IsDestroyed())
           {    celle_centrali1[0][0] = C1.getRigaCentrale();
                celle_centrali1[0][1] = C1.getColonnaCentrale();
                dim_vector1 = 1;
           }
           if(!C2.IsDestroyed())
           {    celle_centrali1[1][0] = C2.getRigaCentrale();
                celle_centrali1[1][1] = C2.getColonnaCentrale();
                dim_vector1 = 2;
           }
           if(!C3.IsDestroyed())
           {    celle_centrali1[2][0] = C3.getRigaCentrale();
                celle_centrali1[2][1] = C3.getColonnaCentrale();
                dim_vector1 = 3;
           }
           if(!S1.IsDestroyed())
           {    celle_centrali1[3][0] = S1.getRigaCentrale();
                celle_centrali1[3][1] = S1.getColonnaCentrale();
                dim_vector1 = 4;
           }
           if(!S2.IsDestroyed())
           {    celle_centrali1[4][0] = S2.getRigaCentrale();
                celle_centrali1[4][1] = S2.getColonnaCentrale();
                dim_vector1 = 5;
           }
           if(!S3.IsDestroyed())
           {    celle_centrali1[5][0] = S3.getRigaCentrale();
                celle_centrali1[5][1] = S3.getColonnaCentrale();
                dim_vector1 = 6;
           }
           if(!E1.IsDestroyed())
           {    celle_centrali1[6][0] = E1.getRigaCentrale();
                celle_centrali1[6][1] = E1.getColonnaCentrale();
                dim_vector1 = 7;
           }
           if(!E2.IsDestroyed())
           {    celle_centrali1[7][0] = E2.getRigaCentrale();
                celle_centrali1[7][1] = E2.getColonnaCentrale();
                dim_vector1 = 8;
           }
           bool ok1 = false;
           int random_ship1;
           do
           {    std::srand(std::time(nullptr));
                random_ship1 = std::rand() % dim_vector1;
                riga_bersaglio1 = std::rand() % 12;
                colonna_bersaglio1 = std::rand() % 11 + 1;
                if(celle_centrali1[random_ship1][0] != 0 && celle_centrali1[random_ship1][1] != 0)
                    ok1 = true;
                riga_selezione1 = celle_centrali1[random_ship1][0];
                colonna_selezione1 = celle_centrali1[random_ship1][1];
                riga_selezione_string1 = possibili_righe[riga_selezione1];
                colonna_selezione_string1 = std::to_string(colonna_selezione1);
                riga_bersaglio_string1 = possibili_righe[riga_bersaglio1];
                colonna_bersaglio_string1 = std::to_string(colonna_bersaglio1);
                std::cout << "azione pc1:\n" << riga_selezione_string1 << colonna_selezione_string1 << " " << riga_bersaglio_string1 << colonna_bersaglio_string1 << std::endl;
                if(riga_selezione1 == C1.getRigaCentrale() && colonna_selezione1 == C1.getColonnaCentrale())
                {   d1.fire(C1, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2);
                    d2.delete_ships();
                }
                else if(riga_selezione1 == C2.getRigaCentrale() && colonna_selezione1 == C2.getColonnaCentrale())
                {   d1.fire(C2, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2);
                    d2.delete_ships();
                }
                else if(riga_selezione1 == C3.getRigaCentrale() && colonna_selezione1 == C3.getColonnaCentrale())
                {   d1.fire(C3, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2);
                    d2.delete_ships();
                }
                else if(riga_selezione1 == C1.getRigaCentrale() && colonna_selezione1 == C1.getColonnaCentrale())
                {   if(C1.getOrizzontale())
                    {   if((colonna_bersaglio1+1) < 13 && (colonna_bersaglio1-1) > 0)
                        {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1+1) && !d1.isOccupied(riga_bersaglio1, colonna_bersaglio1-1))
                                d1.moveAndRepair(C1, riga_bersaglio1, colonna_bersaglio1, d1);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                    else
                    {   if((riga_bersaglio1+1) < 12 && (riga_bersaglio1-1) >= 0)
                        {   if(!d1.isOccupied(riga_bersaglio1+1, colonna_bersaglio1) && !d1.isOccupied(riga_bersaglio1-1, colonna_bersaglio1))
                                d1.moveAndRepair(C1, riga_bersaglio1, colonna_bersaglio1, d1);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                }
                else if(riga_selezione1 == C2.getRigaCentrale() && colonna_selezione1 == C2.getColonnaCentrale())
                {   if(C1.getOrizzontale())
                    {   if((colonna_bersaglio1+1) < 13 && (colonna_bersaglio1-1) > 0)
                        {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1+1) && !d1.isOccupied(riga_bersaglio1, colonna_bersaglio1-1))
                                d1.moveAndRepair(C2, riga_bersaglio1, colonna_bersaglio1, d1);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                    else
                    {   if((riga_bersaglio1+1) < 12 && (riga_bersaglio1-1) >= 0)
                        {   if(!d1.isOccupied(riga_bersaglio1+1, colonna_bersaglio1) && !d1.isOccupied(riga_bersaglio1-1, colonna_bersaglio1))
                                d1.moveAndRepair(C2, riga_bersaglio1, colonna_bersaglio1, d1);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                }
                else if(riga_selezione1 == C3.getRigaCentrale() && colonna_selezione1 == C3.getColonnaCentrale())
                {   if(C1.getOrizzontale())
                    {   if((colonna_bersaglio1+1) < 13 && (colonna_bersaglio1-1) > 0)
                        {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1+1) && !d1.isOccupied(riga_bersaglio1, colonna_bersaglio1-1))
                                d1.moveAndRepair(C3, riga_bersaglio1, colonna_bersaglio1, d1);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                    else
                    {   if((riga_bersaglio1+1) < 12 && (riga_bersaglio1-1) >= 0)
                        {   if(!d1.isOccupied(riga_bersaglio1+1, colonna_bersaglio1) && !d1.isOccupied(riga_bersaglio1-1, colonna_bersaglio1))
                                d1.moveAndRepair(C3, riga_bersaglio1, colonna_bersaglio1, d1);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                }
                else if(riga_selezione1 == E1.getRigaCentrale() && colonna_selezione1 == E1.getColonnaCentrale())
                {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1))
                        d1.moveAndScan(E1, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2);
                    else
                        ok1 = false;
                }
                else if(riga_selezione1 == E2.getRigaCentrale() && colonna_selezione1 == E2.getColonnaCentrale())
                {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1))
                        d1.moveAndScan(E2, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2);
                    else
                        ok1 = false;
                }
           }
           while(!ok1 || colonna_bersaglio1 == 0);
           
           std::this_thread::sleep_for(std::chrono::seconds(1));
           
//azione pc2
           
           int riga_selezione2 = 0, colonna_selezione2 = 0, riga_bersaglio2 = 0, colonna_bersaglio2 = 0;
           std::string riga_selezione_string2 = "", colonna_selezione_string2 = "", riga_bersaglio_string2 = "", colonna_bersaglio_string2  = "";
           std::vector<std::vector<int>> celle_centrali2;
           celle_centrali2.resize(righe_vector, std::vector<int>(colonne_vector, inizio));
           for(int i = 0; i < righe_vector; i++)
           {    for(int j = 0; j < colonne_vector; j++)
                    celle_centrali2[i][j] = 0;
           }
           int dim_vector2 = 0;
           if(!nave1.IsDestroyed())
           {    celle_centrali2[0][0] = nave1.getRigaCentrale();
                celle_centrali2[0][1] = nave1.getColonnaCentrale();
                dim_vector2 = 1;
           }
           if(!nave2.IsDestroyed())
           {    celle_centrali2[1][0] = nave2.getRigaCentrale();
                celle_centrali2[1][1] = nave2.getColonnaCentrale();
                dim_vector2 = 2;
           }
           if(!nave3.IsDestroyed())
           {    celle_centrali2[2][0] = nave3.getRigaCentrale();
                celle_centrali2[2][1] = nave3.getColonnaCentrale();
                dim_vector2 = 3;
           }
           if(!naves1.IsDestroyed())
           {    celle_centrali2[3][0] = naves1.getRigaCentrale();
                celle_centrali2[3][1] = naves1.getColonnaCentrale();
                dim_vector2 = 4;
           }
           if(!naves2.IsDestroyed())
           {    celle_centrali2[4][0] = naves2.getRigaCentrale();
                celle_centrali2[4][1] = naves2.getColonnaCentrale();
                dim_vector2 = 5;
           }
           if(!naves3.IsDestroyed())
           {    celle_centrali2[5][0] = naves3.getRigaCentrale();
                celle_centrali2[5][1] = naves3.getColonnaCentrale();
                dim_vector2 = 6;
           }
           if(!navesott1.IsDestroyed())
           {    celle_centrali2[6][0] = navesott1.getRigaCentrale();
                celle_centrali2[6][1] = navesott1.getColonnaCentrale();
                dim_vector2 = 7;
           }
           if(!navesott2.IsDestroyed())
           {    celle_centrali2[7][0] = navesott2.getRigaCentrale();
                celle_centrali2[7][1] = navesott2.getColonnaCentrale();
                dim_vector2 = 8;
           }
           bool ok2 = false;
           int random_ship2;
           do
           {    std::srand(std::time(nullptr));
                random_ship2 = std::rand() % dim_vector1;
                riga_bersaglio2 = std::rand() % 12;
                colonna_bersaglio2 = std::rand() % 11 +1;
                if(celle_centrali2[random_ship2][0] != 0 && celle_centrali2[random_ship2][1] != 0)
                    ok2 = true;
                riga_selezione2 = celle_centrali2[random_ship2][0];
                colonna_selezione2 = celle_centrali2[random_ship2][1];
                riga_selezione_string2 = possibili_righe[riga_selezione2];
                colonna_selezione_string2 = std::to_string(colonna_selezione2);
                riga_bersaglio_string2 = possibili_righe[riga_bersaglio2];
                colonna_bersaglio_string2 = std::to_string(colonna_bersaglio2);
                std::cout << "azione pc2:\n" << riga_selezione_string2 << colonna_selezione_string2 << " " << riga_bersaglio_string2 << colonna_bersaglio_string2 << std::endl;
                if(riga_selezione2 == nave1.getRigaCentrale() && colonna_selezione2 == nave1.getColonnaCentrale())
                {   d2.fire(nave1, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1);
               d1.delete_ships();
                }
                else if(riga_selezione2 == nave2.getRigaCentrale() && colonna_selezione2 == nave2.getColonnaCentrale())
                {   d2.fire(nave2, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1);
               d1.delete_ships();
                }
                else if(riga_selezione2 == nave3.getRigaCentrale() && colonna_selezione2 == nave3.getColonnaCentrale())
                {   d2.fire(nave3, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1);
                    d1.delete_ships();
                }
                else if(riga_selezione2 == naves1.getRigaCentrale() && colonna_selezione2 == naves1.getColonnaCentrale())
                {   if(naves1.getOrizzontale())
                    {   if((colonna_bersaglio2+1) < 13 && (colonna_bersaglio2-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio2, colonna_bersaglio2+1) && !d2.isOccupied(riga_bersaglio2, colonna_bersaglio2-1))
                                d2.moveAndRepair(naves1, riga_bersaglio2, colonna_bersaglio2, d2);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                    else
                    {   if((riga_bersaglio2+1) < 12 && (riga_bersaglio2-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio2+1, colonna_bersaglio2) && !d2.isOccupied(riga_bersaglio2-1, colonna_bersaglio2))
                                d2.moveAndRepair(naves1, riga_bersaglio2, colonna_bersaglio2, d2);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                }
                else if(riga_selezione2 == naves2.getRigaCentrale() && colonna_selezione2 == naves2.getColonnaCentrale())
                {   if(naves2.getOrizzontale())
                    {   if((colonna_bersaglio2+1) < 13 && (colonna_bersaglio2-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio2, colonna_bersaglio2+1) && !d2.isOccupied(riga_bersaglio2, colonna_bersaglio2-1))
                                d2.moveAndRepair(naves2, riga_bersaglio2, colonna_bersaglio2, d2);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                    else
                    {   if((riga_bersaglio2+1) < 12 && (riga_bersaglio2-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio2+1, colonna_bersaglio2) && !d2.isOccupied(riga_bersaglio2-1, colonna_bersaglio2))
                                d2.moveAndRepair(naves2, riga_bersaglio2, colonna_bersaglio2, d2);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                }
                else if(riga_selezione2 == naves3.getRigaCentrale() && colonna_selezione2 == naves3.getColonnaCentrale())
                {   if(naves3.getOrizzontale())
                    {   if((colonna_bersaglio2+1) < 13 && (colonna_bersaglio2-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio2, colonna_bersaglio2+1) && !d2.isOccupied(riga_bersaglio2, colonna_bersaglio2-1))
                                d2.moveAndRepair(naves3, riga_bersaglio2, colonna_bersaglio2, d2);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                    else
                    {   if((riga_bersaglio2+1) < 12 && (riga_bersaglio2-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio2+1, colonna_bersaglio2) && !d2.isOccupied(riga_bersaglio2-1, colonna_bersaglio2))
                                d2.moveAndRepair(naves3, riga_bersaglio2, colonna_bersaglio2, d2);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                }
                else if(riga_selezione2 == navesott1.getRigaCentrale() && colonna_selezione2 == navesott1.getColonnaCentrale())
                {   if(!d2.isOccupied(riga_bersaglio2, colonna_bersaglio2))
                        d2.moveAndScan(navesott1, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1);
                    else
                        ok2 = false;
                }
                else if(riga_selezione2 == navesott2.getRigaCentrale() && colonna_selezione2 == navesott2.getColonnaCentrale())
                {   if(!d2.isOccupied(riga_bersaglio2, colonna_bersaglio2))
                        d2.moveAndScan(navesott2, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1);
                    else
                        ok2 = false;
                }
           }
           while(!ok2 || colonna_bersaglio2 == 0);

//verifica azione
           std::cout << "tabelle pc1:\n";
           std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
           std::cout << "Tabelle pc2:\n";
           std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
        }
    }
}