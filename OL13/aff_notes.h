#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
#include "qnote.h"
#include "manager.h"
class page_notes: public QWidget
{
    Q_OBJECT

protected:
    QNote* note;
    Note& n;

    QWidget* dock_editer;
    QWidget* dock_rel;
    QHBoxLayout* layout_titre;
    //QLineEdit* titre;
    QLabel* info;
    QVBoxLayout* layout_p;
    QWidget* dock; //à vérifier
public:
    page_notes(Note &N);
    ~page_notes();
    QWidget& getdock_editer(){
        return *dock_editer;
    }
signals:
    void supp_dock_editer();
    void update_model();
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
