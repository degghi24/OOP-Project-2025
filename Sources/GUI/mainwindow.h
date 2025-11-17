#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QPushButton>
#include "Sources/GUI/librarymodel.h"
#include "Sources/GUI/libraryfilterproxymodel.h"
#include "Sources/GUI/infovisitor.h"
#include <QStackedWidget>
//#include <memory>
#include <QModelIndex>

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    LibraryModel* model;
    LibraryFilterProxyModel* proxymodel;
    QListView* listView;
    QStackedWidget* stackedWidget;
    QWidget* mainPage;
    QWidget* infoPage;
    QLineEdit* searchBar;

    QPushButton* btnAll;
    QPushButton* btnBook;
    QPushButton* btnFilm;
    QPushButton* btnMusic;
    QPushButton* btnVideogame;
    QPushButton* btnPhotograph;

    QString filePath;
    QList<Product*> productList;

    InfoVisitor* infoVisitor;

private slots:
    void filterAll();
    void filterBooks();
    void filterFilms();
    void filterMusic();
    void filterVideogames();
    void filterPhotograph();
    void openAddProductDialog();
    void deleteProduct();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupUI();
    void loadFromJson();
    void loadFromXml();
    void showProductDetails(const QModelIndex& index);
    void clearLayout(QLayout* layout);
    void saveProducts();
    void saveToJson();
    void saveToXml();
};
#endif // MAINWINDOW_H
