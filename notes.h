//
//  notes.hpp
//  OL12PROJET
//
//  Created by Louise Naudin on 11/05/2017.
//  Copyright © 2017 LNA. All rights reserved.
//

#ifndef notes_h
#define notes_h

#include "timing.h"
#include "include.h"

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
    NotesException(const std::string& message):info(message){}
    std::string getinfo() const {return info;}
private:
    std::string info;
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
    const std::string id;
    std::string title;
    TIME::Date creation_date;
    TIME::Date lastmodif_date;
    bool isArchive; //Si jamais on l'archive alors elle devient const
    bool isDeleted; //Si jamais on la met dans la corbeille

public:
    const std::string getId() const {return id;}
    const std::string getTitle() const {return title;}
    const TIME::Date getCreation_date() const {return creation_date;}
    const TIME::Date getLastmodif_date() const {return lastmodif_date;}
    bool getIsArchive() const {return isArchive;}
    bool getIsDeleted() const {return isDeleted;}

    Note(const std::string& i, const std::string& ti);

    void setTitle(const std::string& t){title=t;}
    void setLastmodif_date(const TIME::Date& d){lastmodif_date=d;}

    //PRIVATE ?
    Note(const Note& n); //constructeur de recopie private pour le handler
    Note& operator=(const Note& n);   //operateur d'affectation private pour le handler
    //~Note();

    virtual std::string toString() const=0;
    void display(std::ostream& f=std::cout) const{
        f<<toString();
    }
};


class Article : public Note{
private:
    std::string text;
public:
    const std::string getText() const {return text;}
    void setText(const std::string& t){text=t;}

    Article(const std::string& i, const std::string& ti, const std::string& te);

    //PRIVATE ?
    Article(const Article& a); //constructeur de recopie private pour le handler
    Article& operator=(const Article& a);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
};


class Task : public Note{
private:
    std::string action;
    ENUM::StatusType status;
    unsigned int priority;
    TIME::Date dueDate;
public:
    const std::string getAction() const {return action;}
    void setAction(const std::string& a) {action=a;}
    const ENUM::StatusType getStatus() const {return status;}
    void setStatus(const ENUM::StatusType& s) {status=s;}
    int getPriority() const {return priority;}
    void setPriority(unsigned int p) {priority=p;}
    const TIME::Date getDueDate() const{return dueDate;}
    void setDueDate(const TIME::Date d){dueDate=d;}

    Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s);  //Premier type de constructeur : les deux optionels oubliés
    Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s, unsigned int p); //Deuxième type de constructeur : priorité ajoutée
    Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s, const TIME::Date d);  //Troisième type : dueDate ajoutée
    Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s, unsigned int p, const TIME::Date d);    //Quatrième type : priorité et dueDate ajoutés

    //PRIVATE ?
    Task(const Task& t); //constructeur de recopie private pour le handler
    Task& operator=(const Task& a);   //operateur d'affectation private pour le handler
    //~Note();

    std::string toString() const;
};


class Recording : public Note{
private:
    std::string description;
    ENUM::RecordingType type;
    //Fichier image a ajouter
public:
    const std::string getDescription() const {return description;}
    void setDescription(const std::string& d) {description=d;}
    const ENUM::RecordingType getType() const {return type;}
    void setType(const ENUM::RecordingType& r) {type=r;}

    Recording(const std::string& i, const std::string& ti, const std::string& d, ENUM::RecordingType r);

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
