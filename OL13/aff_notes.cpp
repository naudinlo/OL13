#include "aff_notes.h"

page_notes::page_notes()
{
    create_dock();
    layout_p=new QVBoxLayout(this);
    layout_titre=new QHBoxLayout;
    titre=new QLineEdit("Titre de la note");
    titre->setEnabled(false);
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
