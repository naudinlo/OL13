#ifndef QREFERENCE_H
#define QREFERENCE_H

#include "manager.h"
#include <QWidget>
#include "QInclude.h"
namespace Ui {
class Qreference;
}

class Qreference : public QWidget
{
    Q_OBJECT

public:
    explicit Qreference(Note& n,QWidget *parent = 0);
    ~Qreference();
    QStandardItemModel* model_ref;

private:
    Ui::Qreference *ui;
    Note& note;
public slots:
    void update_model();
};

#endif // QREFERENCE_H
