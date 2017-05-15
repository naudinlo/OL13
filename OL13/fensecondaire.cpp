#include "fensecondaire.h"

Fensecondaire::Fensecondaire(QString texte,QWidget* parent): QDialog(parent)
{
    fermer=new(QPushButton) ("fermer",this);
    QObject::connect(fermer,SIGNAL(clicked(bool)),this,SLOT(close()));
    text=new(QTextEdit) (this);
    text->setPlainText(texte);

    fen=new(QVBoxLayout)(this);
    fen->addWidget(text);
    fen->addWidget(fermer);
    this->setLayout(fen);

}

