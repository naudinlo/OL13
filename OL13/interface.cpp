/**
 * \file      interface.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définit l'interface principale de l'application.
 */




#include "interface.h"
/**
 * \fn        interface::interface
 * \brief     Constructeur de la classe interface
 *              Fenêtre principale de l'application, gére tous
 *              les docks, effectue la liason entre les docks, les
 *             widget, et les boites de dialogues.
 *
 * \param
 */

interface::interface(): QMainWindow()
{
    /*** Initialisation des attributs ***/
        note_manager=NotesManager::getInstance();
        try{
            note_manager->load_fichier();
        }
        catch(NotesException e){
            QMessageBox::critical(this,"recupération des données",e.getinfo());
        }

        note_page=0;
        ZoneCentrale=new page_vide();

    /****Fenetre Principale***/
    // Menu:
        MenuFichier =menuBar()->addMenu("&Fichier");
        MenuEd =menuBar()->addMenu("&Edition");
        MenuAff =menuBar()->addMenu("&Affichage");
        fichiersRecents=MenuFichier->addMenu("Fichers &récents");
        fichiersRecents->addAction("Fichier bidon 2.txt");
        fichiersRecents->addAction("Fichier bidon 3.txt");
        QAction *Actiongras=new QAction("&Gras",this);
        Actiongras->setCheckable(true);
        Actiongras->setShortcut(QKeySequence("ctrl+G"));
        MenuEd->addAction(Actiongras);
        QAction *ActionQuitter =new QAction("&Quitter", this);
        ActionQuitter->setShortcut(QKeySequence("ctrl+Q"));
        ActionQuitter->setIcon(QIcon("LOGOUT.png"));
        connect(ActionQuitter,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
        MenuFichier->addAction(ActionQuitter);
        QAction *ActionOuvrir=new QAction("&Ouvrir",this);
        connect(ActionOuvrir,SIGNAL(triggered(bool)),this,SLOT(OuvrirFichier()));
        ActionOuvrir->setShortcut(QKeySequence("ctrl+O"));
        ActionOuvrir->setIcon(QIcon("Ouvrir.png"));
        QToolBar *toolBarFichier =addToolBar("Fichier");
        toolBarFichier->addAction(ActionOuvrir);
        MenuFichier->addAction(ActionOuvrir);
        QAction *ActionNouveau=new QAction("&Nouvelle note",this);
        ActionNouveau->setIcon(QIcon("new.png"));
        ActionNouveau->setShortcut(QKeySequence("ctrl+N"));
        connect(ActionNouveau,SIGNAL(triggered(bool)),this,SLOT(CreerNote()));
        toolBarFichier->addAction(ActionNouveau);
        MenuFichier->addAction(ActionNouveau);
        QAction *ActionSave=new QAction("&Sauvegarder",this);
        ActionSave->setIcon(QIcon("save.png"));
        ActionSave->setShortcut(QKeySequence("ctrl+S"));
        connect(ActionSave,SIGNAL(triggered(bool)),this,SLOT(save()));
        toolBarFichier->addAction(ActionSave);
        MenuFichier->addAction(ActionSave);

        //Action: supprimer une note

            QAction *ActionSupprimer=new QAction("&Supprimer note",this);
            ActionSupprimer->setIcon(QIcon("delete_Note.jpeg"));
            connect(ActionSupprimer,SIGNAL(triggered(bool)),this,SLOT(supprimer_note()));    //TODO : une fenêtre avec l'ensemble des notes et on choisit celle à supprimer
            toolBar_supp_note=addToolBar("Edition");
            toolBar_supp_note->addAction(ActionSupprimer);
            MenuFichier->addAction(ActionSupprimer);

            QAction *ActionViderCorbeille=new QAction("&Vider la corbeille",this);
            ActionViderCorbeille->setIcon(QIcon("corbeil.jpeg"));
            connect(ActionViderCorbeille,SIGNAL(triggered(bool)),this,SLOT(ViderCorbeille()));    //TODO : une fenêtre avec l'ensemble des notes et on choisit celle à supprimer
            toolBar_supp_note->addAction(ActionViderCorbeille);
            MenuFichier->addAction(ActionViderCorbeille);

    //Action: ajouter des relation
        Action_new_relation=new QAction("Editer de nouvelles relations ",this);
        Action_new_relation->setShortcut(QKeySequence("ctrl+R"));
        connect(Action_new_relation,SIGNAL(triggered(bool)),this,SLOT(E_relation()));
        toolBar_new_Rel=addToolBar("Edition");
        toolBar_new_Rel->addAction(Action_new_relation);
        toolBar_new_Rel->setHidden(true);


        Action_Fermer_Note=new QAction("Fermer la note",this);
        Action_Fermer_Note->setShortcut(QKeySequence("ctrl+alt+Q"));
        connect(Action_Fermer_Note,SIGNAL(triggered(bool)),this,SLOT(close_page_note()));
        toolBar_close=addToolBar("Edition");
        toolBar_close->addAction(Action_Fermer_Note);
        toolBar_close->setHidden(true);

        Action_Archiver_Note=new QAction("Archiver la note",this);
        Action_Archiver_Note->setShortcut(QKeySequence("ctrl+alt+A"));
        toolBar_new_Rel->addAction(Action_Archiver_Note);
        connect(Action_Fermer_Note,SIGNAL(triggered(bool)),this,SLOT(close_page_note()));

        Action_aff_relation=new QAction("Gérer les relations ",this);
        Action_aff_relation->setShortcut(QKeySequence("ctrl+A"));
        connect(Action_aff_relation,SIGNAL(triggered(bool)),this,SLOT(Aff_relation()));
        toolBar_supp_note->addAction(Action_aff_relation);

    CreateDock_selected_Note();
    setCentralWidget(ZoneCentrale);
    update_model();
}
/**
 * \fn interface::~interface
 * \brief Ferme l'interface
 * \details Vide la corbeille puis effectuer une sauvegarde automatique si il y a un fichier de sauvegarde référencer.
 *
 */
interface::~interface(){
    ViderCorbeille();
    if(note_manager->getFilename().isEmpty()){
                int reponse =QMessageBox::question(this,"Sauvegarde","Vous n'avez pas de fichier de sauvegarde en cours, voulez vous un nouveau fichier",QMessageBox::Yes|QMessageBox::No);
                if(reponse ==QMessageBox::Yes){
                    QString fichier = QFileDialog::getSaveFileName(this, "Créer un fichier", QString(), "File (*.xml)");
                    note_manager->setFilename(fichier);
                }
                else{

                QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "File (*.xml)");
                note_manager->setFilename(fichier);
            }

          }

