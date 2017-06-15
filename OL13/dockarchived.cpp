/**
 * \file      dockarchived.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Fenetre dialoque permettant l'edition d'une nouvelle note
 * \details    class :
 *                  - Dock:classe abstraite
 *
 *                  - DockRemove
 *                  - DockArchived
 *
 *                          Attribut:
 *                                  QNote note
 *                          Signaux :
 *                                  change_creer() signal interne à la fenetre.
 *                                  NewNote() envoie la note créer à l'interface //Plus utile.
 */
#include "dockarchived.h"
#include "ui_dockarchived.h"

/**
 * @fn Dock::Dock
 * @param parent
 * @brief Constructeur du Dock
 */
Dock::Dock(QWidget *parent) :
    QDockWidget(parent),
    currentNote(QString::Null()),
    ui(new Ui::DockArchived)
{
    ArchNote=new QStandardItemModel;
    ui->setupUi(this);
    ui->ArchView->setModel(ArchNote);

}


/**
 * @fn Dock::~Dock
 * @brief Destructeur du Dock
 */
Dock::~Dock()
{
    delete ui;
}


void Dock::on_aff_clicked(){
    emit(selection(currentNote, 0));
}

void Dock::on_ArchView_clicked(QModelIndex i){
    currentNote=ArchNote->item(i.row())->text();
    ui->remove->setEnabled(true);
    ui->aff->setEnabled(true);
}

/**
 * @fn DockArchived::update_archNoteModel
 * @brief Mise à jour du Dock des archives
 */
void DockArchived::update_archNoteModel(){
    ArchNote->clear();
    NotesManager* m =NotesManager::getInstance();
    for(QList<Note*>::iterator  it= m->getListArchive().begin();it != m->getListArchive().end();it++){
        QList<QStandardItem*> item;
        Note* n=*it;
        item.append(new QStandardItem(n->getId()));
        item.append(new QStandardItem(n->getType()));
        ArchNote->appendRow(item);
    }
}

/**
 * @fn DockRemove::update_archNoteModel
 * @brief Mise à jour du Dock des éléments supprimés
 */
void DockRemove::update_archNoteModel(){
    ArchNote->clear();
    NotesManager* m =NotesManager::getInstance();
    for(QList<Note*>::iterator it= m->getListDeleted().begin();it != m->getListDeleted().end();it++){
        QList<QStandardItem*> item;
        Note* n=*it;
        item.append(new QStandardItem(n->getId()));
        item.append(new QStandardItem(n->getType()));
        ArchNote->appendRow(item);
    }
}

/**
 * @fn DockRemove::DockRemove
 * @brief Constructeur du Dock des éléments supprimés
 * @param parent
 */
DockRemove::DockRemove(QWidget* parent):Dock(parent){
    ui->remove->setText("Archiver");
    this->setWindowTitle("Notes Supprimées");
}

