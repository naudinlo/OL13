#include "dockarchived.h"
#include "ui_dockarchived.h"

Dock::Dock(QWidget *parent) :
    QDockWidget(parent),
    currentNote(QString::Null()),
    ui(new Ui::DockArchived)
{
    ArchNote=new QStandardItemModel;
    ui->setupUi(this);
    ui->ArchView->setModel(ArchNote);

}

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


DockRemove::DockRemove(QWidget* parent):Dock(parent){
    ui->remove->setText("Archiver");
    this->setWindowTitle("Notes Supprimées");
}

