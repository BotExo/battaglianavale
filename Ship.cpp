//Marco Bettin

#include "Ship.h" 

Ship::Ship(){ //costruttore
  type_ = ShipType::CORAZZATA; //tipo di nave
  this->size_=5;
  this->health_=5;
  this->RigaCentrale=0;
  this->ColonnaCentrale=0;
  this->colonnaInizio = 0;
  this->rigaInizio = 0;
  this->colonnaFine = 0;
  this->rigaFine = 0;
  this->orizzontale = false; //variabile booleana per vedere se la nave e' in orizzontale di default e' false
  this->celleoccupate;
}

//metodo get per la size della nave
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

//metodo set per la size della nave
void Ship::SetSize(int size){
  this->size_ = size;
}

//metodo get per la health della nave
int Ship::GetNumHits() const {
  return health_;
}

//metodo get per il tipo di nave
ShipType Ship::GetType() const {
  return type_;
}

//metodo per prendere un colpo
void Ship::TakeHit() {
  health_--;
}

//metodo per vedere se la nave e' distrutta
bool Ship::IsDestroyed() const {
  return health_ <= 0;
}

//metodo get per la colonna iniziale
int Ship::getColonnaInizio(){
  return (int)colonnaInizio;
}

//metodo get per la riga iniziale
int Ship::getRigaInizio(){
  return rigaInizio;
}

//metodo get per la colonna finale
int Ship::getColonnaFine(){
  return (int)colonnaFine;
}

//metodo get per la riga finale
int Ship::getRigaFine(){
  return rigaFine;
}

//metodo set per settare la nave in orizzontale
void Ship::setOrizzontale() {
  this->orizzontale = true;
}

//metodo get per vedere se la nave e' in orizzontale
bool Ship::getOrizzontale() const{
  return orizzontale;
}


//metodo per stampare le coordinate delle celle occupate
void Ship::printCelleOccupate(){
  for (int i = 0; i < size_; i++)
  {
    std::cout<< " celle occupate: " << celleoccupate[i].first << " " << celleoccupate[i].second <<std::endl;
  }
  
}

//metodo get per la riga centrale
int Ship::getRigaCentrale() const{
  return RigaCentrale;
}

//metodo get per la colonna centrale
int Ship::getColonnaCentrale() const {
  return ColonnaCentrale;
}

//metodo per settare la colonna centrale
void Ship::setColonnaCentrale(int colonna){
  this->ColonnaCentrale = colonna;
}

//metodo per settare la riga centrale
void Ship::setRigaCentrale(int riga){
  this->RigaCentrale = riga;
}

//metodo get per le celle occupate
std::vector<std::pair<int, int>> Ship::getCelleOccupate(){
  return celleoccupate;
}

//metodo per settare le celle occupate
void Ship::setCelleOccupate(std::vector<std::pair<int, int>> celle){
   this->celleoccupate = celle;
}

//metodo per settare il tipo di nave
void Ship::setType(ShipType tipo){
  this->type_ = tipo;
}


void Ship::printShipInfo(){ //metodo per stampare le informazioni della nave
    std::cout << "tipo nave: ";
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

//metodo per settare la vita della nave
void Ship::setHealth(int h)
{   
  this->health_ = h;
}