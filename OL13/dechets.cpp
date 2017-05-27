#include "dechets.h"

/*_____ DECHETS DU MAIN _______*/


void test1(){
    std::cout << "Hello, World!\n";

//    NotesManager nm;
    NotesManager& manager=NotesManager::getInstance();
//    NotesManager* nm=NotesManager::getInstance();

    std::cout<<"point 1";

    Article& a1=manager.getNewNote("article_1",text1);

    Article a1("a1","articletitle1","text1");
    Article& a1("a1","articletitle1","text1");

    std::cout<<a1;

    Task t1("t1","tasktitle1","action1",ENUM::Pending);
    Task t2("t2","tasktitle2","action2",ENUM::Pending, 5);

    nm->createNote(&a1);
    nm->createNote(&t1);
    nm->createNote(&t2);

    QString link("newlink");
    Recording r1("r1", "recordingtitle1", "description1", ENUM::Audio, link);
    Recording r2("r2", "recordingtitle2", "description2", ENUM::Image, link);

    nm->createNote(&r1);
    nm->createNote(&r2);

    std::cout<<r1;
    std::cout<<r2;

//    RelationManager rm;
    RelationManager* rm=RelationManager::getInstance();


    Relation rel("titreRelation","descriptionRelation");
    Relation rel2("tRelation2","dRelation2");

    rm.createRelation(&rel);
    rm.createRelation(&rel2);

//    rel.getNewCoupleRelation(&pt1,&pt2, "relation de tache");
//    rel2.getNewCoupleRelation(&pt1,&pt2, "relation 2 de tache");
    rel.getNewCoupleRelation(&t1,&t2, "relation de tache");
    rel2.getNewCoupleRelation(&t1,&t2, "relation 2 de tache");


//    std::cout<<"\n RELATION : ";
//    //rel.displayRelation(&pt1,&pt2);

//    rel.getNewCoupleRelation(&pr1,&pr2, "relation de recording");
    //rel.displayRelation(&pr1,&pr2);

//    rel.getNewCoupleRelation(&pt1,&pr2,"relation Sym",true);
//    rel2.getNewCoupleRelation(&pt1,&pr2,"relation 2 Sym",true);
    rel.getNewCoupleRelation(&t1,&r2,"relation Sym",true);
    rel2.getNewCoupleRelation(&t1,&r2,"relation 2 Sym",true);

//    rel.displayRelation(&pt1,&pr2);
    rel.displayRelation(&t1,&r2);

//    rel.removeCoupleRelation(&pt1,&pr2);
//    rel.displayRelation(&pt1,&pr2); //Pourquoi ne supprime pas directement les deux ?

//    rel.removeCoupleRelation(&pt1,&pt2);
    nm->deleteNote(&t1);
    //rel.displayRelation(&pt1,&pr2);
    rel.displayRelation(&t1,&r2);

//    pt1.setNewRef(&pt2);
//    pr1.setNewRef(&pr2);
    t1.setNewRef(&t2);
    r1.setNewRef(&r2);

//    pt1.display();
//    pr1.display();

//    pt2.display();
//    pr2.display();

//    //Il faut un relation manager
//    rel.removeNoteRelation(&pt1);
//    rel.displayRelation(&pt1,&pt2);

//    pt1.setIsArchive(true);
//    pt1.display();

    //Il faut un relation manager
    std::cout<<"point 1";

    rel.removeNoteRelation(&t1);
    rel.displayRelation(&t1,&t2);

    std::cout<<"point 3";


    t1.setIsArchive(true);
    t1.display();

    std::cout<<"point 5";


    std::cout<<endl;
    std::cout<<endl;

}



void creation(){
//    NotesManager manager;
    std::cout<<"bug 1';";
    NotesManager* manager=NotesManager::getInstance();

    std::cout<<"bug 2';";

    Article a1("a1","articletitle1","text1");

    std::cout<<"bug 3';";

    manager->createNote(&a1);

    Task t1("t1","tasktitle1","action1",ENUM::Pending);
    Task t2("t2","tasktitle2","action2",ENUM::Pending, 5);
    manager->createNote(&t1);
    manager->createNote(&t2);

    QString link("newlink");
    std::cout<<"avant recording";
    Recording r1("r1", "recordingtitle1", "description1", ENUM::Audio, link);
    Recording r2("r2", "recordingtitle2", "description2", ENUM::Image, link);
    manager->createNote(&r1);
    std::cout<<"premier recording OK \n";

    manager->createNote(&r2);
    std::cout<<"apres recording";

    std::cout<<"bug 4';";

}

