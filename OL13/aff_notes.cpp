/**
 * \file      aff_notes.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     //Bref
 *
 * \details  //Détail
 *
 */


#include "aff_notes.h"

page_notes::page_notes(Note& N):n(N)
{
    /** Window fenetre principale:
     *
***/
        layout_p=new QVBoxLayout(this);
        layout_titre=new QHBoxLayout;
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
        layout_p->addLayout(note->getLayout_titre());
        layout_p->addWidget(note);
        layout_p->addStretch();
        layout_p->addWidget(info);

    /** Création des docks
        * Dock editer
            **/
        dock_editer=new QWidget;
        QHBoxLayout*layout_editer=new QHBoxLayout(dock_editer);
        QPushButton* editer=new QPushButton ("Éditer");
        QLabel* lecture_seul=new QLabel ("Ce document est ouvert en lecture seule");
        if(n.getIsDeleted()){
            lecture_seul->setText("Ce document est supprimé, édition impossible");
            editer->setText("Restaurer la note");
        }
        else if(n.getIsArchive()){
            lecture_seul->setText("Ce document est archivé"
                                  ", édition impossible");
            editer->setText("Restaurer la note");
        }
        editer->setShortcut(QKeySequence("ctrl+E"));
        layout_editer->addStretch();
        layout_editer->addWidget(lecture_seul);
        layout_editer->addWidget(editer);

    //Dock aff relatio

        dock_aff_Rel=new QDockRelation(n.getId());

        /*

        dock_rel=new QWidget;
        QVBoxLayout * layout_aff_rel=new QVBoxLayout(dock_rel);
        QLabel* aff_relation =new QLabel("aff relation");
        layout_aff_rel->addWidget(aff_relation);
        */
   //connect
        connect(editer,SIGNAL(clicked(bool)),this,SLOT(editer_note(bool)));
   //NEW LNA
   //     connect(supprimer,SIGNAL(clicked(bool)),this,SLOT(supprimer_note(bool)));

}
page_notes::~page_notes(){
    note->saveNote(n);
    emit(update_model());
    emit(supp_dock_editer());  // c'est l'interface qui gère la supp du dock
    emit(supp_dock_aff_rel());
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
