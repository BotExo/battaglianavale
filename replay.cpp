//Marco Bettin
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <sstream>

#include "Tabella_attacco.h"
#include "Tabella_difesa.h"
#include "Ship.h"

//creo una classe per segnalare l'invalidita' del comando inserito da riga di comando

class Invalid_comand{};

int main(int argc, char* argv[])
{   

//controllo la validita' degli argomenti inseriti da riga di comando

    if(argc != 3 && argc != 4)
        throw Invalid_comand();
    std::string modalita = argv[1];
    if((modalita != "v" && modalita != "f") || (argc != 3 && modalita == "v") || (argc != 4 && modalita == "f"))
        throw Invalid_comand();
   
//replay in modalita' v, cioe' stampando a video
        
    if(modalita == "v")
    {   
        
//creo le tabelle e le navi, oltre a salvare il nome del file di log in una stringa e ad aprirlo
        
        std::string nome_file_log = argv[2];
        Tab_att a1, a2;
        Tab_dif d1, d2;
        Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
        Ship C1, C2, C3, S1, S2, S3, E1, E2;
        const int coraz = 3;
        const int supp = 3;
        const int sott = 2;
        const int dim_coraz = 5, h_coraz = 5;
        const int dim_supp = 3, h_supp = 3;
        const int dim_sott = 1, h_sott = 1;
        std::ifstream file(nome_file_log);
        
//eseguo azioni finche' il file dii log ha righe
        
        std::string comand = "";
        int lines_counter = 0;
        while(std::getline(file, comand))
        {   
        
//turno p1 
//eseguo i comandi delle prime otto righe che sono di inizializzazione delle navi del p1
        
            if(lines_counter < 8 || (lines_counter > 15 && lines_counter % 2 == 0))
            {   std::string selezione = "", bersaglio = "";
                std::stringstream ss(comand);
                ss >> selezione;
                ss >> bersaglio;
                
//stampo l'azione a video
                
                std::cout << "turno p1: " << selezione << " " << bersaglio << std::endl;
                
//le prime 3 righe creano le corazzate di p1
                
                if(lines_counter < 3)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d1.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "C", dim_coraz);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 0)
                    {   C1.setType(ShipType::CORAZZATA);
                        C1.setRigaCentrale(riga_centrale);
                        C1.setColonnaCentrale(colonna_centrale);
                        C1.setCelleOccupate(celle_occupate_tmp);
                        C1.setHealth(h_coraz);
                        if(riga_poppa_int == riga_prua_int)
                        {   C1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 1)
                        {   C2.setType(ShipType::CORAZZATA);
                            C2.setRigaCentrale(riga_centrale);
                            C2.setColonnaCentrale(colonna_centrale);
                            C2.setCelleOccupate(celle_occupate_tmp);
                            C2.setHealth(h_coraz);
                            if(riga_poppa_int == riga_prua_int)
                            {   C2.setOrizzontale();

                            }
                        } 
                        else if(lines_counter == 2)
                            {   C3.setType(ShipType::CORAZZATA);
                                C3.setRigaCentrale(riga_centrale);
                                C3.setColonnaCentrale(colonna_centrale);
                                C3.setCelleOccupate(celle_occupate_tmp);
                                C3.setHealth(h_coraz);
                                if(riga_poppa_int == riga_prua_int)
                                {   C3.setOrizzontale();

                                }
                            }
                }
                
//le successive 3 righe creano le navi da supporto di p1
                
                if(lines_counter >= 3 && lines_counter < 6)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d1.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "S", dim_supp);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 3)
                    {   S1.setType(ShipType::NAVE_SUPPORTO);
                        S1.setRigaCentrale(riga_centrale);
                        S1.setColonnaCentrale(colonna_centrale);
                        S1.setCelleOccupate(celle_occupate_tmp);
                        S1.SetSize(dim_supp);
                        S1.setHealth(h_supp);
                        if(riga_poppa_int == riga_prua_int)
                        {   S1.setOrizzontale();

                        }
                    } 
                    else if(lines_counter == 4)
                        {   S2.setType(ShipType::NAVE_SUPPORTO);
                            S2.setRigaCentrale(riga_centrale);
                            S2.setColonnaCentrale(colonna_centrale);
                            S2.setCelleOccupate(celle_occupate_tmp);
                            S2.SetSize(dim_supp);
                            S2.setHealth(h_supp);
                            if(riga_poppa_int == riga_prua_int)
                            {   S2.setOrizzontale();

                            }
                        } 
                        else if(lines_counter == 5)
                            {   S3.setType(ShipType::NAVE_SUPPORTO);
                                S3.setRigaCentrale(riga_centrale);
                                S3.setColonnaCentrale(colonna_centrale);
                                S3.setCelleOccupate(celle_occupate_tmp);
                                S3.SetSize(dim_supp);
                                S3.setHealth(h_supp);
                                if(riga_poppa_int == riga_prua_int)
                                {   S3.setOrizzontale();

                                }
                            }
                }
                
