#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>

#include <QtQml/QQmlApplicationEngine>

#include <QtGui/QGuiApplication>
#include <QFile>
int main(int argc, char **argv){
    qDebug()<<"hello world";

    QCoreApplication::setApplicationName("QMemos");
    QtWebEngineQuick::initialize();

    QGuiApplication app(argc, argv);



    QQmlApplicationEngine appEngine;
    QObject::connect(
        &appEngine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    //appEngine.load(QUrl("qrc:/MemosPage.qml"));
    appEngine.loadFromModule("untitled6","MemosPage");
    // if (appEngine.rootObjects().isEmpty())
    //     qFatal("Failed to load sources");



    return app.exec();
}
