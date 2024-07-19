#ifndef QUICKMEMO_H
#define QUICKMEMO_H

#include <QDialog>
#include "wrapper.h"

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
    void keyPressEvent(QKeyEvent* event) override;


private:
    Ui::QuickMemo *ui;

    wrapper *ptr=wrapper::instances();
};


#endif // QUICKMEMO_H
