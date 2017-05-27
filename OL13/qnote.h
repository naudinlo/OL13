#ifndef QNote_H
#define QNote_H
#include "QInclude.h"
#include "notes.h"
class QNote: public QWidget{
    Q_OBJECT
    QLabel* titre;
    QLineEdit* E_titre;
protected:
    QGridLayout* grid;
public:
    virtual Note* get_note(QString id,QString title)=0;
    QNote();
    virtual void load_note(Note& n)=0;
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
    void load_note(Note &N);
public slots:
    void check_creer();
signals:
    void checked_creer(bool);
};

class QTask: public QNote{
    Q_OBJECT
    QVBoxLayout* fen;
    QLabel* action;
    QLineEdit* E_action;
    QGroupBox* priority;
    QHBoxLayout* optional_priority;
    QSpinBox* E_priority;

    QGroupBox* duedate;
    QHBoxLayout* optional_duedate;
    QDateTimeEdit* E_duedate;
    QLabel* status;
    QComboBox* E_status;
    QGridLayout* grid;
    Note* get_note(QString id, QString title);
public:
    QTask();
    void load_note(Note &N);
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
    virtual void load_note(Note& N);
public slots:
    QString OuvrirFichier();
    void check_creer();
signals:
    void checked_creer(bool);
};

#endif // QNote_H
