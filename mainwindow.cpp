#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include "quickmemo.h"
#include "IniConfig.h"
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QWebEngineSettings>
#include <QInputDialog>>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //creat trayIcon
    QApplication::setQuitOnLastWindowClosed(false);
    trayIcon=new QSystemTrayIcon(this);
    auto icon = QIcon(":/memos.png");//前面不应该加qrc。。。
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    trayIcon->setToolTip("QMemos");
    trayIcon->showMessage("title","text",QSystemTrayIcon::Information,3000);
    QAction *quit=new QAction(QStringLiteral("quit"));
    connect(quit,&QAction::triggered,[&](){
        QCoreApplication::quit();
    });
    //添加手动设置信息的方法
    QAction *setUrl=new QAction(QStringLiteral("set Url"));//本应在第一次启动的时候添加
    connect(setUrl,&QAction::triggered,this,[this](){
        QString url;
        IniConfig a;
        while(url.isEmpty()){
            url=QInputDialog::getText(this,tr("设定服务器地址"),tr("请输入memos服务器地址："));
        }
        a.setValue("memos/url",url);
    });
    QAction *setUsername=new QAction(QStringLiteral("set Username"));//只能在此处设置
    connect(setUsername,&QAction::triggered,this,[this](){
        QString username;
        IniConfig a;
        while(username.isEmpty()){
            username=QInputDialog::getText(this,tr("设定服务器地址"),tr("请输入memos服务器地址："));
        }
        a.setValue("memos/username",username);
    });
    QAction *setToken=new QAction(QStringLiteral("set Access-Token"));//本应在登录的时候自动读取
    connect(setToken,&QAction::triggered,this,[this](){
        QString token;
        IniConfig a;
        while(token.isEmpty()){
            token=QInputDialog::getText(this,tr("设定服务器地址"),tr("请输入memos服务器地址："));
        }
        a.setValue("memos/username",token);
    });
    trayMenu=new QMenu;
    trayMenu->addAction(setUrl);
    trayMenu->addAction(setUsername);
    trayMenu->addAction(setToken);
    trayIcon->setContextMenu(trayMenu);
    trayMenu->addAction(quit);

    setWindowTitle(tr("QMemos"));
//    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::messageClicked);
//    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
    connect(trayIcon,&QSystemTrayIcon::activated,this,&MainWindow::whenTrayIconActivated);
    trayIcon->show();

    //read config
    IniConfig a;
    hotkey = new QHotkey(QKeySequence(a.value("hotkey").toString()),true,qApp);
    qDebug()<< "set hotkey"<< a.value("hotkey").toString();
    connect(hotkey,&QHotkey::activated,this,&MainWindow::whenHotkeyActivated);

    QString url=a.value("memos/url").toString();
    qDebug()<<url;
    while(url.isEmpty()){
        url=QInputDialog::getText(this,tr("设定服务器地址"),tr("请输入memos服务器地址："));
    }
    a.setValue("memos/url",url);
    m_profile.reset(new QWebEngineProfile("QMemos"));
    // m_profile->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    // m_profile->settings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    // m_profile->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    // m_profile->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, false);
    qDebug()<<m_profile->isOffTheRecord();
    //m_profile->cookieStore()->deleteAllCookies();
    connect(m_profile->cookieStore(),&QWebEngineCookieStore::cookieAdded, this, &MainWindow::handleCookieAdded);
    m_webview.reset(new QWebEngineView(m_profile.get()));
    this->resize(800, 600);
    this->setCentralWidget(m_webview.get());//原来这么简单

    m_webview->setUrl(QUrl(url));

    //    ui->webEngineView->load(QUrl("http://111.229.25.29:5231/"));
    //auto cookiestore=ui->webEngineView->page()->profile()->cookieStore();

}
#include <QNetworkCookie>
#include <QWebEngineCookieStore>
MainWindow::~MainWindow()
{
    IniConfig a;
    delete ui;
}
void MainWindow::whenHotkeyActivated(){
    QuickMemo w;
    w.exec();
}

void MainWindow::whenTrayIconActivated(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
    case 2:;
    case 3:this->show();
    default:
        break;
    }
}

void MainWindow::handleCookieAdded(const QNetworkCookie &cookie){
    if(cookie.name()=="memos.access-token"){
        auto token=cookie.value();
        IniConfig a;
        a.setValue("memos/access_token",token);
    }
}

