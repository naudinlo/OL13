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
#include "sstream"
//#include "include.h"



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
Recording::Recording(const Recording& r):Note(r),type(r.type),description(r.description.toPlainText()){};

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

Note::Note(const QString& i, const QString& ti):id(i), title(ti), isArchive(false), isDeleted(false){
//    time_t theTime = time(NULL);
//    struct tm *aTime = localtime(&theTime);
//    TIME::Date t0(aTime->tm_mday,aTime->tm_mon + 1,aTime->tm_year + 1900);
//    creation_date=t0;
//    lastmodif_date=t0;
    creation_date=currentDate();
    lastmodif_date=creation_date;
}


Article::Article(const QString& i, const QString& ti, const QString &te):Note(i,ti), text(te){}


Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s):Note(i, ti), action(a), status(s){};  //Premier type de constructeur : les deux optionels oubliés
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p):Note(i, ti), action(a), priority(p), status(s){}; //Deuxième type de constructeur : priorité ajoutée
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, const TIME::Date d):Note(i, ti), action(a), dueDate(d), status(s){};  //Troisième type : dueDate ajoutée
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p, const TIME::Date d):Note(i, ti), action(a), priority(p), dueDate(d), status(s){} //Quatrième type : prio et dueDate ajoutés

Recording::Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l):Note(i, ti), description(d), type(r), link(l){};



//====METHODE ET SURCHARGE

//toString pour display Article
std::__cxx11::string Article::toString()const {
    std::stringstream f;
    f<<"\n=== ARTICLE "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString() <<" - Title : "<<getTitle().toStdString()<<" - Text : "<<text.toPlainText().toStdString()<<"\nCreation Date : "<<getCreation_date()<<" - Last Modification Date : "<<getLastmodif_date()<<"\n";
    return f.str();
}

//toString pour display Task
std::__cxx11::string Task::toString() const {
    std::stringstream f;
    f<<"\n=== TASK "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString() <<" - Title : "<<getTitle().toStdString()<<" - Action : "<<action.toStdString()<<"\nCreation Date : "<<getCreation_date()<<" - Last Modification Date : "<<getLastmodif_date()<<"\nPriority :"<<priority;
    f<<" - Status : ";
    switch(type){
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
    Date d;
    if(dueDate==d){f<<" - No due date.";}
    else {f<<" - Due date : "<<dueDate;}
    f<<"\n";
    return f.str();
}

//toString pour display Recording
std::__cxx11::string Recording::toString() const {
    std::stringstream f;
    f<<"\n=== RECORDING "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString() <<" - Title : "<<getTitle().toStdString()<<" - Description : "<<description.toPlainText().toStdString()<<"\nCreation Date : "<<getCreation_date()<<" - Last Modification Date : "<<getLastmodif_date()<<"\n";
    f<<"Type : ";
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
