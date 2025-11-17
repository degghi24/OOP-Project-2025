#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H
#include <QAbstractTableModel>
#include <QList>
#include "Sources/Headers/product.h"


class LibraryModel : public QAbstractTableModel {
    Q_OBJECT

    private:
        QList<Product*> products;

    public:
        explicit LibraryModel(QObject* parent = nullptr);
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

        bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

        void setProducts(const QList<Product*>& product);
        Product* getProducts(int row) const;
        void addProduct(Product* newProduct);
};

#endif // LIBRARYMODEL_H