//le righe di indice 6 e 7 creano i sottomarini di p1
                
                if(lines_counter >= 6 && lines_counter < 8)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d1.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "E", dim_sott);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    riga_centrale = riga_poppa_int;
                    colonna_centrale = coord_poppa.getColonna();
                    if(lines_counter == 6)
                    {   E1.setType(ShipType::SOTTOMARINO);
                        E1.setRigaCentrale(riga_centrale);
                        E1.setColonnaCentrale(colonna_centrale);
                        E1.setCelleOccupate(celle_occupate_tmp);
                        E1.SetSize(dim_sott);
                        E1.setHealth(h_sott);
                        if(riga_poppa_int == riga_prua_int)
                        {   E1.setOrizzontale();

                        }
                    } 
                    else if(lines_counter == 7)
                        {   E2.setType(ShipType::SOTTOMARINO);
                            E2.setRigaCentrale(riga_centrale);
                            E2.setColonnaCentrale(colonna_centrale);
                            E2.setCelleOccupate(celle_occupate_tmp);
                            E2.SetSize(dim_sott);
                            E2.setHealth(h_sott);
                            if(riga_poppa_int == riga_prua_int)
                            {   E2.setOrizzontale();

                            }
                        } 
                }
                
//le righe con indice pari dopo la riga 15 sono le azioni di pc1
                
                else
                {   std::string riga_selezione = selezione.substr(0,1);
                    int colonna_selezione = std::stoi(selezione.substr(1));
                    Coordinate coord_selezione(riga_selezione, colonna_selezione);
                    std::string riga_bersaglio = bersaglio.substr(0,1);
                    int colonna_bersaglio = std::stoi(bersaglio.substr(1));
                    Coordinate coord_bersaglio(riga_bersaglio, colonna_bersaglio);
                    int riga_selezione_int = coord_selezione.rigaInt(coord_selezione.getRiga()[0]);
                    int riga_bersaglio_int = coord_bersaglio.rigaInt(coord_bersaglio.getRiga()[0]);
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
                }
                
//stampo le tabelle di p1 alla fine del turno
                
                std::cout << "tabelle p1:\n";
                std::cout << d1.getTab() << std::endl << a1.getTab() << std::endl;
            }
            
