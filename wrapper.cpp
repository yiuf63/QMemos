#include "wrapper.h"
#include "IniConfig.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QDebug>

wrapper* wrapper::ptr =nullptr;//静态变量初始化
// Create a slot function to handle the response
void handleResponse(QNetworkReply *reply) {
    // Check if the reply has any error
    if (reply->error() != QNetworkReply::NoError) {
        // Print the error and exit
        qCritical() << "Error:" << reply->errorString()<<"\n"<<reply->error();
        QCoreApplication::exit(1);
        return;
    }
    // Read the response data
    QByteArray data = reply->readAll();
    qDebug()<<data;
    // Parse the JSON data
    QJsonDocument doc = QJsonDocument::fromJson(data);
    qDebug()<<doc;

    // Check if the JSON data is valid
    if (!doc.isObject()) {
        // Print the error and exit
        qCritical() << "Invalid JSON data";
        //QCoreApplication::exit(1);
        return;
    }

    // Get the JSON object
    QJsonObject obj = doc.object();

    // Print the response status code and content
    //qDebug() << "Status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    //qDebug() << "Content:" << QJsonDocument(obj).toJson();

    //QCoreApplication::exit(0);
}
wrapper::wrapper(QObject *parent)
    : QNetworkAccessManager{parent}
{
    manager = new QNetworkAccessManager();

    QObject::connect(manager, &QNetworkAccessManager::finished, handleResponse);
}

wrapper *wrapper::instances()
{
    if(ptr==nullptr){
        ptr=new wrapper;
    }
    return ptr;
}

bool wrapper::sendMemos(QString content)
{
    if(content.isEmpty()) return false;
    IniConfig a;
    qDebug()<<IniConfig::path<<a.allKeys();
    url=a.value("memos/url").toString()+"/api/v1/memos";//我去了。。。 就是这个链接不对，弄得那么久搞不定
    username=a.value("memos/username").toString();
    password=a.value("memos/password").toString();
    token=a.value("memos/access_token").toString();

    qDebug()<<url<<username<<password<<content<<token;
    const QString visibility = "PRIVATE";
    const QJsonArray resourceIdList = QJsonArray();
    const QUrl api_url = QUrl(url);
    // Construct the JSON data with the memo fields
    const QJsonObject json_data = QJsonObject({
        {"content", content},
        {"visibility", visibility},
        {"resourceIdList",resourceIdList}
    });

    const QByteArray auth = (username + ":" + password).toUtf8().toBase64();
    // Create a QNetworkRequest object and set the URL and HTTP method
    QNetworkRequest request;
    request.setUrl(api_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //request.setRawHeader("Authorization","Basic "+auth);
    request.setRawHeader("Authorization","Bearer "+ token.toLatin1());

    //request.setRawHeader("token",token.toLatin1());
    // Create a QNetworkAccessManager object

    qDebug()<<api_url;
    qDebug()<<auth;
    qDebug()<<json_data;
    qDebug()<<token.toLatin1();
    // Send the POST request and get the QNetworkReply object
    auto rep=manager->post(request, QJsonDocument(json_data).toJson());
    handleResponse(rep);
    return false;
}



