//De Maria Giovanni
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>

#include "Tabella_attacco.h"
#include "Tabella_difesa.h"
#include "Ship.h"

//creo una classe per segnalare l'invalidita' del comando

class Invalid_comand{};

int main(int argc, char* argv[])
{ 
  
//controllo la validita' degli argomenti passati da riga di comando
    
    if(argc != 2)
        throw Invalid_comand();
    std::string partita = argv[1];
    if(partita != "pc" && partita != "cc")
        throw Invalid_comand();
        
//partita player vs pc
        
    if(partita == "pc")
    {   

//creo le tabelle e le navi necessarie per la partita e il file per il log della partita
        
        Tab_att a1, a2;
        Tab_dif d1, d2;
        Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
        Ship C1, C2, C3, S1, S2, S3, E1, E2;
        std::ofstream file("log_pc.txt");
        
//inizializzo le due tabelle di difesa e imposto il numero massimo di turni
        
        d1.initTab(C1, C2, C3, S1, S2, S3, E1, E2, file);
        std::cout << "\n";
        d2.auto_initTab(nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2, file);
        std::cout << "\n";
        std::cout << "tabelle player:\n";
        std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
        const int turni = 50;
        
//inizio un ciclo con durata massima di turni = turni
        
        for(int i = 0; i < turni; i++)
        {   
            std::cout << "turno " << i+1 << std::endl;
            std::string possibili_righe = "ABCDEFGHILMN";
        
//azione player
            
            std::string azione_player = "";
            std::string selezione = "", bersaglio = "";
            
//faccio un do while per ripetere l'azione se vengono scritti i comandi speciali
            
            bool finished = true;
            do
            {   finished = true;
                std::cout << "Qual e' la prossima mossa?\n";
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
                
//divido in coordinate selezione e bersaglio l'azione digitata, con coordinate selezione le coordinate del centro di una nave alleata e coordinate bersaglio una coordinata della propria tabella, nel caso delle azioni di move and repair o di move and scan, o della tabella avversaria nel caso del fire
                
                else
                {   std::string riga_selezione = selezione.substr(0,1);
                    int colonna_selezione = std::stoi(selezione.substr(1));
                    Coordinate coord_selezione(riga_selezione, colonna_selezione);
                    std::string riga_bersaglio = bersaglio.substr(0,1);
                    int colonna_bersaglio = std::stoi(bersaglio.substr(1));
                    Coordinate coord_bersaglio(riga_bersaglio, colonna_bersaglio);
                    int riga_selezione_int = coord_selezione.rigaInt(coord_selezione.getRiga()[0]);
                    int riga_bersaglio_int = coord_bersaglio.rigaInt(coord_bersaglio.getRiga()[0]);  
                
//eseguo azione in base alla nave selezionata
                
                    if(riga_selezione_int == C1.getRigaCentrale() && colonna_selezione == C1.getColonnaCentrale())
                    {   d1.fire(C1, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2, nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
                        d2.delete_ship(nave1);
                        d2.delete_ship(nave2);
                        d2.delete_ship(nave3);
                        d2.delete_ship(naves1);
                        d2.delete_ship(naves2);
                        d2.delete_ship(naves3);
                        d2.delete_ship(navesott1);
                        d2.delete_ship(navesott2);
                    }
                    else if(riga_selezione_int == C2.getRigaCentrale() && colonna_selezione == C2.getColonnaCentrale())
                    {   d1.fire(C2, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2, nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
                        d2.delete_ship(nave1);
                        d2.delete_ship(nave2);
                        d2.delete_ship(nave3);
                        d2.delete_ship(naves1);
                        d2.delete_ship(naves2);
                        d2.delete_ship(naves3);
                        d2.delete_ship(navesott1);
                        d2.delete_ship(navesott2);
                    }
                    else if(riga_selezione_int == C3.getRigaCentrale() && colonna_selezione == C3.getColonnaCentrale())
                    {   d1.fire(C3, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2, nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
                        d2.delete_ship(nave1);
                        d2.delete_ship(nave2);
                        d2.delete_ship(nave3);
                        d2.delete_ship(naves1);
                        d2.delete_ship(naves2);
                        d2.delete_ship(naves3);
                        d2.delete_ship(navesott1);
                        d2.delete_ship(navesott2);
                    }
                    else if(riga_selezione_int == S1.getRigaCentrale() && colonna_selezione == S1.getColonnaCentrale())
                    {   d1.moveAndRepair(S1, riga_bersaglio_int, colonna_bersaglio, d1, C1, C2, C3, S2, S3);
                    }
                    else if(riga_selezione_int == S2.getRigaCentrale() && colonna_selezione == S2.getColonnaCentrale())
                    {   d1.moveAndRepair(S2, riga_bersaglio_int, colonna_bersaglio, d1, C1, C2, C3, S1, S3);
                    }
                    else if(riga_selezione_int == S3.getRigaCentrale() && colonna_selezione == S3.getColonnaCentrale())
                    {   d1.moveAndRepair(S3, riga_bersaglio_int, colonna_bersaglio, d1, C1, C2, C3, S1, S2);
                    }
                    else if(riga_selezione_int == E1.getRigaCentrale() && colonna_selezione == E1.getColonnaCentrale())
                    {   d1.moveAndScan(E1, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2);
                    }
                    else if(riga_selezione_int == E2.getRigaCentrale() && colonna_selezione == E2.getColonnaCentrale())
                    {   d1.moveAndScan(E2, riga_bersaglio_int, colonna_bersaglio, d1, a1, d2);
                    }
                    
//controllo che la selezione sia valida, se non lo e' si fa ripetere la scrittura dell'azione
                    
                    else
                    {   std::cout << "Selezione non valida\n";
                        finished = false;
                    }
                }
            }
            while(!finished);
            
//faccio diventare la lettera delle coordinate inserite maiuscola e scrivo l'azione appena eseguita nel file dii log
            
            std::transform(selezione.begin(), selezione.end(), selezione.begin(), ::toupper);
            std::transform(bersaglio.begin(), bersaglio.end(), bersaglio.begin(), ::toupper);
            azione_player = selezione + " " + bersaglio;
            file << azione_player << std::endl;
            
//controllo che le navi avversarie non siano distrutte, se lo sono la partita finisce e viene data la vittoria al player
            
            if(nave1.IsDestroyed() && nave2.IsDestroyed() && nave3.IsDestroyed() && naves1.IsDestroyed() && naves2.IsDestroyed() && naves3.IsDestroyed() && navesott1.IsDestroyed() && navesott2.IsDestroyed())
            {   std::cout << "il player vince" << std::endl;
                break;
            }
            
//azione pc
           
           int riga_selezione = 0, colonna_selezione = 0, riga_bersaglio = 0, colonna_bersaglio = 0;
           std::string riga_selezione_string = "", colonna_selezione_string = "", riga_bersaglio_string = "", colonna_bersaglio_string  = "";
           std::string azione_pc = "";
           
//creo un vettore con tutte le coordinate centrali delle navi del pc
           
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
           
//faccio scegliere una coordinata bersaglio a caso al pc tra quelle appena inserite nel vettore e delle coordinate bersaglio random valide
           
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
                
//eseguo l'azione in base alle coordinate scelte
                
                if(riga_selezione == nave1.getRigaCentrale() && colonna_selezione == nave1.getColonnaCentrale())
                {   d2.fire(nave1, riga_bersaglio, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                    d1.delete_ship(C1);
                    d1.delete_ship(C2);
                    d1.delete_ship(C3);
                    d1.delete_ship(S1);
                    d1.delete_ship(S2);
                    d1.delete_ship(S3);
                    d1.delete_ship(E1);
                    d1.delete_ship(E2);
                }
                else if(riga_selezione == nave2.getRigaCentrale() && colonna_selezione == nave2.getColonnaCentrale())
                {   d2.fire(nave2, riga_bersaglio, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                    d1.delete_ship(C1);
                    d1.delete_ship(C2);
                    d1.delete_ship(C3);
                    d1.delete_ship(S1);
                    d1.delete_ship(S2);
                    d1.delete_ship(S3);
                    d1.delete_ship(E1);
                    d1.delete_ship(E2);
                }
                else if(riga_selezione == nave3.getRigaCentrale() && colonna_selezione == nave3.getColonnaCentrale())
                {   d2.fire(nave3, riga_bersaglio, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                    d1.delete_ship(C1);
                    d1.delete_ship(C2);
                    d1.delete_ship(C3);
                    d1.delete_ship(S1);
                    d1.delete_ship(S2);
                    d1.delete_ship(S3);
                    d1.delete_ship(E1);
                    d1.delete_ship(E2);
                }
                
//controllo che la nave di supporto e il sottomarino siano in una posizione valida se dovessero eseguire lo spostamento e se non lo sono faccio ripetere la selezione random delle coordinate
                
                else if(riga_selezione == naves1.getRigaCentrale() && colonna_selezione == naves1.getColonnaCentrale())
                {   if(naves1.getOrizzontale())
                    {   if((colonna_bersaglio+1) < 13 && (colonna_bersaglio-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio, colonna_bersaglio+1) && !d2.isOccupied(riga_bersaglio, colonna_bersaglio-1))
                                d2.moveAndRepair(naves1, riga_bersaglio, colonna_bersaglio, d2, nave1, nave2, nave3, naves2, naves3);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                    else
                    {   if((riga_bersaglio+1) < 12 && (riga_bersaglio-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio+1, colonna_bersaglio) && !d2.isOccupied(riga_bersaglio-1, colonna_bersaglio))
                                d2.moveAndRepair(naves1, riga_bersaglio, colonna_bersaglio, d2, nave1, nave2, nave3, naves2, naves3);
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
                                d2.moveAndRepair(naves2, riga_bersaglio, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves3);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                    else
                    {   if((riga_bersaglio+1) < 12 && (riga_bersaglio-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio+1, colonna_bersaglio) && !d2.isOccupied(riga_bersaglio-1, colonna_bersaglio))
                                d2.moveAndRepair(naves2, riga_bersaglio, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves3);
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
                                d2.moveAndRepair(naves3, riga_bersaglio, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves2);
                            else
                                ok = false;
                        }
                        else
                            ok = false;
                    }
                    else
                    {   if((riga_bersaglio+1) < 12 && (riga_bersaglio-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio+1, colonna_bersaglio) && !d2.isOccupied(riga_bersaglio-1, colonna_bersaglio))
                                d2.moveAndRepair(naves3, riga_bersaglio, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves2);
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
           
//scrivo l'azione appena compiuta nel file di log
           
           azione_pc = riga_selezione_string + colonna_selezione_string + " " + riga_bersaglio_string + colonna_bersaglio_string;
           file << azione_pc << std::endl;
           std::cout << "turno 1 pc:\n" << azione_pc << std::endl;
           
//controllo l'integrita' delle navi del player, se sono tutte distrutte interrompo e il pc ha vinto
           
           if(C1.IsDestroyed() && C2.IsDestroyed() && C3.IsDestroyed() && S1.IsDestroyed() && S2.IsDestroyed() && S3.IsDestroyed() && E1.IsDestroyed() && E2.IsDestroyed())
            {   std::cout << "il pc vince" << std::endl;
                break;
            }
       }
       
//finita la partita mostro tutte le 4 tabelle e chiudo il file di log
       
           std::cout << "tabelle player:\n";
           std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
           std::cout << "Tabelle pc:\n";
           std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
           file.close();
    }
    
//pc vs pc
    
    else
    {   
    
//creo le tabelle e le navi dei due pc e apro il file di log, uso std::this_thread::sleep_for() per far scegliere due azioni diverse ai due pc e imposto il numero di turni massimi
    
        Tab_att a1, a2;
        Tab_dif d1, d2;
        Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
        Ship C1, C2, C3, S1, S2, S3, E1, E2;
        std::ofstream file("log_cc.txt");
        d1.auto_initTab(C1, C2, C3, S1, S2, S3, E1, E2, file);
        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        d2.auto_initTab(nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2, file);
        std::cout << "\n";
        std::cout << "tabelle pc1:\n";
        std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
        std::cout << "Tabelle pc2:\n";
        std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
        const int turni = 50; //numero di turni massimi
        for(int i = 0; i < turni; i++)
        {   std::string possibili_righe = "ABCDEFGHILMN";
            std::cout << "turno " << i+1 << std::endl;
            int colonne_vector = 2, righe_vector = 8, inizio = 0;

//azione pc1
           
           int riga_selezione1 = 0, colonna_selezione1 = 0, riga_bersaglio1 = 0, colonna_bersaglio1 = 0;
           std::string riga_selezione_string1 = "", colonna_selezione_string1 = "", riga_bersaglio_string1 = "", colonna_bersaglio_string1  = "";
           std::string azione_pc1 = "";
           
//creo un vector con le celle centrali delle navi di pc1
           
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
           
//faccio selezionare una azione valida a caso al pc, il do while viene eseguito finche' non viene selezionata un'azione valida
           
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
                
//stampo a video l'azione e la eseguo con i dovuti controlli per ogni tipo di azione
                
                std::cout << "azione pc1:\n" << riga_selezione_string1 << colonna_selezione_string1 << " " << riga_bersaglio_string1 << colonna_bersaglio_string1 << std::endl;
                if(riga_selezione1 == C1.getRigaCentrale() && colonna_selezione1 == C1.getColonnaCentrale())
                {   d1.fire(C1, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2, nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
                    d2.delete_ship(nave1);
                    d2.delete_ship(nave2);
                    d2.delete_ship(nave3);
                    d2.delete_ship(naves1);
                    d2.delete_ship(naves2);
                    d2.delete_ship(naves3);
                    d2.delete_ship(navesott1);
                    d2.delete_ship(navesott2);
                }
                else if(riga_selezione1 == C2.getRigaCentrale() && colonna_selezione1 == C2.getColonnaCentrale())
                {   d1.fire(C2, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2, nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
                    d2.delete_ship(nave1);
                    d2.delete_ship(nave2);
                    d2.delete_ship(nave3);
                    d2.delete_ship(naves1);
                    d2.delete_ship(naves2);
                    d2.delete_ship(naves3);
                    d2.delete_ship(navesott1);
                    d2.delete_ship(navesott2);
                }
                else if(riga_selezione1 == C3.getRigaCentrale() && colonna_selezione1 == C3.getColonnaCentrale())
                {   d1.fire(C3, riga_bersaglio1, colonna_bersaglio1, d1, a1, d2, nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2);
                    d2.delete_ship(nave1);
                    d2.delete_ship(nave2);
                    d2.delete_ship(nave3);
                    d2.delete_ship(naves1);
                    d2.delete_ship(naves2);
                    d2.delete_ship(naves3);
                    d2.delete_ship(navesott1);
                    d2.delete_ship(navesott2);
                }
                else if(riga_selezione1 == S1.getRigaCentrale() && colonna_selezione1 == S1.getColonnaCentrale())
                {   if(S1.getOrizzontale())
                    {   if((colonna_bersaglio1+1) < 13 && (colonna_bersaglio1-1) > 0)
                        {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1+1) && !d1.isOccupied(riga_bersaglio1, colonna_bersaglio1-1))
                                d1.moveAndRepair(S1, riga_bersaglio1, colonna_bersaglio1, d1, C1, C2, C3, S2, S3);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                    else
                    {   if((riga_bersaglio1+1) < 12 && (riga_bersaglio1-1) >= 0)
                        {   if(!d1.isOccupied(riga_bersaglio1+1, colonna_bersaglio1) && !d1.isOccupied(riga_bersaglio1-1, colonna_bersaglio1))
                                d1.moveAndRepair(S1, riga_bersaglio1, colonna_bersaglio1, d1, C1, C2, C3, S2, S3);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                }
                else if(riga_selezione1 == S2.getRigaCentrale() && colonna_selezione1 == S2.getColonnaCentrale())
                {   if(S2.getOrizzontale())
                    {   if((colonna_bersaglio1+1) < 13 && (colonna_bersaglio1-1) > 0)
                        {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1+1) && !d1.isOccupied(riga_bersaglio1, colonna_bersaglio1-1))
                                d1.moveAndRepair(S2, riga_bersaglio1, colonna_bersaglio1, d1, C1, C2, C3, S1, S3);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                    else
                    {   if((riga_bersaglio1+1) < 12 && (riga_bersaglio1-1) >= 0)
                        {   if(!d1.isOccupied(riga_bersaglio1+1, colonna_bersaglio1) && !d1.isOccupied(riga_bersaglio1-1, colonna_bersaglio1))
                                d1.moveAndRepair(S2, riga_bersaglio1, colonna_bersaglio1, d1, C1, C2, C3, S1, S3);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                }
                else if(riga_selezione1 == S3.getRigaCentrale() && colonna_selezione1 == S3.getColonnaCentrale())
                {   if(S3.getOrizzontale())
                    {   if((colonna_bersaglio1+1) < 13 && (colonna_bersaglio1-1) > 0)
                        {   if(!d1.isOccupied(riga_bersaglio1, colonna_bersaglio1+1) && !d1.isOccupied(riga_bersaglio1, colonna_bersaglio1-1))
                                d1.moveAndRepair(S3, riga_bersaglio1, colonna_bersaglio1, d1, C1, C2, C3, S1, S2);
                            else
                                ok1 = false;
                        }
                        else
                            ok1 = false;
                    }
                    else
                    {   if((riga_bersaglio1+1) < 12 && (riga_bersaglio1-1) >= 0)
                        {   if(!d1.isOccupied(riga_bersaglio1+1, colonna_bersaglio1) && !d1.isOccupied(riga_bersaglio1-1, colonna_bersaglio1))
                                d1.moveAndRepair(S3, riga_bersaglio1, colonna_bersaglio1, d1, C1, C2, C3, S1, S2);
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
                
//aggiungo una pausa di un secondo cosi' se l'azione non e' valida il omputer ne seleziona un'altra e non la stessa per la durata di un secondo, il problema si sarebbe visto nella stampa a video dell'azione
                
                std::this_thread::sleep_for(std::chrono::seconds(1));
           }
           while(!ok1 || colonna_bersaglio1 == 0);
           
//scrivo l'azione eseguita nel file di log e se pc1 ha vinto faccio terminare e stampo a video il pc1 vince
           
           azione_pc1 = riga_selezione_string1 + colonna_selezione_string1 + " " + riga_bersaglio_string1 + colonna_bersaglio_string1;
           file << azione_pc1 << std::endl;
           if(nave1.IsDestroyed() && nave2.IsDestroyed() && nave3.IsDestroyed() && naves1.IsDestroyed() && naves2.IsDestroyed() && naves3.IsDestroyed() && navesott1.IsDestroyed() && navesott2.IsDestroyed())
            {   std::cout << "il pc1 vince" << std::endl;
                break;
            }
           
//stesso utilizzo della funzione seguente adottato durante l'inizializzazione delle navi
           
           std::this_thread::sleep_for(std::chrono::seconds(1));
           
//azione pc2 con gli stessi passaggi di pc1
           
           int riga_selezione2 = 0, colonna_selezione2 = 0, riga_bersaglio2 = 0, colonna_bersaglio2 = 0;
           std::string riga_selezione_string2 = "", colonna_selezione_string2 = "", riga_bersaglio_string2 = "", colonna_bersaglio_string2  = "";
           std::string azione_pc2 = "";
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
                {   d2.fire(nave1, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                    d1.delete_ship(C1);
                    d1.delete_ship(C2);
                    d1.delete_ship(C3);
                    d1.delete_ship(S1);
                    d1.delete_ship(S2);
                    d1.delete_ship(S3);
                    d1.delete_ship(E1);
                    d1.delete_ship(E2);
                }
                else if(riga_selezione2 == nave2.getRigaCentrale() && colonna_selezione2 == nave2.getColonnaCentrale())
                {   d2.fire(nave2, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                    d1.delete_ship(C1);
                    d1.delete_ship(C2);
                    d1.delete_ship(C3);
                    d1.delete_ship(S1);
                    d1.delete_ship(S2);
                    d1.delete_ship(S3);
                    d1.delete_ship(E1);
                    d1.delete_ship(E2);
                }
                else if(riga_selezione2 == nave3.getRigaCentrale() && colonna_selezione2 == nave3.getColonnaCentrale())
                {   d2.fire(nave3, riga_bersaglio2, colonna_bersaglio2, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                    d1.delete_ship(C1);
                    d1.delete_ship(C2);
                    d1.delete_ship(C3);
                    d1.delete_ship(S1);
                    d1.delete_ship(S2);
                    d1.delete_ship(S3);
                    d1.delete_ship(E1);
                    d1.delete_ship(E2);
                }
                else if(riga_selezione2 == naves1.getRigaCentrale() && colonna_selezione2 == naves1.getColonnaCentrale())
                {   if(naves1.getOrizzontale())
                    {   if((colonna_bersaglio2+1) < 13 && (colonna_bersaglio2-1) > 0)
                        {   if(!d2.isOccupied(riga_bersaglio2, colonna_bersaglio2+1) && !d2.isOccupied(riga_bersaglio2, colonna_bersaglio2-1))
                                d2.moveAndRepair(naves1, riga_bersaglio2, colonna_bersaglio2, d2, nave1, nave2, nave3, naves2, naves3);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                    else
                    {   if((riga_bersaglio2+1) < 12 && (riga_bersaglio2-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio2+1, colonna_bersaglio2) && !d2.isOccupied(riga_bersaglio2-1, colonna_bersaglio2))
                                d2.moveAndRepair(naves1, riga_bersaglio2, colonna_bersaglio2, d2, nave1, nave2, nave3, naves2, naves3);
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
                                d2.moveAndRepair(naves2, riga_bersaglio2, colonna_bersaglio2, d2, nave1, nave2, nave3, naves1,  naves3);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                    else
                    {   if((riga_bersaglio2+1) < 12 && (riga_bersaglio2-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio2+1, colonna_bersaglio2) && !d2.isOccupied(riga_bersaglio2-1, colonna_bersaglio2))
                                d2.moveAndRepair(naves2, riga_bersaglio2, colonna_bersaglio2, d2, nave1, nave2, nave3, naves1,  naves3);
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
                                d2.moveAndRepair(naves3, riga_bersaglio2, colonna_bersaglio2, d2, nave1, nave2, nave3, naves1, naves2);
                            else
                                ok2 = false;
                        }
                        else
                            ok2 = false;
                    }
                    else
                    {   if((riga_bersaglio2+1) < 12 && (riga_bersaglio2-1) >= 0)
                        {   if(!d2.isOccupied(riga_bersaglio2+1, colonna_bersaglio2) && !d2.isOccupied(riga_bersaglio2-1, colonna_bersaglio2))
                                d2.moveAndRepair(naves3, riga_bersaglio2, colonna_bersaglio2, d2, nave1, nave2, nave3, naves1, naves2);
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
                std::this_thread::sleep_for(std::chrono::seconds(1));
           }
           while(!ok2 || colonna_bersaglio2 == 0);
           azione_pc2 = riga_selezione_string2 + colonna_selezione_string2 + " " + riga_bersaglio_string2 + colonna_bersaglio_string2;
           file << azione_pc2 << std::endl;
           if(C1.IsDestroyed() && C2.IsDestroyed() && C3.IsDestroyed() && S1.IsDestroyed() && S2.IsDestroyed() && S3.IsDestroyed() && E1.IsDestroyed() && E2.IsDestroyed())
            {   std::cout << "il pc2 vince" << std::endl;
                break;
            }
    
        }

//stampo a video le tabelle finali e chiudo il file di log

           std::cout << "tabelle pc1:\n";
           std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
           std::cout << "Tabelle pc2:\n";
           std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
           file.close();
        }
    }

