#include "deletednote.h"
#include "ui_deletednote.h"

DeletedNote::DeletedNote(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DeletedNote)
{
    ui->setupUi(this);
}

DeletedNote::~DeletedNote()
{
    delete ui;
}
