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
    Recording& r1=m1->getNewRecording("r1", "recordingtitle1", "description1", ENUM::Audio, link);
    Recording& r2=m1->getNewRecording("r2", "recordingtitle2", "description2", ENUM::Image, link);

}

//Cette fonction ne marche pas bien (exemple quand deleteNote ou empty trash)
void afficheNote(){
    std::cout<<"\n=== ALL NOTES ===\n";
    NotesManager* m=NotesManager::getInstance();

    for(NotesManager::Iterator it=m->getIterator(); !it.isDone(); it.next()){
        it.current().display();
    };
}

//exemple quand deleteNote ou empty trash
//Quand relation tout juste supprimée, l'affiche quand meme
void afficheRelation(){
    std::cout<<"\n=== ALL RELATIONS ===\n";
    RelationManager& rm=RelationManager::getInstance();
    for(RelationManager::Iterator it=rm.getIterator(); !it.isDone(); it.next()){
//        std::cout<<it.current()<<"\n";
        std::cout<<"\n- "<<it.current().getTitle().toStdString();
        std::cout<<" description : "<<it.current().getDescription().toStdString()<<std::endl;
        it.current().afficheRelation();
    };
}


void relation(){
    RelationManager& rm=RelationManager::getInstance();
    NotesManager* nm=NotesManager::getInstance();

    Relation& rel1=rm.getNewRelation("titreRelation1", "descriptionRelation1");
    Relation& rel2=rm.getNewRelation("tRelation2", "dRelation2");

    afficheRelation();

    Note& t1=nm->getNote("task_1");
    Note& t2=nm->getNote("task_2");
    Note& r1=nm->getNote("r1");
    Note& r2=nm->getNote("r2");

    rel1.getNewCoupleRelation(&t1,&t2, "relation de tache");
    rel2.getNewCoupleRelation(&t1,&t2, "relation 2 de tache");
    std::cout<<"\n RELATION : ";
    rel1.displayRelation(&t1,&t2);

    rel2.getNewCoupleRelation(&r1,&r2, "relation de recording");
//    rel2.displayRelation(&r1,&r2);

    rel1.getNewCoupleRelation(&t1,&r2,"relation Sym",true);
    rel2.getNewCoupleRelation(&t1,&r2,"relation 2 Sym",true);

//    rel1.displayRelation(&t1,&r2);
//    rel2.displayRelation(&t1,&r2);

//    rel1.removeCoupleRelation(&t1,&t2);
    rm.deleteRelation("tRelation2");
//    const QString& st1=t1.getId();
//    nm->deleteNote(st1);
//    rel1.displayRelation(&t1,&t2);

    afficheRelation();

/*
    t1.setNewRef(&t2);
    r1.setNewRef(&r2);

    t1.setIsArchive(true);
    t1.display();
//    nm->deleteNote("task_1");

//    nm->emptyTrash();

    std::cout<<"\n OK note supprimée \n";

//    Note& nt1=nm->getNote("task_1");
//    nt1.display();
*/
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


int main(int argc, char * argv[]) {
    try {
            creation(); // cette ligne peut Ítre mise en commentaire aprËs la 1Ëre exÈcution
//            affiche();
            relation();
            afficheNote();
            afficheRelation();
        }
        catch(NotesException& e){
            std::cout<<e.getinfo().toStdString()<<"\n";
        }

    //PROGRAMME(argc,argv);
    return 0;
}
