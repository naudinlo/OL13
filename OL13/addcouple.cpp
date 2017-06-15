/**
 * \file      addcouple.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Fenetre de création de nouveau couple
 *
 * \details    class :
 *                  addCouple
 */
#include "addcouple.h"
#include "ui_addcouple.h"
#include "manager.h"

/**
 * @fn addCouple::addCouple
 * @param parent
 * \brief constructeur
 */
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
        if (!it.liste()->isEmpty()){
            QStandardItem* item=new QStandardItem(it.current().getId());
            item->setWhatsThis(it.current().getId());
            modelfrom->appendRow(item);
        }
    }
    ui->From->setModel(modelfrom);
    ui->toView->setModel(modelto);
}

/**
 * @fn addCouple::updateModel_to
 * @param index
 * \brief Met à jour le model
 * \details les ids sont affichées de tels façon à empécher l'ecriture d'un couple sur soi-même
 *
 */
void addCouple::updateModel_to(QModelIndex index){
    modelto->clear();
    i1=index;
    NotesManager* m=NotesManager::getInstance();
    for(NotesManager::Iterator it=m->getIterator();!it.isDone();it.next()){
        if(!it.liste()->isEmpty()){
            if(it.current().getId()!= modelfrom->itemFromIndex(index)->whatsThis())
            {
                QStandardItem* item=new QStandardItem(it.current().getId());
                item->setWhatsThis(it.current().getId());
                modelto->appendRow(item);
            }
        }
    }
}
/**
 * @fn addCouple::on_toView_clicked
 * @param i
 * \brief Autorise le boutton save
 */
void addCouple::on_toView_clicked(QModelIndex i){

    ui->save->setEnabled(true);
    i2=i;
}
/**
 * @fn addCouple::on_save_clicked
 * \brief envoi le signal des paramètres du nouveau couple formé.
 */
void addCouple::on_save_clicked(){
    emit(addNewCouple(modelfrom->itemFromIndex(i1)->whatsThis(),modelto->itemFromIndex(i2)->whatsThis(),ui->lineEdit->text(),ui->Yes->isChecked()));
    this->close();
}
/**
 * @fn addCouple::~addCouple
 */
addCouple::~addCouple()
{
    delete ui;
}