            if(!(note_manager->getFilename().isEmpty()))
            {
                note_manager->save();
                fichiersRecents->addAction(note_manager->getFilename());
                QMessageBox::information(this,"Sauvegarde","Sauvegarde Reussi");
            }
            else{
                QMessageBox::critical(this,"Sauvegarde","Pas de fichier de sauvegarde");
            }
    NotesManager::libererInstance();

}


/**
 * \fn        interface::addAction_new_rel
 * \brief fonction outils, permettant de connecter, afficher l'action d'achiver une note
 * a la page courante.
 *
*/

void interface::addAction_new_rel(){

    MenuEd->addAction(Action_new_relation);
    toolBar_new_Rel->setHidden(false);
    connect(Action_Archiver_Note,SIGNAL(triggered(bool)),note_page,SLOT(Archiver_page_note()));
    toolBar_close->setHidden(false);

}
/**
<<<<<<< HEAD
 * \fn        interface::CreateDock_edited_Note
 * \brief Création des docks : Editer_note, et Afficher_Relation
 * affichés lors de l'ouverture d'une note
 *
*/

void interface::CreateDock_edited_Note(){
    dock_editer_note=new QDockWidget("Editer Document",this);
    dock_editer_note->setAllowedAreas(Qt::TopDockWidgetArea);
    dock_editer_note->setWidget(&(note_page->getdock_editer()));
    addDockWidget(Qt::TopDockWidgetArea,dock_editer_note);
    MenuEd->addAction(dock_editer_note->toggleViewAction());
    connect(note_page,SIGNAL(supp_dock_editer()),this,SLOT(supp_dock_editer()));

    dock_aff_Relation=new QDockWidget("Panneau des relations",this);
    dock_aff_Relation->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dock_aff_Relation);
    dock_aff_Relation->setWidget(note_page->getdock_aff_rel());
    MenuEd->addAction(dock_aff_Relation->toggleViewAction());
    connect(note_page,SIGNAL(supp_dock_aff_rel()),this,SLOT(supp_dock_aff_rel()));
    connect(note_page->getdock_aff_rel(),SIGNAL(selectionNote(QString,int)),this,SLOT(afficher_note(QString,int)));
}
/**
 * \fn interface:CreateDock_selected_Note
 * @brief Création des docks de selection de Note (panneu gauche)
 */
