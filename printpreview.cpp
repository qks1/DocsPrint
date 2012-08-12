#include "printpreview.h"


PrintPreview::PrintPreview(QSqlQueryModel *model, QString name, QString num, QString note, QString date, QWidget *parent) :
    QWidget(parent)
{
    close_button = new QPushButton("ЗАКРЫТЬ");
    print_button = new QPushButton("ПЕЧАТЬ");
    talon = new QTextEdit();
    controls = new QWidget();
    this->docname = name;
    this->docnum = num;
    this->docnote = note;
    this->docdate = date;
    t = new QTextDocument();
    talon->setDocument(t);

    set_layout();
    create_preview(model, name, num, note, date);
    connects();

}


inline void PrintPreview::set_layout(){
    QHBoxLayout *hlt = new QHBoxLayout();
    hlt->addWidget(close_button);
    hlt->addWidget(print_button);
    controls->setLayout(hlt);
    resize();

    QVBoxLayout *vlt = new QVBoxLayout();
    vlt->addWidget(controls);
    vlt->addWidget(talon);
    this->setLayout(vlt);
}

void PrintPreview::resize(){
    close_button->adjustSize();
    print_button->adjustSize();
    controls->setFixedSize(close_button->width()+print_button->width(), close_button->height() + 30);
}

inline void PrintPreview::connects(){
    QObject::connect(this->close_button, SIGNAL(clicked()),
                     this, SLOT(close_slot()));
    QObject::connect(this->print_button, SIGNAL(clicked()),
                     this, SLOT(print()));
}

void PrintPreview::create_preview(QSqlQueryModel *model, QString name, QString num, QString note, QString date){
    QSettings settings("erk", "DocsPrint");
    QString font = settings.value("FONTS/print_family", "Times New Roman").toString();
    int size = settings.value("FONTS/print_size", 14).toInt();
    // создаём хтмл
    QString html = "";//<style type=\"text/css\">\nTD{\nborder:1px solid black;\n}\n</style>";
    html += "<h1> Талон " + name + " №" + num + " от " + date + ".</h1>";
    html += "<h2>" + note + "</h2>";
    for(int i = 0; i < model->rowCount(); i++){
        html += "<table border=1 bordercolor=black width=100% style='margin: 10px 0px 0px 0px; font-size:" + QString::number(size) + "px; font-family:" + font + ";'>";
        html += "<tr>";
        html += "<td width=8% align='center' valign='center'><i>id</i></td>";
        html += "<td width=23% align='center' valign='center'><i>Наименование</i></td>";
        html += "<td width=8% align='center' valign='center'><i>Кол-во</i></td>";
        html += "<td width=8% align='center' valign='center'><i>Год</i></td>";
        html += "<td width=8% align='center' valign='center'><i>Приёмка</i></td>";
        html += "<td width=8% align='center' valign='center'><i>Склад</i></td>";
        html += "<td width=8% align='center' valign='center'><i>Стеллаж</i></td>";
        html += "<td width=8% align='center' valign='center'><i>Полка</i></td>";
        html += "<td width=8% align='center' valign='center'><i>Ящик</i></td>";
        html += "<td width=25% align='center' valign='center'><i>Категория</i></td>";
        html += "</tr>";
        //------------------------------------------------
        html += "<tr>";
        html += "<td rowspan='3' align='center' valign='center'><b>" + model->itemData(model->index(i,0))[0].toString() + "</td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,2))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,3))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,8))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,11))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,4))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,5))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,6))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,7))[0].toString() + "</b></td>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,12))[0].toString() + "</b></td>";
        html += "</tr>";
        html += "<tr>";
        html += "<td align='center' valign='center'><i>Доп. параметры</i></td>";
        html += "<td colspan='8' align='center' valign='center'><i>Примечание</i></td>";
        html += "</tr>";
        html += "<tr>";
        html += "<td align='center' valign='center'><b>" + model->itemData(model->index(i,13))[0].toString() + "</b></td>";
        html += "<td colspan='8' align='center' valign='center'><b>" + model->itemData(model->index(i,10))[0].toString() + "</b></td>";
        html += "</tr>";
        html += "</table>";
        html += "<br />";

    }

    talon->setHtml(html);
}

void PrintPreview::close_slot(){
    emit(close_signal());
}

void PrintPreview::print(){
    QPrinter *pp = new QPrinter();
    pp->setPageSize(QPrinter::A4);
    pp->setOrientation(QPrinter::Landscape);
    pp->setPageMargins(15,10,15,10,QPrinter::Millimeter);

    QPrintDialog *pd = new QPrintDialog(pp);
    if(pd->exec() == QDialog::Accepted){
        t->print(pp);
    }
    else
        return;

}
