#ifndef QUICKMEMO_H
#define QUICKMEMO_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class QuickMemo; }
QT_END_NAMESPACE

class QuickMemo : public QDialog
{
    Q_OBJECT

public:
    QuickMemo(QWidget *parent = nullptr);
    ~QuickMemo();

protected:
    void saveQuit();

private:
    Ui::QuickMemo *ui;
};


#endif // QUICKMEMO_H
