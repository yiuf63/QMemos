#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>

#include <QtQml/QQmlApplicationEngine>

#include <QtGui/QGuiApplication>
int main(int argc, char **argv){
    qDebug()<<"hello world";

    QCoreApplication::setApplicationName("QMemos");
    QtWebEngineQuick::initialize();

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine appEngine;
    appEngine.load(QUrl("qrc:/MemosPage.qml"));

    if (appEngine.rootObjects().isEmpty())
        qFatal("Failed to load sources");



    return app.exec();
}
