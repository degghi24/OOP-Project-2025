#include "Sources/Headers/digitalproduct.h"

DigitalProduct::DigitalProduct(string name, string descr, string genre, string country, int year, int cost, int stars, string image, string company)
    : Product(name, descr, genre, country, year, cost, stars, image), company(company){}

DigitalProduct::~DigitalProduct(){}

string DigitalProduct::getCompany() const{
    return company;
}

void DigitalProduct::setCompany(const string& newcompany){
    company = newcompany;
}
