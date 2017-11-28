#ifndef SELECTPLUGIN_H
#define SELECTPLUGIN_H
//
//菜单项选择控件
//
#include <QWidget>
#include<QLabel>
#include"mytextedit.h"
namespace Ui {
    class SelectPlugin;
}

class SelectPlugin : public QWidget
{
    Q_OBJECT

public:
    explicit SelectPlugin(QWidget *parent = 0);
    ~SelectPlugin();
public:
     QLabel *label;

public:
    void SelectFocusIn(QColor col);
    void SelectFocusOut(QColor col);
    void AdjustPluginSize();
    void PressEnterKey();
private:
    Ui::SelectPlugin *ui;
};

#endif // SELECTPLUGIN_H
