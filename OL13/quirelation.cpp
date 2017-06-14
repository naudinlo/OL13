/**
* \file      quirelation.cpp
* \author    Garnier Maxime, Naudin Louise, Pépin Hugues
* \version   1.0
* \date      14 Juin 2017
* \brief     Gérer les couples d'une relations par l'interface.
*
* \details         class :
*                       QUIRelation :
*                           Attibuts:
*                               -Relation& R
*                               -NotesCouple* c //le couple qu'on a selectionné
*/
#include "quirelation.h"
#include "ui_quirelation.h"
/**
 * @fn QUiRelation::QUiRelation
 * @param r
 * @param parent
 * \brief constructeur
 */
QUiRelation::QUiRelation(Relation &r, QWidget *parent) :QDialog(parent),R(r),
    ui(new Ui::QUiRelation)
{
    ui->setupUi(this);
    ui->ETitre->setText(r.getTitle());
    ui->EDesciption->document()->setPlainText(r.getDescription());
    model = new QStandardItemModel;
    create_model();

}
/**
 * \fn QUiRelation::~QUiRelation
 */
QUiRelation::~QUiRelation()
{
    delete ui;
}
/**
 * @fn QUiRelation::create_model
 * \brief Met à jour le model.
 * \details sauvegarde tous les couples et caractérisque de la relation courrante.
 *
 */
void QUiRelation::create_model(){
    model->clear();
    QList<QString> presentNote;
    for(Relation::Iterator it=R.getIterator();!it.isDone();it.next()){
        if(! presentNote.contains(it.current().getCoupleNoteX()->getId())){
                //on n'affiche qu'une fois les notes symétriques
            QList< QStandardItem* > item;
                    item.append(new QStandardItem(it.current().getCoupleNoteX()->getId()));
                    if(it.current().getSymetric()){
                        item.append(new QStandardItem("<->"));
                        presentNote.push_front(it.current().getCoupleNoteY()->getId());

                    }
                    else{
                        item.append(new QStandardItem("->"));
                    }
                    item.append(new QStandardItem(it.current().getCoupleNoteY()->getId()));
                    item.append(new QStandardItem(it.current().getLabel()));

               model->appendRow(item);

        }
    }
    ui->RelationView->setModel(model);
}
/**
 * @fn QUiRelation::on_RelationView_doubleClicked
 * @param index
 * \details selection d'un couple parmi le model.
 */
void QUiRelation::on_RelationView_doubleClicked(QModelIndex index){

    NotesManager* m=NotesManager::getInstance();
        try{
           Note* n1 =&(m->getNote(model->item(index.row(),0)->text()));
           Note* n2= &(m->getNote(model->item(index.row(),2)->text()));
           c =R.getCoupleRelation(n1,n2);
            ui->remove->setEnabled(true);
            ui->show->setEnabled(true);
        }
        catch(NotesException e){
           QMessageBox::warning(this,"Note couple",e.getinfo());
        }

}
/**
 * @fn QUiRelation::on_EDesciption_textChanged
 * brief Mettre à jour la Description de la relation.
 */
void QUiRelation::on_EDesciption_textChanged(){
    R.setDescription(ui->EDesciption->document()->toPlainText());
}
/**
 * \fn QUiRelation::on_ETitre_textChanged
 * @param t
 *
 * brief Mettre à jour du titre de la relation.
 */
void QUiRelation::on_ETitre_textChanged(QString t){
    R.setTitle(t);
}
