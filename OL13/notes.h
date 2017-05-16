//
//  notes.hpp
//  OL12PROJET
//
//  Created by Louise Naudin on 11/05/2017.
//  Copyright © 2017 LNA. All rights reserved.
//

#ifndef notes_h
#define notes_h
#include <QString>
#include <QTextDocument>
#include "timing.h"
//#include "include.h"

class NotesException;
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
/* POUR QT
 public:
 NotesException(const QString& message):info(message){}
 QString getInfo() const { return info; }
 private:
 QString info;
 */
};

class Note{
private:
    const QString id;
    QString title;
    TIME::Date creation_date;
    TIME::Date lastmodif_date;
    bool isArchive; //Si jamais on l'archive alors elle devient const
    bool isDeleted; //Si jamais on la met dans la corbeille

public:
    const QString getId() const {return id;}
    const QString getTitle() const {return title;}
    const TIME::Date getCreation_date() const {return creation_date;}
    const TIME::Date getLastmodif_date() const {return lastmodif_date;}
    bool getIsArchive() const {return isArchive;}
    bool getIsDeleted() const {return isDeleted;}

    Note(const QString& i, const QString& ti);

    void setTitle(const QString& t){title=t;}
    void setLastmodif_date(const TIME::Date& d){lastmodif_date=d;}

    //PRIVATE ?
    Note(const Note& n); //constructeur de recopie private pour le handler
    Note& operator=(const Note& n);   //operateur d'affectation private pour le handler
    virtual ~Note(){}

    virtual std::string toString() const=0;
    void display(std::ostream& f=std::cout) const{
        f<<toString();
    }
};


class Article : public Note{
private:
    QTextDocument text;
public:
    const QTextDocument& getText() const {return text;}
    void setText(const QString& t){text.setPlainText(t);}

    Article(const QString& i, const QString& ti, const QString& te);

    //PRIVATE ?
    Article(const Article& a); //constructeur de recopie private pour le handler
    Article& operator=(const Article& a);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
};


class Task : public Note{
private:
    QString action;
    ENUM::StatusType status;
    unsigned int priority;
    TIME::Date dueDate;
public:
    const QString getAction() const {return action;}
    void setAction(const QString& a) {action=a;}
    const ENUM::StatusType getStatus() const {return status;}
    void setStatus(const ENUM::StatusType& s) {status=s;}
    int getPriority() const {return priority;}
    void setPriority(unsigned int p) {priority=p;}
    const TIME::Date getDueDate() const{return dueDate;}
    void setDueDate(const TIME::Date d){dueDate=d;}

    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s);  //Premier type de constructeur : les deux optionels oubliés
    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p); //Deuxième type de constructeur : priorité ajoutée
    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, const TIME::Date d);  //Troisième type : dueDate ajoutée
    Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p, const TIME::Date d);    //Quatrième type : priorité et dueDate ajoutés

    //PRIVATE ?
    Task(const Task& t); //constructeur de recopie private pour le handler
    Task& operator=(const Task& a);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
};


class Recording : public Note{
private:
    QTextDocument description;
    ENUM::RecordingType type;
    QString link;
    //Fichier image a ajouter
public:
    const QTextDocument& getDescription() const {return description;}
    void setDescription(const QString& d) {description.setPlainText(d);}
    const ENUM::RecordingType getType() const {return type;}
    void setType(const ENUM::RecordingType& r) {type=r;}

    Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l);

    //PRIVATE ?
    Recording(const Recording& r); //constructeur de recopie private pour le handler
    Recording& operator=(const Recording& r);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
};

//Surcharge affichage avec polymorphisme
std::ostream& operator<<(std::ostream& f, const Article& a);
std::ostream& operator<<(std::ostream& f, const Task& t);
std::ostream& operator<<(std::ostream& f, const Recording& t);



#endif /* notes_hpp */
