/**
 * \file      notes.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définitions des fonctions déclarées dans le qnotes.h
 *
 * \details  Domaines des méthodes comprises dans ce fichier :
 *              - Constructeur
 *              - Destructeur
 *              - Affichage
 *              - Sauvegarde
 *              - Chargement
 *           Le détail est donné dans la suite du fichier.
 *
 */
#include "qnote.h"
/**
 * \fn QNote::QNote
 * \brief Constructueur de la clase QNote
 */
QNote::QNote(){
    titre=new QLabel("titre");
    E_titre=new QLineEdit;
    E_titre->setReadOnly(true);
    layout_titre = new QVBoxLayout;
    layout_titre->addStretch();
    layout_titre->addWidget(E_titre);
    layout_titre->addStretch();;

}
/**
 * \fn QNote::QNote
 * \brief Constructueur de la clase QArticle
 */
QArticle::QArticle(): QNote(){
    grid=new QGridLayout(this);
    text=new QLabel("Saisir le texte");
    E_text=new QTextEdit();
    grid->addWidget(E_text,0,1,0,5);
    grid->addWidget(text,0,0);
}
/**
 * \fn QNote::QNote
 * \brief Constructueur de la clase QTask
 */
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
    priority->setTitle("Priorité :");
    optional_priority=new QHBoxLayout;
    priority->setLayout(optional_priority);
    E_priority=new QSpinBox();
    optional_priority->addStretch();
    optional_priority->addWidget(E_priority);

    status=new QLabel("État");
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
/**
 * \fn QNote::QNote
 * \brief Constructueur de la clase QRecording
 */
QRecording::QRecording():QNote(){
    grid=new QGridLayout(this);
    description=new QLabel("Description:");
    E_description=new QTextEdit;
    type=new QLabel("Type d'enregistrement");
    E_link=new QLineEdit;
    E_link->setEnabled(false);
    read=new QPushButton("Lire l'enregistrement");
    stop=new QPushButton("Fermer");
    read->setEnabled(false);
    stop->setEnabled(true);
    link=new QPushButton("Sélectionner un enregistrement");
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
/**
 * \fn QRecording::read_record
 * \brief lance la lecture de l'enregestriment importé
 * \details la lecture dépends du type d'enregistrement
 * La classe QMediaPlayer demmande de faire des liasions avec les fichiers librairie de l'ordinateur.
 * Fonctionnel sous linux.
 *
 */
void QRecording::read_record(){
    read->setEnabled(false);
    stop->setEnabled(true);
    grid->addWidget(stop,5,1);
    player=new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(E_link->text()));
    player->setVolume(70);


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
/**
 * \fn QRecording::stop_record
 */
void QRecording::stop_record(){
    if(stop->isEnabled()==true){
        stop->setEnabled(false);
        if(E_type->currentText()!=1)
            videoWidget->close();
        player->stop();
        read->setEnabled(true);
    }
}

/**
 * \fn QRecording::OuvrirFichier
 * @return Qstring fichier
 * \brief Permet à l'utilisateur de choisir un enregistrement.
 */
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
    QString fichier = QFileDialog::getOpenFileName(this,"Sélectionner un enregistrement",QString(),Filtre);
    if(fichier != 0){
            E_link->setText(fichier);
            read->setEnabled(true);
            grid->addWidget(read,5,0);
    }
    return fichier;
}

/**
 * @fn QArticle::get_note
 * @param id
 * @param title
 * @return Note&
 * \brief Renvoi la note créer avec le constructeur d'article.
 */
Note& QArticle::get_note(QString id,QString title){

    return NotesManager::getInstance()->getNewArticle(id,title,E_text->document()->toPlainText());
}
/**
 * @fn QTask::get_note
 * @param id
 * @param title
 * @return Note&
 * \brief Renvoi la note créer avec le constructeur de Task
 */
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
/**
 * @fn QRecording::get_note
 * @param id
 * @param title
 * @return Note&
 * \brief Renvoi la note créer avec le constructeur de Recording.
 */
Note& QRecording::get_note(QString id, QString title){
    ENUM::RecordingType t=static_cast<ENUM::RecordingType>(E_type->currentIndex());
    return NotesManager::getInstance()->getNewRecording(id,title,E_description->document()->toPlainText(),t,E_link->text());

}


/**
 * \fn QArticle::check_creer
 * \brief Vérifier que les champs nécessaire à l'appelle des constructeurs on été saisi par
 * l'utilisateur.
 */
void QArticle::check_creer(){
}
/**
 * \fn QRecording::check_creer
 * \brief Vérifier que les champs nécessaire à l'appelle des constructeurs on été saisi par
 * l'utilisateur.
 */
void QRecording::check_creer(){
    if(!E_description->document()->isEmpty() && !E_link->text().isEmpty())
        emit checked_creer(true);
    else
        emit checked_creer(false);
}/**
 * \fn Task::check_creer
 * \brief Vérifier que les champs nécessaire à l'appelle des constructeurs on été saisi par
 * l'utilisateur.
 */
void QTask::check_creer(){

    if(!E_action->text().isEmpty())
    {
        emit checked_creer(true);

    }
    else emit checked_creer(false);

    }
/**
 * \fn QNote::load_note
 * @param n
 * \brief Methode Virtuel
 * charge les données d'une note dans l'interface graphique
 */
void QNote::load_note(Note &n){
    E_titre->setText(n.getTitle());
}
/**
 * \fn QArticle::load_note
 * @param n
 * \brief charge les données d'un Article dans l'interface graphique
 */
void QArticle::load_note(Note &N){
    QNote::load_note(N);
    Article& n= dynamic_cast<Article&>(N);
    E_text->setDocument(n.getText().clone());
    E_text->setReadOnly(true);
}
/**
 * \fn QRecording::load_note
 * @param n
 * \brief charge les données d'un Recording dans l'interface graphique
 */
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
/**
 * \fn QTask::load_note
 * @param n
 * \brief charge les données d'une TAsk dans l'interface graphique
 */
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
/**
 * \fn QNote::readOnly
 * @param status
 * \brief mode lecture seul de la note.
 */
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
/**
 * \fn QNote::saveNote
 * @param n
 * \brief sauvegarde les modfications apporté par l'utilisateur sur la note.
 * \details On supprime tous les réfèrences avant de ré-éditer tous les références.
 */
void QNote::saveNote(Note &n){
    n.deleteAllReference();
    n.setTitle(E_titre->text());
    n.setLastmodif_date(QDateTime::currentDateTime());
}
/**
 * @brief QArticle::saveNote
 * @param N
 *
 */
void QArticle::saveNote(Note &N){
    QNote::saveNote(N);
    Article& n= dynamic_cast<Article&>(N);
    n.setText(E_text->document()->toPlainText());
}
/**
 * @brief QTask::saveNote
 * @param N
 */
void QTask::saveNote(Note &N){
    QNote::saveNote(N);
    ENUM::StatusType s=static_cast<ENUM::StatusType>(E_status->currentIndex());
    Task& n= dynamic_cast<Task&>(N);
    n.setAction(E_action->text());
    n.setDueDate(E_duedate->dateTime());
    n.setPriority(E_priority->value());
    n.setStatus(s);
}
/**
 * @brief QRecording::saveNote
 * @param N
 */
void QRecording::saveNote(Note &N){
    QNote::saveNote(N);
    ENUM::RecordingType t=static_cast<ENUM::RecordingType>(E_type->currentIndex());
    Recording& n= dynamic_cast<Recording&>(N);
    n.setDescription(E_description->document()->toPlainText());
    n.setLink(E_link->text());
    n.setType(t);
}
