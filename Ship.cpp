#include "Ship.h"
#include "Tabella_difesa.h"

// Constructor
Ship::Ship(ShipType tipo, char ColIn, int RigIn, char ColFin, int RigFin, bool orizzontale) {
  type_ = tipo;
  switch (tipo) {
    case ShipType::CORAZZATA:
      size_=5;
      health_ = 5;
    case ShipType::NAVE_SUPPORTO:
      size_=3;
      health_ = 3;
    case ShipType::SOTTOMARINO:
      size_= 1;
      health_ = 1;
  }
  this->colonnaInizio = ColIn;
  this->rigaInizio = RigIn;
  this->colonnaFine = ColFin;
  this->rigaFine = RigFin;
  if (ColIn == ColFin){
    orizzontale = false;
  }
    else {
    orizzontale = true;
  } 
}

Ship::Ship(ShipType type, int RigaCentrale, int ColonnaCentrale, bool orizzontale, std::vector<int> celle_occ){
  type_ = type;
  switch (type) {
    case ShipType::CORAZZATA:
      size_=5;
      health_ = 5;
    case ShipType::NAVE_SUPPORTO:
      size_=3;
      health_ = 3;
    case ShipType::SOTTOMARINO:
      size_= 1;
      health_ = 1;
  }
  this->RigaCentrale = RigaCentrale;
  this->ColonnaCentrale = ColonnaCentrale;
  this->orizzontale = orizzontale;

}

// Returns the size of the ship
int Ship::GetSize() const {
  switch (type_) {
    case ShipType::CORAZZATA:
      return 5;
    case ShipType::NAVE_SUPPORTO:
      return 3;
    case ShipType::SOTTOMARINO:
      return 1;
    default:
      return 0;
  }
}

// Returns the number of hits the ship has taken
int Ship::GetNumHits() const {
  return health_;
}

// Returns the type of the ship
ShipType Ship::GetType() const {
  return type_;
}

// Takes a hit on the ship
void Ship::TakeHit() {
  health_--;
}

// Returns true if the ship is destroyed, false otherwise
bool Ship::IsDestroyed() const {
  return health_ <= 0;
}

void Ship::setOrizzontale() const {
  orizzontale == true;
}

int Ship::getColonnaInizio(){
  return (int)colonnaInizio;
}

int Ship::getRigaInizio(){
  return rigaInizio;
}

int Ship::getColonnaFine(){
  return (int)colonnaFine;
}

int Ship::getRigaFine(){
  return rigaFine;
}



/*
void Ship::moveShip(Ship &ship, int middleX, int middleY, Tab_dif const& tabdif) {
    // Copy the state of each cell that the ship occupies in the hit matrix before moving the ship.
    Tab_dif tempMatrix[13][13];
    for (int x = ship.getColonnaInizio(); x <= ship.getColonnaFine(); x++) {
        for (int y = ship.getRigaInizio(); y <= ship.getRigaFine(); y++) {
            tempMatrix[x][y] == tabdif.matrix[x][y];
        }
    }
    // Remove the ship from its current position on the game board
    for (int x = ship.getStartX(); x <= ship.getEndX(); x++) {
        for (int y = ship.getStartY(); y <= ship.getEndY(); y++) {
            m_gameBoard[x][y] = '.';
        }
    }


}    */