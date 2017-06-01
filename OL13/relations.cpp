#include "relations.h"
#include "sstream"


//A FAIRE
std::string Relation::displayRelation(){
//    RelationManager& rm=RelationManager::getInstance();
    std::stringstream f;
    for(Relation::Iterator it=this->getIterator(); !it.isDone(); it.next()){
        f<<"  - Note "<<it.current().getCoupleNoteX()->getId().toStdString();
        f<<" vers Note "<<it.current().getCoupleNoteY()->getId().toStdString();
        if (it.current().getSymetric()) f<<"  de façon symétrique.";
        if (it.current().getLabel()!=0) f<<"\n    Label : "<<it.current().getLabel().toStdString();
        f<<std::endl;
    };
    return f.str();
}


NotesCouple &Relation::getNewCoupleRelation(Note* n1,  Note* n2, QString label, bool s) {
//    if (n1!=n2){
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
//    }
//    else return 0;
}

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

NotesCouple* Relation::getCoupleRelation(Note *n1, Note *n2) const {
    for(unsigned int i=0; i<nbCouple; i++){
        if (relations[i]->getCoupleNoteX()->getId()==n1->getId() && relations[i]->getCoupleNoteY()->getId()==n2->getId()){
            return (relations[i]);
        }
    }
    return 0;
    throw NotesException("erreur, impossible to the relation from this couple, relation de notes inexistante");
}

void Relation::displayCoupleRelation(Note *n1, Note *n2)const{
    const NotesCouple* nc=getCoupleRelation(n1,n2);
    if (nc!=0){
        std::cout<<"\n=== RELATION "<<this->getTitle().toStdString()<<" ===\n";
        std::cout<<"\n - Description : "<<this->getDescription().toStdString();
        std::cout<<"\n - Note "<<nc->getCoupleNoteX()->getTitle().toStdString();
        std::cout<<" est en relation avec Note "<<nc->getCoupleNoteY()->getTitle().toStdString();
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


void Relation::removeNoteRelation(Note* n1){
    for(unsigned int i=0; i<nbCouple; i++){
        if (relations[i]->getCoupleNoteX()->getId()==n1->getId() || relations[i]->getCoupleNoteY()->getId()==n1->getId()){
            delete relations[i];
            relations[i]=relations[--nbCouple];
            i--;
        }
    }
}




/*
void Relation::removeCoupleRelation(Note* n1, Note* n2){
    unsigned int i;
      while(i<nbCouple && relations[i]->getCoupleNoteX()->getId()!=n1->getId() && relations[i]->getCoupleNoteY()->getId()!=n2->getId()){
          i++;
      }
      if (i==nbCouple) throw NotesException("erreur : Aucune relation entre ses deux notes");
      delete relations[i];
      relations[i]=relations[--nbCouple];
}
*/


//Relation::~Relation(){
//    for(unsigned int i=0; i<nbCouple; i++){
//        delete rel[i];
//    }
//    delete[] articles;
//    nbArticles=0;
//    nbMaxArticles=0;
//    articles=nullptr;
//}

/*
 std::string Relation::toStringRel(Note *n1, Note *n2)const{
    std::stringstream f;
    const NotesCouple* nc=getCoupleRelation(n1,n2);
    if (nc!=nullptr){
        f<<"\n=== RELATION "<<this->getTitle().toStdString()<<" ===\n";
        f<<"\n - Description : "<<this->getDescription().toStdString();
        f<<"\n - Note "<<nc->getCoupleNoteX()->getTitle().toStdString();
        f<<" est en relation avec Note "<<nc->getCoupleNoteY()->getTitle().toStdString();
        f<<"\n";
    }
    else { throw "Erreur de display relation couple";}
};
*/
