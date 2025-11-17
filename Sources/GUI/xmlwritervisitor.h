#ifndef XMLWRITERVISITOR_H
#define XMLWRITERVISITOR_H

#include <QtXml/QDomDocument>
#include "Sources/Model/visitor.h"
#include "Sources/Headers/product.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"
#include <QXmlStreamWriter>

class XmlWriterVisitor : public Visitor {

public:
    XmlWriterVisitor();
    ~XmlWriterVisitor() = default;

    bool writeAll(const QString& filename, const QList<Product*>& products);

    void visitFilm(Film& f) override;
    void visitBook(Book& b) override;
    void visitMusic(Music& m) override;
    void visitPhotograph(Photograph& p) override;
    void visitVideogame(Videogame& v) override;

private:
    QXmlStreamWriter* xml;
    void writeCommonAttributes(Product& p);
};

#endif // XMLWRITERVISITOR_H
