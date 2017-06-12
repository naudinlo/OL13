/**
 * \file      relation.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     //Bref
 *
 * \details  //Détail
 *
 */


#ifndef RELATION_H
#define RELATION_H

#include "notes.h"

class NotesCouple;
class Relation;

class NotesCouple {
private:
    Note* notex;
    Note* notey;
    QString label;
    bool symetric;
public:
    NotesCouple(Note* nx, Note* ny, QString l=0, bool s=false):notex(nx),notey(ny),label(l), symetric(s){}
    Note* getCoupleNoteX() const {return notex;}
    Note* getCoupleNoteY() const  {return notey;}
    QString getLabel() const  {return label;}
    void setLabel(QString l) {label=l;}
    bool getSymetric() const {return symetric;}
};

class Relation {
private:
    QString title;
    QString description;
    NotesCouple ** relations;
    unsigned int nbCouple;
    unsigned int nbMaxCouple;
    void addCoupleRelation(NotesCouple* nc);
public:
    NotesCouple& getNewCoupleRelation(Note* n1, Note* n2, QString label=0, bool s=false);
    NotesCouple* getCoupleRelation(Note* n1, Note* n2);
    Relation(QString t, QString d):title(t), description(d),relations(new NotesCouple*[5]), nbCouple(0), nbMaxCouple(5){}
    const QString getTitle() const{return title;}
    void setTitle(QString t){title=t;}
    void setDescription(QString d){description=d;}
    const QString getDescription() const{return description;}
    NotesCouple* getCoupleRelation(Note* n1, Note* n2)const;
    void removeCoupleRelation(Note* n1, Note* n2);
    void removeNoteRelation(Note* n1);

//    QList<Note*>* addNoteAscendant(Note * n, QList<Note*>* listAscendants);
//    Note** noteRelAsc(Note * n);

    std::string displayRelation();
//    std::string toString() const;
//    void display(std::ostream& f=std::cout) const{
//        f<<displayRelation();
//    }

    //Iterator
    class Iterator{
    private:
        NotesCouple** tab;  //adresse du tableau de pointeur
        unsigned int nb;        //nb élément dans le tableau
        unsigned int index;     //indice courant
        Iterator(NotesCouple** t, unsigned int n):tab(t), nb(n), index(0){}
        friend class Relation;
    public:
        void next(){
            if (index==nb) throw NotesException("incrémentation invalide");
            index++;
        }
        bool isDone()const {return nb==index;}
        NotesCouple& current() const {return *tab[index];}
    };
    Iterator getIterator(){
        return Iterator(relations, nbCouple);
    }

//    std::string toStringRel(Note *n1, Note *n2)const;
//    void displayRel(Note *n1, Note *n2, std::ostream& f=std::cout) const{
//        f<<toStringRel(n1,n2);
//    }
    void displayCoupleRelation(Note *n1, Note *n2)const;
};






#endif // RELATION_H
