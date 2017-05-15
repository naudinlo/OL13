#ifndef FENSECONDAIRE_H
#define FENSECONDAIRE_H

#include <QObject>
#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
class Fensecondaire: public QDialog
{
    Q_OBJECT
    QVBoxLayout* fen;
    QPushButton* fermer;
    QTextEdit* text;

public:
    Fensecondaire(QString  texte,QWidget* parent=0);
};

#endif // FENSECONDAIRE_H
