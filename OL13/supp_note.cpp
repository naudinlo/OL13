/**
 * \file      supp_note.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     //Bref
 *
 * \details  //Détail
 *
 */


#include "supp_note.h"
/**
 * @fn supp_note::supp_note
 * @param m
 * @param parent
 * \brief constructeur
 */
supp_note::supp_note(QStandardItemModel* m, QWidget* parent):QDialog(parent),model(m)
{
    layout =new QVBoxLayout;
    vue=new QListView(this);
    vue->setAlternatingRowColors(true);
    vue->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vue->setModel(model);
    vue->setDisabled(false);
    vue->setSelectionMode(QAbstractItemView::ExtendedSelection);

    layout->addWidget(vue);
    setLayout(layout);
    supp=new QPushButton("Supprimer la ou les notes selectionnées");
    layout->addWidget(supp);
    connect(supp,SIGNAL(clicked(bool)),this,SLOT(supp_selection_note()));
}
/**
 * @fn supp_note::supp_selection_note
 * \brief supprimer les notes selectionné
 * \details Pour les details de la suppréssion se répertorié à la classe manager.
 *
 */
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
                manager->deleteNote(current_id);
                QMessageBox::information(this,current_id,"Note supprimée");
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
                //manager->deleteNote(current_id,i.row()); Dans la vue d'une seconde Versions de l'application
            }
            catch(NotesException e){
                QMessageBox::warning(this,'Impossibe de supprimer '+current_id,e.getinfo());
            }

        }

    }
    emit(close_note());
    this->close();

}
