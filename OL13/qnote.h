#ifndef QNote_H
#define QNote_H
#include "QInclude.h"
#include "notes.h"
#include "manager.h"
#include "relations.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
class QNote: public QWidget{
    Q_OBJECT
    QLabel* titre;
    QLineEdit* E_titre;
protected:
    QGridLayout* grid;
public:
    virtual Note& get_note(QString id,QString title)=0;
    virtual void readOnly(bool status);
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
    Note& get_note(QString id, QString title);
public:
    QArticle();
    void load_note(Note &N);
    void readOnly(bool status);
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
    Note &get_note(QString id, QString title);
public:
    QTask();
    void load_note(Note &N);
    void readOnly(bool status);
signals:
    void checked_creer(bool);
public slots:
    void check_creer();
};

class QRecording: public QNote {
    Q_OBJECT
    QLabel* description;
    QTextEdit* E_description;
    QLabel* type;
    QComboBox* E_type;
    QLineEdit* E_link;
    QPushButton* link;
    QPushButton* read;
    QPushButton* stop;


    QGridLayout* grid;
    Note& get_note(QString id, QString title);
    QMediaPlayer* player;
    QVideoWidget* videoWidget;
    QMediaPlaylist* playlist;

public:
    QRecording();
    virtual void load_note(Note& N);
    void readOnly(bool status);
public slots:
    QString OuvrirFichier();
    void check_creer();
    void read_record();
    void stop_record();
signals:
    void checked_creer(bool);
    void recording_ready();
};

#endif // QNote_H
