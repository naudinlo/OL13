#include "interface.h"

interface::interface(): QMainWindow(), fen_creerNote(this)
{
    note_manager=NotesManager::getInstance();

    QWidget *ZoneCentrale = new QWidget(this);
    MenuFichier =menuBar()->addMenu("&fichier");
    MenuEd =menuBar()->addMenu("&Edition");
    MenuAff =menuBar()->addMenu("&Affichage");
    fichiersRecents=MenuFichier->addMenu("Ficher &récents");
    fichiersRecents->addAction("Fichier bidon 1.txt");

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
    QToolBar *toolBarFichier =addToolBar("fichier");
    toolBarFichier->addAction(ActionOuvrir);
    MenuFichier->addAction(ActionOuvrir);


    QAction *ActionNouveau=new QAction("&Nouvelle Note",this);
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

    QLabel *text = new QLabel("selectionner une Note à afficher");
    text->setEnabled(false);
    QHBoxLayout *layout=new QHBoxLayout;
    layout->addStretch();
    layout->addWidget(text);
    layout->addStretch();

    ZoneCentrale->setEnabled(false);
    ZoneCentrale->setFont(QFont("grey0"));
    ZoneCentrale->setLayout(layout);

    CreateDock_selected_Note();
    setCentralWidget(ZoneCentrale);
}

void interface::CreateDock_selected_Note(){
    listNote=new selection_note();
    dock_selected_Note=new QDockWidget("Selectionner Une Note",this);
    dock_selected_Note->setAllowedAreas(Qt::LeftDockWidgetArea );
    dock_selected_Note->setWidget(listNote);
    addDockWidget(Qt::LeftDockWidgetArea, dock_selected_Note);
    MenuAff->addAction(dock_selected_Note->toggleViewAction());
    connect(listNote,SIGNAL(selection(QModelIndex)),this,SLOT(afficher_note(QModelIndex)));
}
void interface::Destruct_selected_Note(){
    delete listNote;
    MenuAff->removeAction(dock_selected_Note->toggleViewAction());
    delete dock_selected_Note;
}

void interface::OuvrirFichier(){
    QString fichier = QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString());
    if(fichier != 0)
    {
        QMessageBox::information(this,"Fichier","vous avez sélèctionnée:"+fichier);
        Destruct_selected_Note();
        QMessageBox::information(this,"Fichier","vous avez sélèctionnée:"+fichier);
        CreateDock_selected_Note(); //prendre en compte le changement de vue
        note_manager->setFilename(fichier.toStdString());
        //note_manager->load();
    }
    else
        QMessageBox::warning(this,"Fichier","Impossible d'ouvrir le fichier"+fichier);

}
void interface::save(){
    while(note_manager->getFilename().empty())
    {
        QMessageBox::information(this,"sauvegarde","selectionner un ficher");
        OuvrirFichier();
    }
    note_manager->save();
}

void interface::CreerNote(){

    fen_creerNote.show();
    connect(&fen_creerNote,SIGNAL(newNote(Note* )),this,SLOT(addNewNote(Note*)));
}

void interface::addNewNote(Note* n){

    QStandardItem *newitem = new QStandardItem(n->getTitle());
    newitem->setEditable(false);
    newitem->setWhatsThis(n->getId());
    listNote->getModel()->appendRow(newitem);
    newitem->appendRow(new QStandardItem("1 version"));
    listNote->getVue()->setModel(listNote->getModel());

}

selection_note::selection_note():QWidget(){

    layout= new QVBoxLayout(this);
    model= new QStandardItemModel;
    QStandardItem *item = new QStandardItem("article bidule");
    model->appendRow(item);
    item->appendRow(new QStandardItem("1 version"));
    vue=new QTreeView(this);
    vue->setModel(model);
    vue->header()->hide();
    vue->setDisabled(false);
    item->setEditable(false);
    layout->addWidget(vue);
    setLayout(layout);
    connect(vue,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(emit_selection(QModelIndex)));

}
void interface::afficher_note(QModelIndex index){
    QMessageBox::information(this, "note","new note");
    QStandardItem* current=listNote->model->item(index.row(),index.column());
    QMessageBox::information(this, current->text(),current->whatsThis());

}

