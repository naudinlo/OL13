#ifndef INTERFACE_H
#define INTERFACE_H
//#include "include.h"
//#include "QInclude.h"
#include "Creation_Note.h"
#include <QDockWidget>
#include "manager.h"
#include "aff_notes.h"
#include "sstream"
#include <QList>
#include <QDate>
#include <QStandardItemModel>
#include <typeinfo>
class selection_note;


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
    void selection(QString);
public slots:
    void emit_selection(QModelIndex i);
};



class interface:public QMainWindow
{
    Q_OBJECT
    Creation_Note* fen_creerNote;
    selection_note* listNote;
    page_notes* note_page;
    QWidget* ZoneCentrale;
    QMenu *MenuFichier;
    QMenu *MenuEd;
    QMenu *MenuAff;
    QMenu *fichiersRecents;

    QDockWidget* dock_selected_Note;
    QDockWidget* dock_editer_note;
    NotesManager* note_manager;

public:
    interface();
    void CreateDock_selected_Note();//doit prendre un fichier est chargé la liste
    void CreateDock_edited_Note();
    void Destruct_selected_Note();
    ~interface(){
        NotesManager::libererInstance();
    }

public slots:
   void OuvrirFichier();
   void CreerNote();
   void test(){
   }
   void addNewNote(Note &n);
   void afficher_note(QString id);
   void supp_dock_editer(){

       MenuEd->removeAction(dock_selected_Note->toggleViewAction());
       delete dock_editer_note;
   }

   void save();
};


#endif // INTERFACE_H
