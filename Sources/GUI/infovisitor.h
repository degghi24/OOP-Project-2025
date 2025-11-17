#ifndef INFOVISITOR_H
#define INFOVISITOR_H

#include <QObject>
#include <QList>
#include <QPushButton>
#include <QFormLayout>
#include <QMap>
#include <QModelIndex>

#include "Sources/Headers/product.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"
#include "Sources/Model/visitor.h"

#include <QLineEdit>

class InfoVisitor : public QObject, public Visitor
{
    Q_OBJECT

public:
    explicit InfoVisitor(QObject* parent = nullptr);
    QWidget* createImageWidget(Product& p);
    QWidget* createButtonWidget();
    void enableEdit();
    void applyEdits();
    void setProduct(Product* p);
    QWidget* getWidget() const;
    void setProductIndex(const QModelIndex& index);
    QModelIndex getProductIndex() const;

    void visitFilm(Film& f) override;
    void visitVideogame(Videogame& v) override;
    void visitMusic(Music& m) override;
    void visitBook(Book& b) override;
    void visitPhotograph(Photograph& p) override;

    void resetWidget();
    static void deleteLayoutRecursively(QLayout* layout);

signals:
    void modifiedSignal();
    void backSignal();
    void deleteProductSignal();

private slots:
    void on_deleteButton_clicked();

private:
    QWidget* widget = nullptr;
    Product* product = nullptr;
    QString productType;

    QPushButton* backButton;
    QPushButton* modifyButton;
    QPushButton* saveButton;
    QPushButton* deleteButton;
    QPushButton* imageButton;

    QMap<QString, QWidget*> editableMap;

    QLineEdit* imageEdit;
    QModelIndex productIndex;

    QFormLayout* commonSetUp(Product& p);
    QFormLayout* setUpDigital(DigitalProduct& d, QFormLayout* layout);
    QFormLayout* setUpPhysical(PhysicalProduct& p, QFormLayout* layout);
};

#endif // INFOVISITOR_H