//turno p2
            
            else
            {   std::string selezione = "", bersaglio = "";
                std::stringstream ss(comand);
                ss >> selezione;
                ss >> bersaglio;
                
//stampo l'azione a video
                
                std::cout << "turno p2: " << selezione << " " << bersaglio << std::endl;
                
//le prime 3 righe dopo la creazione delle navi di p1 sono la creazione delle corazzate di p2
                
                if(lines_counter < 11)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d2.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "C", dim_coraz);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 8)
                    {   nave1.setType(ShipType::CORAZZATA);
                        nave1.setRigaCentrale(riga_centrale);
                        nave1.setColonnaCentrale(colonna_centrale);
                        nave1.setCelleOccupate(celle_occupate_tmp);
                        nave1.setHealth(h_coraz);
                        if(riga_poppa_int == riga_prua_int)
                        {   nave1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 9)
                        {   nave2.setType(ShipType::CORAZZATA);
                            nave2.setRigaCentrale(riga_centrale);
                            nave2.setColonnaCentrale(colonna_centrale);
                            nave2.setCelleOccupate(celle_occupate_tmp);
                            nave2.setHealth(h_coraz);
                            if(riga_poppa_int == riga_prua_int)
                            {   nave2.setOrizzontale();
                            }
                        } 
                        else if(lines_counter == 10)
                            {   nave3.setType(ShipType::CORAZZATA);
                                nave3.setRigaCentrale(riga_centrale);
                                nave3.setColonnaCentrale(colonna_centrale);
                                nave3.setCelleOccupate(celle_occupate_tmp);
                                nave3.setHealth(h_coraz);
                                if(riga_poppa_int == riga_prua_int)
                                {   nave3.setOrizzontale();
                                }
                            }
                }
                
//le successive 3 sono la creazione delle navi di supporto di p2
                
                if(lines_counter >= 11 && lines_counter < 14)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d2.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "S", dim_supp);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 11)
                    {   naves1.setType(ShipType::NAVE_SUPPORTO);
                        naves1.setRigaCentrale(riga_centrale);
                        naves1.setColonnaCentrale(colonna_centrale);
                        naves1.setCelleOccupate(celle_occupate_tmp);
                        naves1.SetSize(dim_supp);
                        naves1.setHealth(h_supp);
                        if(riga_poppa_int == riga_prua_int)
                        {   naves1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 12)
                        {   naves2.setType(ShipType::NAVE_SUPPORTO);
                            naves2.setRigaCentrale(riga_centrale);
                            naves2.setColonnaCentrale(colonna_centrale);
                            naves2.setCelleOccupate(celle_occupate_tmp);
                            naves2.SetSize(dim_supp);
                            naves2.setHealth(h_supp);
                            if(riga_poppa_int == riga_prua_int)
                            {   naves2.setOrizzontale();
                            }
                        } 
                        else if(lines_counter == 13)
                            {   naves3.setType(ShipType::NAVE_SUPPORTO);
                                naves3.setRigaCentrale(riga_centrale);
                                naves3.setColonnaCentrale(colonna_centrale);
                                naves3.setCelleOccupate(celle_occupate_tmp);
                                naves3.SetSize(dim_supp);
                                naves3.setHealth(h_supp);
                                if(riga_poppa_int == riga_prua_int)
                                {   naves3.setOrizzontale();
                                }
                            }
                }
                
//le righe di indice 14 e 15 creano i sottomarini di p2
                
                if(lines_counter >= 14 && lines_counter < 16)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d2.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "E", dim_sott);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    riga_centrale = riga_poppa_int;
                    colonna_centrale = coord_poppa.getColonna();
                    if(lines_counter == 14)
                    {   navesott1.setType(ShipType::SOTTOMARINO);
                        navesott1.setRigaCentrale(riga_centrale);
                        navesott1.setColonnaCentrale(colonna_centrale);
                        navesott1.setCelleOccupate(celle_occupate_tmp);
                        navesott1.SetSize(dim_sott);
                        navesott1.setHealth(h_sott);
                        if(riga_poppa_int == riga_prua_int)
                        {   navesott1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 15)
                        {   navesott2.setType(ShipType::SOTTOMARINO);
                            navesott2.setRigaCentrale(riga_centrale);
                            navesott2.setColonnaCentrale(colonna_centrale);
                            navesott2.setCelleOccupate(celle_occupate_tmp);
                            navesott2.SetSize(dim_sott);
                            navesott2.setHealth(h_sott);
                            if(riga_poppa_int == riga_prua_int)
                            {   navesott2.setOrizzontale();
                            }
                        } 
                }
                
