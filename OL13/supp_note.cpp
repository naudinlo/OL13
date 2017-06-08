#include "supp_note.h"

supp_note::supp_note(QStandardItemModel* m, QWidget* parent):QDialog(parent),model(m)
{
    layout =new QVBoxLayout;
    vue=new QTreeView(this);
    vue->setAlternatingRowColors(true);
    vue->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vue->setModel(model);
    vue->header()->hide();
    vue->setDisabled(false);
    vue->setSelectionMode(QAbstractItemView::ExtendedSelection);

    layout->addWidget(vue);
    setLayout(layout);
    supp=new QPushButton("supprimer les notes selectionnées");
    layout->addWidget(supp);
    connect(supp,SIGNAL(clicked(bool)),this,SLOT(supp_selection_note()));
}

void supp_note::supp_selection_note(){
    QItemSelectionModel *selection = vue->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();
    NotesManager* manager=NotesManager::getInstance();
    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QString current_id;
        if(!listeSelections[i].parent().isValid())
        {

            current_id=model->item(listeSelections[i].row(),0)->whatsThis();
            try
            {
                //manager->deleteNote(current_id);
            }
            catch(NotesException e){
                QMessageBox::warning(this,'Impossibe de supprimer '+current_id,e.getinfo());
            }
        }
        else
        {
            current_id=model->item(listeSelections[i].parent().row(),0)->whatsThis();

            try
            {
                //manager->deleteNote(current_id,i.row());
            }
            catch(NotesException e){
                QMessageBox::warning(this,'Impossibe de supprimer '+current_id,e.getinfo());
            }

        }

    }
    this->close();

}
