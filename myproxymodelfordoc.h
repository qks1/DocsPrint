#ifndef MYPROXYMODELFORDOC_H
#define MYPROXYMODELFORDOC_H

#include <QSortFilterProxyModel>
#include <QColor>
#include <QPixmap>

class MyProxyModelForDoc : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit MyProxyModelForDoc(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    
signals:
    
public slots:
    
};

#endif // MYPROXYMODELFORDOC_H
