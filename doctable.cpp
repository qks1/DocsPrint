#include "doctable.h"


DocTable::DocTable(int iddoc, QString docname, QString docnum, QString docnote, QString docdate, QWidget *parent) :
    QWidget(parent)
{
    this->iddoc = iddoc;
    this->name = docname;
    this->num = docnum;
    this->note = docnote;
    this->date = docdate;
    controls = new QWidget();
    storages_box = new QGroupBox("Выберите склады для печати");
    // чекбоксы для складов будем создавать динамически, после заполнения таблицы
    print = new QPushButton("ПЕЧАТЬ");
    close_button = new QPushButton("НАЗАД");
    table = new QTableView();
    model = new QSqlQueryModel();
    pmodel = new MyProxyModelForDoc();
    row_height = table->verticalHeader()->fontMetrics().height() + 2;
    first = true;
    storages.clear();
    storages_selected.clear();

    pmodel->setSourceModel(model);
    table->setModel(pmodel);

    set_columns_names();
    custom_table();
    set_layout();
    connects();
    fill(iddoc);
}

DocTable::~DocTable(){
    QCheckBox *cb;
    foreach(cb, storages_list)
        delete cb;
}

inline void DocTable::connects(){
    QObject::connect(this->close_button, SIGNAL(clicked()),
                     this, SLOT(close_slot()));
    QObject::connect(this->print, SIGNAL(clicked()),
                     this, SLOT(preview_slot()));
}

void DocTable::custom_table(){
    table->verticalHeader()->hide();
    table->horizontalHeader()->setMovable(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setDefaultSectionSize(row_height);
    table->horizontalHeader()->setHighlightSections(false);
    table->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    table->setAlternatingRowColors(true);
}

void DocTable::rename_columns(){
    for(int i = 0; i < pmodel->columnCount(); i++){
        if(columns[pmodel->headerData(i, Qt::Horizontal).toString()] != "")
            pmodel->setHeaderData(i, Qt::Horizontal, columns[pmodel->headerData(i, Qt::Horizontal).toString()]);
    }
}


inline void DocTable::set_layout(){
    // только групбокс с чекбоксами по кол-ву складов и кнопка печать
    QHBoxLayout *hlt = new QHBoxLayout();
    hlt->addWidget(close_button);
    hlt->addWidget(print);
    QHBoxLayout *wlt = new QHBoxLayout();
    storages_box->setLayout(wlt);
    hlt->addWidget(storages_box);
    controls->setLayout(hlt);
    resize();
    QVBoxLayout *vlt = new QVBoxLayout();
    vlt->addWidget(controls);
    vlt->addWidget(table);

    this->setLayout(vlt);
}

void DocTable::resize(){
    close_button->adjustSize();
    print->adjustSize();
    storages_box->setGeometry(0,0,qApp->font().pointSize()*30,qApp->font().pointSize()*10);
    int total_width = close_button->width() + print->width() + storages_box->width();
    int total_height = storages_box->height();
    controls->setFixedSize(total_width, total_height);
    table->verticalHeader()->setDefaultSectionSize(table->verticalHeader()->fontMetrics().height() + 2);
    table->resizeColumnsToContents();
    row_height = table->verticalHeader()->fontMetrics().height() + 2;
    table->horizontalHeader()->resizeSection(1, row_height*1.5);
}

inline void DocTable::set_columns_names(){
    columns["mdate"] = "Дата";
    columns["myear"] = "Год";
    columns["pod"] = "Г";
    columns["tovmark"] = "Тов. марка";
    columns["fost"] = "Кол-во";
    columns["storage"] = "Склад";
    columns["board"] = "Стеллаж.";
    columns["plase"] = "Полка";
    columns["box"] = "Ящик";
    columns["notes"] = "Доп.парам.";
    columns["primmen"] = "Примечание";
    columns["tovcat"] = "Категория";
    columns["nu"] = "Норм.уп.";
    columns["except"] = "Приёмка";
    columns["id"] = "id";
}

void DocTable::add_checkboxes(){
    QString s;
    QLayoutItem *item;
    while((item = storages_box->layout()->takeAt(0)) != 0){
        item->widget()->hide();
        //item->widget()->deleteLater();
    }
    delete storages_box->layout();
    QHBoxLayout *lt = new QHBoxLayout();
    QCheckBox *cb;
    foreach(cb, storages_list){
        cb->setChecked(storages.indexOf(cb->text()) < 0 ? false : true);
        lt->addWidget(cb);
    }
    storages_box->setLayout(lt);

}

void DocTable::fill(int iddoc){
    QString storages_string = (storages_list.size() == 0 ? "" : " AND storage IN (" + storages.join(",") + ") ");
    QString query = "SELECT idtov,pod,tovmark,fost,storage,board,plase,box,myear,nu,primmen,except,tovcat,notes FROM chek WHERE idlist = '" + QString::number(iddoc) + "' " + storages_string + " ORDER BY numt";
    model->setQuery(query);
    if(first){
        // выбираем номера складов
        QSqlQuery strgs;
        strgs.exec("SELECT DISTINCT storage FROM chek WHERE idlist = '" + QString::number(iddoc) + "' ORDER BY storage");
        QCheckBox *cb = 0;
        while(strgs.next()){
            cb = new QCheckBox(strgs.value(0).toString());
            cb->setChecked(true);
            storages_list << cb;
            storages << strgs.value(0).toString();
            QObject::connect(cb, SIGNAL(stateChanged(int)),
                             this, SLOT(checkbox_pressed(int)));
        }
        add_checkboxes();
        first = false;
    }
    rename_columns();
    //table->hideColumn(0);
    table->resizeColumnsToContents();
    table->horizontalHeader()->resizeSection(1, row_height*1.5);
}

void DocTable::fill_slot(int id){
    this->fill(id);
}

void DocTable::close_slot(){
    emit(close_signal());
}

void DocTable::preview_slot(){
    emit(print_preview(model, name, num, note, date));
}

void DocTable::checkbox_pressed(int c){
    QCheckBox *cb;
    storages.clear();
    foreach(cb, storages_list){
        if(cb->checkState() == Qt::Checked)
            storages << cb->text();
    }
    if(!first) fill(this->iddoc);
}
