/**
 * \file      main.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     //Bref
 *
 * \details  //Détail
 *
 */


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

//AFFICHE LES DERNIÈRES VERSIONS DE TOUTES LES NOTES
//Cette fonction ne marche pas bien (exemple quand deleteNote ou empty trash)
void displayAllNote(){
    std::cout<<"\n*=== ALL NOTES ===*\n";
    NotesManager* m=NotesManager::getInstance();

    for(NotesManager::Iterator it=m->getIterator(); !it.isDone(); it.next()){
        it.current().display();
    };
}


void displayAllVersion(){
    NotesManager* m=NotesManager::getInstance();
    std::cout<<"\n*=== ALL VERSIONS ALL NOTES ===*\n";
    NotesManager::Iterator itNote=m->getIterator();
    while(!itNote.isDone()){
        if(!itNote.liste()->isEmpty()){
            cout<<endl<<"// Versions de la note : "<<itNote.current().getId().toStdString()<<" \\\\"<<endl;
            QList<Note*>::iterator itVersion=(itNote.liste())->begin();
            unsigned int i=0;
            while (itVersion!=itNote.liste()->end()) {
                cout<<endl<<"--- Version "<<i++<<" ---";
                itVersion.operator *()->display();
                itVersion++;
            }
        }
        itNote.next();
    }
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
    RelationManager& rm=RelationManager::getInstance();
    NotesManager* nm=NotesManager::getInstance();

    Relation& rel1=rm.getNewRelation("titreRelation1", "descriptionRelation1");
    Relation& rel2=rm.getNewRelation("tRelation2", "dRelation2");

//    displayAllRelation();

    Note& t1=nm->getNote("task_1");
    Note& t2=nm->getNote("task_2");
    Note& r1=nm->getNote("r1");
    Note& r2=nm->getNote("r2");

//    QString str="mon super titre de \ref{r1}";
//    capture_ref(str);

/*
    rel1.getNewCoupleRelation(&t1,&t2, "relation de tache");
    rel2.getNewCoupleRelation(&t1,&t2, "relation 2 de tache");
    rel2.getNewCoupleRelation(&r1,&r2, "relation de recording");

    rel1.getNewCoupleRelation(&t1,&r2,"relation Sym",true);
    rel2.getNewCoupleRelation(&t1,&r2,"relation 2 Sym",true);

    rel1.removeCoupleRelation(&t1,&t2);
    displayAllRelation();
*/
    const QString& st1=t1.getId();
    nm->deleteNote(st1);
/*    displayAllRelation();

    rm.deleteRelation("tRelation2");
    displayAllRelation();

    Relation& rel3=rm.getNewRelation("tRelation3", "dRelation3");
    rel3.getNewCoupleRelation(&r1,&t2, "relation 3 de tache");
    rel3.getNewCoupleRelation(&r1,&r2, "relation 3 de recording");
    displayAllRelation();
*/

//    t2.setNewRef(&r1);
//    r1.setNewRef(&r2);

    nm->deleteNote("article_1");
    nm->deleteNote("article_2");
    displayAllNote();

//    nm->emptyTrash();

    //ATTENTION : IL FAUT FREE LE TABLEAU DE REF
    nm->deleteNote("task_2");

    nm->deleteNote("r1");
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

try{
   NotesManager* m=NotesManager::getInstance();
//   m->getNewArticle("test","test1","test de l'itérator");
   Article& a1=m->getNewArticle("test","test1","test de l'itérator");
//   m->getNewTask("testTask","testTask1","testTask de l'itérator",ENUM::OnGoing);
   Task& t1=m->getNewTask("testTask","testTask1","testTask de l'itérator",ENUM::OnGoing);
   Article& ar1=m->getNewArticle("test2","test2","test2 de l'itérator");

   Article& a2=m->editArticle(a1);
   a2.setTitle("test1v2");
   a2.setText("test des versions editées");

   Task& t2=m->editTask(t1);
   t2.setTitle("testTaskv2");
   t2.setAction("URGENT edition");


//   NotesManager::Iterator it=m->getIterator();
//   cout<<it.current();
//   while(!it.isDone()){
//       cout<<endl<<endl<<"Note"<<endl<<"================"<<endl;
//       QList<Note*>::iterator it3=(it.liste())->begin();
//       while (it3!=it.liste()->end()) {
//            it3.operator *()->display();
//            it3++;
//       }
//       it.next();
//   }
//    m->setFilename("test_save.xml");
//    m->save();

//   displayAllVersion();

   cout<<"\n\n===== PARTIE TEST RELATION ET VERSION =====\n";

   RelationManager& rm=RelationManager::getInstance();
   Relation& rel1=rm.getNewRelation("titreRelation1", "descriptionRelation1");
   Relation& rel2=rm.getNewRelation("titreRelation2", "descriptionRelation2");
   rel1.getNewCoupleRelation(&a2,&t2);
   rel1.getNewCoupleRelation(&ar1,&t2);
   rel1.getNewCoupleRelation(&a2,&ar1);
   rel2.getNewCoupleRelation(&a2,&ar1);
//   displayAllRelation();
//   cout<<rel1.displayRelation();
   cout<<rel2.displayRelation();
//   rel1.removeNoteRelation(&a2);
   cout<<rel1.displayRelation();

   QList<Note*> listAscendants=m->getListAscendants("test");
   QList<Note*> listDescendants=m->getListDescendants("test2");

      //Test pour voir si la liste retourne bien les bonnes choses
      QList<Note*>::iterator i;
      std::cout<<"\nLes relations ascendantes de test sont :\n";
      for (i = listAscendants.begin(); i != listAscendants.end(); ++i)
          cout << " - "<<(*i)->getId().toStdString() << endl;
      std::cout<<"\nLes relations descendantes de test2 sont :\n";
      for (i = listDescendants.begin(); i != listDescendants.end(); ++i)
          cout << " - "<<(*i)->getId().toStdString() << endl;

      cout<<"\n\n===== PARTIE TEST DELETE VERSION + EMPTY TRASH =====\n";

      m->deleteNote("test");
      m->deleteNote("test2");
      displayAllVersion();

      m->emptyTrash();
      NotesManager::Iterator it=m->getIterator();
      it.next();
      it.current().display();
      displayAllVersion();

      m->getNewArticle("TestReinsertion","TestReins","Test de la reinsertion d'une note apres une suppression");



   cout<<endl<<endl<<"================"<<endl;

    }
    catch(NotesException& e){
        std::cout<<e.getinfo().toStdString()<<"\n";
    }

}


int main(int argc, char * argv[]) {

    //fct();
    PROGRAMME(argc,argv);
    //creation();
    return 0;
}
