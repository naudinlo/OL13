/**
* \file      qrelations.h
* \author    Garnier Maxime, Naudin Louise, Pépin Hugues
* \version   1.0
* \date      14 Juin 2017
* \brief     Implémentation des relations de manière graphique
*
* \details         class :
*                   -QDockRelation
*                       Permet l'affichage de la structure arborescente des relations
*                   -Edit_NotesCouples
*                       Permet l'edition de nouveaux couples
*                   -Edit_relation
*                       Permet l'edition d'une nouvelle relation
*/

#ifndef QRELATIONS_H
#define QRELATIONS_H

#include <QInclude.h>
#include "relations.h"
#include "manager.h"
#include "notes.h"


class QDockRelation:public QWidget{
    Q_OBJECT
    QGridLayout* L_fen;
    QLabel* Label_from;
    QLabel* Label_to;
    QStandardItemModel* model_from;
    QStandardItemModel* model_to;
    QTableView* rel_from;
    QTableView* rel_to;
    QString id;
public:
    QDockRelation(const QString &id);
public slots:
    void emit_From_selection(QModelIndex i);
    void emit_to_selection(QModelIndex i);
    void updateModels();
signals:
    void selectionNote(QString, int);
    void selectionRelation(QString titre);
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
    void setCouple(QString); //message récuper par l'affichage d'une relation

public slots:
    /**
     * @fn fermer
     * \brief ferme le fenetre et envoie un signal pour creer le nouveau couple
     */
    void fermer(){
        //envoi un signal pour créer un nouveau couple selon la config choisie
        if(yes->isChecked()){
            emit newCouple(n1,n2,E_Label->text(),symetric);

            emit setCouple(E_Label->text());
        }
        else
        {
            emit newCouple(n1,n2,"",symetric);
        }
        this->close();
    }/**
     * @nf eneableE_label
     *
     */
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
    Relation* R; //Relation en cours d'édition

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
    Edit_relation(QStandardItemModel* m, QString id, QWidget *parent);
signals:
    void newRelation();
public slots:
    void clicSelection();
    void enabledAppend(){
        if(!(E_titre->text().isEmpty() || E_description->document()->toPlainText().isEmpty()))
            append->setEnabled(true);
        else
            append->setEnabled(false);
    }
    /**
     * @nf addCouple
     * @param n1
     * @param n2
     * @param label
     * @param s
     * \brief creer le nouveau couple avec les paramètres choisis
     * \details les paramètre sont recu par signal depuis edit_couple.
     */
    void addCouple(Note* n1, Note* n2, QString label,bool s){
     try{
            if(label.isEmpty())
                R->getNewCoupleRelation(n1,n2,0,s);
            else{
                R->getNewCoupleRelation(n1,n2,label,s);
           }
            emit(newRelation());
        }
     catch(NotesException e){
                QMessageBox::warning(this,"Error Couple",e.getinfo());
    }
 }
};



#endif // QRELATIONS_H
