/**
 * \file      supp_note.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     //Bref
 *
 * \details  //Détail
 *
 */


#ifndef SUPP_NOTE_H
#define SUPP_NOTE_H
#include "QInclude.h"
#include "manager.h"

class supp_note: public QDialog
{
    Q_OBJECT
    QVBoxLayout* layout;
    QTreeView* vue;
    QStandardItemModel* model;
    QPushButton* supp;
public:
    supp_note(QStandardItemModel* m, QWidget *parent);
public slots:
    void supp_selection_note();
signals:
    void close_note();
};

#endif // SUPP_NOTE_H
