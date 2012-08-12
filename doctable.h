#ifndef DOCTABLE_H
#define DOCTABLE_H

#include <QtGui>
#include <QtSql>
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include <QTableView>
#include "myproxymodelfordoc.h"
#include "myproxymodel.h"

class DocTable : public QWidget
{
    Q_OBJECT
public:
    explicit DocTable(int iddoc, QString docname, QString docnum, QString docnote, QString docdate, QWidget *parent = 0);
    ~DocTable();
    void resize();

private:
    QList<QCheckBox*> storages_list;
    QGroupBox *storages_box;
    QPushButton *print;
    QPushButton *close_button;
    MyProxyModelForDoc *pmodel;
    void fill(int id);
    inline void set_layout();
    inline void connects();
    inline void set_columns_names();
    QWidget *controls;
    QTableView *table;
    QSqlQueryModel *model;
    QString name, num, note, date;
    QMap<QString, QString> columns;
    int row_height;
    void custom_table();
    int iddoc;

    void rename_columns();
    void add_checkboxes();

    bool first;
    QStringList storages;
    QStringList storages_selected;
    
signals:
    void close_signal();
    void print_preview(QSqlQueryModel*, QString, QString, QString, QString);

private slots:
    void close_slot();
    void checkbox_pressed(int);
    void preview_slot();
    
public slots:
    void fill_slot(int);
};

#endif // DOCTABLE_H
