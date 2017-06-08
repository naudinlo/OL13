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
};

#endif // SUPP_NOTE_H
