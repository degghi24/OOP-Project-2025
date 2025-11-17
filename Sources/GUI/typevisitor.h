#ifndef TYPEVISITOR_H
#define TYPEVISITOR_H
#include "Sources/Model/visitor.h"
#include <QString>

class TypeVisitor : public Visitor {

private:
    QString classType;

public:
    TypeVisitor();
    void visitBook(Book&) override;
    void visitFilm(Film&) override;
    void visitMusic(Music&) override;
    void visitVideogame(Videogame&) override;
    void visitPhotograph(Photograph&) override;

    QString getType() const;
};

#endif // TYPEVISITOR_H
