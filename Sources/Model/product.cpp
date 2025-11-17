#include "Sources/Headers/product.h"

Product::Product(string name, string descr, string genre, string country, int year, int cost, int stars, string image)
    : name(name), description(descr), genre(genre), country(country), year_of_publication(year), cost(cost), stars(stars), imagePath(image){}

string Product::getName() const {
    return name;
}

void Product::setName(const string& newname) {
    name = newname;
}

string Product::getDescription() const {
    return description;
}

void Product::setDescription(const string& newdescription) {
    description = newdescription;
}

string Product::getGenre() const {
    return genre;
}

void Product::setGenre(const string& newgenre){
    genre = newgenre;

}

string Product::getCountry() const {
    return country;
}

void Product::setCountry(const string& newcountry){
    country = newcountry;
}

int Product::getYear() const {
    return year_of_publication;
}

void Product::setYear(int newyear){
    year_of_publication = newyear;
}

int Product::getCost() const {
    return cost;
}

void Product::setCost(int newcost){
    cost = newcost;
}

int Product::getStars() const {
    return stars;
}

void Product::setStars(int newstars) {
    stars = newstars;
}

string Product::getImage() const{
    return imagePath;
}

void Product::setImage(const string& newimage){
    imagePath = newimage;
}
