#ifndef ENTERFORM_H
#define ENTERFORM_H
//
//
//
#include <QWidget>
#include<QKeyEvent>
namespace Ui {
    class EnterForm;
}

class EnterForm : public QWidget
{
    Q_OBJECT

public:
    explicit EnterForm(QWidget *parent = 0);
    ~EnterForm();
private:
    void keyPressEvent(QKeyEvent *);
private:
    Ui::EnterForm *ui;
};

#endif // ENTERFORM_H
