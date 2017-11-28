#include "mainmenuform.h"
#include "ui_mainmenuform.h"

MainMenuForm::MainMenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuForm)
{
    ui->setupUi(this);
}

MainMenuForm::~MainMenuForm()
{
    delete ui;
}
