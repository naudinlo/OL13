#include "aff_notes.h"

page_notes::page_notes(Note& n)
{
    create_dock();
    layout_p=new QVBoxLayout(this);
    layout_titre=new QHBoxLayout;
    titre=new QLabel(n.getTitle());
    titre->setEnabled(false);
    info=new QLabel("Cette note est un :"+n.getType()+" Créer le :"+n.getCreation_date().toString()+" Dernière modification le :"+n.getLastmodif_date().toString());
    layout_titre->addStretch();
    layout_titre->addWidget(titre);
    layout_titre->addStretch();
    layout_p->addLayout(layout_titre);


}
void page_notes::create_dock(){
    dock=new QWidget;
    QHBoxLayout*layout=new QHBoxLayout(dock);
    QLabel* lecture_seul=new QLabel ("Ce documment est ouvert en lecture seul");
    QPushButton* editer=new QPushButton ("Edité");
    layout->addStretch();
    layout->addWidget(lecture_seul);
    layout->addWidget(editer);
}
page_article::page_article(Article &n): page_notes(n){
    description=new QTextEdit;
    description->setEnabled(false);
    description->setDocument(&(n.getText()));
    layout_p->addStretch();
    layout_p->addWidget(description);
    addInfo();

}
page_Task::page_Task(Task &n): page_notes(n){
    action=new QLabel ("Action");
    E_action=new QLineEdit;

    duedate=new QGroupBox ();
    duedate->setCheckable(true);
    duedate->setTitle("Date de réalisation :");
    optional_duedate=new QHBoxLayout();
    duedate->setLayout(optional_duedate);
    E_duedate=new QDateTimeEdit();
    E_duedate->setDate(QDate::currentDate());
    E_duedate->setTime(QTime::currentTime());
    E_duedate->setCalendarPopup(true);
    optional_duedate->addStretch();
    optional_duedate->addWidget(E_duedate);
    priority=new QGroupBox ();
    priority->setCheckable(true);
    priority->setTitle("priorité :");
    optional_priority=new QHBoxLayout;
    priority->setLayout(optional_priority);
    E_priority=new QSpinBox();
    optional_priority->addStretch();
    optional_priority->addWidget(E_priority);

    status=new QLabel("Etat");
    E_status=new QComboBox;
    E_status->addItem("En cours");
    E_status->addItem("En attente");
    E_status->addItem("Complétée");

    grid=new QGridLayout(this);
    grid->addWidget(action,0,0);
    grid->addWidget(E_action,0,1);
    grid->addWidget(status,1,0);
    grid->addWidget(E_status,1,1);
    grid->addWidget(duedate,2,0,2,2);
    grid->addWidget(priority,3,0,3,2);

    layout_p->addLayout(grid);
    addInfo();

}
