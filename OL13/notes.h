/**
 * \file      notes.h
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

/**************Enumération********************/
/**
 *\namespace ENUM
 * \brief Namespace dédié aux énumarations
 */
namespace ENUM
{
    enum StatusType { Pending, OnGoing, Completed };
    enum RecordingType { Image, Audio, Video };
}


/**************NotesException********************/

class NotesException{
public:
    /**
     * @fn NotesException
     * @param message
     * @brief Constructeur de NotesException
     */
    NotesException(const QString& message):info(message){}
    /**
     * @fn getinfo
     * @brief Accesseur du champ info
     * @return QString
     */
    QString getinfo() const {return info;}
private:
    QString info;
};


/**************Note********************/

class Note{
private:
    const QString id;
    QString title;
    QDateTime creation_date;
    QDateTime lastmodif_date;
    bool isArchive; //Si jamais on l'archive alors elle devient const
    bool isDeleted; //Si jamais on la met dans la corbeille

    unsigned int nbIsRef;

public:
    /**
     * @fn getId
     * @brief Accesseur du champ id
     * @return QString
     */
    const QString getId() const {return id;}
    /**
     * @fn getTitle
     * @brief Accesseur du champ title
     * @return QString
     */
    const QString getTitle() const {return title;}
    /**
     * @fn getCreation_date
     * @brief Accesseur du champ creation_date
     * @return QDateTime
     */
    const QDateTime getCreation_date() const {return creation_date;}
    /**
     * @fn getLastmodif_date
     * @brief Accesseur du champ lastmodif_date
     * @return QDateTime
     */
    const QDateTime getLastmodif_date() const {return lastmodif_date;}
    /**
     * @fn getIsArchive
     * @brief Accesseur du champ isArchive
     * @return bool
     */
    bool getIsArchive() const {return isArchive;}
    /**
     * @fn getIsDeleted
     * @brief Accesseur du champ isDeleted
     * @return bool
     */
    bool getIsDeleted() const {return isDeleted;}
    /**
     * @fn setIsArchive
     * @brief Affectation du champ isArchive
     * @param bool a
     */
    void setIsArchive(bool a){isArchive=a;}
    /**
     * @fn setIsDeleted
     * @brief Affectation du champ isDeleted
     * @param bool b
     */
    void setIsDeleted(bool d){isDeleted=d;}
    /**
     * @fn getType
     * @brief Accesseur du type de note
     * @return QString
     */
    QString getType()const {return QString(typeid(*this).name()).remove(0,1);}
    Note(const QString& i, const QString& ti);
    /**
     * @fn Note::Note
     * @brief Constructeur de note
     * @param i
     * @param ti
     * @param cd
     * @param lmd
     * @param iA
     * @param iD
     */
    Note(const QString&i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD):
        id(i),title(ti),creation_date(cd),lastmodif_date(lmd),isArchive(iA),isDeleted(iD), nbIsRef(0){}
    /**
     * @fn setTitle
     * @brief Affectation du champ title
     * @param const Qstring& t
     */
    void setTitle(const QString& t){generateRef(t); title=t;}
    /**
     * @fn setCreation_date
     * @brief Affectation du champ creation_date
     * @param const QDateTime& d
     */
    void setCreation_date(const QDateTime& d){creation_date=d;}
    /**
     * @fn setLastmodif_date
     * @brief Affectation du champ lastmodif_date
     * @param const QDateTime& d
     */
    void setLastmodif_date(const QDateTime& d){lastmodif_date=d;}

    Note(const Note& n); //constructeur de recopie private pour le handler
    Note& operator=(const Note& n);   //operateur d'affectation private pour le handler
    virtual ~Note();

    virtual std::string toString() const;
    /**
     * @fn display
     * @brief Permet d'afficher une note sur un flux ostream
     * @param std::ostream& f=std::cout
     */
    void display(std::ostream& f=std::cout) const{
        f<<toString();
    }
    virtual void saveNote(QFile *file);
    /**
     * @fn setNbIsRef
     * @brief Affectation du champ nbIsRef
     * @param unsigned int n
     */
    void setNbIsRef(unsigned int n){nbIsRef=n;}
    /**
     * @fn getNbIsRef
     * @brief Accesseur du champ nbIsRef
     * @return unsigned int
     */
    unsigned int getNbIsRef()const{return nbIsRef;}

    QList<QString> references;
    void deleteReference(const QString& id);
    void deleteAllReference();
    void setNewRef(const QString& id);
    Note& getReference(const QString &id) const;

    void generateRef(const QString& champTexte);

};

/**************Article********************/


class Article : public Note{
private:
    QTextDocument text;
public:
    /**
     * @fn      const QTextDocument& getText()const
     * @brief   Accesseur du champ Text
     * @return const QTextDocument&
     */
    const QTextDocument& getText()const {return text;}
    /**
     * @fn      void setText(const QString& t)
     * @brief   Affectation du champ Text
     * @param   const QString&
     */
    void setText(const QString& t){generateRef(t); text.setPlainText(t);}

    Article(const QString& i, const QString& ti, const QString& te);
    Article(const QString& i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD, const QString& te):
        Note(i,ti,cd,lmd,iA,iD), text(te){}

    Article(const Article& a); //constructeur de recopie private pour le handler
    Article& operator=(const Article& a);   //operateur d'affectation private pour le handler

    std::string toString() const;
    void saveNote(QFile *file);
};

/**************Task********************/

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

    Task(const Task& t); //constructeur de recopie private pour le handler
    Task& operator=(const Task& a);   //operateur d'affectation private pour le handler

    std::string toString() const;
    void saveNote(QFile *file);
};


/**************Recording********************/


class Recording : public Note{
private:
    QTextDocument description;
    ENUM::RecordingType type;
    QString link;
public:
    const QTextDocument& getDescription() const {return description;}
    ENUM::RecordingType getType() const {return type;}
    const QString getLink() const {return link;}
    void setDescription(const QString& d) {generateRef(d);description.setPlainText(d);}
    void setType(const ENUM::RecordingType& r) {type=r;}
    void setLink(const QString& l){link=l;}
    Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l);
    Recording(const QString& i, const QString& ti, const QDateTime& cd, const QDateTime& lmd, bool iA, bool iD, const QString& d, ENUM::RecordingType ty, const QString& li):
        Note(i,ti,cd,lmd,iA,iD), description(d), type(ty), link(li){}

    Recording(const Recording& r); //constructeur de recopie private pour le handler
    Recording& operator=(const Recording& r);   //operateur d'affectation private pour le handler

    std::string toString() const;
    void saveNote(QFile *file);
};

/**************Autre********************/


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
