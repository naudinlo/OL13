#include "addcouple.h"
#include "ui_addcouple.h"
#include "manager.h"

addCouple::addCouple(QWidget *parent) :
    QDialog(parent),
    i1(QModelIndex()),
    i2(QModelIndex()),
    ui(new Ui::addCouple)
{
    ui->setupUi(this);
    modelfrom = new QStandardItemModel;
    modelto = new QStandardItemModel;
    connect(ui->From,SIGNAL(clicked(QModelIndex)),this,SLOT(updateModel_to(QModelIndex)));

    NotesManager* m=NotesManager::getInstance();
    for(NotesManager::Iterator it=m->getIterator();!it.isDone();it.next()){
        QStandardItem* item=new QStandardItem(it.current().getId());
        item->setWhatsThis(it.current().getId());
        modelfrom->appendRow(item);
    }
    ui->From->setModel(modelfrom);
    ui->toView->setModel(modelto);
}
void addCouple::updateModel_to(QModelIndex index){
    modelto->clear();
    i1=index;
    NotesManager* m=NotesManager::getInstance();
    for(NotesManager::Iterator it=m->getIterator();!it.isDone();it.next()){
        if(it.current().getId()!= modelfrom->itemFromIndex(index)->whatsThis())
        {
            QStandardItem* item=new QStandardItem(it.current().getId());
            item->setWhatsThis(it.current().getId());
            modelto->appendRow(item);
        }
    }
}
void addCouple::on_toView_clicked(QModelIndex i){

    ui->save->setEnabled(true);
    i2=i;
}

void addCouple::on_save_clicked(){
    emit(addNewCouple(modelfrom->itemFromIndex(i1)->whatsThis(),modelto->itemFromIndex(i2)->whatsThis(),ui->lineEdit->text(),ui->Yes->isChecked()));
    this->close();
}

addCouple::~addCouple()
{
    delete ui;
}
