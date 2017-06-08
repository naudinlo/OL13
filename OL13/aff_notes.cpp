#include "aff_notes.h"

page_notes::page_notes(Note& n)
{
    /** Window fenetre principale:
     *
***/
        layout_p=new QVBoxLayout(this);
        layout_titre=new QHBoxLayout;
        titre=new QLineEdit (n.getTitle());
        titre->setReadOnly(true);
        info=new QLabel("Cette note est un "+n.getType()+"\nCréation le "+n.getCreation_date().toString("dd.MM.yyyy hh:mm")+"\nDernière modification le "+n.getLastmodif_date().toString("dd.MM.yyyy hh:mm"));

        //On recuperer l'affichage d'une note particulière
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

    /** Création des docks
        * Dock editer
            **/
        dock_editer=new QWidget;
        QHBoxLayout*layout_editer=new QHBoxLayout(dock_editer);
        QLabel* lecture_seul=new QLabel ("Ce document est ouvert en lecture seule");
        QPushButton* editer=new QPushButton ("Editer");
        editer->setShortcut(QKeySequence("ctrl+E"));
        QPushButton* supprimer=new QPushButton ("Supprimer");
        layout_editer->addStretch();
        layout_editer->addWidget(lecture_seul);
        layout_editer->addWidget(editer);

    //Dock aff relatio
        dock_rel=new QWidget;
        QVBoxLayout * layout_aff_rel=new QVBoxLayout(dock_rel);
        QLabel* aff_relation =new QLabel("aff relation");
        layout_aff_rel->addWidget(aff_relation);
   //connect
        connect(editer,SIGNAL(clicked(bool)),this,SLOT(editer_note(bool)));
   //NEW LNA
   //     connect(supprimer,SIGNAL(clicked(bool)),this,SLOT(supprimer_note(bool)));

}
page_notes::~page_notes(){
    emit(supp_dock_editer());  // c'est l'interface qui gère la supp du dock
    delete layout_titre;
    delete info;
    delete layout_p;
    delete note;
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
