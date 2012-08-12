#include "myproxymodelfordoc.h"

MyProxyModelForDoc::MyProxyModelForDoc(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QVariant MyProxyModelForDoc::data (const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole && index.column() == 1)
            return "";

    if (role == Qt::DecorationRole){
        if(index.column() == 1 && QSortFilterProxyModel::data(index).toString() == "1")
            return QPixmap("ok.png");
    }

    return QSortFilterProxyModel::data(index, role);
}
