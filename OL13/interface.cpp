/**
 * \file      interface.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     //Expliquer brievement à quoi sert ce fichier.
 *              //EX : Définit les modèles de voiture et leur particularités.
 *
 * \details    //Expliquer en détail.
 *              //EX :Cette classe surcharge les accesseurs standards du module_voiture pour
 *                  convenir aux spécificités des différents modèles possibles.
 */




#include "interface.h"

interface::interface(): QMainWindow()
{
    /*** Initialisation des attributs ***/
        note_manager=NotesManager::getInstance();
        note_page=0;
        ZoneCentrale=new page_vide();

    /****Fenetre Principale***/
    // Menu:
        MenuFichier =menuBar()->addMenu("&Fichier");
        MenuEd =menuBar()->addMenu("&Edition");
        MenuAff =menuBar()->addMenu("&Affichage");
        fichiersRecents=MenuFichier->addMenu("Fichers &récents");
        fichiersRecents->addAction("Fichier bidon 1.txt");
        fichiersRecents->addAction("Fichier bidon 2.txt");
        fichiersRecents->addAction("Fichier bidon 3.txt");
        QAction *Actiongras=new QAction("&Gras",this);
        Actiongras->setCheckable(true);
        Actiongras->setShortcut(QKeySequence("ctrl+G"));
        MenuEd->addAction(Actiongras);
        QAction *ActionQuitter =new QAction("&Quitter", this);
        ActionQuitter->setShortcut(QKeySequence("ctrl+Q"));
    //    ActionQuitter->setIcon(QIcon("LOGOUT.png"));
        connect(ActionQuitter,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
        MenuFichier->addAction(ActionQuitter);
        QAction *ActionOuvrir=new QAction("&Ouvrir",this);
        connect(ActionOuvrir,SIGNAL(triggered(bool)),this,SLOT(OuvrirFichier()));
        ActionOuvrir->setShortcut(QKeySequence("ctrl+O"));
    //    ActionOuvrir->setIcon(QIcon("Ouvrir.png"));
        QToolBar *toolBarFichier =addToolBar("Fichier");
        toolBarFichier->addAction(ActionOuvrir);
        MenuFichier->addAction(ActionOuvrir);
        QAction *ActionNouveau=new QAction("&Nouvelle note",this);
    //    ActionNouveau->setIcon(QIcon("new.png"));
        ActionNouveau->setShortcut(QKeySequence("ctrl+N"));
        connect(ActionNouveau,SIGNAL(triggered(bool)),this,SLOT(CreerNote()));
        toolBarFichier->addAction(ActionNouveau);
        MenuFichier->addAction(ActionNouveau);
        QAction *ActionSave=new QAction("&Sauvegarder",this);
    //    ActionSave->setIcon(QIcon("save.png"));
        ActionSave->setShortcut(QKeySequence("ctrl+S"));
        connect(ActionSave,SIGNAL(triggered(bool)),this,SLOT(save()));
        toolBarFichier->addAction(ActionSave);
        MenuFichier->addAction(ActionSave);


    //Action: ajouter des relation
        Action_new_relation=new QAction("Editer de nouvelles relations ",this);
        Action_new_relation->setShortcut(QKeySequence("ctrl+R"));
        connect(Action_new_relation,SIGNAL(triggered(bool)),this,SLOT(E_relation()));
        toolBar_new_Rel=addToolBar("Edition");
        toolBar_new_Rel->addAction(Action_new_relation);
        toolBar_new_Rel->setHidden(true);
     /*
        Action_aff_relation=new QAction("Afficher les relations ",this);
        Action_aff_relation->setShortcut(QKeySequence("ctrl+A"));
        connect(Action_aff_relation,SIGNAL(triggered(bool)),this,SLOT(Aff_relation()));
        toolBar_new_Rel=addToolBar("Edition");
        toolBar_new_Rel->addAction(Action_aff_relation);
        toolBar_new_Rel->setHidden(true);
    */
    //Action: supprimer une note
        //TODO : supprimer note ! Créer slot supprimer_note
        QAction *ActionSupprimer=new QAction("&Supprimer note",this);
        connect(ActionSupprimer,SIGNAL(triggered(bool)),this,SLOT(supprimer_note()));    //TODO : une fenêtre avec l'ensemble des notes et on choisit celle à supprimer
        toolBar_supp_note=addToolBar("Edition");
        toolBar_supp_note->addAction(ActionSupprimer);

    CreateDock_selected_Note();
    setCentralWidget(ZoneCentrale);
}
void interface::addAction_new_rel(){

    MenuEd->addAction(Action_new_relation);
    toolBar_new_Rel->setHidden(false);

}

void interface::CreateDock_edited_Note(){
    dock_editer_note=new QDockWidget("Editer Document",this);
    dock_editer_note->setAllowedAreas(Qt::TopDockWidgetArea);
    dock_editer_note->setWidget(&(note_page->getdock_editer()));
    addDockWidget(Qt::TopDockWidgetArea,dock_editer_note);
    MenuEd->addAction(dock_editer_note->toggleViewAction());
    connect(note_page,SIGNAL(supp_dock_editer()),this,SLOT(supp_dock_editer()));

    dock_aff_Relation=new QDockWidget("Afficher les relations",this);
    dock_aff_Relation->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dock_aff_Relation);
    dock_aff_Relation->setWidget(note_page->getdock_aff_rel());
    MenuEd->addAction(dock_aff_Relation->toggleViewAction());
    connect(note_page,SIGNAL(supp_dock_aff_rel()),this,SLOT(supp_dock_aff_rel()));
    connect(note_page->getdock_aff_rel(),SIGNAL(selection(QString,int)),this,SLOT(afficher_note(QString,int)));
}


