#include "apitest.h"
#include<QDebug>
ApiTest::ApiTest(QObject *parent)
    : QObject{parent}
{

}

void ApiTest::test()
{
    qDebug()<<"test";
    QVERIFY(true);
}

