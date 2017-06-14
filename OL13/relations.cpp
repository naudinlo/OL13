/**
 * \file      relations.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définitions des fonctions déclarées dans le relations.h
 *
 * \details
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
 *             L'ensemble des méthodes de ces classes sont explicitées dans la suite du fichier.
 *
 */


#include "relations.h"
#include "sstream"


/**
 * \fn        std::string Relation::displayRelation()
 * \brief     Affiche une relation et l'ensemble des couples de notes qui en font parti
 */
std::string Relation::displayRelation(){
    std::stringstream f;
    f<<"\n"<<this->getTitle().toStdString()<<" "<<this->getDescription().toStdString()<<endl;
    for(Relation::Iterator it=this->getIterator(); !it.isDone(); it.next()){
        f<<"\n  - Note "<<it.current().getCoupleNoteX()->getId().toStdString();
        f<<" vers Note "<<it.current().getCoupleNoteY()->getId().toStdString();
        if (it.current().getSymetric()) f<<"  de façon symétrique.";
        if (it.current().getLabel()!=0) f<<"\n    Label : "<<it.current().getLabel().toStdString();
    };
    f<<std::endl;
    return f.str();
}

/**
 * \fn        NotesCouple &Relation::getNewCoupleRelation(Note* n1,  Note* n2, QString label, bool s)
 * \brief     Créer un couple de note dans une relation
 * \param     Note* n1                  Note X du couple dans la relation
 *            Note* n2                  Note Y du couple dans la relation
 *            QString label             Label du couple dans la relation
 *            bool s                    Symétrie du couple dans la relation
 */
NotesCouple &Relation::getNewCoupleRelation(Note* n1,  Note* n2, QString label, bool s) {
        NotesCouple* nc= new NotesCouple(n1,n2,label,s);
        for(unsigned int i=0; i<nbCouple; i++){
            if ((relations[i]->getCoupleNoteX()==n1 && relations[i]->getCoupleNoteY()==n2) || (relations[i]->getCoupleNoteX()==n2 && relations[i]->getCoupleNoteY()==n1)){
                throw NotesException("erreur, couple déjà en relation");
            }
        }
        addCoupleRelation(nc);
        //Cas où la relation est symétrique
        if (s) {
            NotesCouple* ncsym= new NotesCouple(n2,n1,label,s);
            addCoupleRelation(ncsym);
        }
        return *nc;
}

/**
 * \fn        void Relation::addCoupleRelation(NotesCouple* nc)
 * \brief     Ajoute un couple de note à un tableau de couple de note d'une relation
 * \param     NotesCouple* nc             Couple de note à ajouter à la relation
 */
void Relation::addCoupleRelation(NotesCouple* nc){
    if (nbCouple==nbMaxCouple){
        //besoin en grandissement
        NotesCouple** newtab=relations;
        for(unsigned int i=0; i<nbCouple; i++){
            newtab[i]=relations[i];
            //mise à jour des attributs
        }
        nbMaxCouple+=5;
        NotesCouple ** old=relations;
        relations=newtab;
        delete[] old;
    }
    relations[nbCouple]=nc;
    nbCouple++;
}

/**
 * \fn        NotesCouple* Relation::getCoupleRelation(Note *n1, Note *n2)const
 * \brief     Retourne un pointeur sur un couple d'une référence dont les deux notes sont passées en paramètre
 * \param     Note* n1             Note X du couple de la relation a retourner
 * \param     Note* n2             Note Y du couple de la relation a retourner
 */
NotesCouple* Relation::getCoupleRelation(Note *n1, Note *n2)const{
    for(unsigned int i=0; i<nbCouple; i++){
        if (relations[i]->getCoupleNoteX()->getId()==n1->getId() && relations[i]->getCoupleNoteY()->getId()==n2->getId()){
            return (relations[i]);
        }
    }
    return 0;
    throw NotesException("erreur, impossible to the relation from this couple, relation de notes inexistante");
}


/**
 * \fn        void Relation::displayCoupleRelation(Note *n1, Note *n2)const
 * \brief     Affiche un couple dans une relation
 * \param     Note* n1             Note X du couple de la relation a afficher
 * \param     Note* n2             Note Y du couple de la relation a afficher
 */
void Relation::displayCoupleRelation(Note *n1, Note *n2)const{
    const NotesCouple* nc=getCoupleRelation(n1,n2);
    if (nc!=0){
        std::cout<<"\n=== RELATION "<<this->getTitle().toStdString()<<" ===\n";
        std::cout<<"\n - Description : "<<this->getDescription().toStdString();
        std::cout<<"\n - Note "<<nc->getCoupleNoteX()->getId().toStdString();
        std::cout<<" est en relation avec Note "<<nc->getCoupleNoteY()->getId().toStdString();
        if (nc->getLabel()!=0) std::cout<<"\n - Label : "<<nc->getLabel().toStdString();
        std::cout<<"\n - Relation symétrique : ";
        if (nc->getSymetric()) std::cout<<"Yes";
        else std::cout<<"No";
        std::cout<<"\n";
    }
    else{
        std::cout<<"\n Erreur : Il n'existe pas de relation entre "<<n1->getTitle().toStdString()<<" et "<<n2->getTitle().toStdString()<<std::endl;;
    }
}



/**
 * \fn        void Relation::removeCoupleRelation(Note* n1, Note* n2)
 * \brief     Supprime un couple de note d'une relation
 * \details   Si le couple demandé est symétrique, le deux couples créés par ces notes sont supprimés.
 * \param     Note* n1             Note X du couple a supprimer de la relation
 * \param     Note* n2             Note Y du couple a supprimer de la relation
 */
void Relation::removeCoupleRelation(Note* n1, Note* n2){
    unsigned int i=0;
    while(i<nbCouple && relations[i]->getCoupleNoteX()->getId()!=n1->getId() && relations[i]->getCoupleNoteY()->getId()!=n2->getId()){
        i++;
    }
    if (i==nbCouple) throw NotesException("erreur : Aucune relation entre ses deux notes");
    bool relSym=relations[i]->getSymetric();
    delete relations[i];
    relations[i]=relations[--nbCouple];
    if (relSym){
        i=0;
        while(i<nbCouple && relations[i]->getCoupleNoteX()->getId()!=n2->getId() && relations[i]->getCoupleNoteY()->getId()!=n1->getId()){
            i++;
        }
        if (i==nbCouple) throw NotesException("erreur : Aucune relation entre ses deux notes");
        delete relations[i];
        relations[i]=relations[--nbCouple];
    }
}


/**
 * \fn        void Relation::removeNoteRelation(Note* n1)
 * \brief     Supprime une note d'une relation
 * \details   Si une note passée en paramètre appartient à un couple présent au sein de la relation this,
 *              le couple est supprimée de la relation.
 * \param     Note* n1             Note a supprimer de la relation
 */
void Relation::removeNoteRelation(Note* n1){
    for(unsigned int i=0; i<nbCouple; i++){
        if (relations[i]->getCoupleNoteX()->getId()==n1->getId() || relations[i]->getCoupleNoteY()->getId()==n1->getId()){
            delete relations[i];
            relations[i]=relations[--nbCouple];
            i--;
        }
    }
}


