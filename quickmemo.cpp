#include "quickmemo.h"
#include "ui_quickmemo.h"
#include <QDebug>
#include <QKeyEvent>
QuickMemo::QuickMemo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QuickMemo)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);
    connect(ui->btnSave,&QPushButton::clicked,this,&QuickMemo::saveQuit);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    // ui->input->setStyleSheet("color: white;"
    //                          //"selection-background-color: white;"
    //                          );
}

QuickMemo::~QuickMemo()
{
    delete ui;
}

void QuickMemo::saveQuit()
{
    QString msg=ui->input->toPlainText();
    wrapper w;
    //ptr->sendMemos(ui->input->toPlainText());
    w.sendMemos(msg);
    this->close();
}

void QuickMemo::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S && event->modifiers() == Qt::ControlModifier) {
        saveQuit();
        event->accept(); // 接受该事件，不再继续传递
    }
    else {
        QWidget::keyPressEvent(event); // 其他情况交由父类处理
    }
}