//le righe di indice dispari dopo l'inizializzazione di tutte le navi sono le azioni di p2
                
                else
                {   std::string riga_selezione = selezione.substr(0,1);
                    int colonna_selezione = std::stoi(selezione.substr(1));
                    Coordinate coord_selezione(riga_selezione, colonna_selezione);
                    std::string riga_bersaglio = bersaglio.substr(0,1);
                    int colonna_bersaglio = std::stoi(bersaglio.substr(1));
                    Coordinate coord_bersaglio(riga_bersaglio, colonna_bersaglio);
                    int riga_selezione_int = coord_selezione.rigaInt(coord_selezione.getRiga()[0]);
                    int riga_bersaglio_int = coord_bersaglio.rigaInt(coord_bersaglio.getRiga()[0]);
                    if(riga_selezione_int == nave1.getRigaCentrale() && colonna_selezione == nave1.getColonnaCentrale())
                    {   d2.fire(nave1, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                        d1.delete_ship(C1);
                        d1.delete_ship(C2);
                        d1.delete_ship(C3);
                        d1.delete_ship(S1);
                        d1.delete_ship(S2);
                        d1.delete_ship(S3);
                        d1.delete_ship(E1);
                        d1.delete_ship(E2);
                    }
                    else if(riga_selezione_int == nave2.getRigaCentrale() && colonna_selezione == nave2.getColonnaCentrale())
                    {   d2.fire(nave2, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                        d1.delete_ship(C1);
                        d1.delete_ship(C2);
                        d1.delete_ship(C3);
                        d1.delete_ship(S1);
                        d1.delete_ship(S2);
                        d1.delete_ship(S3);
                        d1.delete_ship(E1);
                        d1.delete_ship(E2);
                    }
                    else if(riga_selezione_int == nave3.getRigaCentrale() && colonna_selezione == nave3.getColonnaCentrale())
                    {   d2.fire(nave3, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                        d1.delete_ship(C1);
                        d1.delete_ship(C2);
                        d1.delete_ship(C3);
                        d1.delete_ship(S1);
                        d1.delete_ship(S2);
                        d1.delete_ship(S3);
                        d1.delete_ship(E1);
                        d1.delete_ship(E2);
                    }
                    else if(riga_selezione_int == naves1.getRigaCentrale() && colonna_selezione == naves1.getColonnaCentrale())
                    {   d2.moveAndRepair(naves1, riga_bersaglio_int, colonna_bersaglio, d2, nave1, nave2, nave3, naves2, naves3);
                    }
                    else if(riga_selezione_int == naves2.getRigaCentrale() && colonna_selezione == naves2.getColonnaCentrale())
                    {   d2.moveAndRepair(naves2, riga_bersaglio_int, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves3);
                    }
                    else if(riga_selezione_int == naves3.getRigaCentrale() && colonna_selezione == naves3.getColonnaCentrale())
                    {   d2.moveAndRepair(naves3, riga_bersaglio_int, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves2);
                    }
                    else if(riga_selezione_int == navesott1.getRigaCentrale() && colonna_selezione == navesott1.getColonnaCentrale())
                    {   d2.moveAndScan(navesott1, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1);
                    }
                    else if(riga_selezione_int == navesott2.getRigaCentrale() && colonna_selezione == navesott2.getColonnaCentrale())
                    {   d2.moveAndScan(navesott2, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1);
                    }
                }
                
//stampo le tabelle di p2 alla fine del turno
                
                std::cout << "tabelle p2:\n";
                std::cout << d2.getTab() << std::endl << a2.getTab() << std::endl;
            }
            
//passo alla riga successiva e faccio passare un secondo di stacco tra un turno e l'altro
            
            lines_counter++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
//finite le righe di file chiudo il file di log
        
        file.close();
    }
    
//replay con f con stampa su file di aoutput
    
    else
    {   
    
///salvo gli argomenti passati da riga di comando in due stringhe, creo le tabelle e le navi, infine apro i file di log e di output
    
        std::string nome_file_log = argv[2];
        std::string nome_file_output_replay = argv[3];
        Tab_att a1, a2;
        Tab_dif d1, d2;
        Ship nave1, nave2, nave3, naves1, naves2, naves3, navesott1, navesott2;
        Ship C1, C2, C3, S1, S2, S3, E1, E2;
        const int coraz = 3;
        const int supp = 3;
        const int sott = 2;
        const int dim_coraz = 5, h_coraz = 5;
        const int dim_supp = 3, h_supp = 3;
        const int dim_sott = 1, h_sott = 1;
        std::ifstream file(nome_file_log);
        std::ofstream file_out(nome_file_output_replay);
        
//come per il replay con stampa a video lle prime otto righe e quelle di indice pari dopo la riga di indice 15 sono azioni di p1
        
        std::string comand = "";
        int lines_counter = 0;
        while(std::getline(file, comand))
        {   if(lines_counter < 8 || (lines_counter > 15 && lines_counter % 2 == 0))
            {   std::string selezione = "", bersaglio = "";
                std::stringstream ss(comand);
                ss >> selezione;
                ss >> bersaglio;
                
//stampo l'azione sul file di output
                
                file_out << "turno p1: " << selezione << " " << bersaglio << std::endl;
                
//inizializzo le corazzate di p1
                
                if(lines_counter < 3)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d1.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "C", dim_coraz);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 0)
                    {   C1.setType(ShipType::CORAZZATA);
                        C1.setRigaCentrale(riga_centrale);
                        C1.setColonnaCentrale(colonna_centrale);
                        C1.setCelleOccupate(celle_occupate_tmp);
                        C1.setHealth(h_coraz);
                        if(riga_poppa_int == riga_prua_int)
                        {   C1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 1)
                        {   C2.setType(ShipType::CORAZZATA);
                            C2.setRigaCentrale(riga_centrale);
                            C2.setColonnaCentrale(colonna_centrale);
                            C2.setCelleOccupate(celle_occupate_tmp);
                            C2.setHealth(h_coraz);
                            if(riga_poppa_int == riga_prua_int)
                            {   C2.setOrizzontale();
                            }
                        } 
                        else if(lines_counter == 2)
                            {   C3.setType(ShipType::CORAZZATA);
                                C3.setRigaCentrale(riga_centrale);
                                C3.setColonnaCentrale(colonna_centrale);
                                C3.setCelleOccupate(celle_occupate_tmp);
                                C3.setHealth(h_coraz);
                                if(riga_poppa_int == riga_prua_int)
                                {   C3.setOrizzontale();
                                }
                            }
                }
                
//inizializzo le navi di supporto di p1
                
                if(lines_counter >= 3 && lines_counter < 6)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d1.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "S", dim_supp);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 3)
                    {   S1.setType(ShipType::NAVE_SUPPORTO);
                        S1.setRigaCentrale(riga_centrale);
                        S1.setColonnaCentrale(colonna_centrale);
                        S1.setCelleOccupate(celle_occupate_tmp);
                        S1.SetSize(dim_supp);
                        S1.setHealth(h_supp);
                        if(riga_poppa_int == riga_prua_int)
                        {   S1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 4)
                        {   S2.setType(ShipType::NAVE_SUPPORTO);
                            S2.setRigaCentrale(riga_centrale);
                            S2.setColonnaCentrale(colonna_centrale);
                            S2.setCelleOccupate(celle_occupate_tmp);
                            S2.SetSize(dim_supp);
                            S2.setHealth(h_supp);
                            if(riga_poppa_int == riga_prua_int)
                            {   S2.setOrizzontale();
                            }
                        } 
                        else if(lines_counter == 5)
                            {   S3.setType(ShipType::NAVE_SUPPORTO);
                                S3.setRigaCentrale(riga_centrale);
                                S3.setColonnaCentrale(colonna_centrale);
                                S3.setCelleOccupate(celle_occupate_tmp);
                                S3.SetSize(dim_supp);
                                S3.setHealth(h_supp);
                                if(riga_poppa_int == riga_prua_int)
                                {   S3.setOrizzontale();
                                }
                            }
                }

