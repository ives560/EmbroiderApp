#include "manageform.h"
#include "ui_manageform.h"

ManageForm::ManageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageForm)
{
    ui->setupUi(this);
    CurSel=0;
    InitSelectArray();
    InitWidgetsText();
    SelPlugin(0);
}

ManageForm::~ManageForm()
{
    delete ui;
}
//键盘按键事件
void ManageForm::keyPressEvent(QKeyEvent *k)
{
    switch(k->key())
    {
        case Qt::Key_Escape: this->close(); break;
        case Qt::Key_0: SelPlugin(4); break;
        case Qt::Key_1: SelPlugin(0);  break;
        case Qt::Key_2: SelPlugin(1); break;
        case Qt::Key_3: SelPlugin(2); break;
        case Qt::Key_4: SelPlugin(3); break;

        case Qt::Key_Up: ArrowsSelPlugin(false); break;
        case Qt::Key_Down: ArrowsSelPlugin(true); break;
    }
}
//初始化菜单项数组
void ManageForm::InitSelectArray()
{
    SelectArray[0]=ui->widget;
    SelectArray[1]=ui->widget_2;
    SelectArray[2]=ui->widget_3;
    SelectArray[3]=ui->widget_4;
    SelectArray[4]=ui->widget_5;

}
//初始化菜单响显示文字
void ManageForm::InitWidgetsText()
{
    SelectArray[0]->label->setText(tr("1.花样拷贝"));
    SelectArray[1]->label->setText(tr("2.花样删除"));
    SelectArray[2]->label->setText(tr("3.花样查看"));
    SelectArray[3]->label->setText(tr("4.信息统计"));
    SelectArray[4]->label->setText(tr("0.返回"));
    //调整大小
    for(int i=0;i<5;i++)
    {
        SelectArray[i]->AdjustPluginSize();
    }
}
//改变选择新菜单项的颜色
void ManageForm::SelPlugin(int sel)
{
    SelectArray[CurSel]->SelectFocusOut(QColor(0,0,0,0));//无色
    CurSel=sel;
    SelectArray[CurSel]->SelectFocusIn(QColor(100,100,255));//白色

}
//菜单项选择移动方向
//true为向下移动
//false为向上移动
void ManageForm::ArrowsSelPlugin(bool UpDown)
{
    int newSel=CurSel;
    if(UpDown==true)//Down
    {
        newSel++;
        if(newSel==5)
            newSel=0;
        SelPlugin(newSel);
    }
    else if(UpDown==false)//Up
    {
        newSel--;
        if(newSel==-1)
            newSel=4;
        SelPlugin(newSel);
    }
}
