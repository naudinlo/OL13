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
 *              Détail des méthodes donné dans le .cpp.
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
    Note ** references;
    unsigned int nbRef;
    unsigned int nbMaxRef;

    unsigned int nbIsRef;

    void addReference(Note* n);

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

    void setTitle(const QString& t){title=t;}
    void setLastmodif_date(const QDateTime& d){lastmodif_date=d;}

    //PRIVATE ?
    Note(const Note& n); //constructeur de recopie private pour le handler
    Note& operator=(const Note& n);   //operateur d'affectation private pour le handler
    virtual ~Note();

    virtual std::string toString() const;
    void display(std::ostream& f=std::cout) const{
        f<<toString();
    }
    virtual void saveNote(QFile *file);

    //Les notes que this reference
    Note& setNewRef(Note* n);

    Note& getReference(const QString &id) const;
    Note& getReferenceInt(unsigned int i) const;
    unsigned int getNbRef() const{return nbRef;}
    unsigned int getNbMaxRef() const{return nbMaxRef;}
    void setNbRef(unsigned int n){ nbRef=n;}
    void deleteReference(const QString& id);
    void deleteAllReference();


    void setNbIsRef(unsigned int n){nbIsRef=n;}
    unsigned int getNbIsRef()const{return nbIsRef;}

};


class Article : public Note{
private:
    QTextDocument text;
public:
    const QTextDocument& getText()const {return text;}
    void setText(const QString& t){text.setPlainText(t);}

    Article(const QString& i, const QString& ti, const QString& te);

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
    void setAction(const QString& a) {action=a;}
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
    //Fichier image a ajouter
public:
    const QTextDocument& getDescription() const {return description;}
    ENUM::RecordingType getType() const {return type;}
    const QString getLink() const {return link;} //voir si on garde cette structure pour les images
    void setDescription(const QString& d) {description.setPlainText(d);}
    void setType(const ENUM::RecordingType& r) {type=r;}
    void setLink(const QString& l){link=l;}
    Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l);

    //PRIVATE ?
    Recording(const Recording& r); //constructeur de recopie private pour le handler
    Recording& operator=(const Recording& r);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
    void saveNote(QFile *file);
};

//Surcharge affichage avec polymorphisme
std::ostream& operator<<(std::ostream& f, const Article& a);
std::ostream& operator<<(std::ostream& f, const Task& t);
std::ostream& operator<<(std::ostream& f, const Recording& t);

//Retourner directement le statut de int à stringQ
QString getStatustoStr(ENUM::StatusType status);
QString getRecordingtoStr(ENUM::StatusType recording);



#endif /* notes_hpp */