//inizializzo i sottomarini di p1
                
                if(lines_counter >= 6 && lines_counter < 8)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d1.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "E", dim_sott);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    riga_centrale = riga_poppa_int;
                    colonna_centrale = coord_poppa.getColonna();
                    if(lines_counter == 6)
                    {   E1.setType(ShipType::SOTTOMARINO);
                        E1.setRigaCentrale(riga_centrale);
                        E1.setColonnaCentrale(colonna_centrale);
                        E1.setCelleOccupate(celle_occupate_tmp);
                        E1.SetSize(dim_sott);
                        E1.setHealth(h_sott);
                        if(riga_poppa_int == riga_prua_int)
                        {   E1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 7)
                        {   E2.setType(ShipType::SOTTOMARINO);
                            E2.setRigaCentrale(riga_centrale);
                            E2.setColonnaCentrale(colonna_centrale);
                            E2.setCelleOccupate(celle_occupate_tmp);
                            E2.SetSize(dim_sott);
                            E2.setHealth(h_sott);
                            if(riga_poppa_int == riga_prua_int)
                            {   E2.setOrizzontale();
                            }
                        } 
                }
                
//dopo la riga di indice 15 se l'indice di riga correnete e' pari eseguo un'azione di p1
                
                else
                {   std::string riga_selezione = selezione.substr(0,1);
                    int colonna_selezione = std::stoi(selezione.substr(1));
                    Coordinate coord_selezione(riga_selezione, colonna_selezione);
                    std::string riga_bersaglio = bersaglio.substr(0,1);
                    int colonna_bersaglio = std::stoi(bersaglio.substr(1));
                    Coordinate coord_bersaglio(riga_bersaglio, colonna_bersaglio);
                    int riga_selezione_int = coord_selezione.rigaInt(coord_selezione.getRiga()[0]);
                    int riga_bersaglio_int = coord_bersaglio.rigaInt(coord_bersaglio.getRiga()[0]);
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
                }
                
