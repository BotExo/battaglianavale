#include "Ship.h"
#include "Tabella_difesa.h"

// Constructor
/*Ship::Ship(ShipType tipo, char ColIn, int RigIn, char ColFin, int RigFin, bool orizzontale, std::vector<int> celle_occ) {
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
  celleoccupate;
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
  celleoccupate;
}*/

Ship::Ship(){
  type_ = ShipType::CORAZZATA;
  size_=5;
  health_ = 5;
  int RigaCentrale=0;
  int ColonnaCentrale=0;
  this->colonnaInizio = 0;
  this->rigaInizio = 0;
  this->colonnaFine = 0;
  this->rigaFine = 0;
  this->orizzontale = false;
  this->celleoccupate;
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

void Ship::setOrizzontale() {
  orizzontale = true;
}

bool Ship::getOrizzontale() const{
  return orizzontale;
}

void Ship::printCelleOccupate(){
  std::cout<< celleoccupate.at(0) << " " << celleoccupate.at(1) << " " << celleoccupate.at(2) <<" "<< celleoccupate.at(3) <<std::endl;
}

int Ship::getRigaCentrale() const{
  return RigaCentrale;
}

int Ship::getColonnaCentrale() const {
  return ColonnaCentrale;
}

void Ship::setColonnaCentrale(int colonna){
  this->ColonnaCentrale = colonna;
}

void Ship::setRigaCentrale(int riga){
  this->RigaCentrale = riga;
}

std::vector<int> Ship::getCelleOccupate(){
  return celleoccupate;
}

void Ship::setCelleOccupate(std::vector<int> celle){
   celleoccupate = celle;
}

void Ship::setType(ShipType tipo){
  type_ = tipo;
}

void Ship::printShipInfo(){
  if (type_ == ShipType::CORAZZATA){
      std::cout << "corazzata" << "\n";
    }
    else if (type_ == ShipType::NAVE_SUPPORTO){
      std::cout << "nave supporto" << "\n";
    }
    else if (type_ == ShipType::SOTTOMARINO){
      std::cout << "sottomarino" << "\n";
    }
    std::cout << "riga centrale: " << RigaCentrale << "\n";
    std::cout << "colonna centrale: " << ColonnaCentrale << "\n";
}

