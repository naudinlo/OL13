#ifndef QRELATIONS_H
#define QRELATIONS_H

#include <QInclude.h>
#include "relations.h"
#include "manager.h"
#include "notes.h"

class QNotesCouple: public QWidget {
private:
    Note* notex;
    Note* notey;
    QLineEdit* label;
    bool symetric;
public:
    QNotesCouple(Note* x, Note* y, bool s):notex(x),notey(y), symetric(s){
        label=new QLineEdit;
    }
    //void add_Label(QString id1, QString id2);

};

class QDockRelation:public QWidget{
    QGridLayout* L_fen;
    QLabel* Label_from;
    QLabel* Label_to;
    QStandardItemModel* model_from;
    QStandardItemModel* model_to;
    QListView* rel_from;
    QListView* rel_to;
public:
    QDockRelation(const QString &id);
};


class Qrelations
{
    Relation& R; //Relation Courante
public:
    Qrelations(QString t, QString d);
    void getNewCoupleRelation(Note* n1,Note* n2,QString l=0,bool s=false)
    {
        R.getNewCoupleRelation(n1,n2,l,s);
    }
    string displayRelation(){
        return R.displayRelation();
    }
};

class Edit_NotesCouple: public QDialog{

    // a voir :
    Note* n1;
    Note* n2;
    bool symetric;

    Q_OBJECT
    QVBoxLayout* L_fen;
    QLabel* Label;
    QGroupBox* choix;
    QHBoxLayout* L_yes;
    QRadioButton *yes ;
    QLineEdit* E_Label;
    QRadioButton *no ;
    QVBoxLayout *cbox;
    QPushButton* quit;

public:
    Edit_NotesCouple(Note* n1, Note* n2, QWidget* parent=nullptr,bool s=false);
signals:
    void newCouple(Note*, Note*,QString,bool); //message récuperer par Edit_relation
    //representant la demande d'ajout d'un nouveau couple à une relation
    //signal emis par fermer()
public slots:
    void fermer(){
        //envoi un signal pour créer un nouveau couple selon la config choisie
        if(yes->isChecked()){
            emit newCouple(n1,n2,E_Label->text(),symetric);
        }
        else
        {
            emit newCouple(n1,n2,"",symetric);
        }
        this->close();
    }
    void eneableE_label(){
        if(yes->isChecked()){
            E_Label->setEnabled(true);
            if(E_Label->text().isEmpty())
                quit->setEnabled(false);
            else{
                quit->setEnabled(true);
            }
        }
        else{
            E_Label->setEnabled(false);
            quit->setEnabled(true);
        }
    }
};

class Edit_relation:public QDialog{
    Note& note; //note courante
    Qrelations* R; //Relation en cours d'édition

    Q_OBJECT
    QGridLayout* L_fen;
    QLabel* titre;
    QGroupBox* description;
    QHBoxLayout* L_description;
    QLineEdit* E_titre;
    QTextEdit* E_description;
    QLabel* Label_from;
    QLabel* Label_to;
    QStandardItemModel* model;
    QListView* ref_from;
    QListView* ref_to;
    QPushButton* append;
    void addNoteToR();

public:
    Edit_relation(QStandardItemModel* m, int index, QString id, QWidget *parent);
public slots:
    void clicSelection();
    void enabledAppend(){
        if(!(E_titre->text().isEmpty() || E_description->document()->toPlainText().isEmpty()))
            append->setEnabled(true);
        else
            append->setEnabled(false);
    }
    void addCouple(Note* n1, Note* n2, QString label,bool s){
     try{
            if(label.isEmpty())
                R->getNewCoupleRelation(n1,n2,0,s);
            else{
                R->getNewCoupleRelation(n1,n2,label,s);
           }
        }
     catch(NotesException e){
                QMessageBox::warning(this,"Error Couple",e.getinfo());
    }
 }
};



#endif // QRELATIONS_H
