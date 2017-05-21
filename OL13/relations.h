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
    const QString getDescription() const{return description;}
    NotesCouple* getCoupleRelation(Note* n1, Note* n2)const;
    void removeCoupleRelation(Note* n1, Note* n2);
    void removeNoteRelation(Note* n1);


//    std::string toStringRel(Note *n1, Note *n2)const;
//    void displayRel(Note *n1, Note *n2, std::ostream& f=std::cout) const{
//        f<<toStringRel(n1,n2);
//    }
    void displayRelation(Note *n1, Note *n2)const;
};






#endif // RELATION_H
