#include "interface.h"

interface::interface(): QMainWindow(), indexNote()
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

    //Action: supprimer une note
        //TODO : supprimer note ! Créer slot supprimer_note
        QAction *ActionSupprimer=new QAction("&Supprimer note",this);
    //    connect(ActionSupprimer,SIGNAL(triggered(bool)),this,SLOT(supprimer_note(QString &id)));    //TODO : une fenêtre avec l'ensemble des notes et on choisit celle à supprimer
        toolBarFichier->addAction(ActionSupprimer);
        MenuFichier->addAction(ActionSupprimer);

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
    connect(listNote,SIGNAL(selection(QString,QModelIndex)),this,SLOT(afficher_note(QString,QModelIndex)));
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
        CreateDock_selected_Note(); //prendre en compte le changement de vue
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
    delete fen_creerNote;
}

selection_note::selection_note():QWidget(){

    layout= new QVBoxLayout(this);
    model= new QStandardItemModel;

//Partie à modifier quand on aura load

    /*
    QStandardItem *item = new QStandardItem("Article Bidule");
    QStandardItem *item2 = new QStandardItem("Type");
    QList< QStandardItem* >  items;
    items.append(item);
    items.append(item2);

    model->appendRow(items);
    item->appendRow(new QStandardItem("1 version"));
    */
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
void selection_note::emit_selection(QModelIndex i){
    QModelIndex index;
    QStandardItem* current_note;
    QStandardItem* current_versions;

    if(!i.parent().isValid())
    {
        current_note=model->item(i.row(),0);
        current_versions=current_note->child(0,0); //on selection la plus récente version si on a pas select de versions
    }
    else
    {
        current_note=model->item(i.parent().row(),0);
        current_versions=current_note->child(i.row(),0);
    }
  emit selection(current_versions->whatsThis(),i);
}

void interface::afficher_note(QString id, QModelIndex index){
    if(note_page!=0) //Si à dejà ouvert une note avant, il faut
    {
        if(MenuEd->actions().contains(Action_new_relation)){ //Fermer les docks restants (ex: editer note)
            MenuEd->removeAction(Action_new_relation);
            toolBar_new_Rel->hide();
        }
        delete note_page; //Fermer la note
        note_page=0;
        ZoneCentrale=new page_vide();
    }
    try{
        Note& current=note_manager->getNote(id);
        note_page=new page_notes(current);
        indexNote=index.row();
        note_id=id;
        ZoneCentrale=note_page;
        CreateDock_edited_Note();
        addAction_new_rel();

    }
    catch(NotesException e)
    {
        QMessageBox::warning(this,"Error",e.getinfo());
    }
    setCentralWidget(ZoneCentrale);
}

