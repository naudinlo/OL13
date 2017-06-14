/**
 * \file      qmanagerelation.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     // Fenetre de dialoque permettant de gérer les relations.
 *
 * \details         attributs :
 *                                   QString currentR // titre de la relations selectionné
 *                 Signaux:
 *                                    void update_relation()
 *
 */



#ifndef QMANAGERELATION_H
#define QMANAGERELATION_H

#include <QDialog>
#include <QInclude.h>
#include <manager.h>
#include "quirelation.h"
namespace Ui {
class QManageRelation;
}

class QManageRelation : public QDialog
{
    Q_OBJECT
public:
    explicit QManageRelation(QWidget *parent = 0);
    ~QManageRelation();

signals:
    void update_relation();
private:
    Ui::QManageRelation *ui;
    QUiRelation* selectedR;
    QStandardItemModel* model;
    QString currentR;
    void UpdateModel();
public slots:
    /**
     * \fn on_show_clicked
     * \brief ouvre l'editeur de couple
     * \details mets à jours les données et envoi un signal de mis à jour.
     */
    void on_show_clicked(){
        try{
            selectedR =new QUiRelation (RelationManager::getInstance().getRelation( currentR),this);
            selectedR->exec();
            connect(selectedR,SIGNAL(newCouple()),this,SLOT(emit_update_relation()));
            UpdateModel();
            emit(update_relation());
        }
        catch(NotesException e){
            QMessageBox::warning(this,"Show Relation",e.getinfo());
        }
    }
    void emit_update_relation(){emit(update_relation());}
    void on_RelationView_doubleClicked(QModelIndex index);
    /**
     * \fn on_remove_clicked
     * \brief supprime la relation selectionner
     * \details envoie le message de demande de mis à jour.
     */
    void on_remove_clicked(){
        try{
            RelationManager::getInstance().deleteRelation(currentR);
            QMessageBox::information(this,"Suppression Relation", "La relation est supprimé");
            UpdateModel();
            emit(update_relation());

        }
        catch(NotesException e){
            QMessageBox::warning(this,"Suppression Relation", e.getinfo());
        }
    }

};

#endif // QMANAGERELATION_H
