/**
* \file      qreference.h
* \author    Garnier Maxime, Naudin Louise, Pépin Hugues
* \version   1.0
* \date      14 Juin 2017
* \brief     Fenetre permettant la visualisation des relations existantes
*
* \details         attributs :
*                                   Note& note;
*/
#ifndef QREFERENCE_H
#define QREFERENCE_H

#include "manager.h"
#include <QWidget>
#include "QInclude.h"
namespace Ui {
class Qreference;
}

class Qreference : public QWidget
{
    Q_OBJECT

public:
    explicit Qreference(Note& n,QWidget *parent = 0);
    ~Qreference();
    QStandardItemModel* model_ref;

private:
    Ui::Qreference *ui;
    Note& note;
public slots:
    void update_model();
};

#endif // QREFERENCE_H
