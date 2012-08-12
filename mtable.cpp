#include "mtable.h"


MTable::MTable(QWidget *parent)
    : QWidget(parent)
{
    // создаём все кнопки и поя ввода даты, который для удобства размещения поместим на специальный виджет controls
    controls = new QWidget();
    from_label = new QLabel("С:");
    to_label = new QLabel("По:");
    type_label = new QLabel("Тип:");
    from_date = new QDateEdit();
    to_date = new QDateEdit;
    type_box = new QComboBox();
    refresh_button = new QPushButton("ОБНОВИТЬ");
    table = new QTableView();
    model = new QSqlQueryModel();
    pmodel = new MyProxyModel();

    // сохраним высоту строки, потом она нам понадобится, чтобы по неё калибровать ширину некоторых столбцов
    row_height = table->verticalHeader()->fontMetrics().height() + 2;

    //hidden - показываем или нет скрытые типы документов. По умолчанию - нет.
    hidden = false;
    // фильтр по типу документов. Пока пуст.
    filter = 0;

    // связываем модели и представления
    pmodel->setSourceModel(model);
    table->setModel(pmodel);

    // воплощаем всё в реальность
    set_columns_names();
    fill_checkbox();
    custom_dates();
    custom_table();
    set_layout();
    connects();
    fill();

}

inline void MTable::connects(){
    // смена даты
    QObject::connect(this->from_date, SIGNAL(dateChanged(QDate)),
                     this, SLOT(date_changed(QDate)));
    QObject::connect(this->to_date, SIGNAL(dateChanged(QDate)),
                     this, SLOT(date_changed(QDate)));

    // чекбоксы со складами
    QObject::connect(this->type_box, SIGNAL(activated(QString)),
                     this, SLOT(checkbox_used(QString)));

    // кнопка "Обновить"
    QObject::connect(this->refresh_button, SIGNAL(clicked()),
                     this, SLOT(refresh()));

    // двойной щелчок по строке - вызов документа
    QObject::connect(this->table, SIGNAL(doubleClicked(QModelIndex)),
                     this, SLOT(double_click(QModelIndex)));
}

inline void MTable::custom_dates(){
    // по умолчанию устанавливаем в оба поля выбора даты сегодняшнее число
    QDate date = QDate::currentDate();
    from_date->setDate(date);
    to_date->setDate(date);

    // активируем выпадающий календарь
    from_date->setCalendarPopup(true);
    to_date->setCalendarPopup(true);
    from_date->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    to_date->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
}

void MTable::custom_table(){
    // приводим таблицу к нужному виду: скрываем заголовок, делаем выбор целой строки, запрещаем редактирование,
    // ставим высоту строки по умолчанию, раскрашиваем через строчку, отменяем выделение заголовков жирным
    table->verticalHeader()->hide();
    //table->horizontalHeader()->setMovable(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setDefaultSectionSize(row_height);
    table->horizontalHeader()->setHighlightSections(false);
    table->setAlternatingRowColors(true);
    // это в принципе не нужно: по щелчку правой кнопкой на выдавать контекстного меню
    table->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
}

inline void MTable::set_layout(){
    // все элементы управления запихнём в виджет
    QHBoxLayout *hlt = new QHBoxLayout();
    hlt->addWidget(from_label);
    hlt->addWidget(from_date);
    hlt->addWidget(to_label);
    hlt->addWidget(to_date);
    hlt->addSpacing(20);
    hlt->addWidget(type_label);
    hlt->addWidget(type_box);
    hlt->addWidget(refresh_button);
    resize();
    controls->setLayout(hlt);

    // виджет и таблицу пихаем в лайаут
    QVBoxLayout *vlt = new QVBoxLayout();
    vlt->addWidget(controls);
    vlt->addWidget(table);

    this->setLayout(vlt);
}

void MTable::resize(){
    from_label->adjustSize();
    from_date->adjustSize();
    to_label->adjustSize();
    to_date->adjustSize();
    type_label->adjustSize();
    type_box->adjustSize();
    refresh_button->adjustSize();
    int total_width = from_label->width() + from_date->width() + to_label->width() + to_date->width() + type_label->width() + type_box->width() + refresh_button->width() + 20;
    int total_height = from_label->height() + 30;
    controls->setFixedSize(total_width, total_height);
    table->verticalHeader()->setDefaultSectionSize(table->verticalHeader()->fontMetrics().height() + 2);
    table->resizeColumnsToContents();
    row_height = table->verticalHeader()->fontMetrics().height() + 2;
    table->horizontalHeader()->resizeSection(1, row_height*1.5);
    table->horizontalHeader()->resizeSection(2, row_height*1.5);
    table->horizontalHeader()->resizeSection(3, row_height*1.5);
}

