#include "wrapper.h"
#include "IniConfig.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QDebug>


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

    // Parse the JSON data
    QJsonDocument doc = QJsonDocument::fromJson(data);

    // Check if the JSON data is valid
    if (!doc.isObject()) {
        // Print the error and exit
        qCritical() << "Invalid JSON data";
        QCoreApplication::exit(1);
        return;
    }

    // Get the JSON object
    QJsonObject obj = doc.object();

    // Print the response status code and content
    qDebug() << "Status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Content:" << QJsonDocument(obj).toJson();

    // Exit the application
    QCoreApplication::exit(0);
}

wrapper::wrapper(QObject *parent)
    : QNetworkAccessManager{parent}
{
    IniConfig a;
    qDebug()<<a.allKeys()<<IniConfig::path;
    url=a.value("login/url").toString();
    username=a.value("login/username").toString();
    password=a.value("login/password").toString();
    url=url+"api/memo";
    content = "Hello #memos from code";
    qDebug()<<url<<username<<password<<content;
    const QString visibility = "PRIVATE";
    const QJsonArray resourceIdList = QJsonArray();
    const QUrl api_url = QUrl(url);
    // Construct the JSON data with the memo fields
    const QJsonObject json_data = QJsonObject({
        {"content", content},
        {"visibility", visibility},
        {"resourceIdList", resourceIdList}
    });
    const QByteArray auth = (username + ":" + password).toUtf8().toBase64();
    // Create a QNetworkRequest object and set the URL and HTTP method
    QNetworkRequest request;
    request.setUrl(api_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization","Basic "+auth);
    // Create a QNetworkAccessManager object
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // Connect the finished() signal and the handleResponse() slot
    QObject::connect(manager, &QNetworkAccessManager::finished, handleResponse);
    qDebug()<<api_url;
    qDebug()<<auth;
    qDebug()<<json_data;

    // Send the POST request and get the QNetworkReply object
    QNetworkReply *reply = manager->post(request, QJsonDocument(json_data).toJson());

}

bool wrapper::sendMemos(QString)
{
    return false;
}



