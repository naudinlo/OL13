/**
 * \file      note.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définit le type note et ses types dérivés
 *
 * \details   Classes présentes :
 *                  - NotesException
 *                      Gère les exceptions relatives aux notes.

 *                  - Note
 *                      Classe mère abstraite définissant l'ensemble des attributs et comportement des notes.
 *
 *                      Possède un attribut Note ** references permettant d'accéder aux références de la note.
 *                      Possède deux attributs booléens isArchived et isDeleted permettant de spécifier
 *                        si une note est supprimée ou non.
 *
 *                      Les méthodes toString et display sont virtuelles : redéfinies dans les sous classes,
 *                        elles permettent un affichage personnalisé des différents typs de notes.
 *
 *                  - Article
 *                      Classe article, dérivant de la classe Note, avec en plus l'attribut text.
 *
 *                  - Task
 *                      Classe task, dérivant de la classe Note, avec en plus les attributs action, status,
 *                        et les attributs optionnels dueDate et priority.
 *
 *                  - Recording
 *                      Classe recording, dérivant de la classe Note, avec en plus les attributs descriptions,
 *                        type et un link vers un fichier image, audio ou video.
 *
 *              L'ensemble des méthodes définies dans ce fichier sont explicitées dans le fichier .cpp associé.
 */


#ifndef notes_h
#define notes_h
#include <QString>
#include <QTextDocument>
#include <QDate>
#include <typeinfo>
#include <iostream>
#include "QInclude.h"

class NotesException;
class Note;
class Article;
class Task;
class Recording;


namespace ENUM
{
    enum StatusType { Pending, OnGoing, Completed };
    enum RecordingType { Image, Audio, Video };
}


class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getinfo() const {return info;}
private:
    QString info;
};

class Note{
private:
    const QString id;
    QString title;
    QDateTime creation_date;
    QDateTime lastmodif_date;
    bool isArchive; //Si jamais on l'archive alors elle devient const
    bool isDeleted; //Si jamais on la met dans la corbeille

    // LNA test ref 09.06
//    Note ** referencesOLD;
//    QList<QString> referencesQ;
//    unsigned int nbRefOLD;
//    unsigned int nbMaxRefOLD;

    unsigned int nbIsRef;

//    void addReferenceOLD(Note* n);
//    void addReferenceQ(const QString& id);
public:
    const QString getId() const {return id;}
    const QString getTitle() const {return title;}
    const QDateTime getCreation_date() const {return creation_date;}
    const QDateTime getLastmodif_date() const {return lastmodif_date;}
    bool getIsArchive() const {return isArchive;}
    bool getIsDeleted() const {return isDeleted;}
    void setIsArchive(bool a){isArchive=a;}
    void setIsDeleted(bool d){isDeleted=d;}

    QString getType()const {return QString(typeid(*this).name()).remove(0,1);}
    Note(const QString& i, const QString& ti);
//    Note(const QString&i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD):
//        id(i),title(ti),creation_date(cd),lastmodif_date(lmd),isArchive(iA),isDeleted(iD), references(new Note*[5]), nbRef(0), nbMaxRef(5),nbIsRef(0){}
    Note(const QString&i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD):
        id(i),title(ti),creation_date(cd),lastmodif_date(lmd),isArchive(iA),isDeleted(iD), nbIsRef(0){}

    void setTitle(const QString& t){generateRef(t); title=t;}
    void setCreation_date(const QDateTime& d){creation_date=d;}
    void setLastmodif_date(const QDateTime& d){lastmodif_date=d;}

    Note(const Note& n); //constructeur de recopie private pour le handler
    Note& operator=(const Note& n);   //operateur d'affectation private pour le handler
    virtual ~Note();

    virtual std::string toString() const;
    void display(std::ostream& f=std::cout) const{
        f<<toString();
    }
    virtual void saveNote(QFile *file);

