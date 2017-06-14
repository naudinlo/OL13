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
/**
 * @fn page_notes::page_notes
 * @param N
 * \brief constructeur
 * \details Donne les informations non éditable de la note ouverte
 * créer les docks relative à la note courante
 */
page_notes::page_notes(Note& N):n(N),newNote(nullptr)
{
    /** Window fenetre principale:
     *
***/
        layout_p=new QVBoxLayout(this);
        layout_info=new QHBoxLayout;
        info=new QLabel("Cette note est un "+n.getType()+"\nCréation le "+n.getCreation_date().toString("dd.MM.yyyy hh:mm")+"\nDernière modification le "+n.getLastmodif_date().toString("dd.MM.yyyy hh:mm"));
        savebutton =new QPushButton("Sauvegarder");
        savebutton->setHidden(true);
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
        connect(dock_aff_Rel,SIGNAL(selectionRelation(QString)),this,SLOT(aff_Relation(QString)));
        /*

        dock_rel=new QWidget;
        QVBoxLayout * layout_aff_rel=new QVBoxLayout(dock_rel);
        QLabel* aff_relation =new QLabel("aff relation");
        layout_aff_rel->addWidget(aff_relation);
        */
    //Widget Reférence
        widget_ref = new Qreference(n);

   //connect
        connect(editer,SIGNAL(clicked(bool)),this,SLOT(editer_note(bool)));
   //NEW LNA
   //     connect(supprimer,SIGNAL(clicked(bool)),this,SLOT(supprimer_note(bool)));
        connect(savebutton,SIGNAL(clicked(bool)),this,SLOT(on_savebutton_clicked()));
        //connect(savebutton,SIGNAL(clicked(bool)),widget_ref,SLOT(update_model()));

        L_titre=new QVBoxLayout;
        L_titre->addWidget(savebutton);
        QGridLayout* HL_titre=new QGridLayout();
        L_titre->addLayout(HL_titre);
        QLineEdit* id=new QLineEdit();
        id->setEnabled(false);
        QLabel* idLabel=new QLabel("Identifiant de la note:");
        QLabel* titreLabel=new QLabel("Titre :");
        HL_titre->addWidget(idLabel,0,0);
        HL_titre->addWidget(titreLabel,0,1);
        HL_titre->addWidget(id,1,0);
        id->setText(n.getId());
        HL_titre->addLayout(note->getLayout_titre(),1,1);
        layout_p->addLayout(L_titre);
        layout_p->addWidget(note);
        layout_p->addStretch();
        layout_info->addWidget(info);
        layout_info->addWidget(widget_ref);
        layout_p->addLayout(layout_info);
}
/**
 * @fn page_notes::~page_notes
 * \brief effectue une saugarde automatique de la note
 * \details demmande la fermeture des docks par l'interface
 */
page_notes::~page_notes(){
    if(newNote !=nullptr){
        try{
        note->saveNote(*newNote);
        }
        catch(NotesException e){
            QMessageBox::critical(this,"echec: automatique sauvegarde",e.getinfo());
        }
    }
    emit(update_model());
    emit(supp_dock_editer());  // c'est l'interface qui gère la supp du dock
    emit(supp_dock_aff_rel());
    delete L_titre;
    delete info;
    delete layout_p;
    delete note;
}
/**
 * @fn page_vide::page_vide
 * \brief constructeur de la page d'acceuil
 */
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
