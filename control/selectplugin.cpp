#include "selectplugin.h"
#include "ui_selectplugin.h"

SelectPlugin::SelectPlugin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectPlugin)
{
    ui->setupUi(this);
    label=ui->label;
    //label->adjustSize();
}

SelectPlugin::~SelectPlugin()
{
    delete ui;
}
//获得焦点
void SelectPlugin::SelectFocusIn(QColor col)
{
    QPalette pa=palette();
    pa.setColor(QPalette::Window,col);
    this->setPalette(pa);
}
//失去焦点
void SelectPlugin::SelectFocusOut(QColor col)
{
    QPalette pa=palette();
    pa.setColor(QPalette::Window,col);
    this->setPalette(pa);
}
//大小改变
void SelectPlugin::AdjustPluginSize()
{
    label->adjustSize();
    this->setFixedSize(label->width(),label->height());
}
//按下回车键
void SelectPlugin::PressEnterKey()
{


    label->setFocus();
//    MyTextEdit *edit;
//    QString str=label->text();

//    edit=new MyTextEdit(this);
//    edit->setFocusPolicy(Qt::StrongFocus);
//    edit->setText(str);
//    edit->move(0,0);
//    edit->resize(150,20);
//    edit->show();
//    int pos=str.indexOf(':');
//    pos++;
//    edit->setCursorPosition(pos);
//    edit->setFocus();
}
