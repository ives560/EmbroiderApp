#ifndef SETFORM_H
#define SETFORM_H

#include <QWidget>
#include<QKeyEvent>
#include"control/selectplugin.h"
namespace Ui {
    class SetForm;
}

class SetForm : public QWidget
{
    Q_OBJECT

public:
    explicit SetForm(QWidget *parent = 0);
    ~SetForm();
private:
    SelectPlugin *SelectArray[8];
    int CurSel;

private:
    void keyPressEvent(QKeyEvent *);
    void InitBackColor();
    void InitWidgetsText();
    void InitSelectArray();
    void SelPlugin(int sel);
    void ArrowsSelPlugin(bool UpDown);
    void PressEnterKey(int sel);

private:
    Ui::SetForm *ui;
};

#endif // SETFORM_H
