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
class page_notes: public QWidget
{
    Q_OBJECT

protected:
    QNote* note;
    Note& n;

    QWidget* dock_editer;
    QDockRelation* dock_aff_Rel;
    QHBoxLayout* layout_titre;
    //QLineEdit* titre;
    QLabel* info;
    QVBoxLayout* layout_p;
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
public slots:
    void editer_note(bool status){
        //TODO : FAIRE EN SORTE QUE LA FONCTION MARCHE!!!
        note->readOnly(status);
        delete dock_editer;
        emit(supp_dock_editer());
        if(n.getType()=="Article"){
            n =NotesManager::getInstance()->editArticle(dynamic_cast<Article&>(n));
        }
        else if(n.getType()=="Recording"){
            n =NotesManager::getInstance()->editRecording(dynamic_cast<Recording&>(n));
        }
        else
        {
            n =NotesManager::getInstance()->editTask(dynamic_cast<Task&>(n));
        }
    }
};

class page_vide: public QWidget{
public:
    page_vide();
};

#endif // AFF_NOTES_H
