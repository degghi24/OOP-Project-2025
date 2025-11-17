QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/GUI/addproductdialog.cpp \
    Sources/GUI/infovisitor.cpp \
    Sources/GUI/jsonwritervisitor.cpp \
    Sources/GUI/libraryfilterproxymodel.cpp \
    Sources/GUI/librarymodel.cpp \
    Sources/GUI/mainwindow.cpp \
    Sources/GUI/menubar.cpp \
    Sources/GUI/typevisitor.cpp \
    Sources/GUI/xmlwritervisitor.cpp \
    Sources/Model/book.cpp \
    Sources/Model/digitalproduct.cpp \
    Sources/Model/film.cpp \
    Sources/Model/main.cpp \
    Sources/Model/music.cpp \
    Sources/Model/photograph.cpp \
    Sources/Model/physicalproduct.cpp \
    Sources/Model/product.cpp \
    Sources/Model/videogame.cpp \
    Sources/Data/XML/xmlreader.cpp \
    Sources/Data/JSON/jsonreader.cpp \
    Sources/Model/visitor.cpp

HEADERS += \
    Sources/GUI/addproductdialog.h \
    Sources/GUI/infovisitor.h \
    Sources/GUI/jsonwritervisitor.h \
    Sources/GUI/libraryfilterproxymodel.h \
    Sources/GUI/librarymodel.h \
    Sources/GUI/mainwindow.h \
    Sources/GUI/menubar.h \
    Sources/GUI/typevisitor.h \
    Sources/GUI/xmlwritervisitor.h \
    Sources/Headers/book.h \
    Sources/Headers/digitalproduct.h \
    Sources/Headers/film.h \
    Sources/Headers/library.h \
    Sources/Headers/music.h \
    Sources/Headers/photograph.h \
    Sources/Headers/physicalproduct.h \
    Sources/Headers/product.h \
    Sources/Headers/videogame.h \
    Sources/Data/XML/xmlreader.h \
    Sources/Data/JSON/jsonreader.h \
    Sources/Model/visitor.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Sources/Data/JSON/library.json \
    Sources/Data/XML/library.xml
