#include "Sources/GUI/jsonwritervisitor.h"

JsonWriterVisitor::JsonWriterVisitor() {}

void JsonWriterVisitor::productFields(const Product& p){
    obj["name"] = QString::fromStdString(p.getName());
    obj["description"] = QString::fromStdString(p.getDescription());
    obj["genre"] = QString::fromStdString(p.getGenre());
    obj["country"] = QString::fromStdString(p.getCountry());
    obj["year_of_publication"] = p.getYear();
    obj["cost"] = p.getCost();
    obj["stars"] = p.getStars();
    obj["imagePath"] = QString::fromStdString(p.getImage());
}

void JsonWriterVisitor::digitalFields(const DigitalProduct& d){
    obj["company"] = QString::fromStdString(d.getCompany());
}

void JsonWriterVisitor::physicalFields(const PhysicalProduct& p){
    obj["author"] = QString::fromStdString(p.getAuthor());
}

void JsonWriterVisitor::visitFilm(Film& f){
    obj["type"] = "Film";
    productFields(f);
    digitalFields(f);
    obj["director"] = QString::fromStdString(f.getDirector());
    obj["actor"] = QString::fromStdString(f.getActor());
    obj["minutes"] = f.getMinutes();
}

void JsonWriterVisitor::visitBook(Book& b){
    obj["type"] = "Book";
    productFields(b);
    physicalFields(b);
    obj["pages"] = b.getPages();
    obj["publisher"] = QString::fromStdString(b.getPublisher());
    obj["ISBN"] = b.getISBN();
}

void JsonWriterVisitor::visitMusic(Music& m){
    obj["type"] = "Music";
    productFields(m);
    digitalFields(m);
    obj["minutes"] = m.getMinutes();
    obj["singer"] = QString::fromStdString(m.getSinger());
    obj["album"] = QString::fromStdString(m.getAlbum());
}

void JsonWriterVisitor::visitPhotograph(Photograph& p){
    obj["type"] = "Photograph";
    productFields(p);
    physicalFields(p);
    obj["isColourful"] = p.getIsColourful();
    obj["length"] = p.getLength();
    obj["width"] = p.getWidth();
}

void JsonWriterVisitor::visitVideogame(Videogame& v){
    obj["type"] = "Videogame";
    productFields(v);
    digitalFields(v);
    obj["platform"] = QString::fromStdString(v.getPlatform());
    obj["isMultiplayer"] = v.getIsMultiplayer();
}

QJsonObject JsonWriterVisitor::getJsonObject() const{
    return obj;
}
