/**
 * \file      interface.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définit l'interface principale de l'application.
 *
 * \details    //Classes présentes:
 *           -interface :
 *                  L'interface est la pièce maitresse de l'application graphique, elle
 *                  connecte et relie les docks, fenêtres de diagualogue et les fenêtres principales.
 *                  attributs :
 *                                    Creation_Note* fen_creerNote;         //fenetre dialogue permettant de créer une note
 *                                    selection_note* listNote;             //liste des notes
 *                                    page_notes* note_page;                //Fenetre principale
*                                     Edit_relation* new_relation;          //fenetre dialogue d'ajout de relation
 *                                    supp_note* fen_supp;                  //fenetre dialogue de suppression de note
 *                                    QManageRelation* affR;                //dock d'affichage des relations d'une note
 *                                    DockArchived* dock_aff_archived_Note; //dock d'affichagedes notes archivées
 *                                    DockRemove* dock_aff_removed_Note;    // dock d'affichagedes notes supprimées
 *                 Signaux:
 *                                    void S_update_model();
 *                                    void L_update_model();
 *                                    void A_update_model();
 *
 *           -selection_note:
 *                  Premier dock, sur le coté gauche, affiche les notes actives, et à permet leurs affichages par un double-click,
 *                  en envoyant le signal selection(Qstring, int).
 *                  Ce dock est mis à jour par reception du signal L_update_model() emis par l'interface.
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
#include "quirelation.h"
#include "qmanagerelation.h"
#include "dockarchived.h"
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
    supp_note* fen_supp; //fenetre dialogue
    QManageRelation* affR; //dock d'aff des relations d'une note
    DockArchived* dock_aff_archived_Note; //dock des notes archivées
    DockRemove* dock_aff_removed_Note; // dock des notes supprimées


    Q_OBJECT
    QWidget* ZoneCentrale;
    QMenu *MenuFichier;
    QMenu *MenuEd;
    QMenu *MenuAff;
    QMenu *fichiersRecents;
    QAction* Action_new_relation;
    QAction* Action_aff_relation;
    QAction* Action_Fermer_Note;
    QAction* Action_Archiver_Note;
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

    ~interface();
signals:
    void S_update_model();
    void L_update_model();
    void A_update_model();

public slots:
    /**
     * \fn update_model
     * \brief envoi un signal de mis à jours à tous les docks.
     */
    void update_model(){
        emit(S_update_model());
        emit(L_update_model());
        emit(A_update_model());
           }
    /**
    * \fn E_relation
    * \brief E_relation
    */
   void E_relation(){
       new_relation = new Edit_relation(listNote->getModel(),note_id,this);
       connect(new_relation,SIGNAL(newRelation()),note_page->getdock_aff_rel(),SLOT(updateModels()));
       new_relation->show();

   }
   /**
    * \fn Aff_relation
    * \brief lance et connecte la fenetre de gestion des relations.
    * \details connecte cette dernière avec le dock relation sur la page principale
    */
   void Aff_relation(){
        affR= new QManageRelation (this);
        if(note_page !=nullptr){
            connect(affR,SIGNAL(update_relation()),note_page->getdock_aff_rel(),SLOT(updateModels()));
        }
        affR->exec();
   }
   /**
    * \fn ViderCorbeille
    * \brief Vide la corbeille
    * \details ferme la page en cours, et appelle emptyTrash, une methode du manager
    * mes à jours les docks
    */
   void ViderCorbeille(){
       close_page_note();
       try{
           NotesManager::getInstance()->emptyTrash();
       QMessageBox::information(this,"Corbeille ","Vider la Corbeille");
       }
       catch (NotesException e){
           QMessageBox::warning(this,"Erreur corbeille", e.getinfo());
       }
      update_model();
   }

   void addAction_new_rel();
   void OuvrirFichier();
   void CreerNote();
  void afficher_note(QString id, int i);
  /**
    * \fn supp_dock_editer
    * \brief ferme le dock editer
    */
   void supp_dock_editer(){
       MenuEd->removeAction(dock_editer_note->toggleViewAction());
       dock_editer_note->close();
   } /**
    * \fn supp_dock_aff_rel
    * \brief ferme le dock editer
    * */
   void supp_dock_aff_rel(){
       MenuEd->removeAction(dock_aff_Relation->toggleViewAction());
       dock_aff_Relation->close();
   }
   /**
    * \fn supprimer_note
    * \brief appelle la fenêtre de dialogue de suppression de note
    * \details Ferme la page en cours, et mes à jours les docks
    */
   void supprimer_note(){
       fen_supp = new supp_note(listNote->getModel(),this);
       fen_supp->show();
       connect(fen_supp,SIGNAL(close_note()),this,SLOT(close_page_note()));
       update_model();
       //Recharger le Model dans la liste des Notes;
   }
   void close_page_note();

   void save();


};


#endif // INTERFACE_H
