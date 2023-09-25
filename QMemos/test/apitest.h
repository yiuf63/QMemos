#ifndef APITEST_H
#define APITEST_H

#include <QObject>
#include <QtTest/QtTest>

class ApiTest : public QObject
{
    Q_OBJECT
public:
    explicit ApiTest(QObject *parent = nullptr);

private slots:
    void test();

signals:

};
/*
 *
 initTestCase()将在执行第一个测试函数之前调用。
 initTestCase_data()将调用以创建全局测试数据表。
 cleanupTestCase()将在执行最后一个测试函数后调用。
 init()将在执行每个测试函数之前调用。
 cleanup()将在每次测试函数后调用。
*/
#endif // APITEST_H
