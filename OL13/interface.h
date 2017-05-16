#ifndef INTERFACE_H
#define INTERFACE_H
//#include "include.h"
//#include "QInclude.h"
#include "Creation_Note.h"
#include <QDockWidget>
class selection_note;


class selection_note: public QWidget{
    QVBoxLayout* layout;
    QStandardItemModel* model;
    QTreeView* vue;

public:
    selection_note();
    QStandardItemModel* getModel(){return model;}
    QTreeView* getVue(){return vue;}


public slots:

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

public:
    interface();
    void CreateDock_selected_Note();//doit prendre un fichier est chargé la liste
    void Destruct_selected_Note();


public slots:
   void OuvrirFichier();
   void CreerNote();
   void test(){
       QStandardItem *newitem = new QStandardItem("article autre");
       newitem->setEditable(false);
       listNote->getModel()->appendRow(newitem);
       newitem->appendRow(new QStandardItem("1 version"));
       listNote->getVue()->setModel(listNote->getModel());
   }
   void addNewNote(Note* n);


};


#endif // INTERFACE_H
