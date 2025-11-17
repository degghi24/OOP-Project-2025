#include "Sources/Headers/videogame.h"
#include "Sources/Model/visitor.h"

Videogame::Videogame(string name, string descr, string genre, string country, int year, int cost, int stars, string image, string company, string plat, bool multiplayer)
    : DigitalProduct(name, descr, genre, country, year, cost, stars, image, company), platform(plat), isMultiplayer(multiplayer){}

Videogame::~Videogame(){}

string Videogame::getPlatform() const{
    return platform;
}

void Videogame::setPlatform(const string& newplatform){
    platform = newplatform;
}

bool Videogame::getIsMultiplayer() const{
    return isMultiplayer;
}

void Videogame::setIsMultiplayer(bool newmultiplayer){
    isMultiplayer = newmultiplayer;
}

void Videogame::accept(Visitor& visitor){
    visitor.visitVideogame(*this);
}
