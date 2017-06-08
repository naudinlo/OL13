#include "qrelations.h"

Qrelations::Qrelations(QString t, QString d):R(RelationManager::getInstance().getNewRelation(t,d)){

}



Edit_relation::Edit_relation(QStandardItemModel* m,int index,QString id, QWidget* parent): QDialog(parent),
    model(m),note(NotesManager::getInstance()->getNote(id)){
    /*** Window: Permettant de chosir le titre, la descp de la relation, et les notes faisant
                 parties des couples de la relation***/
        this->setWindowTitle("Ajouter Relation");
        L_fen=new QGridLayout(this);
        titre= new QLabel("Titre de la relation");
        E_titre = new QLineEdit;
        connect(E_titre,SIGNAL(textChanged(QString)),this,SLOT(enabledAppend()));
        L_description=new QHBoxLayout;
        description=new QGroupBox();
        description->setTitle("description :");
        description->setCheckable(false);
        description->setLayout(L_description);
        E_description= new QTextEdit;
        L_description->addWidget(E_description);
        connect(E_description,SIGNAL(textChanged()),this,SLOT(enabledAppend()));
        Label_from=new QLabel("Définer une Relation venant de :");
        ref_from=new QListView;
        ref_from->setAlternatingRowColors(true);
        ref_from->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ref_from->setModel(model);
        ref_from->setDisabled(false);
        ref_from->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ref_from->setRowHidden(index,true);
        Label_to=new QLabel("Définer une Relation vers :");
        ref_to=new QListView;
        ref_to->setAlternatingRowColors(true);
        ref_to->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ref_to->setModel(model);
        ref_to->setDisabled(false);
        //ref_to->horizontalHeader()->hide();
        ref_to->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ref_to->setRowHidden(index,true);
        append=new QPushButton("Ajouter");
        append->setEnabled(false);
        L_fen->addWidget(titre,0,0);
        L_fen->addWidget(E_titre,0,1);
        L_fen->addWidget(description,1,0,1,2);
        L_fen->addWidget(Label_from,2,0,1,2);
        L_fen->addWidget(ref_from,3,0,1,2);
        L_fen->addWidget(Label_to,4,0);
        L_fen->addWidget(ref_to,5,0,1,2);
        L_fen->addWidget(append,6,1);

    //***connect***//
        connect(append,SIGNAL(clicked(bool)),this,SLOT(clicSelection()));

}

void Edit_relation::clicSelection()
{   /* Création d'une relation, en donnant les paramètre: titre, descp
      */
    R=new Qrelations(E_titre->text(),E_description->document()->toPlainText());
    addNoteToR(); //se charge d'ajouter les couples dans la relation définie précedement
    this->close();
}

void Edit_relation::addNoteToR(){
    /***
     * Recupération des notes définisant les nouveaux couples
     * **/
    QItemSelectionModel *selection_from = ref_from->selectionModel();
    QModelIndexList listeSelections_from = selection_from->selectedIndexes();
    NotesManager* manager=NotesManager::getInstance();
    QItemSelectionModel* selection_to = ref_to->selectionModel();
    QModelIndexList listeSelections_to = selection_to->selectedIndexes();

    Edit_NotesCouple* C; //Pointeur vide reprentant la fenetre permettant un new couple de la relation
    //prend un argument les 2 notes du couple, et un bool pour symetric

    for(int i=0;i<listeSelections_from.size();i++){

        QString current_id=model->itemFromIndex(listeSelections_from[i])->whatsThis();
        if(selection_to->isSelected(listeSelections_from[i])){
            C= new Edit_NotesCouple(&(manager->getNote(current_id)),&note,this,true); //configuration :couple symétric
        }
        else{
            C= new Edit_NotesCouple(&(manager->getNote(current_id)),&note,this); //configuration :non symétric
        }
        connect(C,SIGNAL(newCouple(Note*,Note*,QString,bool)),this,SLOT(addCouple(Note*,Note*,QString,bool)));
        C->exec();
    }
    for (int i = 0 ; i < listeSelections_to.size() ; i++)
    {
        if(!(selection_from->isSelected(listeSelections_to[i]))){
            // ce couple n'a pas encore été traité
        QString current_id=model->itemFromIndex(listeSelections_to[i])->whatsThis();
        C= new Edit_NotesCouple(&note,&(manager->getNote(current_id)),this);
        connect(C,SIGNAL(newCouple(Note*,Note*,QString,bool)),this,SLOT(addCouple(Note*,Note*,QString,bool)));
        C->exec();
        }
    }
            QMessageBox::information(this,"relation",QString::fromStdString(R->displayRelation()));
}

Edit_NotesCouple::Edit_NotesCouple(Note *na, Note *nb, QWidget* parent, bool s):QDialog(parent),n1(na),n2(nb),symetric(s){
    /***
     * Window; permettant d'éditer un couple d'une relation: label
     * */
        L_fen=new QVBoxLayout(this);
        Label=new QLabel;
        if(symetric){
            Label->setText("souhaitez vous saisir un Label entre le couple :"+ n1->getId()+" <-> "+n2->getId() );
        }
        else{
                Label->setText("souhaitez vous saisir un Label entre le couple :"+ n1->getId()+" -> "+n2->getId() );
    }
        choix =new QGroupBox;
        L_yes=new QHBoxLayout;
        yes = new QRadioButton("Oui");
        E_Label= new QLineEdit;
        E_Label->setEnabled(false);
        L_yes->addWidget(yes);
        L_yes->addWidget(E_Label);
        no = new QRadioButton("Non");
        no->setChecked(true);
        cbox = new QVBoxLayout;
            cbox->addLayout(L_yes);
            cbox->addWidget(no);
       choix->setLayout(cbox);
       quit=new QPushButton("Fin");
       L_fen->addWidget(Label);
       L_fen->addWidget(choix);
       L_fen->addWidget(quit);

       /**Connect: **/
   connect(quit,SIGNAL(clicked(bool)),this,SLOT(fermer())); // voir le slot fermer
   connect(E_Label,SIGNAL(textChanged(QString)),this,SLOT(eneableE_label()));
   connect(yes,SIGNAL(clicked(bool)),this,SLOT(eneableE_label()));
   connect(no,SIGNAL(clicked(bool)),this,SLOT(eneableE_label()));
}
