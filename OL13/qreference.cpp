/**
* \file      qreference.cpp
* \author    Garnier Maxime, Naudin Louise, Pépin Hugues
* \version   1.0
* \date      14 Juin 2017
* \brief     Fenetre permettant la visualisation des relations existantes
*/
#include "qreference.h"
#include "ui_qreference.h"
/**
 * @fn Qreference::Qreference
 * @param n
 * @param parent
 * \fn constructeur de la widget
 */
Qreference::Qreference(Note &n, QWidget *parent) :
    QWidget(parent),note(n),
    ui(new Ui::Qreference)
{
    ui->setupUi(this);
    model_ref = new QStandardItemModel;
    update_model();
    ui->refView->setModel(model_ref);
}
/**
 * \fn Qreference::~Qreference
 */
Qreference::~Qreference()
{
    delete ui;
}
/**
 * @fn Qreference::update_model
 * \brief Met à jour le tableau de note référée
 */
void Qreference::update_model(){
    model_ref->clear();
    QList<QStandardItem* >item;
    Note& n=NotesManager::getInstance()->getNote(note.getId());
    for(unsigned int i=0;i<n.references.size();i++){
        item.append(new QStandardItem(n.references.at(i)));
    }
    model_ref->appendRow(item);


}
