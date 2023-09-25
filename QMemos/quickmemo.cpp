#include "quickmemo.h"
#include "./ui_quickmemo.h"
#include <QDebug>

QuickMemo::QuickMemo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QuickMemo)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);
    connect(ui->btn,&QPushButton::clicked,this,&QuickMemo::saveQuit);
}

QuickMemo::~QuickMemo()
{
    delete ui;
}

void QuickMemo::saveQuit()
{
    QString msg=ui->input->toPlainText();
    qDebug()<<msg;
    this->close();
}