/*
void interface::CreateDock_aff_Relation(){
    dock_aff_Relation=new QDockWidget("Afficher les relation liès à cette Note",this);
    dock_aff_Relation->setAllowedAreas(Qt::RightDockWidgetArea);
    //dock_aff_Relation->setWidget();
}
*/
void interface::CreateDock_selected_Note(){
    listNote=new selection_note();
    dock_selected_Note=new QDockWidget("Sélectionner une note",this);
    dock_selected_Note->setAllowedAreas(Qt::LeftDockWidgetArea );
    dock_selected_Note->setWidget(listNote);
    dock_selected_Note->setMaximumWidth(300);
    addDockWidget(Qt::LeftDockWidgetArea, dock_selected_Note);
    MenuAff->addAction(dock_selected_Note->toggleViewAction());
    connect(listNote,SIGNAL(selection(QString,int)),this,SLOT(afficher_note(QString,int)));
    connect(this,SIGNAL(update_model()),listNote,SLOT(update_model()));
}
void interface::Destruct_selected_Note(){
    delete listNote;
    MenuAff->removeAction(dock_selected_Note->toggleViewAction());
    delete dock_selected_Note;
}

void interface::OuvrirFichier(){
    //QString fichier = QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString());
    QFileDialog openfile(this,"Ouvrir un fichier",QString());
    QString fichier=openfile.getOpenFileName();
    if(fichier != 0)
    {
        Destruct_selected_Note();
        QMessageBox::information(this,"Fichier","Vous avez sélectionné:"+fichier);
        //CreateDock_selected_Note(); //prendre en compte le changement de vue
        emit(update_model());
        note_manager->setFilename(fichier);
        //note_manager->load();
    }
    else if(!openfile.close())
        QMessageBox::warning(this,"Fichier","Impossible d'ouvrir le fichier"+fichier);

}
void interface::save(){
    if(note_manager->getFilename().isEmpty())
    {
        QMessageBox::information(this,"Sauvegarde","Sélectionner un ficher");
        OuvrirFichier();
    }
    //note_manager->save();
}

void interface::CreerNote(){
    fen_creerNote= new Creation_Note(this);
    fen_creerNote->show();
    connect(fen_creerNote,SIGNAL(newNote(Note& )),this,SLOT(addNewNote(Note&)));
}

