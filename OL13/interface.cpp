#include "interface.h"

interface::interface(): QMainWindow(), fen_creerNote(this)
{
    listNote=new selection_note();
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
    QDockWidget* dock=new QDockWidget("Selectionner Une Note",this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea );
    dock->setWidget(listNote);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    MenuAff->addAction(dock->toggleViewAction());
}
void interface::OuvrirFichier(){
    QString fichier = QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString());
    if(fichier != 0)
            QMessageBox::information(this,"Fichier","vous avez sélèctionnée:"+fichier);

}

void interface::CreerNote(){

    fen_creerNote.show();
}

selection_note::selection_note():QWidget(){
    layout= new QVBoxLayout(this);
    model=new QDirModel;
    vue=new QTreeView(this);
    vue->setModel(model);
    layout->addWidget(vue);
    setLayout(layout);
}
