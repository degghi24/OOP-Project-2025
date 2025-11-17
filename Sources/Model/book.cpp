#include "Sources/Headers/book.h"
#include "Sources/Model/visitor.h"

Book::Book(string name, string descr, string genre, string country, int year, int cost, int stars, string image, string author, int pages, string publ, int ISBN)
    : PhysicalProduct(name, descr, genre, country, year, cost, stars, image, author), pages(pages), publisher(publ), ISBN(ISBN){}

Book::~Book(){}

int Book::getPages() const{
    return pages;
}

void Book::setPages(int newpages){
    pages = newpages;
}

string Book::getPublisher() const{
    return publisher;
}

void Book::setPublisher(const string& newpublisher){
    publisher = newpublisher;
}

int Book::getISBN() const{
    return ISBN;
}

void Book::setISBN(int newISBN){
    ISBN = newISBN;
}

void Book::accept(Visitor& visitor){
    visitor.visitBook(*this);
}
