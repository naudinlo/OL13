/**
 * \file      interface.h
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



#ifndef INTERFACE_H
#define INTERFACE_H
//#include "include.h"
//#include "QInclude.h"
#include "Creation_Note.h"
#include <QDockWidget>
#include "manager.h"
#include "aff_notes.h"
#include "qrelations.h"
#include "sstream"
#include <QList>
#include <QDate>
#include <QStandardItemModel>
#include <typeinfo>
#include "supp_note.h"
class selection_note: public QWidget{
    Q_OBJECT
    QVBoxLayout* layout;

    QTreeView* vue;
    QStandardItemModel* model;
public:
    selection_note();
    QStandardItemModel* getModel()const {return model;}
    QTreeView* getVue(){return vue;}
signals:
    void selection(QString, int);
public slots:
    void emit_selection(QModelIndex i);
    void update_model();
};



class interface:public QMainWindow
{
    //Attribut
    Creation_Note* fen_creerNote; //fenetre pour créer une note
    selection_note* listNote; //liste des notes
    page_notes* note_page;    //affichage d'une note
    Edit_relation* new_relation; //fenetre d'ajout de relation
    NotesManager* note_manager;
    supp_note* fen_supp;

    Q_OBJECT
    QWidget* ZoneCentrale;
    QMenu *MenuFichier;
    QMenu *MenuEd;
    QMenu *MenuAff;
    QMenu *fichiersRecents;
    QAction* Action_new_relation;
    QAction* Action_aff_relation;
    QAction* Action_Fermer_Note;
    QToolBar* toolBar_new_Rel;
    QToolBar* toolBar_close;
    QToolBar* toolBar_supp_note;
    QToolBar* toolBar_save_note;
    QToolBar* toolBar_aff_Rel;
    QDockWidget* dock_selected_Note;
    QDockWidget* dock_editer_note;
    QDockWidget* dock_aff_Relation;

    //A modifier
    QString note_id;

    void CreateDock_selected_Note();//doit prendre un fichier est chargé la liste
    void CreateDock_edited_Note();
    void Destruct_selected_Note();
    //void CreateDock_aff_Relation();

public:
    interface();

    ~interface(){
        NotesManager::libererInstance();
    }
signals:
    void update_model();

public slots:
   void E_relation(){
       new_relation = new Edit_relation(listNote->getModel(),note_id,this);
       new_relation->show();

   }
   void Aff_relation(){

   }
   void ViderCorbeille(){
       close_page_note();
       try{
           NotesManager::getInstance()->emptyTrash();
       QMessageBox::information(this,"Corbeille ","Corbeille vider");
       }
       catch (NotesException e){
           QMessageBox::warning(this,"Erreur corbeille", e.getinfo());
       }
      emit(update_model());
   }

   void addAction_new_rel();
   void OuvrirFichier();
   void CreerNote();
   void addNewNote(Note &n);
   void afficher_note(QString id, int i);
   void supp_dock_editer(){
       MenuEd->removeAction(dock_editer_note->toggleViewAction());
       dock_editer_note->close();
   }
   void supp_dock_aff_rel(){
       MenuEd->removeAction(dock_aff_Relation->toggleViewAction());
       dock_aff_Relation->close();
   }

   void supprimer_note(){
       fen_supp = new supp_note(listNote->getModel(),this);
       fen_supp->show();
       connect(fen_supp,SIGNAL(close_note()),this,SLOT(close_page_note()));
       //Recharger le Model dans la liste des Notes;s
   }
   void close_page_note();

   void save();
};


#endif // INTERFACE_H
