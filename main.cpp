#include <QtGui>
#include <QtSql>
#include "mtable.h"
#include "mainwindow.h"

bool createConnection(QSqlDatabase db){
    // читаем настройки
    QSettings settings("erk", "DocsPrint");
    settings.beginGroup("DATABASE");
    QString DB_NAME = settings.value("basename", "sqlmbase").toString();
    QString DB_USER = settings.value("baseuser", "kk").toString();
    QString DB_PASS = settings.value("basepass", "").toString();
    QString DB_HOST = settings.value("basehost", "localhost").toString();
    settings.endGroup();
    // перезаписываем настройки, если что-то было пусто
    settings.beginGroup("DATABASE");
    if(settings.value("basename").toString() != DB_NAME)
        settings.setValue("basename", DB_NAME);
    if(settings.value("basehost").toString() != DB_HOST)
        settings.setValue("basehost", DB_HOST);
    if(settings.value("baseuser").toString() != DB_USER)
        settings.setValue("baseuser", DB_USER);
    if(settings.value("basepass").toString() != DB_PASS)
        settings.setValue("basepass", DB_PASS);
    settings.endGroup();

    // устанавливаем параметры БД
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASS);
    db.setHostName(DB_HOST);

    // если db.open завершается неудачно, выдаём ошибку
    if(!(db.open())){
        QMessageBox::warning(0, "Ошибка", "Не удалось подключиться к базе данных. Проверьте настройки.\n" + db.lastError().text(), QMessageBox::Ok);
        return false;
    }
    // если с базой соединились, возвращаем true
    return true;
}

void read_fonts(){
    QSettings settings("erk", "DocsPrint");
    settings.beginGroup("FONTS");
    QString system_font_family = settings.value("system_family", qApp->font().family()).toString();
    int system_font_size = settings.value("system_size", 8).toInt();
    QString print_font_family = settings.value("print_family", qApp->font().family()).toString();
    int print_font_size = settings.value("print_size", 14).toInt();
    settings.endGroup();
    if(system_font_size <= 0)
        system_font_size = 12;
    if(print_font_size <= 0)
        print_font_size = 14;

    QFont system_font, print_font;
    system_font.setFamily(system_font_family);
    system_font.setPointSize(system_font_size);
    print_font.setFamily(print_font_family);
    print_font.setPointSize(print_font_size);
    qApp->setFont(system_font);

    settings.beginGroup("FONTS");
    if(settings.value("system_family").toString() != system_font_family)
            settings.setValue("system_family", system_font_family);
    if(settings.value("system_size").toInt() != system_font_size)
            settings.setValue("system_size", system_font_size);
    if(settings.value("print_family").toString() != print_font_family)
            settings.setValue("print_family", print_font_family);
    if(settings.value("print_size").toInt() != print_font_size)
            settings.setValue("print_size", print_font_size);
    settings.endGroup();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

    app.setApplicationName("Печать талонов");
    app.setApplicationVersion("1.0.0");
    app.setWindowIcon(QIcon("icon.png"));

    // создаём соединение с БД
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    bool success = createConnection(db);

    // читаем из настроек и устанавливаем шрифты
    read_fonts();

    // создаём главное окно, в констркуктор которого передаём результат соединения с БД
    MainWindow *mw = new MainWindow(success, db);
    mw->setWindowState(Qt::WindowMaximized);
    mw->setWindowTitle("Печать талонов");
    mw->show();


    // закрытие окна при выборе пункта меню "Закрыть"
    QObject::connect(mw, SIGNAL(exit_signal()),
            &app, SLOT(closeAllWindows()));




    return app.exec();
}
