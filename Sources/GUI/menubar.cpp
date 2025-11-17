#include "Sources/GUI/menubar.h"
#include <QMenu>

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent) {
    setUpMenu();
}

//per creare la menubar
void MenuBar::setUpMenu(){
    QMenu* menu = this->addMenu("File");
    QMenu* addMenu = this->addMenu("Add");

    QAction* jsonAction = new QAction("Load from JSON", this);
    QAction* xmlAction = new QAction("Load from XML", this);
    QAction* newProductAction = new QAction("New product", this);

    menu->addAction(jsonAction);
    menu->addAction(xmlAction);
    addMenu->addAction(newProductAction);

    connect(jsonAction, &QAction::triggered, this, &MenuBar::loadJsonSignal);
    connect(xmlAction, &QAction::triggered, this, &MenuBar::loadXmlSignal);
    connect(newProductAction, &QAction::triggered, this, &MenuBar::addProductSignal);
}
