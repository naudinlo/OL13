#include "qrelations.h"


Edit_relation::Edit_relation(QStandardItemModel* m,int index,QString id, QWidget* parent):
    model(m),note(NotesManager::getInstance()->getNote(id)),QDialog(parent){
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
    //ref_from->horizontalHeader()->hide();
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
    connect(append,SIGNAL(clicked(bool)),this,SLOT(clicSelection()));

    L_fen->addWidget(titre,0,0);
    L_fen->addWidget(E_titre,0,1);
    L_fen->addWidget(description,1,0,1,2);
    L_fen->addWidget(Label_from,2,0,1,2);
    L_fen->addWidget(ref_from,3,0,1,2);
    L_fen->addWidget(Label_to,4,0);
    L_fen->addWidget(ref_to,5,0,1,2);
    L_fen->addWidget(append,6,1);

}

void Edit_relation::clicSelection()
{
    Relation R(E_titre->text(),E_description->document()->toPlainText());
    addNoteToR(R);
    this->close();
}
void Edit_relation::addNoteToR(Relation R){
    QItemSelectionModel *selection = ref_from->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    NotesManager* manager=NotesManager::getInstance();
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QString current_id=model->itemFromIndex(listeSelections[i])->child(0,0)->whatsThis();
        try{
        R.getNewCoupleRelation(&(manager->getNote(current_id)),&note);
        }
        catch(NotesException e){
            QMessageBox::warning(this,"Error relation from",e.getinfo());
        }
      }

    QItemSelectionModel* selection2 = ref_to->selectionModel();
    listeSelections = selection2->selectedIndexes();
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QString current_id=model->itemFromIndex(listeSelections[i])->child(0,0)->whatsThis();
        try{
        R.getNewCoupleRelation(&note,&(manager->getNote(current_id)));
        }
        catch(NotesException e){
            QMessageBox::warning(this,"Error relation to",e.getinfo());
        }
      }
    QMessageBox::information(this,"relation",QString::fromStdString(R.displayRelation()));

}
