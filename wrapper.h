﻿#ifndef WRAPPER_H
#define WRAPPER_H

#include <QtNetwork/QNetworkAccessManager>

class wrapper : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit wrapper(QObject *parent = nullptr);

    QNetworkAccessManager *manager;

    static wrapper* instances();
    inline QString getUrl(){
        return url;
    }
private:
    QString username,password,url,token;
    QString content;

    static wrapper* ptr;

public slots:
    bool sendMemos(QString);

};

#endif // WRAPPER_H

/*
    IniConfig::initialPath();
    IniConfig b;
    b.setValue("login/url","***");
    b.setValue("login/username","***");
    b.setValue("login/password","***");
    b.setValue("login/openid","***");
    b.setValue("login/access_token","***");
*/
