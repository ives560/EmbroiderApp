#ifndef MANAGEFORM_H
#define MANAGEFORM_H

#include <QWidget>
#include<QKeyEvent>
#include"control/selectplugin.h"
namespace Ui {
    class ManageForm;
}

class ManageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ManageForm(QWidget *parent = 0);
    ~ManageForm();
private:
    SelectPlugin *SelectArray[5];
    int CurSel;
private:
    void keyPressEvent(QKeyEvent *);
    void InitWidgetsText();
    void InitSelectArray();
    void SelPlugin(int sel);
    void ArrowsSelPlugin(bool UpDown);
private:
    Ui::ManageForm *ui;
};

#endif // MANAGEFORM_H
