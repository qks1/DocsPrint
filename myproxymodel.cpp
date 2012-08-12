#include "myproxymodel.h"

MyProxyModel::MyProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QVariant MyProxyModel::data (const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole && (index.column() == 1 || index.column() == 2 || index.column() == 3))
            return "";

    if (role == Qt::DecorationRole){
        if(index.column() == 1 && QSortFilterProxyModel::data(index).toString() == "3")
            return QPixmap("ok.png");
        if(index.column() == 2 && QSortFilterProxyModel::data(index).toString() == "1")
            return QPixmap("ok.png");
        if(index.column() == 3 && QSortFilterProxyModel::data(index).toString() == "2")
            return QPixmap("ok.png");
    }

    return QSortFilterProxyModel::data(index, role);
}
