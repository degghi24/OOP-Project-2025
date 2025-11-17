#include "Sources/GUI/libraryfilterproxymodel.h"
#include "Sources/Headers/product.h"
#include "Sources/GUI/typevisitor.h"

LibraryFilterProxyModel::LibraryFilterProxyModel(QObject* parent) : QSortFilterProxyModel(parent) {}

bool LibraryFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const {

    QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariant var = sourceModel()->data(idx, Qt::UserRole);
    Product* p = reinterpret_cast<Product*>(var.value<void*>());
    if (!p) {
        return false;
    }

    //Filtro per classe
    if (filterType != "All" && !filterType.isEmpty()) {
        TypeVisitor visitor;
        p->accept(visitor);
        if (visitor.getType() != filterType) {
            return false;
        }
    }

    //Filtro per nome (searchbar)
    if (!searchFilter.isEmpty()) {
        QString name = QString::fromStdString(p->getName());
        if (!name.contains(searchFilter, Qt::CaseInsensitive)) {
            return false;
        }
    }

    return true;
}


void LibraryFilterProxyModel::setFilter(const QString& type){
    filterType = type;
    invalidateFilter();
}

void LibraryFilterProxyModel::setSearchFilter(const QString& text){
    searchFilter = text;
    invalidateFilter();
}
