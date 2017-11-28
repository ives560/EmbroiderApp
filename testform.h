#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include<QKeyEvent>
#include<QLabel>
#include"ioperate/ioperate.h"
namespace Ui {
    class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = 0);
    ~TestForm();

private:
    void keyPressEvent(QKeyEvent *);
    void ShowText(int gpio,bool state);
private:
    IOperate ioper;
private:
    Ui::TestForm *ui;
};

#endif // TESTFORM_H
