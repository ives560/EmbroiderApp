#ifndef MAINMENUFORM_H
#define MAINMENUFORM_H

#include <QWidget>

namespace Ui {
    class MainMenuForm;
}

class MainMenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuForm(QWidget *parent = 0);
    ~MainMenuForm();

private:
    Ui::MainMenuForm *ui;
};

#endif // MAINMENUFORM_H
