#ifndef Creation_Note_H
#define Creation_Note_H

#include "qnote.h"
class Creation_Note: public QDialog
{
     Q_OBJECT

    QNote* note;

    QGroupBox* B_type;
    QGroupBox* B_defNote;
    QGroupBox* B_comm;
    QVBoxLayout* L_fen;
    QHBoxLayout* L_bouton;
    QGridLayout* L_type;
    QGridLayout* L_defClass;
    QGridLayout* L_comm;

    QLineEdit* E_title;
    QLineEdit* E_Auteur;
    QTextEdit* E_commentaire;

    QLabel* title;
    QLabel* type;

    QComboBox* typeBox;

    QLabel* auteur;
    QLabel* desc_class;


    QPushButton* Creer;
    QPushButton* quitter;

    bool E_title_not_null;
    bool E_note_not_null;
    void edit_article();
    void edit_tache();
    void edit_enregistrement();

public:
    Creation_Note(QWidget* parent);
signals:
    void change_Creer();
    void newNote(Note& n);

 public slots:
    void Creer_Note();
    void select_type(int type);
    void activer_E_title_not_null(){
        E_title_not_null=!E_title->text().isEmpty();
        emit change_Creer();
    }
    void activer_E_note_not_null(bool status){
        E_note_not_null=status;
        emit change_Creer();
    }

    void activer_Creer(){
        Creer->setEnabled(E_title_not_null && E_note_not_null);
        }
};

#endif // Creation_Note_H
