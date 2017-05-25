//
//  notes.cpp
//  OL12PROJET
//
//  Created by Louise Naudin on 11/05/2017.
//  Copyright © 2017 LNA. All rights reserved.
//

#include "notes.h"
#include "sstream"
//#include "include.h"



//====OPERATEUR AFFECATION, CONSTRUCTEUR DE RECOPIE

//Surcharge la méthode constructeur dans le cas nouvelle note B(A);
Note::Note(const Note& n):id(n.id+lastmodif_date.toString("dd.MM")),title(n.title),lastmodif_date(QDateTime::currentDateTime()){
};

//Surcharge de l'opérateur = dans le cas nouvelle note B=A;
Note& Note::operator=(const Note& n){
    if (this!=&n){  //empecher l'auto-affectation
        title=n.title;
        //LNA ERREUR ICI
        //id=n.id+"_bis";
    }
    return *this;
};


//Surcharge la méthode constructeur dans le cas nouvel article Article B(A);
Article::Article(const Article& a):Note(a), text(a.text.toPlainText()){};

//Surcharge de l'opérateur = dans le cas nouvel article Article B=A;
Article& Article::operator=(const Article& a){
    if (this!=&a){  //empecher l'auto-affectation
        Note::operator=(a);
        text.setPlainText(a.text.toPlainText());
    }
    return *this;
};


//Surcharge la méthode constructeur dans le cas nouvelle task B(A);
Task::Task(const Task& t):Note(t), action(t.action),status(t.status),priority(t.priority),dueDate(t.dueDate){};

//Surcharge de l'opérateur = dans le cas nouvelle task B=A;
Task& Task::operator=(const Task& t){
    if (this!=&t){  //empecher l'auto-affectation
        Note::operator=(t);
        action=t.action;
        priority=t.priority;
        dueDate=t.dueDate;
        status=t.status;
    }
    return *this;
};

//Surcharge la méthode constructeur dans le cas nouveau recording B(A);
Recording::Recording(const Recording& r):Note(r),description(r.description.toPlainText()),type(r.type){};

//Surcharge de l'opérateur = dans le cas nouveau recording B=A;
Recording& Recording::operator=(const Recording& r){
    if (this!=&r){  //empecher l'auto-affectation
        Recording::operator=(r);
        description.setPlainText(r.description.toPlainText());
        type=r.type;
    }
    return *this;
};


//====CONSTRUCTEUR

Note::Note(const QString& i, const QString& ti):id(i), title(ti), isArchive(false), isDeleted(false), references(new Note*[5]), nbRef(0), nbMaxRef(5),nbIsRef(0){
//    time_t theTime = time(NULL);
//    struct tm *aTime = localtime(&theTime);
//    TIME::Date t0(aTime->tm_mday,aTime->tm_mon + 1,aTime->tm_year + 1900);
//    creation_date=t0;
//    lastmodif_date=t0;
    creation_date=QDateTime::currentDateTime();
    lastmodif_date=creation_date;
}


Article::Article(const QString& i, const QString& ti, const QString &te):Note(i,ti), text(te){}


Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s):Note(i, ti), action(a), status(s), priority(-1){};  //Premier type de constructeur : les deux optionels oubliés
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p):Note(i, ti), action(a), status(s), priority(p){}; //Deuxième type de constructeur : priorité ajoutée
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, const QDateTime d):Note(i, ti), action(a), status(s), priority(-1), dueDate(d){};  //Troisième type : dueDate ajoutée
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d):Note(i, ti), action(a), status(s), priority(p), dueDate(d){} //Quatrième type : prio et dueDate ajoutés


Recording::Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l):Note(i, ti), description(d), type(r), link(l){};



//====METHODE ET SURCHARGE



//toString pour display Article
std::string Article::toString()const {
    std::stringstream f;
    f<<"\n=== ARTICLE "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString()<<"\n - Title : "<<getTitle().toStdString()<<"\n - Text : "<<text.toPlainText().toStdString()<<"\n - Creation date : "<<getCreation_date().toString("dd.MM.yyyy").toStdString()<<"\n - Last modification date : "<<getLastmodif_date().toString("dd.MM.yyyy").toStdString()<<"\n";

    //Affichage des references
    f<<"\n - Reference :";
    if(getNbRef()==0) f<<" none";
    for(unsigned int i=0; i<getNbRef(); i++){
        f<<"\n   - "<<getReferenceInt(i).getId().toStdString()<<" "<<getReferenceInt(i).getTitle().toStdString();
    }
    f<<"\n - Article reférencé par "<<getNbIsRef()<<" note(s).";

    if (getIsArchive()) f<<"\n - Note Archivée.";
    if (getIsDeleted()) f<<"\n - Note Supprimée.";

    f<<"\n";
    return f.str();
}

