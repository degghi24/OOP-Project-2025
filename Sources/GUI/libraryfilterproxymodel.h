#ifndef LIBRARYFILTERPROXYMODEL_H
#define LIBRARYFILTERPROXYMODEL_H
#include <QSortFilterProxyModel>

class LibraryFilterProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

private:
    QString filterType = "All";
    QString searchFilter;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

public:
    explicit LibraryFilterProxyModel(QObject* parent = nullptr);
    void setFilter(const QString& type);
    void setSearchFilter(const QString& text);
};

#endif // LIBRARYFILTERPROXYMODEL_H
