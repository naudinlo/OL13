/**
 * \file      undoredo.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Gestion Undo Redo
 */


#ifndef UNDOREDO_H
#define UNDOREDO_H

#include <QUndoCommand>


class AppendText : public QUndoCommand
{
public:
    AppendText(QString *doc, const QString &text)
        : m_document(doc), m_text(text) { setText("append text"); }
    virtual void undo()
        { m_document->chop(m_text.length()); }
    virtual void redo()
        { m_document->append(m_text); }
private:
    QString *m_document;
    QString m_text;
};



#endif // UNDOREDO_H
