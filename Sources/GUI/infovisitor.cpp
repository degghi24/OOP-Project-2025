#include "Sources/GUI/infovisitor.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"
#include "Sources/GUI/typevisitor.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QCheckBox>
#include <QFormLayout>
#include <QApplication>
#include <QDir>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QDateTime>
#include <QImageReader>

InfoVisitor::InfoVisitor(QObject* parent) : QObject(parent) {
    widget = new QWidget;
}

void InfoVisitor::setProduct(Product* p) {
    product = p;
    if (!p) return;

    TypeVisitor visitor;
    p->accept(visitor);
    productType = visitor.getType();

    p->accept(*this);
}

void InfoVisitor::setProductIndex(const QModelIndex& index) {
    productIndex = index;
}

QFormLayout* InfoVisitor::commonSetUp(Product& p) {
    QFormLayout* commonLayout = new QFormLayout();

    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(p.getName()));
    titleEdit->setReadOnly(true);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(p.getDescription()));
    descrEdit->setReadOnly(true);
    descrEdit->setFixedHeight(80);

    QLineEdit* genreEdit = new QLineEdit(QString::fromStdString(p.getGenre()));
    genreEdit->setReadOnly(true);

    QLineEdit* countryEdit = new QLineEdit(QString::fromStdString(p.getCountry()));
    countryEdit->setReadOnly(true);

    QLineEdit* yearEdit = new QLineEdit(QString::number(p.getYear()));
    yearEdit->setReadOnly(true);

    QLineEdit* costEdit = new QLineEdit(QString::number(p.getCost()));
    costEdit->setReadOnly(true);

    QLineEdit* starsEdit = new QLineEdit(QString::number(p.getStars()));
    starsEdit->setReadOnly(true);

    editableMap["name"] = titleEdit;                   //aggiungo alla QMap gli attributi comuni
    editableMap["description"] = descrEdit;
    editableMap["genre"] = genreEdit;
    editableMap["country"] = countryEdit;
    editableMap["year"] = yearEdit;
    editableMap["cost"] = costEdit;
    editableMap["stars"] = starsEdit;

    commonLayout->addRow("Title:", titleEdit);
    commonLayout->addRow("Description:", descrEdit);
    commonLayout->addRow("Genre:", genreEdit);
    commonLayout->addRow("Country:", countryEdit);
    commonLayout->addRow("Year:", yearEdit);
    commonLayout->addRow("Price:", costEdit);
    commonLayout->addRow("Stars:", starsEdit);

    return commonLayout;
}

QFormLayout* InfoVisitor::setUpDigital(DigitalProduct& d, QFormLayout* layout) {
    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(d.getCompany()));
    companyEdit->setReadOnly(true);
    editableMap["company"] = companyEdit;
    layout->addRow("Production company:", companyEdit);
    return layout;
}

QFormLayout* InfoVisitor::setUpPhysical(PhysicalProduct& p, QFormLayout* layout) {
    QLineEdit* authorEdit = new QLineEdit(QString::fromStdString(p.getAuthor()));
    authorEdit->setReadOnly(true);
    editableMap["author"] = authorEdit;
    layout->addRow("Author:", authorEdit);
    return layout;
}

