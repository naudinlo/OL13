#ifndef QUIRELATION_H
#define QUIRELATION_H

#include <QDialog>
#include "relations.h"
#include "QInclude.h"
#include "manager.h"
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
public slots:
    void on_show_clicked(){
        Edit_NotesCouple Editcouple(c->getCoupleNoteX(),c->getCoupleNoteY(),this,c->getSymetric());
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
    }
    void on_RelationView_objectNameChanged(QString t);
};

#endif // QUIRELATION_H
