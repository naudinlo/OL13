#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"

class page_notes: public QWidget
{
    QWidget* dock;
    QVBoxLayout* layout_p;
    QHBoxLayout* layout_titre;
    QLineEdit* titre;
public:
    page_notes();
    void create_dock();
    QWidget& getdock(){
        return *dock;
    }
};

#endif // AFF_NOTES_H
