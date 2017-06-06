#include "aff_notes.h"

page_notes::page_notes(Note& n)
{
    create_dock();
    layout_p=new QVBoxLayout(this);
    layout_titre=new QHBoxLayout;
    titre=new QLineEdit (n.getTitle());
    titre->setReadOnly(true);
    info=new QLabel("Cette note est un "+n.getType()+"\nCréation le "+n.getCreation_date().toString("dd.MM.yyyy hh:mm")+"\nDernière modification le "+n.getLastmodif_date().toString("dd.MM.yyyy hh:mm"));
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
    layout_titre->addStretch();
    layout_titre->addWidget(titre);
    layout_titre->addStretch();
    layout_p->addLayout(layout_titre);

    layout_p->addWidget(note);
    layout_p->addStretch();
    layout_p->addWidget(info);

}
page_notes::~page_notes(){
    emit(supp_dock_editer());  // c'est l'interface qui gère la supp du dock
    delete layout_titre;
    delete info;
    delete layout_p;
    delete note;
}
void page_notes::create_dock(){
    dock=new QWidget;
    QHBoxLayout*layout=new QHBoxLayout(dock);
    QLabel* lecture_seul=new QLabel ("Ce document est ouvert en lecture seule");
    QPushButton* editer=new QPushButton ("Editer");
    editer->setShortcut(QKeySequence("ctrl+E"));
    layout->addStretch();
    layout->addWidget(lecture_seul);
    layout->addWidget(editer);
    connect(editer,SIGNAL(clicked(bool)),this,SLOT(editer_note(bool)));
}

page_vide::page_vide():QWidget(){
    QLabel *text = new QLabel("Sélectionner une note à afficher");
    text->setEnabled(false);
    QHBoxLayout *layout=new QHBoxLayout;
    layout->addStretch();
    layout->addWidget(text);
    layout->addStretch();

    this->setEnabled(false);
    this->setFont(QFont("grey0"));
    this->setLayout(layout);

}
