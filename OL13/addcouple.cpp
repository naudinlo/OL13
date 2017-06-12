#include "addcouple.h"
#include "ui_addcouple.h"

addCouple::addCouple(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCouple)
{
    ui->setupUi(this);
}

addCouple::~addCouple()
{
    delete ui;
}
