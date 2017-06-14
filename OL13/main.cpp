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


void displayAllNote(){
    std::cout<<"\n*=== ALL NOTES ===*\n";
    NotesManager* m=NotesManager::getInstance();

    for(NotesManager::Iterator it=m->getIterator(); !it.isDone(); it.next()){
        if(!it.liste()->isEmpty()) it.current().display();
    };
}


void displayAllVersion(){
    NotesManager* m=NotesManager::getInstance();
    std::cout<<"\n*=== ALL VERSIONS ALL NOTES ===*\n";
    NotesManager::Iterator itNote=m->getIterator();
    while(!itNote.isDone()){
        if(!itNote.liste()->isEmpty()){
            cout<<endl<<"// Versions de la note : "<<itNote.current().getId().toStdString()<<" \\\\"<<endl;
            unsigned int i=0;
            for(QList<Note*>::iterator itVersion=(itNote.liste())->begin();itVersion!=itNote.liste()->end();itVersion++){
                cout<<endl<<"--- Version "<<i++<<" ---";
                itVersion.operator *()->display();
            }
        }
        itNote.next();
    }
}

void displayAllRelation(){
    std::cout<<"\n*=== ALL RELATIONS ===*\n";
    RelationManager& rm=RelationManager::getInstance();
    for(RelationManager::Iterator it=rm.getIterator(); !it.isDone(); it.next()){
        std::cout<<"\n- "<<it.current().getTitle().toStdString();
        std::cout<<" description : "<<it.current().getDescription().toStdString()<<std::endl;
        it.current().displayRelation();
    };
}


int PROGRAMME(int argc,char *argv[])
{
    // UTF-8 Encoding
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    interface Fenprincipale;
    Fenprincipale.showMaximized();
    Fenprincipale.setWindowIcon(QIcon("Pluri-notes.png"));
    return app.exec();
}


int main(int argc, char * argv[]) {

    //Lancement de l'application Plurinote
    PROGRAMME(argc,argv);

    return 0;
}
