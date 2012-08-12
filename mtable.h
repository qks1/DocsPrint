#ifndef TABLE_H
#define TABLE_H

#include <QtGui>
#include <QtSql>
#include "myproxymodel.h"


class MTable : public QWidget
{
    Q_OBJECT
    
public:
    MTable(QWidget *parent = 0);

    void fill();
    void resize();

protected:


private:
    // элементы формы
    QLabel *from_label;
    QLabel *to_label;
    QLabel *type_label;
    QDateEdit *from_date;
    QDateEdit *to_date;
    QComboBox *type_box;
    QPushButton *refresh_button;
    QWidget *controls;
    QTableView *table;
    QSqlQueryModel *model;
    MyProxyModel *pmodel;
    QMap<QString, QString> columns;
    int row_height;

    void custom_table();
    void rename_columns();

    bool hidden;
    int filter;

    inline void set_layout();
    inline void connects();
    inline void set_columns_names();

    inline void custom_dates();
    void fill_checkbox();

    void keyReleaseEvent(QKeyEvent *);

signals:
    void show_doc_signal(int, QString, QString, QString, QString);

private slots:
    void date_changed(QDate);
    void switch_hidden();
    void checkbox_used(QString);
    void refresh();
    void double_click(QModelIndex);

};


#endif // TABLE_H
