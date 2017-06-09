#include "qnote.h"

QNote::QNote(){
    titre=new QLabel("titre");
    E_titre=new QLineEdit;
    E_titre->setReadOnly(true);
    layout_titre = new QVBoxLayout;
    layout_titre->addStretch();
    layout_titre->addWidget(E_titre);
    layout_titre->addStretch();;

}

QArticle::QArticle(): QNote(){
    grid=new QGridLayout(this);
    text=new QLabel("Saisir Texte");
    E_text=new QTextEdit();
    grid->addWidget(E_text,0,1,0,5);
    grid->addWidget(text,0,0);
}

QTask::QTask():QNote(){

    action=new QLabel ("Action");
    E_action=new QLineEdit;
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

    connect(E_action,SIGNAL(textEdited(QString)),SLOT(check_creer()));

}

QRecording::QRecording():QNote(){
    grid=new QGridLayout(this);
    description=new QLabel("Descrition:");
    E_description=new QTextEdit;
    type=new QLabel("Type d'enregistrement");
    E_link=new QLineEdit;
    E_link->setEnabled(false);
    read=new QPushButton("Lire Enregistrement");
    stop=new QPushButton("Fermer");
    read->setEnabled(false);
    stop->setEnabled(true);
    link=new QPushButton("Selectionner enregistrement");
    E_type=new QComboBox;
    E_type->addItem("Image");
    E_type->addItem("Audio");
    E_type->addItem("Video");
    grid->addWidget(description,0,0);
    grid->addWidget(E_description,1,0,1,2);
    grid->addWidget(type,2,0);
    grid->addWidget(E_type,2,1);
    grid->addWidget(link,3,0);
    grid->addWidget(E_link,3,1);


    connect(read,SIGNAL(clicked(bool)),this,SLOT(read_record()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(stop_record()));
    connect(link,SIGNAL(clicked(bool)),this,SLOT(OuvrirFichier()));
    connect(E_link,SIGNAL(textChanged(QString)),this,SLOT(check_creer()));
    connect(E_description,SIGNAL(textChanged()),this,SLOT(check_creer()));
    connect(this,SIGNAL(destroyed(QObject*)),this,SLOT(read_record()));
}

void QRecording::read_record(){
    read->setEnabled(false);
    stop->setEnabled(true);
    grid->addWidget(stop,5,1);
    player=new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(E_link->text()));
    player->setVolume(50);


    if(E_type->currentIndex()==1){
        player->play();

    }
    else{
        videoWidget = new QVideoWidget;
        grid->addWidget(videoWidget,10,0,15,2);
        player->setVideoOutput(videoWidget);
        videoWidget->show();
        if(E_type->currentIndex()==2){
            player->play();
        }

    }
}

void QRecording::stop_record(){
    if(stop->isEnabled()==true){
        stop->setEnabled(false);
        if(E_type->currentText()!=1)
            videoWidget->close();
        player->stop();
        read->setEnabled(true);
    }
}


QString QRecording::OuvrirFichier(){
    QString Filtre;
    switch(E_type->currentIndex()){
    case 0:
        Filtre="Images (*.png *.gif *.jpg *.jpeg *.JPG)";
        break;
    case 1:
        Filtre="Audio (*.mp3 *.waw)";
       break;
    case 2:
        Filtre="Video (*.mp4 *.avi)";
        break;
    }


    QString fichier = QFileDialog::getOpenFileName(this,"Selectionner un enregistrement",QString(),Filtre);
    if(fichier != 0){
            E_link->setText(fichier);
            read->setEnabled(true);
            grid->addWidget(read,5,0);
    }
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

void QNote::load_note(Note &n){
    E_titre->setText(n.getTitle());
}

void QArticle::load_note(Note &N){
    QNote::load_note(N);
    Article& n= dynamic_cast<Article&>(N);
    E_text->setDocument(n.getText().clone());
    E_text->setReadOnly(true);
}

void QRecording::load_note(Note &N){
    QNote::load_note(N);
    Recording& n= dynamic_cast<Recording&>(N);
    E_link->setText(n.getLink());
    E_type->setCurrentIndex(n.getType());
    E_description->setDocument(n.getDescription().clone());
    read->setEnabled(true);
    grid->addWidget(read,5,0);
    readOnly(true);

}

void QTask::load_note(Note& N){
    QNote::load_note(N);
    Task& n= dynamic_cast<Task&>(N);
    E_action->setText(n.getAction());
    E_status->setCurrentIndex(n.getStatus());
    delete E_duedate;
    E_duedate=new QDateTimeEdit (n.getDueDate());
    E_duedate->setCalendarPopup(true);
    if(n.getDueDate()==QDateTime()){
        duedate->setChecked(false);
        E_duedate->setDateTime(QDateTime::currentDateTime());
    }
    optional_duedate->addWidget(E_duedate);
    if(n.getPriority()==-1)
        priority->setChecked(false);
    E_priority->setValue(n.getPriority());
    readOnly(true);
}

void QNote::readOnly(bool status){
    E_titre->setReadOnly(status);
}

void QArticle::readOnly(bool status){
    QNote::readOnly(status);
    E_text->setReadOnly(status);
}

void QRecording::readOnly(bool status){
    QNote::readOnly(status);
    E_description->setReadOnly(status);
    E_type->setEnabled(!status);
    link->setEnabled(!status);
}
void QTask::readOnly(bool status){
    QNote::readOnly(status);
    E_action->setReadOnly(status);
    E_status->setDisabled(status);
    duedate->setEnabled(!status);
    E_duedate->setReadOnly(status);
    priority->setEnabled(!status);
    E_priority->setReadOnly(status);
    E_action->setReadOnly(status);
}

void QNote::saveNote(Note &n){
    n.setTitle(E_titre->text());
    n.setLastmodif_date(QDateTime::currentDateTime());
}
void QArticle::saveNote(Note &N){
    QNote::saveNote(N);
    Article& n= dynamic_cast<Article&>(N);
    n.setText(E_text->document()->toPlainText());
}
void QTask::saveNote(Note &N){
    QNote::saveNote(N);
    ENUM::StatusType s=static_cast<ENUM::StatusType>(E_status->currentIndex());
    Task& n= dynamic_cast<Task&>(N);
    n.setAction(E_action->text());
    n.setDueDate(E_duedate->dateTime());
    n.setPriority(E_priority->value());
    n.setStatus(s);
}
void QRecording::saveNote(Note &N){
    QNote::saveNote(N);
    ENUM::RecordingType t=static_cast<ENUM::RecordingType>(E_type->currentIndex());
    Recording& n= dynamic_cast<Recording&>(N);
    n.setDescription(E_description->document()->toPlainText());
    n.setLink(E_link->text());
    n.setType(t);
}

