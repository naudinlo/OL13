#ifndef QUIRELATION_H
#define QUIRELATION_H

#include <QDialog>
#include "relations.h"
#include "QInclude.h"
#include "manager.h"
#include "addcouple.h"
#include "qrelations.h"
namespace Ui {
class QUiRelation;
}

class QUiRelation : public QDialog
{
    Q_OBJECT
    QStandardItemModel* model;
    Relation& R;
    NotesCouple* c;
public:
    explicit QUiRelation(Relation& r,QWidget *parent = 0);
    ~QUiRelation();

private:
    Ui::QUiRelation *ui;
    void create_model();
signals:
    void newCouple();
public slots:
    void setCouple(QString l){
        c->setLabel(l);
        create_model();
    }

    void on_show_clicked(){
        Edit_NotesCouple Editcouple(c->getCoupleNoteX(),c->getCoupleNoteY(),this);
        connect(&Editcouple,SIGNAL(setCouple(QString)),this,SLOT(setCouple(QString)));
        Editcouple.exec();
    }
    void on_ETitre_textChanged(QString t);
    void on_EDesciption_textChanged();
    void on_RelationView_doubleClicked(QModelIndex index);
    void on_remove_clicked(){
        try{
            R.removeCoupleRelation(c->getCoupleNoteX(),c->getCoupleNoteY());

            QMessageBox::warning(this,"Couple relation","supprimé");
        }
        catch(NotesException e){
            QMessageBox::warning(this,"Remove Couple relation",e.getinfo());
        }
        create_model();
    }
    void on_addCouple_clicked(){
        addCouple addC(this);
        connect(&addC,SIGNAL(addNewCouple(QString,QString,QString,bool)),this,SLOT(addNewCouple(QString,QString,QString,bool)));
        addC.exec();
    }
    void addNewCouple(QString id1,QString id2,QString l,bool s){
        try{
            NotesManager* m=NotesManager::getInstance();
            R.getNewCoupleRelation(&(m->getNote(id1)),&(m->getNote(id2)),l,s);
            emit(newCouple());
        }
        catch(NotesException e){
            QMessageBox::warning(this,"add New Couple",e.getinfo());
        }
        create_model();
        QMessageBox::information(this,"mis a jour","");
    }
};

#endif // QUIRELATION_H
