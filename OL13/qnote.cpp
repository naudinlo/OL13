#include "qnote.h"

QNote::QNote(){
    titre=new QLabel("titre");
    E_titre=new QLineEdit;
}

QArticle::QArticle(): QNote(){
    grid=new QGridLayout(this);
    text=new QLabel("Saisir Texte");
    E_text=new QTextEdit();
    grid->addWidget(E_text,0,1,0,2);
    grid->addWidget(text,0,0);
}

QTask::QTask():QNote(){

    action=new QLabel ("Action");
    E_action=new QLineEdit;
    connect(E_action,SIGNAL(textEdited(QString)),SLOT(check_creer()));


    duedate=new QGroupBox ();
    duedate->setCheckable(true);
    duedate->setTitle("Date de réalisation :");
    optional_duedate=new QHBoxLayout();
    E_duedate=new QDateTimeEdit();
    E_duedate->setDate(QDate::currentDate());
    E_duedate->setTime(QTime::currentTime());
    E_duedate->setCalendarPopup(true);
    optional_duedate->addStretch();
    optional_duedate->addWidget(E_duedate);
    duedate->setLayout(optional_duedate);
    priority=new QGroupBox ();
    priority->setCheckable(true);
    priority->setTitle("priorité :");
    optional_priority=new QHBoxLayout;
    priority->setLayout(optional_priority);
    E_priority=new QSpinBox();
    optional_priority->addStretch();
    optional_priority->addWidget(E_priority);

    status=new QLabel("Etat");
    E_status=new QComboBox;
    E_status->addItem("En cours");
    E_status->addItem("En attente");
    E_status->addItem("Complétée");

    grid=new QGridLayout(this);
    grid->addWidget(action,0,0);
    grid->addWidget(E_action,0,1);
    grid->addWidget(status,1,0);
    grid->addWidget(E_status,1,1);
    grid->addWidget(duedate,2,0,2,2);
    grid->addWidget(priority,4,0,4,2);

    fen=new QVBoxLayout (this);
    fen->addLayout(grid);

}

QRecording::QRecording():QNote(){
    grid=new QGridLayout(this);
    description=new QLabel("Descrition:");
    E_description=new QTextEdit;
    type=new QLabel("Type d'enregistrement");
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


Note& QArticle::get_note(QString id,QString title){

    return NotesManager::getInstance()->getNewArticle(id,title,E_text->document()->toPlainText());
}

Note& QTask::get_note(QString id, QString title){
    ENUM::StatusType etat=static_cast<ENUM::StatusType>(E_status->currentIndex());
    if(priority->isChecked() && duedate->isChecked())
    {
        return NotesManager::getInstance()->getNewTask(id,title,E_action->text(),etat,E_priority->value(),E_duedate->dateTime());
    }
    else if(priority->isChecked())
        return NotesManager::getInstance()->getNewTask(id,title,E_action->text(),etat,E_priority->value());
    else if(duedate->isChecked())
        return NotesManager::getInstance()->getNewTask(id,title,E_action->text(),etat,E_duedate->dateTime());
    return NotesManager::getInstance()->getNewTask(id,title,E_action->text(),etat);
}

Note& QRecording::get_note(QString id, QString title){
    ENUM::RecordingType t=static_cast<ENUM::RecordingType>(E_type->currentIndex());
    return NotesManager::getInstance()->getNewRecording(id,title,E_description->document()->toPlainText(),t,E_link->text());
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


void QArticle::load_note(Note &N){
    Article& n= dynamic_cast<Article&>(N);
    E_text->setDocument(n.getText().clone());
    E_text->setReadOnly(true);
}

void QRecording::load_note(Note &N){
    Recording& n= dynamic_cast<Recording&>(N);

}

void QTask::load_note(Note& N){
    Task& n= dynamic_cast<Task&>(N);
    E_action->setText(n.getAction());
    E_action->setReadOnly(true);
    delete E_duedate;
    E_duedate=new QDateTimeEdit (n.getDueDate());
    E_duedate->setReadOnly(true);
    optional_duedate->addWidget(E_duedate);
    E_priority->setValue(n.getPriority());
    E_priority->setReadOnly(true);
}

void QNote::readOnly(bool status){
    E_titre->setReadOnly(status);
}

void QArticle::readOnly(bool status){
    this->QNote::readOnly(status);
    E_text->setReadOnly(status);
}

void QRecording::readOnly(bool status){
    this->QNote::readOnly(status);
}
void QTask::readOnly(bool status){
    this->QNote::readOnly(status);
    E_action->setReadOnly(status);
    E_duedate->setReadOnly(status);
    E_priority->setReadOnly(status);


}