inline void MTable::set_columns_names(){
    columns["mdate"] = "Дата";
    columns["mtime"] = "Время";
    columns["doc"] = "Документ";
    columns["numdoc"] = "Номер";
    columns["klient"] = "Клиент";
    columns["gg"] = "гот.";
    columns["pp"] = "опл.";
    columns["im"] = "спис.";
    columns["vidan"] = "выд.";
    columns["prim"] = "Примечание";
    columns["prim_k"] = "Для кого";
    columns["id"] = "id";
}

void MTable::rename_columns(){
    // переименовываем столбцы, беря названия из columns
    for(int i = 0; i < pmodel->columnCount(); i++){
        if(columns[pmodel->headerData(i, Qt::Horizontal).toString()] != "")
            pmodel->setHeaderData(i, Qt::Horizontal, columns[pmodel->headerData(i, Qt::Horizontal).toString()]);
    }
}

// заполнение таблицы
void MTable::fill(){
    // устанавливаем фильтры (по дате и типу документов), формируем запрос
    QString begin = from_date->date().toString("yyyy-MM-dd");
    QString end = to_date->date().toString("yyyy-MM-dd");
    QString docs = (hidden ? " > 0" : " < 20");     // >0 - это просто так
    QString query = "SELECT id,pp,gg,vidan,doc,numdoc,mdate,mtime,klient,prim FROM listdoc WHERE mdate >= '" + begin + "' AND mdate <= '" + end + "' AND g1 " + docs + " AND g1 != '7' AND im != '3' " + (filter == 0 ? "" : (" AND g1 = " + QString::number(filter))) + " ORDER BY mdate DESC, mtime DESC";
    model->setQuery(query);
    // переименовываем столбцы
    rename_columns();
    // скрываем столбец id
    table->hideColumn(0);
    // подбираем ширину столбцов
    table->resizeColumnsToContents();
    table->horizontalHeader()->resizeSection(1, row_height*1.5);
    table->horizontalHeader()->resizeSection(2, row_height*1.5);
    table->horizontalHeader()->resizeSection(3, row_height*1.5);
}

// обрабатываем нажатие Ctrl+Q
void MTable::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Q:
        if(event->modifiers() && Qt::ControlModifier){
            switch_hidden();
        }
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void MTable::fill_checkbox(){
    type_box->clear();
    type_box->addItem("");
    type_box->addItem("Чек");
    type_box->addItem("Счёт");
    type_box->addItem("Заявка");
    type_box->addItem("Накладная");
    if(hidden){
        type_box->addItem("Р-отгрузка");
        type_box->addItem("Б-отгрузка");
        type_box->addItem("М-отгрузка");
    }
}

void MTable::date_changed(QDate date){
    fill();
}

void MTable::switch_hidden(){
    hidden = !hidden;
    fill_checkbox();
    fill();
}

void MTable::checkbox_used(QString str){
    if(str == "Счёт")
        filter = 2;
    else if(str == "Заявка")
        filter = 5;
    else if(str == "Накладная")
        filter = 7;
    else if(str == "Чек")
        filter = 1;
    else if(str == "Р-отгрузка")
        filter = 21;
    else if(str == "Б-отгрузка")
        filter = 22;
    else if(str == "М-отгрузка")
        filter = 20;
    else
        filter = 0;
    fill();
}

void MTable::refresh(){
    fill();
}

void MTable::double_click(QModelIndex mi){
    int id = pmodel->data(pmodel->index(mi.row(),0), Qt::DisplayRole).toInt();
    QString docname = pmodel->data(pmodel->index(mi.row(),4), Qt::DisplayRole).toString();
    QString docnum = pmodel->data(pmodel->index(mi.row(),5), Qt::DisplayRole).toString();
    QString docnote = pmodel->data(pmodel->index(mi.row(),9), Qt::DisplayRole).toString();
    QString docdate = pmodel->data(pmodel->index(mi.row(),6), Qt::DisplayRole).toString();
    emit(show_doc_signal(id, docname, docnum, docnote, docdate));
}