//finito il turno stampo sul file di output del tabelle di p1
                
                file_out << "tabelle p1:\n";
                file_out << d1.getTab() << std::endl << a1.getTab() << std::endl;
            }
            
//se l'indice di riga e' compreso tra 8 e 15 oppure e' maggiore di 15 e dispari l'azione da eseguire e' di p2
            
            else
            {   std::string selezione = "", bersaglio = "";
                std::stringstream ss(comand);
                ss >> selezione;
                ss >> bersaglio;
                
//stampo l'azione sul file di output
                
                file_out << "turno p2: " << selezione << " " << bersaglio << std::endl;
                
//inizializzo le corazzate di p2 se l'indice di riga e' compreso tra 8 e 11
                
                if(lines_counter < 11)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d2.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "C", dim_coraz);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 8)
                    {   nave1.setType(ShipType::CORAZZATA);
                        nave1.setRigaCentrale(riga_centrale);
                        nave1.setColonnaCentrale(colonna_centrale);
                        nave1.setCelleOccupate(celle_occupate_tmp);
                        nave1.setHealth(h_coraz);
                        if(riga_poppa_int == riga_prua_int)
                        {   nave1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 9)
                        {   nave2.setType(ShipType::CORAZZATA);
                            nave2.setRigaCentrale(riga_centrale);
                            nave2.setColonnaCentrale(colonna_centrale);
                            nave2.setCelleOccupate(celle_occupate_tmp);
                            nave2.setHealth(h_coraz);
                            if(riga_poppa_int == riga_prua_int)
                            {   nave2.setOrizzontale();
                            }
                        } 
                        else if(lines_counter == 10)
                            {   nave3.setType(ShipType::CORAZZATA);
                                nave3.setRigaCentrale(riga_centrale);
                                nave3.setColonnaCentrale(colonna_centrale);
                                nave3.setCelleOccupate(celle_occupate_tmp);
                                nave3.setHealth(h_coraz);
                                if(riga_poppa_int == riga_prua_int)
                                {   nave3.setOrizzontale();
                                }
                            }
                }
                
