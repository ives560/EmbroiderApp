#ifndef HANDFORM_H
#define HANDFORM_H

#include <QWidget>
#include<QKeyEvent>
namespace Ui {
    class HandForm;
}

class HandForm : public QWidget
{
    Q_OBJECT

public:
    explicit HandForm(QWidget *parent = 0);
    ~HandForm();
private:
    void keyPressEvent(QKeyEvent *);

private:
    Ui::HandForm *ui;
};

#endif // HANDFORM_H
