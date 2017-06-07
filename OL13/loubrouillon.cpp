

////DANS LE FICHIER H


//class DeleteNote:public QDialog{

//    Q_OBJECT
//    QGridLayout* L_fen;
//    QLabel* titre;
//    QGroupBox* description;
//    QHBoxLayout* L_description;
////    QLineEdit* E_titre;
////   QTextEdit* E_description;
//  //  QLabel* Label_from;
////    QLabel* Label_to;
//   QLabel* Label_notes;
//    QStandardItemModel* model;
//  //  QListView* ref_from;
//  //  QListView* ref_to;
//QListView* list_notes;
//    QPushButton* supprimer;
////  Note& note;
////    Relation* R;
////    void addNoteToR();
//void DeleteListNote();

//public:
// //   Edit_relation(QStandardItemModel* m, int index, QString id, QWidget *parent);
// DeleteNote(QStandardItemModel* m, int index, QString id, QWidget *parent);
//public slots:
//    void deleteNote();


//    //DANS LE FICHIER CPP


////Edit_relation::Edit_relation(QStandardItemModel* m, int index,QString id, QWidget* parent): QDialog(parent),
//DeleteNote::DeleteNote(QStandardItemModel* m, int index,QString id, QWidget* parent): QDialog(parent),
//    model(m), note(NotesManager::getInstance()->getNote(id)){
///*
//[…]

//Label_from=new QLabel("Définer une Relation venant de :");
//    ref_from=new QListView;
//    ref_from->setAlternatingRowColors(true);
//    ref_from->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ref_from->setModel(model);
//    ref_from->setDisabled(false);
//    //ref_from->horizontalHeader()->hide();
//    ref_from->setSelectionMode(QAbstractItemView::ExtendedSelection);
//    ref_from->setRowHidden(index,true);
//  */

//    Label_notes=new QLabel("Liste des notes existantes :");
//        list_notes=new QListView;
//        list_notes->setAlternatingRowColors(true);
//        list_notes->setEditTriggers(QAbstractItemView::NoEditTriggers);
//        list_notes->setModel(model);
//        list_notes->setDisabled(false);
//        //ref_from->horizontalHeader()->hide();
//        list_notes->setSelectionMode(QAbstractItemView::ExtendedSelection);
//        list_notes->setRowHidden(index,true);

///*append=new QPushButton("Ajouter");
//    append->setEnabled(false);
//    connect(append,SIGNAL(clicked(bool)),this,SLOT(clicSelection()));
//*/

//    deleteNote=new QPushButton("Supprimer");
//    deleteNote->setEnabled(false);
//    connect(supprimer,SIGNAL(clicked(bool)),this,SLOT(deleteNote()));

//}

///*
//void Edit_relation::clicSelection()
//{
//    R=new Relation (E_titre->text(),E_description->document()->toPlainText());
//    addNoteToR();
//    this->close();
//}
//*/


//void DeleteNote::deleteNote()
//{
////    R=new Relation (E_titre->text(),E_description->document()->toPlainText());
//   //TODO : MODIFIER addNoteToR();

//    QItemSelectionModel *selection_toDelete = list_notes->selectionModel();
//    QModelIndexList listNotes_toDelete = selection_toDelete->selectedIndexes();
//    NotesManager* manager=NotesManager::getInstance();

//    for(int i=0;i<listeSelections_from.size();i++){
//        QString current_id=model->itemFromIndex(listeSelections_from[i])->child(0,0)->whatsThis();
//        //COMMENT SUPPRIMER LES NOTES ?
//        //TODO : (&(manager->getNote(current_id)),&note,this);
//        }

////   QMessageBox::information(this,"relation",QString::fromStdString(R->displayRelation()));
//    QMessageBox::information(this,"Les notes ont bien été supprimées.");


//    this->close();

//}

///*
//void Edit_relation::addNoteToR(){
//    QItemSelectionModel *selection_from = ref_from->selectionModel();
//    QModelIndexList listeSelections_from = selection_from->selectedIndexes();
//    NotesManager* manager=NotesManager::getInstance();


////    Edit_NotesCouple* C;

//    for(int i=0;i<listeSelections_from.size();i++){
//        QString current_id=model->itemFromIndex(listeSelections_from[i])->child(0,0)->whatsThis();
///*        if(selection_to->isSelected(listeSelections_from[i])){
//            C= new Edit_NotesCouple(&(manager->getNote(current_id)),&note,this,true); //couple symÃ©tric
//        }
//        else{
//            C= new Edit_NotesCouple(&(manager->getNote(current_id)),&note,this); //non symÃ©tric
//        }
//*/

//    //COMMENT SUPPRIMER LES NOTES ?
//    (&(manager->getNote(current_id)),&note,this);
//        connect(C,SIGNAL(newCouple(Note*,Note*,QString,bool)),this,SLOT(addCouple(Note*,Note*,QString,bool)));
//        C->exec();
//    }

//    QMessageBox::information(this,"relation",QString::fromStdString(R->displayRelation()));

//}


//*/
