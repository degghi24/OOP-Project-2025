#ifndef JSONWRITERVISITOR_H
#define JSONWRITERVISITOR_H

#include "Sources/Headers/product.h"
#include "Sources/Headers/digitalproduct.h"
#include "Sources/Headers/physicalproduct.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"
#include "Sources/Model/visitor.h"
#include <QJsonObject>

class JsonWriterVisitor : public Visitor{

    private:
        QJsonObject obj;
        void productFields(const Product& p);
        void digitalFields(const DigitalProduct& d);
        void physicalFields(const PhysicalProduct& p);

    public:
        JsonWriterVisitor();

        void visitFilm(Film& f) override;
        void visitBook(Book& b) override;
        void visitMusic(Music& m) override;
        void visitPhotograph(Photograph& p) override;
        void visitVideogame(Videogame& v) override;

        QJsonObject getJsonObject() const;
};

#endif // JSONWRITERVISITOR_H
