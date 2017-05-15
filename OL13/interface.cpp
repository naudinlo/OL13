#include "interface.h"

interface::interface(): QMainWindow(), fen_creerNote(this)
{
    QWidget *ZoneCentrale = new QWidget(this);
    QMenu *MenuFichier =menuBar()->addMenu("&fichier");
    QMenu *MenuEd =menuBar()->addMenu("&Edition");
    QMenu *MenuAff =menuBar()->addMenu("&Affichage");
    QMenu *fichiersRecents=MenuFichier->addMenu("Ficher &récents");
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
    //ZoneCentrale->setEnabled(false);
    ZoneCentrale->setFont(QFont("grey0"));
    ZoneCentrale->setLayout(layout);
    setCentralWidget(ZoneCentrale);


}

void interface::OuvrirFichier(){
    QString fichier = QFileDialog::getOpenFileName(this,"Ouvrir un fichier",QString());
    if(fichier != 0)
            QMessageBox::information(this,"Fichier","vous avez sélèctionnée:"+fichier);

}

void interface::CreerNote(){

    fen_creerNote.show();
}
