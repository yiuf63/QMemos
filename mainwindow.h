#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QMenu>
#include <QHotkey>
#include <QNetworkCookie>
#include <QtWebEngineWidgets/QWebEngineView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void reload(){
        m_webview->reload();
    }
    ~MainWindow();

protected:
    void whenHotkeyActivated();
    void whenTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
private:
    Ui::MainWindow *ui;

    QMenu *trayMenu;
    QSystemTrayIcon *trayIcon;

    QHotkey *hotkey;

    void handleCookieAdded(const QNetworkCookie &cookie);

    QScopedPointer<QWebEngineView> m_webview;
    QScopedPointer<QWebEngineProfile> m_profile;
};

#endif // MAINWINDOW_H
