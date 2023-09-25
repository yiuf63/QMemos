#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QDesktopServices>
#include <QMenu>
#include <QHotkey>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void whenHotkeyActivated();
    void whenTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;

    QMenu *trayMenu;
    QSystemTrayIcon *trayIcon;

    QHotkey *hotkey;
};

#endif // MAINWINDOW_H
