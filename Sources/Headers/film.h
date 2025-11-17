#ifndef FILM_H
#define FILM_H
#include "Sources/Headers/digitalproduct.h"

class Visitor;


class Film : public DigitalProduct {

    private:
        string director;
        string mainActor;
        int minutes;

    public:
        Film(string name, string descr, string genre, string country, int year, int cost, int stars, string image, string company, string dir, string actor, int min);
        ~Film();
        string getDirector() const;
        void setDirector(const string& newdirector);
        string getActor() const;
        void setActor(const string& newactor);
        int getMinutes() const;
        void setMinutes(int newminutes);
        void accept(Visitor& visitor) override;
};

#endif // FILM_H
