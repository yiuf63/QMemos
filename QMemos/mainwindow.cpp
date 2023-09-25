#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include "quickmemo.h"
#include "IniConfig.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setQuitOnLastWindowClosed(false);
    trayIcon=new QSystemTrayIcon(this);
    auto icon = QIcon(":/heart.png");//前面不应该加qrc。。。
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    trayIcon->setToolTip("QMemos");

    //trayIcon->showMessage("title","text",QSystemTrayIcon::Information,3000);

    QAction *quit=new QAction(QStringLiteral("quit"));
    connect(quit,&QAction::triggered,[&](){
        QCoreApplication::quit();
    });
    trayMenu=new QMenu;
    trayMenu->addAction(quit);
    trayIcon->setContextMenu(trayMenu);
    setWindowTitle(tr("QMemos"));
//    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::messageClicked);
//    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
    connect(trayIcon,&QSystemTrayIcon::activated,this,&MainWindow::whenTrayIconActivated);
    trayIcon->show();

    IniConfig a;

    hotkey = new QHotkey(QKeySequence(a.value("hotkey").toString()),true,qApp);
    connect(hotkey,&QHotkey::activated,this,&MainWindow::whenHotkeyActivated);
    this->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::whenHotkeyActivated(){
    QuickMemo w;
    w.exec();
}

void MainWindow::whenTrayIconActivated(QSystemTrayIcon::ActivationReason reason){
    qDebug()<<reason;
    switch (reason) {
    case 2:;
    case 3:this->show();
    default:
        break;
    }
}
