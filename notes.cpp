//
//  notes.cpp
//  OL12PROJET
//
//  Created by Louise Naudin on 11/05/2017.
//  Copyright © 2017 LNA. All rights reserved.
//

#include "notes.h"
#include "timing.h"
#include "function.h"
#include "include.h"



//====OPERATEUR AFFECATION, CONSTRUCTEUR DE RECOPIE

//Surcharge la méthode constructeur dans le cas nouvelle note B(A);
Note::Note(const Note& n):title(n.title), id(n.id+"_bis"){
//    std::ostream& f;
//    f<<lastmodif_date;
//    id=n.id+f;
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
Article::Article(const Article& a):Note(a), text(a.text){};

//Surcharge de l'opérateur = dans le cas nouvel article Article B=A;
Article& Article::operator=(const Article& a){
    if (this!=&a){  //empecher l'auto-affectation
        Note::operator=(a);
        text=a.text;
    }
    return *this;
};


//Surcharge la méthode constructeur dans le cas nouvelle task B(A);
Task::Task(const Task& t):Note(t), action(t.action),priority(t.priority),dueDate(t.dueDate),status(t.status){};

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
Recording::Recording(const Recording& r):Note(r),type(r.type),description(r.description){};

//Surcharge de l'opérateur = dans le cas nouveau recording B=A;
Recording& Recording::operator=(const Recording& r){
    if (this!=&r){  //empecher l'auto-affectation
        Recording::operator=(r);
        description=r.description;
        type=r.type;
    }
    return *this;
};


//====CONSTRUCTEUR

Note::Note(const std::string& i, const std::string& ti):id(i), title(ti), isArchive(false), isDeleted(false){
//    time_t theTime = time(NULL);
//    struct tm *aTime = localtime(&theTime);
//    TIME::Date t0(aTime->tm_mday,aTime->tm_mon + 1,aTime->tm_year + 1900);
//    creation_date=t0;
//    lastmodif_date=t0;
    creation_date=currentDate();
    lastmodif_date=creation_date;
}


Article::Article(const std::string& i, const std::string& ti, const std::string& te):Note(i,ti), text(te){}


Task::Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s):Note(i, ti), action(a), status(s){};  //Premier type de constructeur : les deux optionels oubliés
Task::Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s, unsigned int p):Note(i, ti), action(a), priority(p), status(s){}; //Deuxième type de constructeur : priorité ajoutée
Task::Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s, const TIME::Date d):Note(i, ti), action(a), dueDate(d), status(s){};  //Troisième type : dueDate ajoutée
Task::Task(const std::string& i, const std::string& ti, const std::string& a, ENUM::StatusType s, unsigned int p, const TIME::Date d):Note(i, ti), action(a), priority(p), dueDate(d), status(s){} //Quatrième type : prio et dueDate ajoutés

Recording::Recording(const std::string& i, const std::string& ti, const std::string& d, ENUM::RecordingType r):Note(i, ti), description(d), type(r){};



//====METHODE ET SURCHARGE

//toString pour display Article
std::string Article::toString() const {
    std::stringstream f;
    f<<"\n=== ARTICLE "<<getId()<<" ===\n";
    f<<"ID : "<<getId() <<" - Title : "<<getTitle()<<" - Text : "<<text<<"\nCreation Date : "<<getCreation_date()<<" - Last Modification Date : "<<getLastmodif_date()<<"\n";
    return f.str();
}

//toString pour display Task
std::string Task::toString() const {
    std::stringstream f;
    f<<"\n=== TASK "<<getId()<<" ===\n";
    f<<"ID : "<<getId() <<" - Title : "<<getTitle()<<" - Action : "<<action<<"\nCreation Date : "<<getCreation_date()<<" - Last Modification Date : "<<getLastmodif_date()<<"\nPriority :"<<priority<<" - Status : "<<status<<" - dueDate : "<<dueDate<<"\n";
    return f.str();
}

//toString pour display Recording
std::string Recording::toString() const {
    std::stringstream f;
    f<<"\n=== RECORDING "<<getId()<<" ===\n";
    f<<"ID : "<<getId() <<" - Title : "<<getTitle()<<" - Description : "<<description<<"\nCreation Date : "<<getCreation_date()<<" - Last Modification Date : "<<getLastmodif_date()<<"\nType :"<<type<<"\n";
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