//inizializzo le navi di supporto di p2
                
                if(lines_counter >= 11 && lines_counter < 14)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d2.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "S", dim_supp);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    if(riga_poppa_int == riga_prua_int)
                    {   riga_centrale = riga_poppa_int;
                        colonna_centrale = (coord_poppa.getColonna() +  coord_prua.getColonna()) / 2;
                    }
                    else
                    {   colonna_centrale = coord_poppa.getColonna();
                        riga_centrale = (riga_poppa_int + riga_prua_int) / 2;
                    }
                    if(lines_counter == 11)
                    {   naves1.setType(ShipType::NAVE_SUPPORTO);
                        naves1.setRigaCentrale(riga_centrale);
                        naves1.setColonnaCentrale(colonna_centrale);
                        naves1.setCelleOccupate(celle_occupate_tmp);
                        naves1.SetSize(dim_supp);
                        naves1.setHealth(h_supp);
                        if(riga_poppa_int == riga_prua_int)
                        {   naves1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 12)
                        {   naves2.setType(ShipType::NAVE_SUPPORTO);
                            naves2.setRigaCentrale(riga_centrale);
                            naves2.setColonnaCentrale(colonna_centrale);
                            naves2.setCelleOccupate(celle_occupate_tmp);
                            naves2.SetSize(dim_supp);
                            naves2.setHealth(h_supp);
                            if(riga_poppa_int == riga_prua_int)
                            {   naves2.setOrizzontale();
                            }
                        } 
                        else if(lines_counter == 13)
                            {   naves3.setType(ShipType::NAVE_SUPPORTO);
                                naves3.setRigaCentrale(riga_centrale);
                                naves3.setColonnaCentrale(colonna_centrale);
                                naves3.setCelleOccupate(celle_occupate_tmp);
                                naves3.SetSize(dim_supp);
                                naves3.setHealth(h_supp);
                                if(riga_poppa_int == riga_prua_int)
                                {   naves3.setOrizzontale();
                                }
                            }
                }
                
//inizializzo i sottomarini di p2
                
                if(lines_counter >= 14 && lines_counter < 16)
                {   std::string riga_poppa = selezione.substr(0,1);
                    int colonna_poppa = std::stoi(selezione.substr(1));
                    Coordinate coord_poppa(riga_poppa, colonna_poppa);
                    std::string riga_prua = bersaglio.substr(0,1);
                    int colonna_prua = std::stoi(bersaglio.substr(1));
                    Coordinate coord_prua(riga_prua, colonna_prua);
                    int riga_poppa_int = coord_poppa.rigaInt(coord_poppa.getRiga()[0]);
                    int riga_prua_int = coord_prua.rigaInt(coord_prua.getRiga()[0]);
                    d2.Fill(riga_poppa_int, riga_prua_int, coord_poppa.getColonna(), coord_prua.getColonna(), "E", dim_sott);
                    std::vector<std::pair<int, int>> celle_occupate_tmp;
                    int riga_centrale = 0, colonna_centrale = 0;
                    riga_centrale = riga_poppa_int;
                    colonna_centrale = coord_poppa.getColonna();
                    if(lines_counter == 14)
                    {   navesott1.setType(ShipType::SOTTOMARINO);
                        navesott1.setRigaCentrale(riga_centrale);
                        navesott1.setColonnaCentrale(colonna_centrale);
                        navesott1.setCelleOccupate(celle_occupate_tmp);
                        navesott1.SetSize(dim_sott);
                        navesott1.setHealth(h_sott);
                        if(riga_poppa_int == riga_prua_int)
                        {   navesott1.setOrizzontale();
                        }
                    } 
                    else if(lines_counter == 15)
                        {   navesott2.setType(ShipType::SOTTOMARINO);
                            navesott2.setRigaCentrale(riga_centrale);
                            navesott2.setColonnaCentrale(colonna_centrale);
                            navesott2.setCelleOccupate(celle_occupate_tmp);
                            navesott2.SetSize(dim_sott);
                            navesott2.setHealth(h_sott);
                            if(riga_poppa_int == riga_prua_int)
                            {   navesott2.setOrizzontale();
                            }
                        } 
                }
                
