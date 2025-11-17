#include "Sources/GUI/mainwindow.h"
#include "Sources/Data/JSON/jsonreader.h"
#include "Sources/Data/XML/xmlreader.h"
#include "Sources/GUI/infovisitor.h"
#include "Sources/GUI/menubar.h"
#include "Sources/GUI/addproductdialog.h"
#include "Sources/GUI/jsonwritervisitor.h"
#include "Sources/GUI/xmlwritervisitor.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QDomDocument>
#include <QTextStream>
#include <QGraphicsDropShadowEffect>
#include <QVariant>
#include <QList>
#include <QDir>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
    model(new LibraryModel(this)),
    proxymodel(new LibraryFilterProxyModel(this)),
    infoVisitor(nullptr)
{
    setWindowTitle("Digital Library");
    setupUI();
    proxymodel->setSourceModel(model);
    listView->setModel(proxymodel);

    MenuBar* bar = new MenuBar(this);
    setMenuBar(bar);

    connect(bar, &MenuBar::loadJsonSignal, this, &MainWindow::loadFromJson);
    connect(bar, &MenuBar::loadXmlSignal, this, &MainWindow::loadFromXml);
    connect(bar, &MenuBar::addProductSignal, this, &MainWindow::openAddProductDialog);
}

MainWindow::~MainWindow() {
    delete infoVisitor;
}

void MainWindow::filterAll() {            //per i filtri per classe
    proxymodel->setFilter("All");
}

void MainWindow::filterBooks() {
    proxymodel->setFilter("Book");
}

void MainWindow::filterFilms() {
    proxymodel->setFilter("Film");
}

void MainWindow::filterMusic() {
    proxymodel->setFilter("Music");
}

void MainWindow::filterVideogames() {
    proxymodel->setFilter("Videogame");
}

void MainWindow::filterPhotograph() {
    proxymodel->setFilter("Photograph");
}

void MainWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    centralWidget->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1E1E1E, stop:1 #333333); border-radius: 15px;");

    listView = new QListView(this);
    listView->setViewMode(QListView::IconMode);
    listView->setIconSize(QSize(100, 100));
    listView->setGridSize(QSize(120, 140));
    listView->setSpacing(10);
    listView->setResizeMode(QListView::Adjust);
    listView->setMovement(QListView::Static);

    //Stile e ombra per la QListView
    listView->setStyleSheet("QListView { background: #3c3c3c; border-radius: 12px; }"
                            "QListView::item { background: #444444; border-radius: 8px; }"
                            "QListView::item:hover { background: #555555; }");
    QGraphicsDropShadowEffect* listViewShadow = new QGraphicsDropShadowEffect(this);
    listViewShadow->setBlurRadius(15);
    listViewShadow->setColor(QColor(0, 0, 0, 150));
    listViewShadow->setOffset(4, 4);
    listView->setGraphicsEffect(listViewShadow);

    btnAll = new QPushButton("All", this);
    btnBook = new QPushButton("Book", this);
    btnFilm = new QPushButton("Film", this);
    btnMusic = new QPushButton("Music", this);
    btnVideogame = new QPushButton("Videogame", this);
    btnPhotograph = new QPushButton("Photograph", this);

    //Layout per i bottoni
    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(btnAll);
    buttonLayout->addWidget(btnBook);
    buttonLayout->addWidget(btnFilm);
    buttonLayout->addWidget(btnMusic);
    buttonLayout->addWidget(btnVideogame);
    buttonLayout->addWidget(btnPhotograph);
    buttonLayout->addStretch();

    QWidget* buttonWidget = new QWidget(this);
    buttonWidget->setLayout(buttonLayout);

    buttonWidget->setStyleSheet("QWidget { background-color: #2c3e50; border-radius: 15px; }");

    //Per applicare lo stile e l'ombra a tutti i pulsanti
    for (QPushButton* button : buttonWidget->findChildren<QPushButton*>()) {
        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setBlurRadius(10);
        shadowEffect->setColor(QColor(0, 0, 0, 100));
        shadowEffect->setOffset(2, 2);
        button->setGraphicsEffect(shadowEffect);

        button->setStyleSheet("QPushButton { border: 1px solid #555; color: #ecf0f1; border-radius: 8px; background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #424242, stop:1 #525252); padding: 8px; }"
                              "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #525252, stop:1 #424242); }"
                              "QPushButton:pressed { background: #3c3c3c; }");
    }

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search by name...");
    searchBar->setStyleSheet("QLineEdit { background-color: #2c3e50; color: #ecf0f1; border: 1px solid #34495e; border-radius: 8px; padding: 5px; }"
                             "QLineEdit:focus { border: 1px solid #4a637a; }");

    //Per mettere l'ombra per la searchbar
    QGraphicsDropShadowEffect* searchBarShadow = new QGraphicsDropShadowEffect(this);
    searchBarShadow->setBlurRadius(10);
    searchBarShadow->setColor(QColor(0, 0, 0, 100));
    searchBarShadow->setOffset(2, 2);
    searchBar->setGraphicsEffect(searchBarShadow);

    QVBoxLayout* listLayout = new QVBoxLayout;
    listLayout->addWidget(searchBar);

    //per creare linea separatrice
    QFrame* line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("QFrame { background-color: #4a637a; margin-top: 5px; margin-bottom: 5px; }");
    listLayout->addWidget(line);

    listLayout->addWidget(listView);

    QWidget* listWidget = new QWidget(this);
    listWidget->setLayout(listLayout);
    listWidget->setStyleSheet("QWidget { background-color: #3c3c3c; border-radius: 15px; }");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(buttonWidget);
    mainLayout->addWidget(listWidget);

    mainPage = new QWidget;
    mainPage->setLayout(mainLayout);
    infoPage = new QWidget;
    infoPage->setLayout(new QVBoxLayout);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(mainPage);
    stackedWidget->addWidget(infoPage);

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addWidget(stackedWidget);
    centralWidget->setLayout(centralLayout);

    connect(btnAll, &QPushButton::clicked, this, &MainWindow::filterAll);           //filtri
    connect(btnBook, &QPushButton::clicked, this, &MainWindow::filterBooks);
    connect(btnFilm, &QPushButton::clicked, this, &MainWindow::filterFilms);
    connect(btnMusic, &QPushButton::clicked, this, &MainWindow::filterMusic);
    connect(btnVideogame, &QPushButton::clicked, this, &MainWindow::filterVideogames);
    connect(btnPhotograph, &QPushButton::clicked, this, &MainWindow::filterPhotograph);

    connect(searchBar, &QLineEdit::textChanged, proxymodel, &LibraryFilterProxyModel::setSearchFilter);   //searchbar
    connect(listView, &QListView::clicked, this, &MainWindow::showProductDetails);           //per entrare nei dettagli di un prodotto
}


//caricamento file .json sia per windows sia per linux
void MainWindow::loadFromJson() {
    QString baseDir;

#ifdef Q_OS_WINDOWS

    baseDir = QDir(QCoreApplication::applicationDirPath()).absolutePath() + "/../../../Sources/Data/JSON";
#else

    baseDir = QCoreApplication::applicationDirPath() + "/Sources/Data/JSON";
#endif

    QDir dir(baseDir);
    if (!dir.exists()) {
        qWarning() << "Cartella JSON non trovata:" << dir.absolutePath();
        return;
    }

    filePath = dir.filePath("library.json");
    qDebug() << "[DEBUG] Carico JSON da:" << filePath;

    JsonReader reader;
    productList = reader.readAll(filePath.toStdString());
    model->setProducts(productList);
}

//caricamento file .xml sia per windows sia per linux
void MainWindow::loadFromXml() {
    QString baseDir;
#ifdef Q_OS_WINDOWS
    baseDir = QDir(QCoreApplication::applicationDirPath()).absolutePath() + "/../../../Sources/Data/XML";
#else
    baseDir = QCoreApplication::applicationDirPath() + "/Sources/Data/XML";
#endif

    QDir dir(baseDir);
    if (!dir.exists()) {
        qWarning() << "Cartella XML non trovata:" << dir.absolutePath();
        return;
    }

    filePath = dir.filePath("library.xml");
    qDebug() << "[DEBUG] Carico XML da:" << filePath;

    XmlReader reader;
    productList = reader.readAll(filePath);
    model->setProducts(productList);
}

