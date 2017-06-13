#include "quirelation.h"
#include "ui_quirelation.h"

QUiRelation::QUiRelation(Relation &r, QWidget *parent) :QDialog(parent),R(r),
    ui(new Ui::QUiRelation)
{
    ui->setupUi(this);
    ui->ETitre->setText(r.getTitle());
    ui->EDesciption->document()->setPlainText(r.getDescription());
    model = new QStandardItemModel;
    create_model();

}

QUiRelation::~QUiRelation()
{
    delete ui;
}

void QUiRelation::create_model(){
    model->clear();
    QList<QString> presentNote;
    for(Relation::Iterator it=R.getIterator();!it.isDone();it.next()){
        if(! presentNote.contains(it.current().getCoupleNoteX()->getId())){
                //on n'affiche qu'une fois les notes symétriques
            QList< QStandardItem* > item;
                    item.append(new QStandardItem(it.current().getCoupleNoteX()->getId()));
                    if(it.current().getSymetric()){
                        item.append(new QStandardItem("<->"));
                        presentNote.push_front(it.current().getCoupleNoteY()->getId());

                    }
                    else{
                        item.append(new QStandardItem("->"));
                    }
                    item.append(new QStandardItem(it.current().getCoupleNoteY()->getId()));
                    item.append(new QStandardItem(it.current().getLabel()));

               model->appendRow(item);

        }
    }
    ui->RelationView->setModel(model);
}

void QUiRelation::on_RelationView_doubleClicked(QModelIndex index){

    NotesManager* m=NotesManager::getInstance();
        try{
           Note* n1 =&(m->getNote(model->item(index.row(),0)->text()));
           Note* n2= &(m->getNote(model->item(index.row(),2)->text()));
           c =R.getCoupleRelation(n1,n2);
            ui->remove->setEnabled(true);
            ui->show->setEnabled(true);
        }
        catch(NotesException e){
           QMessageBox::warning(this,"Note couple",e.getinfo());
        }

}
void QUiRelation::on_EDesciption_textChanged(){
    R.setDescription(ui->EDesciption->document()->toPlainText());
}
void QUiRelation::on_ETitre_textChanged(QString t){
    R.setTitle(t);
}
