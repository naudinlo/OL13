/**
* \file      quirelation.h
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

#ifndef QUIRELATION_H
#define QUIRELATION_H

#include <QDialog>
#include "relations.h"
#include "QInclude.h"
#include "manager.h"
#include "addcouple.h"
#include "qrelations.h"
namespace Ui {
class QUiRelation;
}

class QUiRelation : public QDialog
{
    Q_OBJECT
    QStandardItemModel* model;
    Relation& R;
    NotesCouple* c;
public:
    explicit QUiRelation(Relation& r,QWidget *parent = 0);
    ~QUiRelation();

private:
    Ui::QUiRelation *ui;
    void create_model();
signals:
    void newCouple();
public slots:
    void setCouple(QString l){
        c->setLabel(l);
        create_model();
    }
    /**
     * nf on_show_clicked
     * \brief lance la fenetre d'edition de couple sur le couple choisi
     */
    void on_show_clicked(){
        Edit_NotesCouple Editcouple(c->getCoupleNoteX(),c->getCoupleNoteY(),this);
        connect(&Editcouple,SIGNAL(setCouple(QString)),this,SLOT(setCouple(QString)));
        Editcouple.exec();
    }
    void on_ETitre_textChanged(QString t);
    void on_EDesciption_textChanged();
    void on_RelationView_doubleClicked(QModelIndex index);
    /**
     * @nf on_remove_clicked
     * \brief supression du couple choisi.
     * \details demande de mis à jour du model après suppression.
     *
     */
    void on_remove_clicked(){
        try{
            R.removeCoupleRelation(c->getCoupleNoteX(),c->getCoupleNoteY());

            QMessageBox::warning(this,"Couple relation","supprimé");
        }
        catch(NotesException e){
            QMessageBox::warning(this,"Remove Couple relation",e.getinfo());
        }
        create_model();
    }
    /**
     * \fn on_addCouple_clicked
     * \brief lancement de la fennetre d'ajout de couple.
     * \details connection entre les deux fenetre pour répertorié le nouvea couple
     */
    void on_addCouple_clicked(){
        addCouple addC(this);
        connect(&addC,SIGNAL(addNewCouple(QString,QString,QString,bool)),this,SLOT(addNewCouple(QString,QString,QString,bool)));
        addC.exec();
    }
    /**
     * @fn addNewCouple
     * @param id1
     * @param id2
     * @param l
     * @param s
     * \brief ajoute le couple édité à la relation actuelle
     * \details demande la mis à jour du model.
     */
    void addNewCouple(QString id1,QString id2,QString l,bool s){
        try{
            NotesManager* m=NotesManager::getInstance();
            R.getNewCoupleRelation(&(m->getNote(id1)),&(m->getNote(id2)),l,s);
            emit(newCouple());
        }
        catch(NotesException e){
            QMessageBox::warning(this,"add New Couple",e.getinfo());
        }
        create_model();
        QMessageBox::information(this,"mis a jour","");
    }
};

#endif // QUIRELATION_H