void interface::CreateDock_selected_Note(){
    listNote=new selection_note();
    dock_selected_Note=new QDockWidget("Sélectionner une note",this);
    dock_selected_Note->setAllowedAreas(Qt::LeftDockWidgetArea );
    dock_selected_Note->setWidget(listNote);
    dock_selected_Note->setMaximumWidth(300);
    dock_selected_Note->setMaximumHeight(200);
    addDockWidget(Qt::LeftDockWidgetArea, dock_selected_Note);
    MenuAff->addAction(dock_selected_Note->toggleViewAction());
    connect(listNote,SIGNAL(selection(QString,int)),this,SLOT(afficher_note(QString,int)));
    connect(this,SIGNAL(L_update_model()),listNote,SLOT(update_model()));

    dock_aff_archived_Note= new DockArchived(this);
    addDockWidget(Qt::LeftDockWidgetArea, dock_aff_archived_Note);
    connect(dock_aff_archived_Note,SIGNAL(selection(QString,int)),this,SLOT(afficher_note(QString,int)));
    connect(this,SIGNAL(A_update_model()),dock_aff_archived_Note,SLOT(update_archNoteModel()));
    connect(dock_aff_archived_Note,SIGNAL(update_removeDock()),this,SLOT(update_model()));

    dock_aff_removed_Note= new DockRemove(this);
    addDockWidget(Qt::LeftDockWidgetArea, dock_aff_removed_Note);
    connect(dock_aff_removed_Note,SIGNAL(selection(QString,int)),this,SLOT(afficher_note(QString,int)));
    connect(this,SIGNAL(S_update_model()),dock_aff_removed_Note,SLOT(update_archNoteModel()));
    connect(dock_aff_removed_Note,SIGNAL(update_removeDock()),this,SLOT(update_model()));
}

/**
 * \fn interface::Destruct_selected_Note
 *
 */
void interface::Destruct_selected_Note(){
    delete listNote;
    MenuAff->removeAction(dock_selected_Note->toggleViewAction());
    delete dock_selected_Note;
}
/**
 * \fn interface::OuvrirFichier
 * @brief Fenêtre permettant de selectionner/chargé un fichier de sauvegarde
 * Met à jour le manager de note et les docks.
 *
 */
void interface::OuvrirFichier(){
    QString fichier = QFileDialog::getOpenFileName(this, "Créer un fichier", QString(), "File (*.xml)");
    if(fichier != 0)
    {
        //QMessageBox::information(this,"Fichier","Vous avez sélectionné:"+fichier);

        fichiersRecents->addAction(fichier);
        note_manager->setFilename(fichier);
        note_manager->load();
        RelationManager::getInstance().load(fichier);
        update_model();

    }
    else{
        QMessageBox::warning(this,"Fichier","Impossible d'ouvrir le fichier");
    }
}
/**
 * \fn interface::save
 * @brief Permet de choisir/créer un fichier de sauvegarde
 * \details En cas de fichier invalide, la sauvegarde n'est pas effectué, et un signal critique est envoyé à l'utilisateur
 * \param
 */
void interface::save(){
        int reponse =QMessageBox::question(this,"Sauvegarde","Créer un nouveau fichier de sauvegarde",QMessageBox::No|QMessageBox::Yes);
        if(reponse ==QMessageBox::Yes){
            QString fichier = QFileDialog::getSaveFileName(this, "Créer un fichier", QString(), "File (*.xml)");
            note_manager->setFilename(fichier);

        }
        else if(note_manager->getFilename().isEmpty()){
            int reponse =QMessageBox::question(this,"Sauvegarde","Vous n'avez pas de fichier de sauvegarde en cours, voulez vous un nouveau fichier",QMessageBox::Yes|QMessageBox::No);
            if(reponse ==QMessageBox::Yes){
                QString fichier = QFileDialog::getSaveFileName(this, "Créer un fichier", QString(), "File (*.xml)");
                note_manager->setFilename(fichier);
            }
            else{

            QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "File (*.xml)");
            note_manager->setFilename(fichier);
        }

      }

        if(!(note_manager->getFilename().isEmpty()))
        {
            note_manager->save();
            note_manager->save_fichier();

            fichiersRecents->addAction(note_manager->getFilename());
            QMessageBox::information(this,"Sauvegarde","Sauvegarde Reussi");
        }
        else{
            QMessageBox::critical(this,"Sauvegarde","Pas de fichier de sauvegarde");
        }


    }


