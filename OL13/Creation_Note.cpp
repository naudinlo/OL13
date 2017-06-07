#include "Creation_Note.h"

Creation_Note::Creation_Note(QWidget* parent): QDialog(parent), E_title_not_null(false), E_note_not_null(true){
    /* **Window: creation Note
    *La où est saisi le titre et l'id de la note
    **/
        this->setWindowTitle("Nouvelle Note");
        L_fen=new(QVBoxLayout) (this);
        L_type=new(QGridLayout) ();
        L_defClass=new(QGridLayout) ();
        L_comm=new(QGridLayout) ();
        L_bouton=new(QHBoxLayout)();
        E_title=new(QLineEdit) ();
        title=new(QLabel)("Titre");
        title->setFrameStyle(QFrame::Panel |QFrame::Raised);
        E_id=new QLineEdit;
        id=new QLabel("Identifiant de la note");
        type=new(QLabel)("Type de Note :");
        typeBox=new(QComboBox);
        typeBox->addItem("Article");
        typeBox->addItem("Tache");
        typeBox->addItem("Enregistrement");
        connect(typeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(select_type(int)));
        L_defClass->addWidget(id,0,0);
        L_defClass->addWidget(E_id,0,1);
        L_defClass->addWidget(title, 1,0);
        L_defClass->addWidget(E_title, 1,1);
        L_defClass->addWidget(type, 2,0);
        L_defClass->addWidget(typeBox, 2,1);
        Creer=new(QPushButton) ("Créer",this);
        Creer->setEnabled(false);
        quitter=new(QPushButton) ("Quitter", this);
        B_defNote=new(QGroupBox)("Note:",this);
        B_defNote->setLayout(L_defClass);
        L_bouton->addWidget(quitter);
        L_bouton->addWidget(Creer);
        B_type=new(QGroupBox)("Article",this);
        note=new QArticle();
        L_type->addWidget(note,0,0);
        B_type->setLayout(L_type);
        L_fen->addWidget(B_defNote);
        L_fen->addWidget(B_type);
        L_fen->addLayout(L_bouton);

    QObject::connect(quitter,SIGNAL(clicked(bool)),this,SLOT(fenclose()));
    QObject::connect(Creer,SIGNAL(clicked(bool)),this,SLOT(Creer_Note()));
    QObject::connect(Creer,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(E_title,SIGNAL(textChanged(QString)),this,SLOT(activer_E_title_not_null()));
    connect(this,SIGNAL(change_Creer()),this,SLOT(activer_Creer()));

}
void Creation_Note::edit_article(){
    B_type->setTitle("Article");
    note=new QArticle();


}
void Creation_Note::edit_tache(){
    B_type->setTitle("Tache");
    note=new QTask();
}
void Creation_Note::edit_enregistrement(){
    B_type->setTitle("Enregistrement");
    note=new QRecording();
}

void Creation_Note::select_type(int type){
    L_type->removeWidget(note);
    delete note;
    Creer->setEnabled(false);
    E_note_not_null=false;
    switch (type) {
    case 0:
        edit_article();
        Creer->setEnabled(true);
        break;
    case 1:

        edit_tache();
        break;
    case 2:
        edit_enregistrement();
        break;
    default:

        break;
    }

    connect(note,SIGNAL(checked_creer(bool)),this,SLOT(activer_E_note_not_null(bool)));
    L_type->addWidget(note,0,0);
}

void Creation_Note::Creer_Note(){
    try{
    Note& essai=note->get_note(E_id->text(),E_title->text());
    QMessageBox::information(this,E_title->text(),QString::fromStdString(essai.toString()));
    emit(newNote(essai));
    }
    catch(NotesException e)
    {
        QMessageBox::warning(this,"Echec lors de la création d'une note", e.getinfo());
    }

}


