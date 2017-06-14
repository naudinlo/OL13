/**
 * \file      Creation_Note.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Fenetre dialoque permettant l'edition d'une nouvelle note
 * \details    class :
 *                  - Creation_Note
 *                          Attribut:
 *                                  QNote note
 *                          Signaux :
 *                                  change_creer() signal interne à la fenetre.
 *                                  NewNote() envoie la note créer à l'interface //Plus utile.
 */


#ifndef Creation_Note_H
#define Creation_Note_H

#include "qnote.h"
class Creation_Note: public QDialog
{

    QNote* note;
    void edit_article();
    void edit_tache();
    void edit_enregistrement();

     Q_OBJECT
    QGroupBox* B_type;
    QGroupBox* B_defNote;
    QVBoxLayout* L_fen;
    QHBoxLayout* L_bouton;
    QGridLayout* L_type;
    QGridLayout* L_defClass;
    QGridLayout* L_comm;
    QLineEdit* E_title;
    QLineEdit* E_id;
    QLabel* title;
    QLabel* id;
    QLabel* type;
    QComboBox* typeBox;
    QPushButton* Creer;
    QPushButton* quitter;
    bool E_title_not_null;
    bool E_note_not_null;
    bool E_id_not_null;

public:
    Creation_Note(QWidget* parent);

signals:
    void change_Creer();
    void newNote(); //envoie la note créer à l'interface.
//signal emis par
 public slots:
    void Creer_Note(); //slot interessant

    void select_type(int type);
    /**
     * @fn fenclose
     */
    void fenclose(){
        delete this;
    }
    /**
     * @fn activer_E_title_not_null
     */
    void activer_E_title_not_null(){
        E_title_not_null=!E_title->text().isEmpty();
        emit change_Creer();
    }
    /**
     * @fn activer_E_note_not_null
     * @param status
     */
    void activer_E_note_not_null(bool status){
        E_note_not_null=status;
        emit change_Creer();
    }
    /**
     * @fn activer_E_id_not_null
     */
    void activer_E_id_not_null(){
        E_id_not_null=!E_id->text().isEmpty();
        emit change_Creer();
    }
    /**
     * @fn activer_Creer
     */
    void activer_Creer(){
        Creer->setEnabled(E_title_not_null && E_note_not_null);
        }


};


#endif // Creation_Note_H
