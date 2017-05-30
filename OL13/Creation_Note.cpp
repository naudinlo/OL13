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
    QObject::connect(Creer,SIGNAL(clicked(bool)),this,SLOT(close()));
    B_defNote=new(QGroupBox)("Note:",this);
    B_defNote->setLayout(L_defClass);


    L_bouton->addWidget(quitter);
    L_bouton->addWidget(Creer);

    B_ref=new(QGroupBox)("Ajouter des relations",this);
    B_ref->setLayout(L_comm);
    B_ref->setCheckable(true);
    B_ref->setChecked(false);


    B_type=new(QGroupBox)("Article",this);

    note=new QArticle();
    connect(E_title,SIGNAL(textChanged(QString)),this,SLOT(activer_E_title_not_null()));
    connect(this,SIGNAL(change_Creer()),this,SLOT(activer_Creer()));
    L_type->addWidget(note,0,0);
    B_type->setLayout(L_type);


    L_fen->addWidget(B_defNote);
    L_fen->addWidget(B_type);
    L_fen->addWidget(B_ref);
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
    QString id(E_title->text()+"_00");
    try{
    Note& essai=note->get_note(id,E_title->text());
    QMessageBox::information(this,E_title->text(),QString::fromStdString(essai.toString()));
    if(B_ref->isChecked())
        emit(newRef());
    emit(newNote(essai));
    }
    catch(NotesException e)
    {
        QMessageBox::warning(this,"Echec lors de la création d'une note", e.getinfo());
    }
    this->close();
}

Edit_relation::Edit_relation(QStandardItemModel *m, QWidget* parent):model(m),QDialog(parent){
    this->setWindowTitle("Ajouter Référence");

    L_fen=new QGridLayout(this);

    Label_from=new QLabel("Définer des références venant de :");
    ref_from=new QTableView;
    ref_from->setAlternatingRowColors(true);
    ref_from->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ref_from->setModel(model);
    ref_from->setDisabled(false);
    ref_from->horizontalHeader()->hide();
    ref_from->setSelectionMode(QAbstractItemView::ExtendedSelection);


    Label_to=new QLabel("Définer des références vers :");
    ref_to=new QTableView;
    ref_to->setAlternatingRowColors(true);
    ref_to->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ref_to->setModel(model);
    ref_to->setDisabled(false);
    ref_to->horizontalHeader()->hide();
    ref_to->setSelectionMode(QAbstractItemView::ExtendedSelection);
    L_fen->addWidget(Label_from,0,0);
    L_fen->addWidget(ref_from,1,0);
    L_fen->addWidget(Label_to,2,0);
    L_fen->addWidget(ref_to,3,0);
}