//se l'indice di riga e' dispari e maggiore di 15 eseguo un'azione
                
                else
                {   std::string riga_selezione = selezione.substr(0,1);
                    int colonna_selezione = std::stoi(selezione.substr(1));
                    Coordinate coord_selezione(riga_selezione, colonna_selezione);
                    std::string riga_bersaglio = bersaglio.substr(0,1);
                    int colonna_bersaglio = std::stoi(bersaglio.substr(1));
                    Coordinate coord_bersaglio(riga_bersaglio, colonna_bersaglio);
                    int riga_selezione_int = coord_selezione.rigaInt(coord_selezione.getRiga()[0]);
                    int riga_bersaglio_int = coord_bersaglio.rigaInt(coord_bersaglio.getRiga()[0]);
                    if(riga_selezione_int == nave1.getRigaCentrale() && colonna_selezione == nave1.getColonnaCentrale())
                    {   d2.fire(nave1, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                        d1.delete_ship(C1);
                        d1.delete_ship(C2);
                        d1.delete_ship(C3);
                        d1.delete_ship(S1);
                        d1.delete_ship(S2);
                        d1.delete_ship(S3);
                        d1.delete_ship(E1);
                        d1.delete_ship(E2);
                    }
                    else if(riga_selezione_int == nave2.getRigaCentrale() && colonna_selezione == nave2.getColonnaCentrale())
                    {   d2.fire(nave2, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                        d1.delete_ship(C1);
                        d1.delete_ship(C2);
                        d1.delete_ship(C3);
                        d1.delete_ship(S1);
                        d1.delete_ship(S2);
                        d1.delete_ship(S3);
                        d1.delete_ship(E1);
                        d1.delete_ship(E2);
                    }
                    else if(riga_selezione_int == nave3.getRigaCentrale() && colonna_selezione == nave3.getColonnaCentrale())
                    {   d2.fire(nave3, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1, C1, C2, C3, S1, S2, S3, E1, E2);
                        d1.delete_ship(C1);
                        d1.delete_ship(C2);
                        d1.delete_ship(C3);
                        d1.delete_ship(S1);
                        d1.delete_ship(S2);
                        d1.delete_ship(S3);
                        d1.delete_ship(E1);
                        d1.delete_ship(E2);
                    }
                    else if(riga_selezione_int == naves1.getRigaCentrale() && colonna_selezione == naves1.getColonnaCentrale())
                    {   d2.moveAndRepair(naves1, riga_bersaglio_int, colonna_bersaglio, d2, nave1, nave2, nave3, naves2, naves3);
                    }
                    else if(riga_selezione_int == naves2.getRigaCentrale() && colonna_selezione == naves2.getColonnaCentrale())
                    {   d2.moveAndRepair(naves2, riga_bersaglio_int, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves3);
                    }
                    else if(riga_selezione_int == naves3.getRigaCentrale() && colonna_selezione == naves3.getColonnaCentrale())
                    {   d2.moveAndRepair(naves3, riga_bersaglio_int, colonna_bersaglio, d2, nave1, nave2, nave3, naves1, naves2);
                    }
                    else if(riga_selezione_int == navesott1.getRigaCentrale() && colonna_selezione == navesott1.getColonnaCentrale())
                    {   d2.moveAndScan(navesott1, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1);
                    }
                    else if(riga_selezione_int == navesott2.getRigaCentrale() && colonna_selezione == navesott2.getColonnaCentrale())
                    {   d2.moveAndScan(navesott2, riga_bersaglio_int, colonna_bersaglio, d2, a2, d1);
                    }
                }
                
//stampo nel file di output le tabelle di p2 alla fine del suo turno
                
                file_out << "tabelle p2:\n";
                file_out << d2.getTab() << std::endl << a2.getTab() << std::endl;
            }
            
//passo alla riga successiva
            
            lines_counter++;
        }
        
//chiudo sia file di log sia di output
        
        file.close();
        file_out.close();
    }
}
