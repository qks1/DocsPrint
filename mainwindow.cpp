#include "mainwindow.h"
#include "settingsdialog.h"

MainWindow::MainWindow(bool success, QSqlDatabase db)
{
    is_connect = success;
    base = db;
    settings = new QSettings("erk", "DocsPrint");
    docs_list = 0;
    doc = 0;
    preview = 0;
    mwidget = 0;
    // если соединение с базой было успешным, создаём центральный виджет (таблицу с документами).
    // Иначе экран будет пустым, пока не соединимся с базой
    if(is_connect)
        create_central_widget();

    // создаём и оживляем меню
    create_actions();
    create_menu();
}

void MainWindow::create_central_widget(){
    // создаём таблицу с документами
    docs_list = new MTable();
    // так как центральный виджет будем меняться, запихиваем созданную таблицу в StackedWidget
    mwidget = new QStackedWidget();
    mwidget->addWidget(docs_list);
    this->setCentralWidget(mwidget);

    // по двоёному щелчку на таблице - показать окно документа
    connect(this->docs_list, SIGNAL(show_doc_signal(int, QString, QString, QString, QString)),
            this, SLOT(signal_from_list(int, QString, QString, QString, QString)));
}

void MainWindow::create_menu(){
    // создаём меню и добавляем туда действия
    QMenu *menu = menuBar()->addMenu("Меню");
    menu->addAction(quit_action);
    menu->addAction(settings_action);
}

void MainWindow::create_actions(){
    quit_action = new QAction("Выход", this);
    quit_action->setStatusTip("Выход из программы");
    connect(quit_action, SIGNAL(activated()), this, SLOT(send_exit()));

    settings_action = new QAction("Настройки", this);
    quit_action->setStatusTip("Открыть окно настроек");
    connect(settings_action, SIGNAL(activated()), this, SLOT(send_settings()));
}


void MainWindow::send_exit(){
    // в случае выбора пункта меню "Выход"
    emit(exit_signal());
}

void MainWindow::send_settings(){
    // открыть диалоговое окно с настройками
    SettingsDialog *sd = new SettingsDialog();
    if(sd->exec() == QDialog::Accepted){
        delete sd;
        // если нажата кнопка ОК и хоть что-то изменено, пересоздаём соединение с базой
        if(base.databaseName() != settings->value("DATABASE/basename").toString() ||
           base.hostName() != settings->value("DATABASE/basehost").toString() ||
           base.userName() != settings->value("DATABASE/baseuser").toString() ||
           base.password() != settings->value("DATABASE/basepass").toString())
                reload_base();
        // если измененён шрифт, меняем его
        QFont new_font;
        new_font.setFamily(settings->value("FONTS/system_family").toString());
        new_font.setPointSize(settings->value("FONTS/system_size").toInt());
        if(new_font != qApp->font()){
            qApp->setFont(new_font);
            if(docs_list > 0) docs_list->resize();
            if(doc > 0) doc->resize();
            if(preview > 0) preview->resize();
        }
        settings->sync();
        return;
    }
    delete sd;
}

void MainWindow::reload_base(){
    // закрываем текущее соединение и создаём новое
    base.close();
    base = QSqlDatabase::addDatabase("QMYSQL");
    settings->beginGroup("DATABASE");
    QString DB_NAME = settings->value("basename", "sqlmbase").toString();
    QString DB_USER = settings->value("baseuser", "kk").toString();
    QString DB_PASS = settings->value("basepass", "").toString();
    QString DB_HOST = settings->value("basehost", "localhost").toString();
    settings->endGroup();
    base.setDatabaseName(DB_NAME);
    base.setUserName(DB_USER);
    base.setPassword(DB_PASS);
    base.setHostName(DB_HOST);
    // если base.open завершается неудачно, выдаём ошибку
    if(!(base.open())){
        QMessageBox::warning(0, "Ошибка", "Не удалось подключиться к базе данных. Проверьте настройки.", QMessageBox::Ok);
        return;
    }
    // иначе, если соединение ещё не было установлено - создаём таблицу с документами, иначе перезаполняем таблицу
    else{
        if(!is_connect){
            create_central_widget();
            is_connect = true;
        }
        else
            docs_list->fill();
    }
}

// создание окна документа
void MainWindow::signal_from_list(int id, QString name, QString num, QString note, QString date){
    // такого не может быть, но пусть будет
    if(!is_connect){
        QMessageBox::warning(this, "Странная ошибка", "Таблица ещё не создана");
        return;
    }
    doc = new DocTable(id, name, num, note, date);
    // добавляем созданный виджет в StackedWidget и делаем его активным
    mwidget->addWidget(doc);
    mwidget->setCurrentIndex(mwidget->indexOf(doc));

    QObject::connect(this->doc, SIGNAL(close_signal()),
            this, SLOT(doc_closed()));
    connect(this->doc, SIGNAL(print_preview(QSqlQueryModel*, QString, QString, QString, QString)),
            this, SLOT(signal_from_doc(QSqlQueryModel*, QString, QString, QString, QString)));
}

// создание окна превью
void MainWindow::signal_from_doc(QSqlQueryModel *model, QString name, QString num, QString note, QString date){
    // передаём туда название документа, номер, дату и примечание, чтобы вставить их в заголовок талона
    // а сам список позиций передаём в виде QSqlQueryModel
    preview = new PrintPreview(model, name, num, note, date);
    // добавляем созданный виджет в StackedWidget и делаем его активным
    mwidget->addWidget(preview);
    mwidget->setCurrentIndex(mwidget->indexOf(preview));

    QObject::connect(this->preview, SIGNAL(close_signal()),
            this, SLOT(preview_closed()));

}

// закрытие окна документа
void MainWindow::doc_closed(){
    // на всякий случай проверим, есть ли виджет документа в StackedWidget, и если всё нормально - удаляем его
    if(mwidget->indexOf(doc) != -1)
        mwidget->removeWidget(doc);
    // делаем активным виджетом список документов
    mwidget->setCurrentIndex(mwidget->indexOf(docs_list));
}

// закрытие окна превью
void MainWindow::preview_closed(){
    // на всякий случай проверим, есть ли виджет превью в StackedWidget, и если всё нормально - удаляем его
    if(mwidget->indexOf(preview) != -1)
        mwidget->removeWidget(preview);
    // делаем активным виджетом окно документа
    mwidget->setCurrentIndex(mwidget->indexOf(doc));
}
