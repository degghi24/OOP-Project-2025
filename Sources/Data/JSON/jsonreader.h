#ifndef JSONREADER_H
#define JSONREADER_H
#include "Sources/Headers/book.h"
#include "Sources/Headers/photograph.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"

#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class JsonReader{

private:
    //gli struct servono per memorizzare gli attributi comuni delle classi concrete
    struct ProductData{
        QString name;
        QString description;
        QString genre;
        QString country;
        int year_of_publication;
        int cost;
        int stars;
        QString imagePath;
    };

    struct DigitalData{
        QString company;
    };

    struct PhysicalData{
        QString author;
    };

    //restituiscono campi dati con gli attributi comuni delle classi concrete
    ProductData readProduct(const QJsonObject& obj);
    DigitalData readDigital(const QJsonObject& obj);
    PhysicalData readPhysical(const QJsonObject& obj);

    //per creare gli oggetti delle varie classi concrete
    Film* readFilm(const QJsonObject& obj);
    Music* readMusic(const QJsonObject& obj);
    Videogame* readVideogame(const QJsonObject& obj);
    Book* readBook(const QJsonObject& obj);
    Photograph* readPhotograph(const QJsonObject& obj);

public:   
    JsonReader();
    QList<Product*> readAll(const string& filename); //restituisce una lista di tutti gli oggetti presenti nel json

};

#endif // JSONREADER_H
