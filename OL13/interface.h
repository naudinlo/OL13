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
    void selection(QString, QModelIndex);
public slots:
    void emit_selection(QModelIndex i);
};



class interface:public QMainWindow
{
    Q_OBJECT
    //Attribut
    Creation_Note* fen_creerNote; //fenetre pour créer une note
    selection_note* listNote; //liste des notes
    page_notes* note_page;    //affichage d'une note
    Edit_relation* relation; //fenetre d'ajout de relation
    NotesManager* note_manager;

    QWidget* ZoneCentrale;
    QMenu *MenuFichier;
    QMenu *MenuEd;
    QMenu *MenuAff;
    QMenu *fichiersRecents;
    QAction* Action_new_relation;
    QToolBar* toolBar_new_Rel;

    QDockWidget* dock_selected_Note;
    QDockWidget* dock_editer_note;
    //QDockWidget* dock_aff_Relation;

    //A modifier
    int indexNote;
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

public slots:
   void E_relation(){
       relation = new Edit_relation(listNote->getModel(),indexNote,note_id,this);
       relation->show();

   }

   void addAction_new_rel();
   void OuvrirFichier();
   void CreerNote();
   void addNewNote(Note &n);
   void afficher_note(QString id,QModelIndex index);
   void supp_dock_editer(){
       MenuEd->removeAction(dock_editer_note->toggleViewAction());
       dock_editer_note->close();
   }

   void save();
};


#endif // INTERFACE_H
