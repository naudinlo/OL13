#ifndef DELETEDNOTE_H
#define DELETEDNOTE_H

#include <QDockWidget>

namespace Ui {
class DeletedNote;
}

class DeletedNote : public QDockWidget
{
    Q_OBJECT

public:
    explicit DeletedNote(QWidget *parent = 0);
    ~DeletedNote();

private:
    Ui::DeletedNote *ui;
};

#endif // DELETEDNOTE_H
