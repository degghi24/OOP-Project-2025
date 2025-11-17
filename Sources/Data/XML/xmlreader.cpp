#include "Sources/Data/XML/xmlreader.h"
#include <QDebug>

XmlReader::XmlReader() {}

QList<Product*> XmlReader::readAll(const QString &filename) {
    QList<Product*> library;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file XML";
        return library;
    }

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement && xml.name() == QStringLiteral("Product")) {
            QString type = xml.attributes().value("type").toString();

            Product* product = nullptr;

            if (type == "Film") product = readFilm(xml);
            else if (type == "Music") product = readMusic(xml);
            else if (type == "Videogame") product = readVideogame(xml);
            else if (type == "Book") product = readBook(xml);
            else if (type == "Photograph") product = readPhotograph(xml);
            else qWarning() << "Classe non valida:" << type;

            if (product != nullptr) library.append(product);
        }
    }

    if (xml.hasError())
        qWarning() << "Errore parsing XML:" << xml.errorString();

    xml.clear();
    return library;
}

void XmlReader::readProduct(QXmlStreamReader &xml, ProductData& prod) {
    const QString tag = xml.name().toString();
    const QString value = xml.readElementText();

    if (tag == QStringLiteral("name")) prod.name = value;
    else if (tag == QStringLiteral("description")) prod.description = value;
    else if (tag == QStringLiteral("genre")) prod.genre = value;
    else if (tag == QStringLiteral("country")) prod.country = value;
    else if (tag == QStringLiteral("year_of_publication")) prod.year_of_publication = value.toInt();
    else if (tag == QStringLiteral("cost")) prod.cost = value.toInt();
    else if (tag == QStringLiteral("stars")) prod.stars = value.toInt();
    else if (tag == QStringLiteral("imagePath")) prod.imagePath = value;
}

void XmlReader::readDigital(QXmlStreamReader &xml, DigitalData& dig) {
    if (xml.name() == QStringLiteral("company"))
        dig.company = xml.readElementText();
}

void XmlReader::readPhysical(QXmlStreamReader &xml, PhysicalData& phy) {
    if (xml.name() == QStringLiteral("author"))
        phy.author = xml.readElementText();
}

Film* XmlReader::readFilm(QXmlStreamReader &xml) {
    ProductData prod;
    DigitalData dig;
    QString director, mainActor;
    int minutes = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("Product"))) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == QStringLiteral("company")) readDigital(xml, dig);
            else if (tag == QStringLiteral("director")) director = xml.readElementText();
            else if (tag == QStringLiteral("mainActor")) mainActor = xml.readElementText();
            else if (tag == QStringLiteral("minutes")) minutes = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Film(prod.name.toStdString(), prod.description.toStdString(),
                    prod.genre.toStdString(), prod.country.toStdString(),
                    prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                    dig.company.toStdString(), director.toStdString(),
                    mainActor.toStdString(), minutes);
}

Music* XmlReader::readMusic(QXmlStreamReader &xml) {
    ProductData prod;
    DigitalData dig;
    QString singer, album;
    int minutes = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("Product"))) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == QStringLiteral("company")) readDigital(xml, dig);
            else if (tag == QStringLiteral("singer")) singer = xml.readElementText();
            else if (tag == QStringLiteral("album")) album = xml.readElementText();
            else if (tag == QStringLiteral("minutes")) minutes = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Music(prod.name.toStdString(), prod.description.toStdString(),
                     prod.genre.toStdString(), prod.country.toStdString(),
                     prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                     dig.company.toStdString(), singer.toStdString(),
                     album.toStdString(), minutes);
}

Videogame* XmlReader::readVideogame(QXmlStreamReader &xml) {
    ProductData prod;
    DigitalData dig;
    QString platform;
    bool isMultiplayer = false;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("Product"))) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == QStringLiteral("company")) readDigital(xml, dig);
            else if (tag == QStringLiteral("platform")) platform = xml.readElementText();
            else if (tag == QStringLiteral("isMultiplayer")) isMultiplayer = (xml.readElementText() == "true");
            else readProduct(xml, prod);
        }
    }

    return new Videogame(prod.name.toStdString(), prod.description.toStdString(),
                         prod.genre.toStdString(), prod.country.toStdString(),
                         prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                         dig.company.toStdString(), platform.toStdString(),
                         isMultiplayer);
}

Book* XmlReader::readBook(QXmlStreamReader &xml) {
    ProductData prod;
    PhysicalData phy;
    int pages = 0, ISBN = 0;
    QString publisher;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("Product"))) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == QStringLiteral("author")) readPhysical(xml, phy);
            else if (tag == QStringLiteral("pages")) pages = xml.readElementText().toInt();
            else if (tag == QStringLiteral("publisher")) publisher = xml.readElementText();
            else if (tag == QStringLiteral("ISBN")) ISBN = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Book(prod.name.toStdString(), prod.description.toStdString(),
                    prod.genre.toStdString(), prod.country.toStdString(),
                    prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                    phy.author.toStdString(), pages,
                    publisher.toStdString(), ISBN);
}

Photograph* XmlReader::readPhotograph(QXmlStreamReader &xml) {
    ProductData prod;
    PhysicalData phy;
    bool isColourful = false;
    int length = 0, width = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QStringLiteral("Product"))) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == QStringLiteral("author")) readPhysical(xml, phy);
            else if (tag == QStringLiteral("isColourful")) isColourful = (xml.readElementText() == "true");
            else if (tag == QStringLiteral("length")) length = xml.readElementText().toInt();
            else if (tag == QStringLiteral("width")) width = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Photograph(prod.name.toStdString(), prod.description.toStdString(),
                          prod.genre.toStdString(), prod.country.toStdString(),
                          prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                          phy.author.toStdString(), isColourful, length, width);
}
