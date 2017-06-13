#include "qreference.h"
#include "ui_qreference.h"

Qreference::Qreference(Note &n, QWidget *parent) :
    QWidget(parent),note(n),
    ui(new Ui::Qreference)
{
    ui->setupUi(this);
    model_ref = new QStandardItemModel;
    update_model();
    ui->refView->setModel(model_ref);
}

Qreference::~Qreference()
{
    delete ui;
}

void Qreference::update_model(){
    model_ref->clear();
    QList<QStandardItem* >item;
    for(unsigned int i=0;i<note.references.size();i++){
        item.append(new QStandardItem(note.references.at(i)));
//        item.append(new QStandardItem(note.getReferenceInt(i).getId()));
    }
    model_ref->appendRow(item);


}
