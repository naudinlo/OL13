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


void test1(){
    std::cout << "Hello, World!\n";


    Article a1("a1","articletitle1","text1");
    std::cout<<a1;

    Task t1("t1","tasktitle1","action1",ENUM::Pending);
    Task t2("t2","tasktitle2","action2",ENUM::Pending, 5);

    QDate d;
    d.addDays(10);
    d.addMonths(4);
    d.addYears(2010);
    const QDate dt(d);
//    Task t3("t3","tasktitle3","action3",ENUM::OnGoing, d);
//    Task t4("t4","tasktitle4","action4",ENUM::Completed, 5, d);

    std::cout<<t1;
    std::cout<<t2;
//    std::cout<<t3;
//    std::cout<<t4;

    QString link("newlink");
    Recording r1("r1", "recordingtitle1", "description1", ENUM::Audio, link);
    Recording r2("r2", "recordingtitle2", "description2", ENUM::Image, link);

//    Task q1("t1","tasktitle1","action1",0);
//    Task q2("t2","tasktitle2","action2",1, 5);

    Task& pt1=t1;
    Task& pt2=t2;
    Recording& pr1=r1;
    Recording& pr2=r2;

    std::cout<<r1;
    std::cout<<r2;

    std::cout<<std::endl;

    NotesCouple nc1(&pt1,&pt2, "anotherNewRel");

    std::cout<<"NC1 : ";
    nc1.getCoupleNoteX()->display();
    nc1.getCoupleNoteY()->display();

    std::cout<<endl;

    NotesCouple nc2(&pr1,&pr2, "newREl");

    std::cout<<"NC2 : ";
    nc2.getCoupleNoteX()->display();
    nc2.getCoupleNoteY()->display();

    Relation rel("titreRelation","descriptionRelation");
    rel.getNewCoupleRelation(&pt1,&pt2, "relation de tache");

    std::cout<<"\n RELATION : ";
    rel.displayRelation(&pt1,&pt2);

    rel.getNewCoupleRelation(&pr1,&pr2, "relation de recording");
    rel.displayRelation(&pr1,&pr2);

    rel.getNewCoupleRelation(&pt1,&pr2,"relation Sym",true);
    rel.displayRelation(&pt1,&pr2);

    rel.removeCoupleRelation(&pt1,&pr2);
    rel.displayRelation(&pt1,&pr2); //Pourquoi ne supprime pas directement les deux ?

    rel.removeCoupleRelation(&pt1,&pt2);
    rel.displayRelation(&pt1,&pr2);
    rel.displayRelation(&pt1,&pt2);

    std::cout<<endl;
    std::cout<<endl;

}
/*
int test2(int argc,char *argv[])
{
    // UTF-8 Encoding
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    interface Fenprincipale;
    Fenprincipale.showMaximized();

    return app.exec();

}
*/

int main(int argc, char * argv[]) {
    test1();
    //test2(argc,argv);
    return 0;
}
