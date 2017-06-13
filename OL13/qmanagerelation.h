#ifndef QMANAGERELATION_H
#define QMANAGERELATION_H

#include <QDialog>
#include <QInclude.h>
#include <manager.h>
#include "quirelation.h"
namespace Ui {
class QManageRelation;
}

class QManageRelation : public QDialog
{
    Q_OBJECT
public:
    explicit QManageRelation(QWidget *parent = 0);
    ~QManageRelation();
    QUiRelation* getSelectedR(){
        return selectedR;
    }

private:
    Ui::QManageRelation *ui;
    QUiRelation* selectedR;
    QStandardItemModel* model;
    QString currentR;
    void UpdateModel();
public slots:
    void on_show_clicked(){
        try{
            selectedR =new QUiRelation (RelationManager::getInstance().getRelation( currentR),this);
            selectedR->exec();
            UpdateModel();
        }
        catch(NotesException e){
            QMessageBox::warning(this,"Show Relation",e.getinfo());
        }
    }
    void on_RelationView_doubleClicked(QModelIndex index);
    void on_remove_clicked(){
        try{
            RelationManager::getInstance().deleteRelation(currentR);
            QMessageBox::information(this,"Suppression Relation", "La relation est supprimé");
            UpdateModel();

        }
        catch(NotesException e){
            QMessageBox::warning(this,"Suppression Relation", e.getinfo());
        }
    }

};

#endif // QMANAGERELATION_H
