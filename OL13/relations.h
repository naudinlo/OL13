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
    /**
     * @fn NotesCouple
     * @brief Constructeur de NotesCouple
     * @param Note* nx
     * @param Note* ny
     * @param QString l
     * @param bool s
     */
    NotesCouple(Note* nx, Note* ny, QString l=0, bool s=false):notex(nx),notey(ny),label(l), symetric(s){}
    /**
     * @fn getCoupleNoteX
     * @brief Accesseur de l'attribut notex
     * @return Note*
     */
    Note* getCoupleNoteX() const {return notex;}
    /**
     * @fn getCoupleNoteY
     * @brief Accesseur de l'attribut notey
     * @return Note*
     */
    Note* getCoupleNoteY() const  {return notey;}
    /**
     * @fn getLabel
     * @brief Accesseur de l'attribut label
     * @return QString
     */
    QString getLabel() const  {return label;}
    /**
     * @fn setLabel
     * @brief affectation de l'attribut label
     * @param QString l
     */
    void setLabel(QString l) {label=l;}
    /**
     * @fn getSymetric
     * @brief Accesseur de l'attribut symetric
     * @return bool
     */
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
    /**
     * @fn Relation
     * @brief Constructeur de la classe Relation
     * @param QString t
     * @param QString d
     */
    Relation(QString t, QString d):title(t), description(d),relations(new NotesCouple*[5]), nbCouple(0), nbMaxCouple(5){}
    /**
     * @fn getTitle
     * @brief Accesseur de l'attribut title
     * @return QString
     */
    const QString getTitle() const{return title;}
    /**
     * @fn setTitle
     * @brief Affectation de l'attribut title
     * @param QString t
     */
    void setTitle(QString t){title=t;}
    /**
     * @fn setDescription
     * @brief Affectation de l'attribut description
     * @param QString d
     */
    void setDescription(QString d){description=d;}

    NotesCouple& getNewCoupleRelation(Note* n1, Note* n2, QString label=0, bool s=false);
    /**
     * @fn getDescription
     * @brief Accesseur de l'attribut description
     * @return QString
     */
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
        /**
         * @fn Iterator
         * @brief Constructeur de la classe Iterator
         * @param NotesCouples** t
         * @param unsigned int n
         */
        Iterator(NotesCouple** t, unsigned int n):tab(t), nb(n), index(0){}
        friend class Relation;
    public:
        /**
         * @fn next
         * @brief Incrémentation de l'itérateur
         */
        void next(){
            if (index==nb) throw NotesException("incrémentation invalide");
            index++;
        }
        /**
         * @fn isDone
         * @brief Vérifie si on a terminé d'itérer
         * @return bool
         */
        bool isDone()const {return nb==index;}
        /**
         * @fn current
         * @brief Renvoi l'élément courant
         * @return NotesCouples&
         */
        NotesCouple& current() const {return *tab[index];}
    };
    /**
     * @fn getIterator
     * @brief Permet d'accéder à l'itérateur
     * @return Iterator
     */
    Iterator getIterator(){
        return Iterator(relations, nbCouple);
    }

    void displayCoupleRelation(Note *n1, Note *n2)const;
};



#endif // RELATION_H
