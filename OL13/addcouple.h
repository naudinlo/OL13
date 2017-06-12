#ifndef ADDCOUPLE_H
#define ADDCOUPLE_H

#include <QDialog>

namespace Ui {
class addCouple;
}

class addCouple : public QDialog
{
    Q_OBJECT

public:
    explicit addCouple(QWidget *parent = 0);
    ~addCouple();

private:
    Ui::addCouple *ui;
};

#endif // ADDCOUPLE_H
