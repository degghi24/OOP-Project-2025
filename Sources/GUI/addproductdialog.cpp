#include "Sources/GUI/addproductdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
#include "Sources/Headers/book.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"

AddProductDialog::AddProductDialog(QWidget* parent)
    : QDialog(parent), newProduct(nullptr) {
    setupUI();
}

AddProductDialog::~AddProductDialog() {
}

void AddProductDialog::setupUI() {
    setWindowTitle("Add New Product");
    resize(400, 200);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter product name...");
    mainLayout->addWidget(new QLabel("Name:"));
    mainLayout->addWidget(nameInput);

    QComboBox* typeComboBox = new QComboBox(this);
    typeComboBox->addItems({"-- Select a product type --", "Book", "Film", "Music", "Videogame", "Photograph"});
    mainLayout->addWidget(new QLabel("Type:"));
    mainLayout->addWidget(typeComboBox);

    addButton = new QPushButton("Add Product", this);
    mainLayout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, this, &AddProductDialog::on_addProduct_clicked);
    connect(typeComboBox, &QComboBox::currentTextChanged, this, &AddProductDialog::updateUIForProductType);
}

void AddProductDialog::on_addProduct_clicked() {
    QString name = nameInput->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Product name cannot be empty!");
        return;
    }

    if (!newProduct) {
        QMessageBox::warning(this, "Error", "Please select a product type!");
        return;
    }

    newProduct->setName(name.toStdString());
    accept();
}

void AddProductDialog::updateUIForProductType(const QString& type) {
    if (newProduct) {
        delete newProduct;
        newProduct = nullptr;
    }

    if (type == "-- Select a product type --") {
        return;
    }

    const string defaultImage = "default.jpg";

    if (type == "Book") {
        newProduct = new Book("", "", "", "", 0, 0, 0, "", "", 0, "", 0);
        newProduct->setImage(defaultImage);
    } else if (type == "Film") {
        newProduct = new Film("", "", "", "", 0, 0, 0, "", "", "", "", 0);
        newProduct->setImage(defaultImage);
    } else if (type == "Music") {
        newProduct = new Music("", "", "", "", 0, 0, 0, "", "", "", "", 0);
        newProduct->setImage(defaultImage);
    } else if (type == "Videogame") {
        newProduct = new Videogame("", "", "", "", 0, 0, 0, "", "", "", 0);
        newProduct->setImage(defaultImage);
    } else if (type == "Photograph") {
        newProduct = new Photograph("", "", "", "", 0, 0, 0, "", "", false, 0, 0);
        newProduct->setImage(defaultImage);
    }
}

Product* AddProductDialog::getNewProduct() const {
    Product* temp = newProduct;
    const_cast<AddProductDialog*>(this)->newProduct = nullptr;
    return temp;
}
