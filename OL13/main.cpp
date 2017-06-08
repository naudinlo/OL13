//
//  main.cpp
//  OL12P
//
//  Created by Louise Naudin on 11/05/2017.
//  Copyright © 2017 LNA. All rights reserved.
//

#include "QInclude.h"
//#include "include.h"
#include "notes.h"
#include "relations.h"
#include "interface.h"
#include <list>

void creation(){
//    NotesManager manager;
//    NotesManager& manager=NotesManager::getInstance();
    NotesManager* m1=NotesManager::getInstance();

    Article& a1=m1->getNewArticle("article_1","a_title_1","a_text_1");
    Article& a2=m1->getNewArticle("article_2","a_title_2","a_text_2");

    Task& t1=m1->getNewTask("task_1","tasktitle1","action1",ENUM::Pending,5);
    Task& t2=m1->getNewTask("task_2", "tasktitle2","action2",ENUM::Pending);
    t2.setPriority(10);

    QString link("newlink");
    //Recording& r1=m1->getNewRecording("r1", "recordingtitle1", "description1", ENUM::Audio, link);
    //Recording& r2=m1->getNewRecording("r2", "recordingtitle2", "description2", ENUM::Image, link);

    //a1.display(std::cout);

}

//Cette fonction ne marche pas bien (exemple quand deleteNote ou empty trash)
void displayAllNote(){
    std::cout<<"\n*=== ALL NOTES ===*\n";
    NotesManager* m=NotesManager::getInstance();

    for(NotesManager::Iterator it=m->getIterator(); !it.isDone(); it.next()){
        it.current().display();
    };
}

//exemple quand deleteNote ou empty trash
//Quand relation tout juste supprimée, l'affiche quand meme
void displayAllRelation(){
    std::cout<<"\n*=== ALL RELATIONS ===*\n";
    RelationManager& rm=RelationManager::getInstance();
    for(RelationManager::Iterator it=rm.getIterator(); !it.isDone(); it.next()){
//        std::cout<<it.current()<<"\n";
        std::cout<<"\n- "<<it.current().getTitle().toStdString();
        std::cout<<" description : "<<it.current().getDescription().toStdString()<<std::endl;
        it.current().displayRelation();
    };
}


void capture_ref_essai(){
//    QRegExp rx("(\\d+)");
//    REGEX : \\ref\{\w+\}
    QRegExp rx("\\w+");
//    QRegExp rx("\\\\ref\{\\w+\}");
//    QString str = "Offsets: 12 14 99 231 7";
    QString str = "coucou c'est que \ref{a1} et une autre ref vers \ref{supertache112} ";
    QStringList list;
    int pos = 0;
    cout<<"coucou\n";

    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(1);
        cout<<rx.cap(1).toStdString()<<"\n";
        pos += rx.matchedLength();
        cout<<pos<<"\n";
        cout<<" +1 \n";
    }
    // list: ["12", "14", "99", "231", "7"]
//    for (unsigned int i=0; i<list.length(); i++){
//        cout<<list(i);
//    }
}

void relation(){
    NotesManager* nm=NotesManager::getInstance();

    Article& a1=nm->getNewArticle("article_1","a_title_1","a_text_1");
    Article& a2=nm->getNewArticle("article_2","a_title_2","a_text_2");

    Task& t1=nm->getNewTask("task_1","tasktitle1","action1",ENUM::Pending,5);
    Task& t2=nm->getNewTask("task_2", "tasktitle2","action2",ENUM::Pending);
    t2.setPriority(10);

    displayAllNote();

    RelationManager& rm=RelationManager::getInstance();

    Relation& rel1=rm.getNewRelation("titreRelation1", "descriptionRelation1");
    Relation& rel2=rm.getNewRelation("tRelation2", "dRelation2");

//    Note& r1cpy=nm->editNote("r1");
//    r1cpy.setTitle("COPYrecording1");

    displayAllRelation();

    //BUG ICI

    Note& n1=nm->getNote("task_1");
    Note& n2=nm->getNote("task_2");
    Note& n3=nm->getNote("article_1");
    Note& n4=nm->getNote("article_2");

    std::cout<<"je suis là5\n";

    const QString& st1=t1.getId();
    nm->deleteNote(st1);

    n2.setNewRef(&n1);
    n1.setNewRef(&n2);

    nm->deleteNote("article_1");
    nm->deleteNote("article_2");
    displayAllNote();

    nm->emptyTrash();

    //ATTENTION : IL FAUT FREE LE TABLEAU DE REF
    nm->deleteNote("task_2");

//    nm->deleteNote("r1");
    nm->deleteNote("r2");

    displayAllNote();

    //Refuse de vider task 2. Pq ?
    nm->emptyTrash();
    displayAllNote();

    //Vider task 2 seulement ici. Pq ?
    nm->emptyTrash();
    displayAllNote();
}

int PROGRAMME(int argc,char *argv[])
{
    // UTF-8 Encoding
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    interface Fenprincipale;
    Fenprincipale.showMaximized();

    return app.exec();
}

void test_list()
{
   list<int> a;
   a.push_front(13);
   a.push_front(14);
   list<int>::iterator it;
   for(it=a.begin(); it!=a.end(); it++) cout<<*it<<endl;
}


void fct(){
    /*
    * try {
           creation(); // cette ligne peut Ítre mise en commentaire aprËs la 1Ëre exÈcution
//            displayAllNote();
           relation();
//            displayAllNote();
//            displayAllRelation();
       }
       catch(NotesException& e){
           std::cout<<e.getinfo().toStdString()<<"\n";
       }
   */
//    capture_ref_essai();

   //std::cout<<NotesManager::getInstance()->updateId("hugues_59").toStdString();
   //PROGRAMME(argc,argv);
   /*Article* a= new Article("test","test","test");
   Article* b= new Article("test2","test2","test2");
   Task* c= new Task("testTask","testTask1","testTask de l'itérator",ENUM::OnGoing);
   Note* n2=a;
   Note* n3=b;
   Note* n4=c;
   n2->display();

   QList<Note*>* liste= new QList<Note*>;
   (*liste).push_front(n2);
   (*liste).push_front(n3);
   (*liste).push_back(n4);

   QList<Note*>::iterator it2;

   for(it2=liste->begin();it2!=liste->end();it2++) it2.operator *()->display();*/



   NotesManager* m=NotesManager::getInstance();
   m->getNewArticle("test","test1","test de l'itérator");
   m->getNewTask("testTask","testTask1","testTask de l'itérator",ENUM::OnGoing);
   m->getNewArticle("test2","test2","test2 de l'itérator");

   NotesManager::Iterator it=m->getIterator();
   cout<<it.current();
   while(!it.isDone()){
       QList<Note*>::iterator it3=(it.liste())->begin();
       it3.operator *()->display();
       it.next();
   }

}


int main(int argc, char * argv[]) {

    try {
//           creation(); // cette ligne peut Ítre mise en commentaire aprËs la 1Ëre exÈcution
//           displayAllNote();
           relation();
           displayAllNote();
           displayAllRelation();
       }
       catch(NotesException& e){
           std::cout<<e.getinfo().toStdString()<<"\n";
       }



    //fct();
//    UndoRedo();

//    PROGRAMME(argc,argv);
    //creation();
    return 0;
}
