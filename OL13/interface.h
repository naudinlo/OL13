#ifndef INTERFACE_H
#define INTERFACE_H
//#include "include.h"
//#include "QInclude.h"
#include "Creation_Note.h"
#include <QDockWidget>
#include "manager.h"
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
    Creation_Note fen_creerNote;
    selection_note* listNote;
    QMenu *MenuFichier;
    QMenu *MenuEd;
    QMenu *MenuAff;
    QMenu *fichiersRecents;
    QDockWidget* dock_selected_Note;
    NotesManager* note_manager;

public:
    interface();
    void CreateDock_selected_Note();//doit prendre un fichier est chargé la liste
    void Destruct_selected_Note();
    ~interface(){
        NotesManager::libererInstance();
    }

public slots:
   void OuvrirFichier();
   void CreerNote();
   void test(){
   }
   void addNewNote(Note* n);
   void afficher_note(QString id);
   void save();
};


#endif // INTERFACE_H
