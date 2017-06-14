#include "qmanagerelation.h"
#include "ui_qmanagerelation.h"
/**
 * \fn QManageRelation::QManageRelation
 * @param parent
 * \brief constructeur de QManagerRelation.
 */
QManageRelation::QManageRelation(QWidget *parent) :
    QDialog(parent),
    currentR(QString::null),
    ui(new Ui::QManageRelation)
{
    model = new QStandardItemModel;

    ui->setupUi(this);
    UpdateModel();


}
/**
 * \fn QManageRelation::UpdateModel
 * \brief Mais à jour la liste de relation.
 */
void QManageRelation::UpdateModel(){
    model->clear();
    for(RelationManager::Iterator it=RelationManager::getInstance().getIterator() ;!it.isDone();it.next()){
        QList< QStandardItem* > item;
                item.append(new QStandardItem(it.current().getTitle()));
                item.append(new QStandardItem(it.current().getDescription()));
                item.at(0)->setWhatsThis(it.current().getTitle());
                model->appendRow(item);
    }
    ui->RelationView->setModel(model);
}
/**
 * \fn QManageRelation::~QManageRelation
 */
QManageRelation::~QManageRelation()
{
    delete ui;
}
/**
 * \fn QManageRelation::on_RelationView_doubleClicked
 * @param index
 * \brief Recupération de la relation choisie.
 * \details rends possible des les fonctions de suppression et d'affichage d'une relation.
 */
void QManageRelation::on_RelationView_doubleClicked(QModelIndex index){
        currentR = model->itemFromIndex(index)->whatsThis();
        ui->remove->setEnabled(true);
        ui->show->setEnabled(true);


}
