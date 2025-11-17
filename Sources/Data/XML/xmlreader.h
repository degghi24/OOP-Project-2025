#ifndef XMLREADER_H
#define XMLREADER_H
#include "Sources/Headers/book.h"
#include "Sources/Headers/photograph.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"

#include <QList>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>

class XmlReader {

private:
    //gli struct servono per memorizzare gli attributi comuni delle classi concrete
    struct ProductData {
        QString name;
        QString description;
        QString genre;
        QString country;
        int year_of_publication;
        int cost;
        int stars;
        QString imagePath;
    };

    struct DigitalData {
        QString company;
    };

    struct PhysicalData {
        QString author;
    };

    //restituiscono campi dati con gli attributi comuni delle classi concrete
    void readProduct(QXmlStreamReader &xml, ProductData& prod);
    void readDigital(QXmlStreamReader &xml, DigitalData& dig);
    void readPhysical(QXmlStreamReader &xml, PhysicalData& phy);

    //per creare gli oggetti delle varie classi concrete
    Film* readFilm(QXmlStreamReader &xml);
    Music* readMusic(QXmlStreamReader &xml);
    Videogame* readVideogame(QXmlStreamReader &xml);
    Book* readBook(QXmlStreamReader &xml);
    Photograph* readPhotograph(QXmlStreamReader &xml);

public:
    XmlReader();
    QList<Product*> readAll(const QString &filename);//restituisce una lista di tutti gli oggetti presenti nel xml
};

#endif // XMLREADER_H
