#ifndef ADDCOUPLE_H
#define ADDCOUPLE_H

#include <QDialog>
#include<QInclude.h>
namespace Ui {
class addCouple;
}

class addCouple : public QDialog
{
    Q_OBJECT
public:
    explicit addCouple(QWidget *parent = 0);
    ~addCouple();

private:
    Ui::addCouple *ui;
    QStandardItemModel* modelfrom;
    QStandardItemModel* modelto;
    QModelIndex i1;
    QModelIndex i2;

public slots:
    void updateModel_to(QModelIndex index);
    void on_toView_clicked(QModelIndex i);
    void on_save_clicked();
signals:
    void addNewCouple(QString, QString, QString, bool);
};

#endif // ADDCOUPLE_H
