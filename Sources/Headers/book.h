#ifndef BOOK_H
#define BOOK_H
#include "Sources/Headers/physicalproduct.h"

class Visitor;

class Book : public PhysicalProduct {

    private:
        int pages;
        string publisher;
        int ISBN;

    public:
        Book(string name, string descr, string genre, string country, int year, int cost, int stars, string image, string author, int pages, string publ, int ISBN);
        ~Book();
        int getPages() const;
        void setPages(int newpages);
        string getPublisher() const;
        void setPublisher(const string& newpublisher);
        int getISBN() const;
        void setISBN(int newISBN);
        void accept(Visitor& visitor) override;
};

#endif // BOOK_H
