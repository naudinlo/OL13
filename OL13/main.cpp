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
#include "interface.h"
/*
void test1(){
    std::cout << "Hello, World!\n";


    Article a1("a1","articletitle1","text1");
    std::cout<<a1;

    Task t1("t1","tasktitle1","action1",ENUM::Pending);
    Task t2("t2","tasktitle2","action2",ENUM::Pending, 5);

    TIME::Date d(10,03,2018);
    Task t3("t3","tasktitle3","action3",ENUM::OnGoing, d);
    Task t4("t4","tasktitle4","action4",ENUM::Completed, 5, d);

    std::cout<<t1;
    std::cout<<t2;
    std::cout<<t3;
    std::cout<<t4;

    Recording r1("r1", "recordingtitle1", "description1", ENUM::Audio);
    Recording r2("r2", "recordingtitle2", "description2", ENUM::Image);

    std::cout<<r1;
    std::cout<<r2;

    std::cout<<std::endl;
}
*/
int test2(int argc,char *argv[])
{
    // UTF-8 Encoding
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    interface Fenprincipale;
    Fenprincipale.showMaximized();


    return app.exec();

}

int main(int argc, char * argv[]) {
	//test1();
    test2(argc,argv);
    return 0;
}
