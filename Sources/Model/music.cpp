#include "Sources/Headers/music.h"
#include "Sources/Model/visitor.h"

Music::Music(string name, string descr, string genre, string country, int year, int cost, int stars, string image, string company, string sin, string alb, int min)
    : DigitalProduct(name, descr, genre, country, year, cost, stars, image, company), singer(sin), album(alb), minutes(min){}

Music::~Music(){}

string Music::getSinger() const{
    return singer;
}

void Music::setSinger(const string& newsinger){
    singer = newsinger;
}

string Music::getAlbum() const{
    return album;
}

void Music::setAlbum(const string& newalbum){
    album = newalbum;
}

int Music::getMinutes() const {
    return minutes;
}

void Music::setMinutes(int newminutes){
    minutes = newminutes;
}

void Music::accept(Visitor& visitor){
    visitor.visitMusic(*this);
}
