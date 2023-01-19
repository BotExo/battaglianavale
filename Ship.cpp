#include "Ship.h"
#include "Tabella_difesa.h"

Ship::Ship(){
  type_ = ShipType::CORAZZATA;
  this->size_=5;
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

void Ship::SetSize(int size){
  this->size_ = size;
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
  for (int i = 0; i < size_; i++)
  {
    std::cout<< " prova di celle occupate: " << celleoccupate[i].first << " " << celleoccupate[i].second <<std::endl;
  }
  
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

std::vector<std::pair<int, int>> Ship::getCelleOccupate(){
  return celleoccupate;
}

void Ship::setCelleOccupate(std::vector<std::pair<int, int>> celle){
   this->celleoccupate = celle;
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

bool Ship::operator==(const Ship& other) const {
  return (ColonnaCentrale == other.ColonnaCentrale && RigaCentrale == other.RigaCentrale);
}

bool Ship::operator!=(const Ship& other) const {
  return (ColonnaCentrale != other.ColonnaCentrale || RigaCentrale != other.RigaCentrale);
}