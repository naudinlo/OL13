#ifndef Creation_Note_H
#define Creation_Note_H

//#include "include.h"
#include "QInclude.h"
#include "notes.h"
class QNote;

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
class QNote:public QWidget{
    Q_OBJECT
protected:
    QGridLayout* grid;
public:
    virtual Note* get_note(QString id,QString title)=0;
    QNote():QWidget(){}
public slots:
    virtual void check_creer()=0;
signals:
   void checked_creer(bool);
};

class QArticle: public QNote{
    Q_OBJECT
    QLabel* text;
    QTextEdit* E_text;
    QGridLayout* grid;
    Note* get_note(QString id, QString title);
public:
    QArticle();
public slots:
    void check_creer();

signals:
    void checked_creer(bool);
};

class QTask: public QNote{
    Q_OBJECT
    QGroupBox* optional;
    QGridLayout* optional_box;
    QVBoxLayout* fen;
    QLabel* action;
    QLineEdit* E_action;
    QLabel* priority;
    QSpinBox* E_priority;

    QLabel* duedate;
    QDateEdit* E_duedate;
    QLabel* status;
    QComboBox* E_status;
    QGridLayout* grid;
    Note* get_note(QString id, QString title);
public:
    QTask();
signals:
    void checked_creer(bool);
public slots:
    void check_creer();
};

class QRecording: public QNote{
    Q_OBJECT
    QLabel* description;
    QTextEdit* E_description;
    QLabel* type;
    QComboBox* E_type;
    QLineEdit* E_link;
    QPushButton* link;
    QGridLayout* grid;
    Note* get_note(QString id, QString title);
public:
    QRecording();
public slots:
    QString OuvrirFichier();
    void check_creer();
signals:
    void checked_creer(bool);
};

#endif // Creation_Note_H
