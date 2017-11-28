#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QKeyEvent>

#include"setform.h"
#include"handform.h"
#include"testform.h"
#include"manageform.h"
#include"enterform.h"
#include"devthread/devicesthread.h"
namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    SelectPlugin *SelectArray[8];
    int CurSel;
    DevicesThread* m_devThread;

private:
    void InitEnterForm();
    void InitSetForm();
    void InitHandForm();
    void InitTestForm();
    void InitManageForm();

    void InitWidgetsText();
    void InitSelectArray();
    void SelPlugin(int sel);
    void ArrowsSelPlugin(bool UpDown);
    void PressEnterKey(int sel);
    void SetPromptText(int sel);

private:
    void keyPressEvent(QKeyEvent *k);

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
