/**
 * \file      aff_notes.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     //Expliquer brievement à quoi sert ce fichier.
 *              //EX : Définit les modèles de voiture et leur particularités.
 *
 * \details    //Expliquer en détail.
 *              //EX :Cette classe surcharge les accesseurs standards du module_voiture pour
 *                  convenir aux spécificités des différents modèles possibles.
 */




#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
#include "qnote.h"
#include "manager.h"
#include "qrelations.h"
#include "quirelation.h"
#include "qreference.h"
class page_notes: public QWidget
{
    Q_OBJECT

protected:
    QNote* note;
    Note& n;
    Note* newNote;
    QWidget* dock_editer;
    QDockRelation* dock_aff_Rel;
    QPushButton* savebutton;
    Qreference* widget_ref;
    //QLineEdit* titre;
    QLabel* info;
    QHBoxLayout* layout_info;
    QVBoxLayout* layout_p;
    QVBoxLayout* L_titre;
public:
    page_notes(Note &N);
    ~page_notes();
    QWidget& getdock_editer(){
        return *dock_editer;
    }
    QDockRelation* getdock_aff_rel(){
        return dock_aff_Rel;
    }

signals:
    void supp_dock_editer();
    void update_model();
    void supp_dock_aff_rel();
    void close_page();
public slots:
    void on_savebutton_clicked(){
        note->saveNote(*newNote);
        emit(update_model());
        widget_ref->update_model();
    }

    void editer_note(bool status){
        //TODO : FAIRE EN SORTE QUE LA FONCTION MARCHE!!!
        note->readOnly(status);
        delete dock_editer;
        if(n.getIsDeleted() ){
            n.setIsDeleted(false);
        }
        else if(n.getIsArchive()){
            n.setIsArchive(false);
        }
        emit(supp_dock_editer());
        if(n.getType()=="Article"){
            newNote =&(NotesManager::getInstance()->editArticle(dynamic_cast<Article&>(n)));
        }
        else if(n.getType()=="Recording"){
            newNote =&NotesManager::getInstance()->editRecording(dynamic_cast<Recording&>(n));
        }
        else
        {
            newNote =&NotesManager::getInstance()->editTask(dynamic_cast<Task&>(n));
        }
        savebutton->setHidden(false);
        emit(update_model());
    }
    void Archiver_page_note(){
        n.setIsArchive(true);
        emit(update_model());
        emit(close_page());
    }
    void aff_Relation(QString titre){ //permet d'afficher une relation depuis le dock
        QUiRelation showR(RelationManager::getInstance().getRelation(titre),this);
        connect(&showR,SIGNAL(newCouple()),this->getdock_aff_rel(),SLOT(updateModels()));
        showR.exec();

    }
};

class page_vide: public QWidget{
public:
    page_vide();
};

#endif // AFF_NOTES_H
