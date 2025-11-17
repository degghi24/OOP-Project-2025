#ifndef LIBRARY_H
#define LIBRARY_H
#include "Sources/Headers/product.h"
#include <list>

class Library {
    private:
        std::list<Product*> library;
    public:
        Library();
};

#endif // LIBRARY_H
