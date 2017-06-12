#include "qmanagerelation.h"
#include "ui_qmanagerelation.h"

QManageRelation::QManageRelation(QWidget *parent) :
    QDialog(parent),
    currentR(QString::null),
    ui(new Ui::QManageRelation)
{
    model = new QStandardItemModel;

    ui->setupUi(this);
    UpdateModel();


}
void QManageRelation::UpdateModel(){
    for(RelationManager::Iterator it=RelationManager::getInstance().getIterator() ;!it.isDone();it.next()){
        QList< QStandardItem* > item;
                item.append(new QStandardItem(it.current().getTitle()));
                item.append(new QStandardItem(it.current().getDescription()));
                item.at(0)->setWhatsThis(it.current().getTitle());
                model->appendRow(item);
    }
    ui->RelationView->setModel(model);
}

QManageRelation::~QManageRelation()
{
    delete ui;
}

void QManageRelation::on_RelationView_doubleClicked(QModelIndex index){
        currentR = model->itemFromIndex(index)->whatsThis();
        ui->remove->setEnabled(true);
        ui->show->setEnabled(true);


}
