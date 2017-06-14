/**
 * \file      relations.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définit le type relation
 *
 *
 * \details   Classes présentes :
 *                  - NotesCouple
 *                      La classe NotesCouple est en agrégation avec la classe Relation :
 *                      une relation contient un ensemble de couple de notes.
 *                      Dans le cas où l'ensemble des couples d'une relation est supprimé,
 *                      la relation existe toujours mais est vide. Elle pourra être repeuplée par de nouveaux couples.
 *
 *                      La classe NotesCouple possède deux attributs noteX et noteY pointant chacun
 *                      sur une note du couple, un attribut pour le label du couple et un attribut
 *                      booléen spécifiant si le couple est symétrique.
 *                      C'est à dire que la relation va de noteX vers noteY et réciproquement.
 *
 *                      La classe NotesCouple est composée par la classe Notes : si les notes sont supprimées,
 *                      les couplent n'existent plus non plus.
 *
 *                  - Relation
 *                      La classe Relation possède un titre, une description et un ensemble de couple de notes.
 *                      Dans l'implémentation de cette classe, un Design Pattern Iterator est utilisé pour
 *                      faciliter la manipulation des données.
 *
 *                      Une classe manager dans manager.h/.cpp est utilisée pour gérer l'ensemble des relations.
 *
 *             L'ensemble des méthodes définies dans ce fichier sont explicitées dans le fichier .cpp associé.
 *
 */


#ifndef RELATION_H
#define RELATION_H

#include "notes.h"

class NotesCouple;
class Relation;

/**************Couple de note********************/

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

/**************Relation********************/

class Relation {
private:
    QString title;
    QString description;
    NotesCouple ** relations;
    unsigned int nbCouple;
    unsigned int nbMaxCouple;
    void addCoupleRelation(NotesCouple* nc);
public:
    Relation(QString t, QString d):title(t), description(d),relations(new NotesCouple*[5]), nbCouple(0), nbMaxCouple(5){}

    const QString getTitle() const{return title;}
    void setTitle(QString t){title=t;}
    void setDescription(QString d){description=d;}

    NotesCouple& getNewCoupleRelation(Note* n1, Note* n2, QString label=0, bool s=false);
    const QString getDescription() const{return description;}
    NotesCouple* getCoupleRelation(Note* n1, Note* n2)const;
    void removeCoupleRelation(Note* n1, Note* n2);
    void removeNoteRelation(Note* n1);

    std::string displayRelation();

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

    void displayCoupleRelation(Note *n1, Note *n2)const;
};



#endif // RELATION_H
