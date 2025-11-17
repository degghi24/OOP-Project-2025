#ifndef DIGITALPRODUCT_H
#define DIGITALPRODUCT_H
#include "Sources/Headers/product.h"

class DigitalProduct : public Product {

private:
        string company;

    public:
        DigitalProduct(string name, string descr, string genre, string country, int year, int cost, int stars, string image, string company);
        ~DigitalProduct();
        string getCompany() const;
        void setCompany(const string& newcompany);
        void accept(Visitor& visitor) override = 0;
};

#endif // DIGITALPRODUCT_H
