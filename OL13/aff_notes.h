#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
#include "qnote.h"
class page_notes: public QWidget
{
protected:
    QWidget* dock;
    QHBoxLayout* layout_titre;
    QLabel* titre;
    QLabel* info;
    QVBoxLayout* layout_p;
    QNote* note;

public:
    page_notes(Note &n);
    void create_dock();
    QWidget& getdock(){
        return *dock;
    }
};

#endif // AFF_NOTES_H