//per mostrare la infopage (pagina dei dettagli)
void MainWindow::showProductDetails(const QModelIndex& index) {
    QModelIndex sourceIndex = proxymodel->mapToSource(index);
    QVariant var = model->data(sourceIndex, Qt::UserRole);

    Product* p = reinterpret_cast<Product*>(var.value<void*>());
    if (!p)
        return;

    if (infoVisitor) {
        clearLayout(infoPage->layout());
        delete infoVisitor;
        infoVisitor = nullptr;
    }

    infoVisitor = new InfoVisitor(this);
    infoVisitor->setProduct(p);
    infoVisitor->setProductIndex(sourceIndex);
    QWidget* productWidget = infoVisitor->getWidget();

    if (!infoPage->layout()) {
        QVBoxLayout* layout = new QVBoxLayout(infoPage);
        layout->addWidget(productWidget);
    } else {
        clearLayout(infoPage->layout());
        infoPage->layout()->addWidget(productWidget);
    }

    connect(infoVisitor, &InfoVisitor::backSignal, this, [this]() {
        stackedWidget->setCurrentWidget(mainPage);
    });

    connect(infoVisitor, &InfoVisitor::deleteProductSignal, this, &MainWindow::deleteProduct);
    connect(infoVisitor, &InfoVisitor::modifiedSignal, this, &MainWindow::saveProducts);

    stackedWidget->setCurrentWidget(infoPage);
}

//per pulire
void MainWindow::clearLayout(QLayout* layout) {
    if (!layout) {
        return;
    }
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        } else if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void MainWindow::openAddProductDialog() {
    AddProductDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Product* newProduct = dialog.getNewProduct();
        if (newProduct) {
            if (model) {
                model->addProduct(newProduct);
                saveProducts();
            }
        }
    }
}

//per salvare modifiche con opzione json o xml in base al file caricato all'inizio
void MainWindow::saveProducts() {
    if (filePath.endsWith(".json")) {
        saveToJson();
    } else if (filePath.endsWith(".xml")) {
        saveToXml();
    } else {
        QMessageBox::warning(this, "Errore", "Formato di file non supportato.");
    }
}

void MainWindow::saveToJson() {
    QJsonArray array;
    for (int row = 0; row < model->rowCount(); ++row) {
        Product* p = model->getProducts(row);
        if (p) {
            JsonWriterVisitor writer;
            p->accept(writer);
            array.append(writer.getJsonObject());
        }
    }
    QJsonDocument doc(array);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Errore", "Impossibile scrivere nel file JSON.");
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

void MainWindow::saveToXml() {
    QList<Product*> updatedList;
    for (int row = 0; row < model->rowCount(); ++row) {
        Product* p = model->getProducts(row);
        if (p) {
            updatedList.append(p);
        }
    }

    XmlWriterVisitor writer;
    if (!writer.writeAll(filePath, updatedList)) {
        QMessageBox::warning(this, "Errore", "Impossibile scrivere nel file XML.");
    } else {
        qDebug() << "File XML salvato correttamente in" << filePath;
    }
}

//per togliere un prodotto
void MainWindow::deleteProduct() {
    if (!infoVisitor || !infoVisitor->getProductIndex().isValid())
        return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Conferma eliminazione",
                                  "Are you sure you want to delete this product?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes)
        return;

    QModelIndex sourceIndex = infoVisitor->getProductIndex();

    if (model->removeRow(sourceIndex.row())) {
        saveProducts();

        //per pulire
        clearLayout(infoPage->layout());
        delete infoVisitor;
        infoVisitor = nullptr;

        stackedWidget->setCurrentWidget(mainPage);
    }
}
