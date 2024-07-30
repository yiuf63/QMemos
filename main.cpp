#include "IniConfig.h"
#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSharedMemory>
#include <QMessageBox>
void configRead(){
    IniConfig::initialPath();
    IniConfig a;
    auto keys=a.allKeys();
    if(!keys.contains("hotkey"))
        a.setValue("hotkey",QKeySequence("Ctrl+Alt+Q"));
}


int main(int argc, char *argv[]){
    //Q_INIT_RESOURCE(res);
    qDebug()<<"QMemos start ";
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);
    QIcon appIcon(":/memos.png");
    QApplication::setWindowIcon(appIcon);

    QSharedMemory singleton(a.applicationName());
    if(!singleton.create(1))  {
        QMessageBox::about(nullptr,"Info","No second start.");
        return -1;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QMemos_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
//    QuickMemo w;
    configRead();
    MainWindow w;
    w.show();
    return a.exec();
}
