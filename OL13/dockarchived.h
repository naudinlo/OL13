#ifndef DOCKARCHIVED_H
#define DOCKARCHIVED_H
#include "QInclude.h"
#include "manager.h"
#include <QDockWidget>

namespace Ui {
class DockArchived;
}

class Dock : public QDockWidget
{
    Q_OBJECT

public:
    explicit Dock(QWidget *parent = 0);
    ~Dock();
signals:
    void update_removeDock();
    void selection(QString, int);
public slots:
    virtual void on_remove_clicked()=0;
    virtual void update_archNoteModel()=0;
    void on_aff_clicked();
    void on_ArchView_clicked(QModelIndex i);

protected:
    Ui::DockArchived *ui;
    QString currentNote;
    QStandardItemModel* ArchNote;

};

class DockArchived: public Dock{
    Q_OBJECT

public:
    DockArchived(QWidget* parent):Dock(parent){
    }

    void update_archNoteModel();
public slots:
    void on_remove_clicked(){
        Note& n=NotesManager::getInstance()->getNote(currentNote);
        n.setIsArchive(false);
        n.setIsDeleted(true);
        emit(update_removeDock());
        update_archNoteModel();
    }

};

class DockRemove: public Dock{
    Q_OBJECT

public:
    void update_archNoteModel();
    DockRemove(QWidget* parent);

public slots:
    void on_remove_clicked(){
        Note& n=NotesManager::getInstance()->getNote(currentNote);
        n.setIsArchive(true);
        n.setIsDeleted(false);
        emit(update_removeDock());
        update_archNoteModel();
    }

};

#endif // DOCKARCHIVED_H
