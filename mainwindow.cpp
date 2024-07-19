#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include "quickmemo.h"
#include "IniConfig.h"
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QWebEngineSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setQuitOnLastWindowClosed(false);
    trayIcon=new QSystemTrayIcon(this);
    auto icon = QIcon(":/memos.png");//前面不应该加qrc。。。
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
    qDebug()<< "set hotkey"<< a.value("hotkey").toString();
    connect(hotkey,&QHotkey::activated,this,&MainWindow::whenHotkeyActivated);
    this->hide();
    QString url=a.value("memos/url").toString();
    qDebug()<<url;
    qDebug()<<1;
    m_profile.reset(new QWebEngineProfile("QMemos"));
    qDebug()<<1.1;
    m_profile->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    qDebug()<<1.2;
    m_profile->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    qDebug()<<1.3;
    m_profile->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    qDebug()<<1.4;
    m_profile->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, false);
    qDebug()<<m_profile->isOffTheRecord();
    qDebug()<<2;
    m_webview.reset(new QWebEngineView(m_profile.get()));

    ui->verticalLayout->addWidget(m_webview.get());
    m_webview->setUrl(QUrl("http://111.229.25.29:5231/"));

    //    ui->webEngineView->load(QUrl("http://111.229.25.29:5231/"));
    //auto cookiestore=ui->webEngineView->page()->profile()->cookieStore();
    //connect(cookiestore,&QWebEngineCookieStore::cookieAdded, this, &MainWindow::handleCookieAdded);
}
#include <QNetworkCookie>
#include <QWebEngineCookieStore>
MainWindow::~MainWindow()
{
    delete ui;
    qDebug()<<"~MainWindow()";
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

void MainWindow::handleCookieAdded(const QNetworkCookie &cookie){
    qDebug()<<cookie;
}

