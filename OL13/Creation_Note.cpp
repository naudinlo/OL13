#include "Creation_Note.h"
Creation_Note::Creation_Note(QWidget* parent): QDialog(parent), E_title_not_null(false), E_note_not_null(true){
    this->setWindowTitle("Nouvelle Note");

    L_fen=new(QVBoxLayout) (this);
    L_type=new(QGridLayout) ();
    L_defClass=new(QGridLayout) ();
    L_comm=new(QGridLayout) ();
    L_bouton=new(QHBoxLayout)();

    E_title=new(QLineEdit) ();
    title=new(QLabel)("Titre");
    title->setFrameStyle(QFrame::Panel |QFrame::Raised);
    type=new(QLabel)("Type de Note :");

    typeBox=new(QComboBox);
    typeBox->addItem("Article");
    typeBox->addItem("Tache");
    typeBox->addItem("Enregistrement");
    connect(typeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(select_type(int)));
    L_defClass->addWidget(title, 0,0);
    L_defClass->addWidget(E_title, 0,1);
    L_defClass->addWidget(type, 1,0);
    L_defClass->addWidget(typeBox, 1,1);





    Creer=new(QPushButton) ("Créer",this);
    Creer->setEnabled(false);
    quitter=new(QPushButton) ("Quitter", this);
    QObject::connect(quitter,SIGNAL(clicked(bool)),this,SLOT(close()));
    QObject::connect(Creer,SIGNAL(clicked(bool)),this,SLOT(Creer_Note()));

    B_defNote=new(QGroupBox)("Note:",this);
    B_defNote->setLayout(L_defClass);


    L_bouton->addWidget(quitter);
    L_bouton->addWidget(Creer);

    B_comm=new(QGroupBox)("Ajouter des Reference",this);
    B_comm->setLayout(L_comm);
    B_comm->setCheckable(true);


    B_type=new(QGroupBox)("Article",this);

    note=new QArticle();
    connect(E_title,SIGNAL(textChanged(QString)),this,SLOT(activer_E_title_not_null()));
    connect(this,SIGNAL(change_Creer()),this,SLOT(activer_Creer()));
    L_type->addWidget(note,0,0);
    B_type->setLayout(L_type);


    L_fen->addWidget(B_defNote);
    L_fen->addWidget(B_type);
    L_fen->addWidget(B_comm);
    L_fen->addLayout(L_bouton);

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
    //gérer l'id
    QString id("xxx");
    Note* essai=note->get_note(id,E_title->text());

    QMessageBox::information(this,E_title->text(),QString::fromStdString(essai->toString()));
}



QArticle::QArticle(): QNote(){
    grid=new QGridLayout(this);
    text=new QLabel("Saisir Texte");
    E_text=new QTextEdit();
    grid->addWidget(E_text,0,1,0,2);
    grid->addWidget(text,0,0);
}

QTask::QTask():QNote(){
    optional=new QGroupBox (this);
    fen=new QVBoxLayout (this);
    optional->setCheckable(true);
    optional->setTitle("option :");
    optional_box=new QGridLayout;
    grid=new QGridLayout(this);
    action=new QLabel ("action");
    priority=new QLabel ("Prioritée");
    E_priority=new QSpinBox;
    duedate=new QLabel ("Date de réalisation");
    E_duedate=new QDateEdit;
    E_duedate->setDate(QDate::currentDate());
    E_duedate->setCalendarPopup(true);
    status=new QLabel("Etat");
    E_status=new QComboBox;
    E_status->addItem("En cours");
    E_status->addItem("En attente");
    E_status->addItem("Complétée");
    E_action=new QLineEdit;
    connect(E_action,SIGNAL(textEdited(QString)),SLOT(check_creer()));
    grid->addWidget(action,0,0);
    grid->addWidget(E_action,0,1);
    grid->addWidget(status,1,0);
    grid->addWidget(E_status,1,1);

    optional_box->addWidget(priority,0,1);
    optional_box->addWidget(E_priority,0,2);
    optional_box->addWidget(duedate,1,1);
    optional_box->addWidget(E_duedate,1,2);

    fen->addLayout(grid);
    optional->setLayout(optional_box);
    fen->addWidget(optional);
}

QRecording::QRecording():QNote(){
    grid=new QGridLayout(this);
    description=new QLabel("descrition:");
    E_description=new QTextEdit;
    type=new QLabel("type d'enregistrement");
    E_link=new QLineEdit;
    E_link->setEnabled(false);
    link=new QPushButton("Selectionner enregistrement");
    E_type=new QComboBox;
    E_type->addItem("Image");
    E_type->addItem("Audio");
    E_type->addItem("Video");
    connect(link,SIGNAL(clicked(bool)),this,SLOT(OuvrirFichier()));
    connect(E_link,SIGNAL(textChanged(QString)),this,SLOT(check_creer()));
    connect(E_description,SIGNAL(textChanged()),this,SLOT(check_creer()));
    grid->addWidget(description,0,0);
    grid->addWidget(E_description,1,0,1,2);
    grid->addWidget(type,2,0);
    grid->addWidget(E_type,2,1);
    grid->addWidget(link,3,0);
    grid->addWidget(E_link,3,1);

}

QString QRecording::OuvrirFichier(){
    QString fichier = QFileDialog::getOpenFileName(this,"Selectionner un enregistrement",QString());
    if(fichier != 0)
            E_link->setText(fichier);
    return fichier;

}

void QArticle::check_creer(){
}

void QRecording::check_creer(){
    if(!E_description->document()->isEmpty() && !E_link->text().isEmpty())
        emit checked_creer(true);
    else
        emit checked_creer(false);
}
void QTask::check_creer(){

    if(!E_action->text().isEmpty())
    {
        emit checked_creer(true);

    }
    else emit checked_creer(false);

    }

Note *QArticle::get_note(QString id,QString title){
   return new Article(id,title,E_text->document()->toPlainText());
}

Note *QTask::get_note(QString id, QString title){
    ENUM::StatusType etat=static_cast<ENUM::StatusType>(E_status->currentIndex());
    if(optional->isChecked())
    {
        QMessageBox::warning(this,"pas encore fait","gérer la date");
        //return new Task(id,title,E_action->text(),etat,E_priority->value(),E_duedate->date());
    }
    return new Task(id,title,E_action->text(),etat);
}

Note *QRecording::get_note(QString id, QString title){
    ENUM::RecordingType t=static_cast<ENUM::RecordingType>(E_type->currentIndex());
    return new Recording(id,title,E_description->document()->toPlainText(),t,E_link->text());
}
