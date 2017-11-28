#include "enterform.h"
#include "ui_enterform.h"

EnterForm::EnterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterForm)
{
    ui->setupUi(this);
}

EnterForm::~EnterForm()
{
    delete ui;
}
//
void EnterForm::keyPressEvent(QKeyEvent *k)
{
    switch(k->key())
    {
        case Qt::Key_Escape: this->close(); break;

    }
}
