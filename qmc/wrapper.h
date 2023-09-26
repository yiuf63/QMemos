#ifndef WRAPPER_H
#define WRAPPER_H

#include <QNetworkAccessManager>

class wrapper : public QNetworkAccessManager
{
public:
    explicit wrapper(QObject *parent = nullptr);

    QNetworkAccessManager *manager;
private:
    QString username,password,url;
    QString content;

    void signin();

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
