#ifndef QRELATIONS_H
#define QRELATIONS_H

#include <QInclude.h>
#include "relations.h"
#include "manager.h"
#include "notes.h"
class Qrelations
{
public:
    Qrelations(){}
};

class Edit_relation:public QDialog{

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
    Note& note;
    void addNoteToR(Relation R);
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

};



#endif // QRELATIONS_H
