#ifndef PRINTPREVIEW_H
#define PRINTPREVIEW_H

#include <QtGui>
#include <QtSql>
#include "doctable.h"


class PrintPreview : public QWidget
{
    Q_OBJECT
public:
    explicit PrintPreview(QSqlQueryModel *model, QString name, QString num, QString note, QString date, QWidget *parent = 0);
    void resize();

private:
    QPushButton *close_button;
    QPushButton *print_button;
    QTextEdit *talon;
    QTextDocument *t;
    QWidget *controls;
    QString docname, docnum, docnote, docdate;

    inline void set_layout();
    inline void connects();
    void create_preview(QSqlQueryModel*, QString, QString, QString, QString);
    
signals:
    void close_signal();

public slots:
    //void preview_slot();
    void close_slot();
    void print();
    
};

#endif // PRINTPREVIEW_H
