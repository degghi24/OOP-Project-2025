#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QMenuBar>

class MenuBar : public QMenuBar {
    Q_OBJECT

private:
    void setUpMenu();

signals:
    void loadJsonSignal();
    void loadXmlSignal();
    void addProductSignal();

public:
    explicit MenuBar(QWidget* parent = nullptr);
};

#endif // MENUBAR_H