    //Les notes que this reference
//    unsigned int getNbRefOLD() const{return nbRef;}
//    unsigned int getNbMaxRefOLD() const{return nbMaxRef;}
//    void setNbRefOLD(unsigned int n){ nbRef=n;}
    void setNbIsRef(unsigned int n){nbIsRef=n;}
    unsigned int getNbIsRef()const{return nbIsRef;}

//    void deleteReferenceOLD(const QString& id);
//    void deleteAllReferenceOLD();
//    Note& setNewRefOLD(Note* n);
//    Note& getReferenceOLD(const QString &id) const;
//    Note& getReferenceIntOLD(unsigned int i) const;

    QList<QString> references;
    void deleteReference(const QString& id);
    void deleteAllReference();
    void setNewRef(const QString& id);
    Note& getReference(const QString &id) const;
//    Note& getReferenceInt(unsigned int i) const;

    void generateRef(const QString& champTexte);

};


class Article : public Note{
private:
    QTextDocument text;
public:
    const QTextDocument& getText()const {return text;}
    void setText(const QString& t){generateRef(t); text.setPlainText(t);}

    Article(const QString& i, const QString& ti, const QString& te);
    Article(const QString& i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD, const QString& te):
        Note(i,ti,cd,lmd,iA,iD), text(te){}

    //PRIVATE ?
    Article(const Article& a); //constructeur de recopie private pour le handler
    Article& operator=(const Article& a);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
    void saveNote(QFile *file);
};


class Task : public Note{
private:
    QString action;
    ENUM::StatusType status;
    unsigned int priority;
    QDateTime dueDate;
public:
    const QString getAction() const {return action;}
    void setAction(const QString& a) {generateRef(a); action=a;}
    ENUM::StatusType getStatus() const {return status;}
    void setStatus(const ENUM::StatusType& s) {status=s;}
    int getPriority() const {return priority;}
    void setPriority(unsigned int p) {priority=p;}
    const QDateTime& getDueDate() const{return dueDate;}
    void setDueDate(const QDateTime d){dueDate=d;}

    //Constructeurs
    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s);  //Premier type de constructeur : les deux optionels oubliés
    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p); //Deuxième type de constructeur : priorité ajoutée
    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, const QDateTime d);  //Troisième type : dueDate ajoutée
    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d);    //Quatrième type : priorité et dueDate ajoutés
    Task(const QString& i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD, const QString a, ENUM::StatusType s, unsigned int p, const QDateTime dD):
        Note(i,ti,cd,lmd,iA,iD), action(a),status(s),priority(p),dueDate(dD){}

    //PRIVATE ?
    Task(const Task& t); //constructeur de recopie private pour le handler
    Task& operator=(const Task& a);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
    void saveNote(QFile *file);
};


class Recording : public Note{
private:
    QTextDocument description;
    ENUM::RecordingType type;
    QString link;
public:
    const QTextDocument& getDescription() const {return description;}
    ENUM::RecordingType getType() const {return type;}
    const QString getLink() const {return link;} //voir si on garde cette structure pour les images
    void setDescription(const QString& d) {generateRef(d);description.setPlainText(d);}
    void setType(const ENUM::RecordingType& r) {type=r;}
    void setLink(const QString& l){link=l;}
    Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l);
    Recording(const QString& i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD, const QString& d, ENUM::RecordingType ty, const QString& li):
        Note(i,ti,cd,lmd,iA,iD), description(d), type(ty), link(li){}

    //PRIVATE ?
    Recording(const Recording& r); //constructeur de recopie private pour le handler
    Recording& operator=(const Recording& r);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
    void saveNote(QFile *file);
};

/**
 * \brief     Surcharge affichage avec polymorphisme
 */
std::ostream& operator<<(std::ostream& f, const Article& a);
std::ostream& operator<<(std::ostream& f, const Task& t);
std::ostream& operator<<(std::ostream& f, const Recording& t);

/**
 * \brief     Retourne directement le statut de int à stringQ
 */
QString getStatustoStr(ENUM::StatusType status);
QString getRecordingtoStr(ENUM::StatusType recording);



#endif /* notes_hpp */
