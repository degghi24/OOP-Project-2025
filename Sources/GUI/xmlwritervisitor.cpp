#include "Sources/GUI/xmlwritervisitor.h"
#include <QString>
#include <QFile>
#include <QDebug>

XmlWriterVisitor::XmlWriterVisitor() : xml(nullptr) {}

bool XmlWriterVisitor::writeAll(const QString& filename, const QList<Product*>& products) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Impossibile aprire il file XML per scrittura";
        return false;
    }

    QXmlStreamWriter writer(&file);
    xml = &writer;
    xml->setAutoFormatting(true);
    xml->writeStartDocument();
    xml->writeStartElement("root");

    for (Product* p : products) {
        if (p) p->accept(*this);
    }

    xml->writeEndElement();
    xml->writeEndDocument();
    file.close();
    return true;
}

void XmlWriterVisitor::writeCommonAttributes(Product& p) {
    xml->writeTextElement("name", QString::fromStdString(p.getName()));
    xml->writeTextElement("description", QString::fromStdString(p.getDescription()));
    xml->writeTextElement("genre", QString::fromStdString(p.getGenre()));
    xml->writeTextElement("country", QString::fromStdString(p.getCountry()));
    xml->writeTextElement("year_of_publication", QString::number(p.getYear()));
    xml->writeTextElement("cost", QString::number(p.getCost()));
    xml->writeTextElement("stars", QString::number(p.getStars()));
    xml->writeTextElement("imagePath", QString::fromStdString(p.getImage()));
}


void XmlWriterVisitor::visitFilm(Film& f) {
    xml->writeStartElement("Product");
    xml->writeAttribute("type", "Film");
    writeCommonAttributes(f);
    xml->writeTextElement("company", QString::fromStdString(f.getCompany()));
    xml->writeTextElement("director", QString::fromStdString(f.getDirector()));
    xml->writeTextElement("mainActor", QString::fromStdString(f.getActor()));
    xml->writeTextElement("minutes", QString::number(f.getMinutes()));
    xml->writeEndElement();
}

void XmlWriterVisitor::visitBook(Book& b) {
    xml->writeStartElement("Product");
    xml->writeAttribute("type", "Book");
    writeCommonAttributes(b);
    xml->writeTextElement("author", QString::fromStdString(b.getAuthor()));
    xml->writeTextElement("pages", QString::number(b.getPages()));
    xml->writeTextElement("publisher", QString::fromStdString(b.getPublisher()));
    xml->writeTextElement("ISBN", QString::number(b.getISBN()));
    xml->writeEndElement();
}

void XmlWriterVisitor::visitMusic(Music& m) {
    xml->writeStartElement("Product");
    xml->writeAttribute("type", "Music");
    writeCommonAttributes(m);
    xml->writeTextElement("company", QString::fromStdString(m.getCompany()));
    xml->writeTextElement("singer", QString::fromStdString(m.getSinger()));
    xml->writeTextElement("album", QString::fromStdString(m.getAlbum()));
    xml->writeTextElement("minutes", QString::number(m.getMinutes()));
    xml->writeEndElement();
}

void XmlWriterVisitor::visitPhotograph(Photograph& p) {
    xml->writeStartElement("Product");
    xml->writeAttribute("type", "Photograph");
    writeCommonAttributes(p);
    xml->writeTextElement("author", QString::fromStdString(p.getAuthor()));
    xml->writeTextElement("isColourful", p.getIsColourful() ? "true" : "false");
    xml->writeTextElement("length", QString::number(p.getLength()));
    xml->writeTextElement("width", QString::number(p.getWidth()));
    xml->writeEndElement();
}

void XmlWriterVisitor::visitVideogame(Videogame& v) {
    xml->writeStartElement("Product");
    xml->writeAttribute("type", "Videogame");
    writeCommonAttributes(v);
    xml->writeTextElement("company", QString::fromStdString(v.getCompany()));
    xml->writeTextElement("platform", QString::fromStdString(v.getPlatform()));
    xml->writeTextElement("isMultiplayer", v.getIsMultiplayer() ? "true" : "false");
    xml->writeEndElement();
}

