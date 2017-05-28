#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
#include "qnote.h"
class page_notes: public QWidget
{
    Q_OBJECT
protected:
    QWidget* dock;
    QHBoxLayout* layout_titre;
    QLabel* titre;
    QLabel* info;
    QVBoxLayout* layout_p;
    QNote* note;

public:
    page_notes(Note &n);
    ~page_notes();
    void create_dock();
    QWidget& getdock(){
        return *dock;
    }
signals:
    void supp_dock_editer();
public slots:
    void editer_note(bool status){
        note->readOnly(status);
        delete dock;
        emit(supp_dock_editer());
    }
};

class page_vide: public QWidget{
public:
    page_vide();
};

#endif // AFF_NOTES_H
