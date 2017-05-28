#include "aff_notes.h"

page_notes::page_notes(Note& n)
{
    create_dock();
    layout_p=new QVBoxLayout(this);
    layout_titre=new QHBoxLayout;
    titre=new QLabel(n.getTitle());
    info=new QLabel("Cette note est un "+n.getType()+" créée le :"+n.getCreation_date().toString()+". Dernière modification le :"+n.getLastmodif_date().toString());
    layout_titre->addStretch();
    layout_titre->addWidget(titre);
    layout_titre->addStretch();
    layout_p->addLayout(layout_titre);
    if(n.getType()=="Recording")
    {
        note=new QRecording;

    }
    else if(n.getType()=="Task")
    {
        note=new QTask;
    }
    else{
        note=new QArticle;
    }
    note->load_note(n);

    layout_p->addWidget(note);
    layout_p->addStretch();
    layout_p->addWidget(info);
}
void page_notes::create_dock(){
    dock=new QWidget;
    QHBoxLayout*layout=new QHBoxLayout(dock);
    QLabel* lecture_seul=new QLabel ("Ce document est ouvert en lecture seule");
    QPushButton* editer=new QPushButton ("Editer");
    layout->addStretch();
    layout->addWidget(lecture_seul);
    layout->addWidget(editer);
    connect(editer,SIGNAL(clicked(bool)),this,SLOT(editer_note(bool)));
}