void InfoVisitor::visitFilm(Film& f) {
    resetWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QWidget* imageWidget = createImageWidget(f);
    mainLayout->addWidget(imageWidget);
    QFormLayout* filmLayout = commonSetUp(f);
    setUpDigital(f, filmLayout);

    QLineEdit* directorEdit = new QLineEdit(QString::fromStdString(f.getDirector()));
    directorEdit->setReadOnly(true);
    QLineEdit* actorEdit = new QLineEdit(QString::fromStdString(f.getActor()));
    actorEdit->setReadOnly(true);
    QLineEdit* minutesEdit = new QLineEdit(QString::number(f.getMinutes()));
    minutesEdit->setReadOnly(true);

    editableMap["director"] = directorEdit;
    editableMap["actor"] = actorEdit;
    editableMap["minutes"] = minutesEdit;

    filmLayout->addRow("Director:", directorEdit);
    filmLayout->addRow("Main actor:", actorEdit);
    filmLayout->addRow("Length (minutes):", minutesEdit);

    QWidget* filmWidget = new QWidget();
    filmWidget->setLayout(filmLayout);
    mainLayout->addWidget(filmWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    widget->setLayout(finalLayout);
}

void InfoVisitor::visitVideogame(Videogame& v) {
    resetWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QWidget* imageWidget = createImageWidget(v);
    mainLayout->addWidget(imageWidget);
    QFormLayout* videogameLayout = commonSetUp(v);
    setUpDigital(v, videogameLayout);

    QLineEdit* platformEdit = new QLineEdit(QString::fromStdString(v.getPlatform()));
    platformEdit->setReadOnly(true);
    QCheckBox* multiplayerBox = new QCheckBox("Multiplayer");
    multiplayerBox->setChecked(v.getIsMultiplayer());
    multiplayerBox->setEnabled(false);

    editableMap["platform"] = platformEdit;
    editableMap["isMultiplayer"] = multiplayerBox;

    videogameLayout->addRow("Platform:", platformEdit);
    videogameLayout->addRow("Multiplayer?", multiplayerBox);

    QWidget* videogameWidget = new QWidget();
    videogameWidget->setLayout(videogameLayout);
    mainLayout->addWidget(videogameWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    widget->setLayout(finalLayout);
}

void InfoVisitor::visitMusic(Music& m) {
    resetWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QWidget* imageWidget = createImageWidget(m);
    mainLayout->addWidget(imageWidget);
    QFormLayout* musicLayout = commonSetUp(m);
    setUpDigital(m, musicLayout);

    QLineEdit* singerEdit = new QLineEdit(QString::fromStdString(m.getSinger()));
    singerEdit->setReadOnly(true);
    QLineEdit* albumEdit = new QLineEdit(QString::fromStdString(m.getAlbum()));
    albumEdit->setReadOnly(true);
    QLineEdit* minutesEdit = new QLineEdit(QString::number(m.getMinutes()));
    minutesEdit->setReadOnly(true);

    editableMap["singer"] = singerEdit;
    editableMap["album"] = albumEdit;
    editableMap["minutes"] = minutesEdit;

    musicLayout->addRow("Singer:", singerEdit);
    musicLayout->addRow("Album:", albumEdit);
    musicLayout->addRow("Length (minutes):", minutesEdit);

    QWidget* musicWidget = new QWidget();
    musicWidget->setLayout(musicLayout);
    mainLayout->addWidget(musicWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    widget->setLayout(finalLayout);
}

void InfoVisitor::visitBook(Book& b) {
    resetWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QWidget* imageWidget = createImageWidget(b);
    mainLayout->addWidget(imageWidget);
    QFormLayout* bookLayout = commonSetUp(b);
    setUpPhysical(b, bookLayout);

    QLineEdit* pagesEdit = new QLineEdit(QString::number(b.getPages()));
    pagesEdit->setReadOnly(true);
    QLineEdit* publisherEdit = new QLineEdit(QString::fromStdString(b.getPublisher()));
    publisherEdit->setReadOnly(true);
    QLineEdit* isbnEdit = new QLineEdit(QString::number(b.getISBN()));
    isbnEdit->setReadOnly(true);

    editableMap["pages"] = pagesEdit;
    editableMap["publisher"] = publisherEdit;
    editableMap["ISBN"] = isbnEdit;

    bookLayout->addRow("Pages:", pagesEdit);
    bookLayout->addRow("Publisher:", publisherEdit);
    bookLayout->addRow("ISBN:", isbnEdit);

    QWidget* bookWidget = new QWidget();
    bookWidget->setLayout(bookLayout);
    mainLayout->addWidget(bookWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    widget->setLayout(finalLayout);
}

void InfoVisitor::visitPhotograph(Photograph& p) {
    resetWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QWidget* imageWidget = createImageWidget(p);
    mainLayout->addWidget(imageWidget);
    QFormLayout* photographLayout = commonSetUp(p);
    setUpPhysical(p, photographLayout);

    QCheckBox* colourBox = new QCheckBox("Colorata");
    colourBox->setChecked(p.getIsColourful());
    colourBox->setEnabled(false);
    QLineEdit* lengthEdit = new QLineEdit(QString::number(p.getLength()));
    lengthEdit->setReadOnly(true);
    QLineEdit* widthEdit = new QLineEdit(QString::number(p.getWidth()));
    widthEdit->setReadOnly(true);

    editableMap["isColourful"] = colourBox;
    editableMap["length"] = lengthEdit;
    editableMap["width"] = widthEdit;

    photographLayout->addRow("Colourful?", colourBox);
    photographLayout->addRow("Length:", lengthEdit);
    photographLayout->addRow("Width:", widthEdit);

    QWidget* photographWidget = new QWidget();
    photographWidget->setLayout(photographLayout);
    mainLayout->addWidget(photographWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    widget->setLayout(finalLayout);
}

QWidget* InfoVisitor::createImageWidget(Product& p) {       //crea il widget con l'immagine del prodotto

    QWidget* container = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(container);

    QLabel* imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);

    QString baseDir;
#ifdef Q_OS_WINDOWS
    baseDir = QDir(QCoreApplication::applicationDirPath()).absolutePath() + "/../../../Sources/IMG";
#else
    baseDir = QCoreApplication::applicationDirPath() + "/Sources/IMG";
#endif

    QDir dir(baseDir);
    if (!dir.exists() && !dir.mkpath(".")) {
        QMessageBox::warning(nullptr, "Errore", "Impossibile creare la cartella immagini:\n" + dir.absolutePath());
        imageLabel->setText("Cartella immagini mancante");
        layout->addWidget(imageLabel);
        return container;
    }

    QString imageName = QString::fromStdString(p.getImage());
    QString fullPath = dir.filePath(imageName);

    QImageReader reader(fullPath);
    reader.setAutoTransform(true);
    QSize maxReadSize(2000, 2000);
    reader.setScaledSize(maxReadSize);

    QImage img = reader.read();
    if (img.isNull()) {
        imageLabel->setText("Nessuna immagine");
    } else {
        imageLabel->setPixmap(QPixmap::fromImage(img).scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    // Pulsante per cambiare immagine
    QPushButton* changeImageButton = new QPushButton("Change image");
    changeImageButton->setStyleSheet(R"(
        QPushButton {
            background-color: #27ae60;
            color: white;
            font-weight: bold;
            border-radius: 6px;
            padding: 6px 12px;
        }
        QPushButton:hover {
            background-color: #2ecc71;
        }
        QPushButton:pressed {
            background-color: #1e8449;
        }
    )");

    imageEdit = new QLineEdit(imageName);
    imageEdit->setReadOnly(true);
    editableMap["image"] = imageEdit;

    connect(changeImageButton, &QPushButton::clicked, this, [this, imageLabel, dir]() {
        QString srcPath = QFileDialog::getOpenFileName(nullptr, "Seleziona Immagine", "", "Immagini (*.png *.jpg *.jpeg)");
        if (!srcPath.isEmpty()) {
            QString extension = QFileInfo(srcPath).suffix();
            QString uniqueName = "img_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + "." + extension;
            QString destPath = dir.filePath(uniqueName);

            if (QFile::copy(srcPath, destPath)) {
                QImageReader reader(destPath);
                reader.setAutoTransform(true);
                QSize maxReadSize(2000, 2000);
                reader.setScaledSize(maxReadSize);
                QImage img = reader.read();
                if (!img.isNull()) {
                    imageLabel->setPixmap(QPixmap::fromImage(img).scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    imageLabel->update();
                    imageLabel->repaint();
                    imageEdit->setText(uniqueName);
                    if (saveButton) saveButton->setEnabled(true);
                } else {
                    imageLabel->setText("Errore nel caricamento");
                }
            } else {
                QMessageBox::warning(nullptr, "Errore", "Errore durante la copia dell'immagine.");
            }
        }
    });

    layout->addWidget(imageLabel);
    layout->addWidget(imageEdit);
    layout->addWidget(changeImageButton);

    return container;
}

//crea il widget dei bottoni
QWidget* InfoVisitor::createButtonWidget() {
    QWidget* buttonWidget = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);

    backButton = new QPushButton("Back");
    modifyButton = new QPushButton("Modify");
    saveButton = new QPushButton("Save");
    saveButton->setEnabled(false);
    deleteButton = new QPushButton("Delete");

    //stile per far vedere che i pulsanti sono stati cliccati
    QString btnStyle = R"(
QPushButton {
    background-color: #4a90e2;
    color: white;
    border-radius: 6px;
    padding: 8px 18px;
    min-width: 90px;
    min-height: 36px;
}
QPushButton:hover {
    background-color: #357ABD;
}
QPushButton:pressed {
    background-color: #2C5F9E;
}
QPushButton:disabled {
    background-color: #888888;
    color: #cccccc;
}
)";
    backButton->setStyleSheet(btnStyle);
    modifyButton->setStyleSheet(btnStyle);
    saveButton->setStyleSheet(btnStyle);

    deleteButton->setStyleSheet(R"(
QPushButton {
    background-color: red;
    color: white;
    font-weight: bold;
    border-radius: 6px;
    padding: 8px 18px;
    min-width: 90px;
    min-height: 36px;
}
QPushButton:hover {
    background-color: darkred;
}
QPushButton:pressed {
    background-color: #8B0000;
}
)");

    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(deleteButton);

    connect(backButton, &QPushButton::clicked, this, &InfoVisitor::backSignal);
    connect(modifyButton, &QPushButton::clicked, this, &InfoVisitor::enableEdit);
    connect(saveButton, &QPushButton::clicked, this, &InfoVisitor::applyEdits);
    connect(deleteButton, &QPushButton::clicked, this, &InfoVisitor::on_deleteButton_clicked);

    return buttonWidget;
}

//per abilitare le modifiche dei campi di un prodotto
void InfoVisitor::enableEdit() {
    for (auto it = editableMap.constBegin(); it != editableMap.constEnd(); ++it) {
        QWidget* w = it.value();
        if (auto* le = qobject_cast<QLineEdit*>(w)) le->setReadOnly(false);
        else if (auto* te = qobject_cast<QTextEdit*>(w)) te->setReadOnly(false);
        else if (auto* cb = qobject_cast<QCheckBox*>(w)) cb->setEnabled(true);
    }
    if (saveButton) saveButton->setEnabled(true);
}

//per applicare le modifiche ai prodotti
void InfoVisitor::applyEdits() {
    if (!product) {
        return;
    }

    if (editableMap.contains("image")) {
        QLineEdit* imgEdit = qobject_cast<QLineEdit*>(editableMap["image"]);
        if (imgEdit) {
            product->setImage(imgEdit->text().toStdString());
        }
    }

    if (auto* title = qobject_cast<QLineEdit*>(editableMap["name"])) {
        product->setName(title->text().toStdString());
    }

    if (auto* descr = qobject_cast<QTextEdit*>(editableMap["description"])) {
        product->setDescription(descr->toPlainText().toStdString());
    }

    product->setGenre(qobject_cast<QLineEdit*>(editableMap["genre"])->text().toStdString());
    product->setCountry(qobject_cast<QLineEdit*>(editableMap["country"])->text().toStdString());
    product->setYear(qobject_cast<QLineEdit*>(editableMap["year"])->text().toInt());
    product->setCost(qobject_cast<QLineEdit*>(editableMap["cost"])->text().toInt());
    product->setStars(qobject_cast<QLineEdit*>(editableMap["stars"])->text().toInt());

    if (productType == "Film") {
        Film* f = dynamic_cast<Film*>(product);
        if (f) {
            f->setDirector(qobject_cast<QLineEdit*>(editableMap["director"])->text().toStdString());
            f->setActor(qobject_cast<QLineEdit*>(editableMap["actor"])->text().toStdString());
            f->setMinutes(qobject_cast<QLineEdit*>(editableMap["minutes"])->text().toInt());
            f->setCompany(qobject_cast<QLineEdit*>(editableMap["company"])->text().toStdString());
        }
    } else if (productType == "Music") {
        Music* m = dynamic_cast<Music*>(product);
        if (m) {
            m->setCompany(qobject_cast<QLineEdit*>(editableMap["company"])->text().toStdString());
            m->setSinger(qobject_cast<QLineEdit*>(editableMap["singer"])->text().toStdString());
            m->setAlbum(qobject_cast<QLineEdit*>(editableMap["album"])->text().toStdString());
            m->setMinutes(qobject_cast<QLineEdit*>(editableMap["minutes"])->text().toInt());
        }
    } else if (productType == "Videogame") {
        Videogame* v = dynamic_cast<Videogame*>(product);
        if (v) {
            v->setCompany(qobject_cast<QLineEdit*>(editableMap["company"])->text().toStdString());
            v->setPlatform(qobject_cast<QLineEdit*>(editableMap["platform"])->text().toStdString());
            v->setIsMultiplayer(qobject_cast<QCheckBox*>(editableMap["isMultiplayer"])->isChecked());
        }
    } else if (productType == "Book") {
        Book* b = dynamic_cast<Book*>(product);
        if (b) {
            b->setAuthor(qobject_cast<QLineEdit*>(editableMap["author"])->text().toStdString());
            b->setPages(qobject_cast<QLineEdit*>(editableMap["pages"])->text().toInt());
            b->setPublisher(qobject_cast<QLineEdit*>(editableMap["publisher"])->text().toStdString());
            b->setISBN(qobject_cast<QLineEdit*>(editableMap["ISBN"])->text().toInt());
        }
    } else if (productType == "Photograph") {
        Photograph* p = dynamic_cast<Photograph*>(product);
        if (p) {
            p->setAuthor(qobject_cast<QLineEdit*>(editableMap["author"])->text().toStdString());
            p->setIsColourful(qobject_cast<QCheckBox*>(editableMap["isColourful"])->isChecked());
            p->setLength(qobject_cast<QLineEdit*>(editableMap["length"])->text().toInt());
            p->setWidth(qobject_cast<QLineEdit*>(editableMap["width"])->text().toInt());
        }
    }

    for (auto it = editableMap.constBegin(); it != editableMap.constEnd(); ++it) {
        QWidget* w = it.value();
        if (auto* le = qobject_cast<QLineEdit*>(w)) le->setReadOnly(true);
        else if (auto* te = qobject_cast<QTextEdit*>(w)) te->setReadOnly(true);
        else if (auto* cb = qobject_cast<QCheckBox*>(w)) cb->setEnabled(false);
    }
    emit modifiedSignal();

}

QModelIndex InfoVisitor::getProductIndex() const {
    return productIndex;
}

void InfoVisitor::on_deleteButton_clicked() {
    emit deleteProductSignal();
}

//funzione per pulire layout e widget per non avere problemi
void InfoVisitor::deleteLayoutRecursively(QLayout* layout) {
    if (!layout) return;
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget()) {
            delete w;
        } else if (QLayout* child = item->layout()) {
            deleteLayoutRecursively(child);
            delete child;
        }
        delete item;
    }
}

//funzione per pulire layout e widget per non avere problemi
void InfoVisitor::resetWidget() {
    if (!widget) widget = new QWidget;

    QLayout* old = widget->layout();
    if (old) {
        deleteLayoutRecursively(old);
        delete old;
    }

    editableMap.clear();
}

QWidget* InfoVisitor::getWidget() const {
    return widget;
}
