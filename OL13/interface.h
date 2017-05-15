#ifndef INTERFACE_H
#define INTERFACE_H
//#include "include.h"
//#include "QInclude.h"
#include "Creation_Note.h"
#include <QDockWidget>
class selection_note;

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


};

class selection_note: public QWidget{
    QVBoxLayout* layout;
    QStandardItemModel* model;
    QTreeView* vue;

public:
    selection_note();
public slots:

};



#endif // INTERFACE_H
