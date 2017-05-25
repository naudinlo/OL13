#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
class page_notes: public QWidget
{
protected:
    QWidget* dock;
    QHBoxLayout* layout_titre;
    QLabel* titre;
    QLabel* info;
    QVBoxLayout* layout_p;
public:
    page_notes(Note &n);
    void create_dock();
    QWidget& getdock(){
        return *dock;
    }
    virtual QWidget* returnNote() =0;
    void addInfo(){
        layout_p->addStretch();
        layout_p->addWidget(info);
    }
};
class page_article:public page_notes{


    QTextEdit* description;
public:
    page_article(Article& n);
    QWidget* returnNote(){
        return this;
    }
};
class page_Task: public page_notes{
    QGroupBox* duedate;
    QHBoxLayout* optional_duedate;
    QVBoxLayout* fen;
    QLabel* action;
    QLineEdit* E_action;
    QGroupBox* priority;
    QHBoxLayout* optional_priority;
    QSpinBox* E_priority;

    //QLabel* duedate;
    QDateTimeEdit* E_duedate;
    QLabel* status;
    QComboBox* E_status;
    QGridLayout* grid;

public:
    page_Task(Task& n);
    QWidget* returnNote(){
        return this;
    }

};



#endif // AFF_NOTES_H