//toString pour display Task
std::string Task::toString() const {
    std::stringstream f;
    f<<"\n=== TASK "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString() <<"\n - Title : "<<getTitle().toStdString()<<"\n - Action : "<<action.toStdString()<<"\n - Creation date : "<<getCreation_date().toString("dd.MM.yyyy").toStdString()<<"\n - Last modification date : "<<getLastmodif_date().toString("dd.MM.yyyy").toStdString();
    if(priority!=-1)
        f<<"\n - Priority : "<<priority;
    else
        f<<"\n - No Priority";
    f<<"\n - Status : ";
    switch(status){
    case 0 :
        f<<"Pending";
        break;
    case 1 :
        f<<"On going";
        break;
    case 2 :
        f<<"Completed";
        break;
    default :
        f<<"None";
    }

    if(dueDate.isNull()){f<<"\n - No due date.";}
    else {f<<"\n - Due date : "<<dueDate.toString("dd.MM.yyyy").toStdString();}


    //Affichage des references
    f<<"\n - Reference :";
    if(getNbRef()==0) f<<" none";
    for(unsigned int i=0; i<getNbRef(); i++){
        f<<"\n   - "<<getReferenceInt(i).getId().toStdString()<<" "<<getReferenceInt(i).getTitle().toStdString();
    }
    f<<"\n - Tâche reférencée par "<<getNbIsRef()<<" note(s).";


    if (getIsArchive()) f<<"\n - Note Archivée.";
    if (getIsDeleted()) f<<"\n - Note Supprimée.";

    f<<"\n";
    return f.str();
}

//toString pour display Recording
std::string Recording::toString() const {
    std::stringstream f;
    f<<"\n=== RECORDING "<<getId().toStdString()<<" ===\n";
    f<<"\n - ID : "<<getId().toStdString() <<"\n - Title : "<<getTitle().toStdString()<<"\n - Description : "<<description.toPlainText().toStdString()<<"\n - Creation date : "<<getCreation_date().toString("dd.MM.yyyy").toStdString()<<"\n - Last modification date : "<<getLastmodif_date().toString("dd.MM.yyyy").toStdString();
    f<<"\n - Type : ";
    switch(type){
    case 0 :
        f<<"Image";
        break;
    case 1 :
        f<<"Audio";
        break;
    case 2 :
        f<<"Video";
        break;
    }

    //Affichage des references
    f<<"\n - Reference :";
    if(getNbRef()==0) f<<" none";
    for(unsigned int i=0; i<getNbRef(); i++){
        f<<"\n   - "<<getReferenceInt(i).getId().toStdString()<<" "<<getReferenceInt(i).getTitle().toStdString();
    }
    f<<"\n - Enregistrement reférencé par "<<getNbIsRef()<<" note(s).";

    if (getIsArchive()) f<<"\n - Note Archivée.";
    if (getIsDeleted()) f<<"\n - Note Supprimée.";

    f<<"\n";
    return f.str();
}

//Surcharge opérateur <<
std::ostream& operator<<(std::ostream& f, const Article& a){
    a.display(f);
    return f;
}

//Surcharge opérateur <<
std::ostream& operator<<(std::ostream& f, const Task& t){
    t.display(f);
    return f;
}

//Surcharge opérateur <<
std::ostream& operator<<(std::ostream& f, const Recording& r){
    r.display(f);
    return f;
}

//Retourner directement le statut de int à string
QString getStatustoStr(ENUM::StatusType status) {
    QString statusName[] = {"Pending", "OnGoing", "Completed"};
    return statusName[status];
}

//Retourner directement le recording de int à string
QString getRecordingtoStr(ENUM::StatusType recording) {
    QString recordingName[] = {"Image", "Audio", "Video"};
    return recordingName[recording];
}



//====REFERENCE

Note& Note::setNewRef(Note* n){
    for(unsigned int i=0; i<nbRef; i++){
        if (references[i]->getId()==n->getId()){
            throw NotesException("erreur, ID déjà existant");
        }
    }
    addReference(n);
    //Incrémente de un le nombre de note qui référence this
    n->setNbIsRef(n->getNbIsRef()+1);
    return *n;
};

void Note::addReference(Note* n){
    if (nbRef==nbMaxRef){
        //besoin en grandissement
        Note** newtab=references;
        for(unsigned int i=0; i<nbRef; i++){
            newtab[i]=references[i];
            //mise à jour des attributs
        }
        nbMaxRef+=5;
        Note ** old=references;
        references=newtab;
        delete[] old;
    }
    references[nbRef]=n;
    nbRef++;
};

Note& Note::getReference(Note* n)const{
    for(unsigned int i=0; i<nbRef; i++){
        if (references[i]->getId()==n->id){
            return (*references[i]);
        }
    }
    throw NotesException("erreur, ID inexistant");
};


Note& Note::getReferenceInt(unsigned int i) const{
  return (*references[i]);
};

