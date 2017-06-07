#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
#include "qnote.h"
class page_notes: public QWidget
{
    Q_OBJECT

protected:
    QNote* note;

    QWidget* dock_editer;
    QWidget* dock_rel;
    QHBoxLayout* layout_titre;
    QLineEdit* titre;
    QLabel* info;
    QVBoxLayout* layout_p;
    QWidget* dock; //à vérifier

public:
    page_notes(Note &n);
    ~page_notes();
    QWidget& getdock_editer(){
        return *dock_editer;
    }
signals:
    void supp_dock_editer();
public slots:
    void editer_note(bool status){
        //TODO : FAIRE EN SORTE QUE LA FONCTION MARCHE!!!
        titre->setReadOnly(status);
        note->readOnly(status);
        delete dock_editer;
        emit(supp_dock_editer());
    }
    void supprimer_note(bool status){
        //TODO : Supprimer la note à partir du note manager
        //TOUT EST FAUX MAIS C'EST POUR AVOIR LA STRUCTURE EN GROS.
         /*
//      NotesManager* m=NotesManager::getTnstance();
        note(NotesManager::getInstance()->getNote(id));
//        QString& id=id;
//        m->getNote(&id);
//        m->deleteNote(&n);
        */
    }
};

class page_vide: public QWidget{
public:
    page_vide();
};

#endif // AFF_NOTES_H
