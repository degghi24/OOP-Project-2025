#include "Sources/GUI/typevisitor.h"

TypeVisitor::TypeVisitor() {}

void TypeVisitor::visitBook(Book&) {
    classType = "Book";
}

void TypeVisitor::visitFilm(Film&) {
     classType = "Film";
}

void TypeVisitor::visitMusic(Music&) {
    classType = "Music";
}

void TypeVisitor::visitVideogame(Videogame&) {
    classType = "Videogame";
}

void TypeVisitor::visitPhotograph(Photograph&) {
    classType = "Photograph";
}

QString TypeVisitor::getType() const {
    return classType;
}
