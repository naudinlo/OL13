#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
#include "qnote.h"
class page_notes: public QWidget
{
    Q_OBJECT
protected:
    QWidget* dock_editer;
    QWidget* dock_rel;
    QHBoxLayout* layout_titre;
    QLineEdit* titre;
    QLabel* info;
    QVBoxLayout* layout_p;
    QNote* note;

public:
    page_notes(Note &n);
    ~page_notes();
    void create_dock();
    QWidget& getdock_editer(){
        return *dock_editer;
    }
signals:
    void supp_dock_editer();
public slots:
    void editer_note(bool status){
        titre->setReadOnly(status);
        note->readOnly(status);
        delete dock_editer;
        emit(supp_dock_editer());
    }
};

class page_vide: public QWidget{
public:
    page_vide();
};

#endif // AFF_NOTES_H
