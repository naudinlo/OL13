/**
 * \file      addcouple.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Fenetre de création de nouveau couple
 *
 * \details    class :
 *                  addCouple
 */


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
    /**
     * \fn      void addNewCouple(QString, QString, QString, bool);
     * @brief   signal addNewCouple
     */
    void addNewCouple(QString, QString, QString, bool);
};

#endif // ADDCOUPLE_H