/**
  *\fn interface::CreerNote
 * @brief Ouvre une fenetre de dialogue de type Creation_Note, pour
 * permettre la création d'une note.
 * \details Une fois la note créer, le dock de note actif est mis à jour sont mis à jours
 *
 */
void interface::CreerNote(){
    fen_creerNote= new Creation_Note(this);
    fen_creerNote->exec();
    emit(L_update_model());
    delete fen_creerNote;

}
/**
 * \fn selection_note::selection_note
 * \brief constructeur du dock de selection de note
 *
 */
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
/**
  *
  * \fn selection_note::update_model
 * @brief Etablie/Met à jours le model contennant tous les Notes actif.
 * \details les notes affichées sont les notes actifs (non supprimées, non archivées) en effectuant une requete au près du
 * Note Manager
 */
void selection_note::update_model(){
    //Partie à modifier quand on aura load
        model->clear();
        NotesManager* m =NotesManager::getInstance();


        for(NotesManager::Iterator it= m->getIterator();!it.isDone();it.next()){
            if(!it.liste()->isEmpty()){
              if(!(it.current().getIsArchive() || it.current().getIsDeleted()))
                  {


                  QList< QStandardItem* >  items;

                      items.append(new QStandardItem(it.current().getId()));
                      items.append(new QStandardItem(it.current().getType()));
                      items.at(0)->setWhatsThis(it.current().getId());
                      model->appendRow(items);
                      for(QList<Note*>::iterator j=it.liste()->begin();j !=it.liste()->end();j++)
                      {
                          QList< QStandardItem* > item2;
                          //item2.push_back(new QStandardItem((*j)->getTitle()));
                          //item2.push_back(new QStandardItem((*j)->getLastmodif_date().toString()));
                          item2.append(new QStandardItem((*j)->getTitle()));
                          item2.append(new QStandardItem ((*j)->getLastmodif_date().toString()));
                          items.at(0)->appendRow(item2);
                      }
              }


            }
        }


}
/**
  *\fn selection_note::emit_selection
 * @brief Identifie la note/versions que l'utilisateur souhaité affiché
 * \details Si on choisit de cliquer sur l'id, d'une note on envoie les paramètre de façon à
 * obtenir la dernière versions. Sinon on envoie les coordonnées de la version sellectionner
 * @param i
 */
void selection_note::emit_selection(QModelIndex i){
    QModelIndex index;
    QStandardItem* current_note;
    QStandardItem* current_versions;

    if(!i.parent().isValid())
    {
        current_versions=model->item(i.row(),0);
        emit selection(current_versions->whatsThis(),0);
    }
    else
    {

        current_note=model->item(i.parent().row(),0);
        emit selection(current_note->whatsThis(),i.row());

    }
}
/**
 * interface::afficher_note
 * @brief slot qui permet l'ouverture d'une note.
 * @param Qstring id
 * @param int i
 * \details Elle vérifie si une note était déjà ouverte avant : la ferme, restaure la note, supprime le pointeur sur la note courante
 * essaye d'ouvrir la versions sélectionné : connecte cette dernière avec l'interface
 * si il est impossible d'ouvrir la note, on affiche la page d'acceuil.
 */
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
        connect(note_page,SIGNAL(update_model()),this,SLOT(update_model()));
        connect(note_page,SIGNAL(close_page()),this,SLOT(close_page_note()));

    }
    catch(NotesException e)
    {
        QMessageBox::warning(this,"Error",e.getinfo());
    }
    setCentralWidget(ZoneCentrale);
}

/**
  *
  * \fn interface::close_page_note
 * @brief Ferme la note en cours, si elle est bien encore ouverte
 * \details Action déclenché lorqu'on click sur le bouton de fermeture d'une note
 */
void interface::close_page_note(){
    if(note_page!=0) //Si à dejà ouvert une note avant, il faut
    {
        if(MenuEd->actions().contains(Action_new_relation)){ //Caché le bouton d'ajout de relation
            MenuEd->removeAction(Action_new_relation);
            toolBar_new_Rel->hide();
        }

        delete note_page; //Fermer la note
        note_page=0;
        toolBar_close->setHidden(true);
        ZoneCentrale=new page_vide();
        setCentralWidget(ZoneCentrale);
    }
}