void interface::addNewNote(Note& n){
    /*
    QList< QStandardItem* > note;
    note.append(new QStandardItem (n.getId()));
    //note.append(new QStandardItem(QString(n.getType())));


    std::stringstream f;
    QString string_dt=(n.getCreation_date()).toString("dd.MM.yyyy");
    f<<string_dt.toStdString();
    QList< QStandardItem* > items;
    items.append(new QStandardItem(n.getTitle()));
    items.append(new QStandardItem (f.str().c_str()));
    note.at(0)->appendRow(items);
    items.at(0)->setWhatsThis(n.getId());;
    listNote->getModel()->appendRow(note);

    listNote->getVue()->setModel(listNote->getModel());
    */
    emit(update_model());
    delete fen_creerNote;
}

selection_note::selection_note():QWidget(){

    layout= new QVBoxLayout(this);
    model= new QStandardItemModel;
    update_model();
    vue=new QTreeView(this);
    vue->setAlternatingRowColors(true);
    vue->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vue->setModel(model);
    vue->header()->hide();
    vue->setDisabled(false);
    layout->addWidget(vue);
    setLayout(layout);
    connect(vue,SIGNAL(activated(QModelIndex)),this,SLOT(emit_selection(QModelIndex)));
}
void selection_note::update_model(){
    //Partie à modifier quand on aura load
        model->clear();
        NotesManager* m =NotesManager::getInstance();


        for(NotesManager::Iterator it= m->getIterator();!it.isDone();it.next()){
            QList< QStandardItem* >  items;

                items.append(new QStandardItem(it.current().getId()));
                items.append(new QStandardItem(it.current().getType()));
                items.at(0)->setWhatsThis(it.current().getId());
                model->appendRow(items);
                for(QList<Note*>::iterator j=it.getIteratorVersions();j !=it.liste()->end();j++)
                {
                    QList< QStandardItem* > item2;
                    //item2.push_back(new QStandardItem((*j)->getTitle()));
                    //item2.push_back(new QStandardItem((*j)->getLastmodif_date().toString()));
                    item2.append(new QStandardItem((*j)->getTitle()));
                    item2.append(new QStandardItem ((*j)->getLastmodif_date().toString()));
                    //items.at(0)->appendRow(item2);
                    items.at(0)->insertRow(0,item2);
                }
        }

}

void selection_note::emit_selection(QModelIndex i){
    QModelIndex index;
    QStandardItem* current_note;
    QStandardItem* current_versions;

    if(!i.parent().isValid())
    {
        QMessageBox::warning(this,"clique","père");
        current_versions=model->item(i.row(),0);
        emit selection(current_versions->whatsThis(),0);
    }
    else
    {
        QMessageBox::warning(this,"clique fils",QString::number(i.row()));

        current_note=model->item(i.parent().row(),0);
        //current_versions=current_note->child(i.row(),0);
        emit selection(current_note->whatsThis(),i.row());

    }
}

void interface::afficher_note(QString id, int i){
    if(note_page!=0) //Si à dejà ouvert une note avant, il faut
    {
        if(MenuEd->actions().contains(Action_new_relation)){ //Caché le bouton d'ajout de relation
            MenuEd->removeAction(Action_new_relation);
            toolBar_new_Rel->hide();
        }

        delete note_page; //Fermer la note
        note_page=0;
        ZoneCentrale=new page_vide();
    }
    try{
            Note& current=note_manager->getNoteVersion(id,i);


        note_page = new page_notes(current);
        note_id=id;
        ZoneCentrale=note_page;
        CreateDock_edited_Note();
        addAction_new_rel();
        connect(note_page,SIGNAL(update_model()),listNote,SLOT(update_model()));

    }
    catch(NotesException e)
    {
        QMessageBox::warning(this,"Error",e.getinfo());
    }
    setCentralWidget(ZoneCentrale);
}

