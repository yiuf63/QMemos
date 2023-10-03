#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>

#include "IniConfig.h"
#include "wrapper.h"
QNetworkAccessManager *manager;

void postback(QNetworkReply* reply){
    QByteArray bytes = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << QStringLiteral("解析Json失败");
        return;
    }

    // 解析Json
    if (doucment.isObject())
    {
        QJsonObject obj = doucment.object();
        QJsonValue value;
        if (obj.contains("data"))
        {
            value = obj.take("data");
            if (value.isString())
            {
                QString data = value.toString();
                qDebug() << data;
            }
        }
    }


}

void post(){
    QJsonObject json;
    json.insert("User", "admin");
    json.insert("Password", "admin");

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    QNetworkRequest request;
    request.setUrl(QUrl("http://httpbin.org/post"));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager->post(request, dataArray);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IniConfig::initialPath();//必须在a出现之后，否则会有问题

//    manager=new QNetworkAccessManager;
//    //manager.
//    QObject::connect(manager,&QNetworkAccessManager::finished,[&a](auto reply){
//        postback(reply);

//    });

    wrapper w;
    QString cont;
    QTextStream qin(stdin);
    qin>>cont;
    w.sendMemos(cont);

    return a.exec();
}
