/**
 * \file      manager.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définitions des fonctions déclarées dans le manager.h
 *
 * \details  //Détail
 *
 */

#include "manager.h"
#include<fstream>
#include <QMessageBox>
#include "QInclude.h"


/**************NotesManager********************/

Article& NotesManager::getNewArticle(const QString& id, const QString& ti,const QString& te){
    Article* n=new Article(id,ti,te);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if(!it.liste()->isEmpty()){
            if (it.current().getId()==id){
                throw NotesException("error, creation of an already existent note");
                return (Article&)it.current();
            }
        }
        it.next();
    }
    if (nbNotes==nbMaxNotes){
        QList<Note*>** newNotes= new QList<Note*>*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        QList<Note*>** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes]= new QList<Note*>;
    QList<Note*>* liste=notes[nbNotes++];
    (*liste).push_front(n);
    return *n;
}


Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d){
    Task* n=new Task(id,ti,a,s,p,d);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (nbNotes==nbMaxNotes){
        QList<Note*>** newNotes= new QList<Note*>*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        QList<Note*>** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes]= new QList<Note*>;
    QList<Note*>* liste=notes[nbNotes++];
    (*liste).push_front(n);
    return *n;
}

Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p){
    Task* n=new Task(id,ti,a,s,p);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (nbNotes==nbMaxNotes){
        QList<Note*>** newNotes= new QList<Note*>*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        QList<Note*>** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes]= new QList<Note*>;
    QList<Note*>* liste=notes[nbNotes++];
    (*liste).push_front(n);
    return *n;
}

Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, const QDateTime d){
    Task* n=new Task(id,ti,a,s,d);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (nbNotes==nbMaxNotes){
        QList<Note*>** newNotes= new QList<Note*>*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        QList<Note*>** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes]= new QList<Note*>;
    QList<Note*>* liste=notes[nbNotes++];
    (*liste).push_front(n);
    return *n;
}

Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s){
    Task* n=new Task(id,ti,a,s);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if ((*it.liste()->begin())->getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (nbNotes==nbMaxNotes){
        QList<Note*>** newNotes= new QList<Note*>*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        QList<Note*>** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes]= new QList<Note*>;
    QList<Note*>* liste=notes[nbNotes++];
    (*liste).push_front(n);
    return *n;
}

Recording& NotesManager::getNewRecording(const QString& id, const QString& ti,const QString& d, ENUM::RecordingType r, QString l){
    Recording* n=new Recording(id,ti,d,r,l);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Recording&)it.current();
        }
        it.next();
    }
    if (nbNotes==nbMaxNotes){
        QList<Note*>** newNotes= new QList<Note*>*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        QList<Note*>** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes]= new QList<Note*>;
    QList<Note*>* liste=notes[nbNotes++];
    (*liste).push_front(n);
    return *n;
}


Article& NotesManager::editArticle(Article& A){
    if (A.getIsDeleted())
        throw NotesException("Impossible d'éditer, la note est actuellement dans la corbeille");
    Article* n=new Article(A);
    QList<Note*>* liste=getListeVersions(n->getId());
    liste->push_front(n);
    return *n;
}

Task& NotesManager::editTask(Task& T){
    if (T.getIsDeleted())
        throw NotesException("Impossible d'éditer, la note est actuellement dans la corbeille");
    Task* n=new Task(T);
    QList<Note*>* liste=getListeVersions(n->getId());
    liste->push_front(n);
    return *n;
}

Recording& NotesManager::editRecording(Recording& R){
    if (R.getIsDeleted())
        throw NotesException("Impossible d'éditer, la note est actuellement dans la corbeille");
    Recording* n=new Recording(R);
    QList<Note*>* liste=getListeVersions(n->getId());
    liste->push_front(n);
    return *n;
}

//ANCIEN editArticle, ... qui prenait en compte des QString id, title, etc.
/*
Article& NotesManager::editArticle(const QString& id, const QString& ti,const QString& te){
    Article* n=new Article(id,ti,te);
    QList<Note*>* liste=getListeVersions(id);
    liste->push_front(n);
    return *n;
}

Task& NotesManager::editTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d){
    Task* n=new Task(id,ti,a,s,p,d);
    QList<Note*>* liste=getListeVersions(id);
    liste->push_front(n);
    return *n;
}

Task& NotesManager::editTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p){
    Task* n=new Task(id,ti,a,s,p);
    QList<Note*>* liste=getListeVersions(id);
    liste->push_front(n);
    return *n;
}

Task& NotesManager::editTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, const QDateTime d){
    Task* n=new Task(id,ti,a,s,d);
    QList<Note*>* liste=getListeVersions(id);
    liste->push_front(n);
    return *n;
}

Task& NotesManager::editTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s){
    Task* n=new Task(id,ti,a,s);
    QList<Note*>* liste=getListeVersions(id);
    liste->push_front(n);
    return *n;
}

Recording& NotesManager::editRecording(const QString& id, const QString& ti,const QString& d, ENUM::RecordingType r, QString l){
    Recording* n=new Recording(id,ti,d,r,l);
    QList<Note*>* liste=getListeVersions(id);
    liste->push_front(n);
    return *n;
}
*/

//ATTENTION : faire une fonction pour chaque type ? Ou un dynamic cast ? // Rep: non laisse comme cela on fera des casts
Note& NotesManager::getNote(const QString& id){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id) return it.current();
        it.next();
    }
    throw NotesException("error, non existent note");

}

Note& NotesManager::getNoteVersion(const QString& id, int indice){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (!it.liste()->isEmpty())
            if (it.current().getId()==id && it.liste()->length()>indice) return *(it.liste()->at(indice));
        it.next();
    }
    throw NotesException("error, non existent note version");
}

QList<Note*>* NotesManager::getListeVersions(const QString& id){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id) return it.liste();
        it.next();
    }
    throw NotesException("error, non existent note");
}


NotesManager::NotesManager():notes(0),nbNotes(0),nbMaxNotes(0){}

NotesManager::~NotesManager(){
    //save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void NotesManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    NotesManager* m=NotesManager::getInstance();
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("NoteManager");

    for(NotesManager::Iterator it=m->getIterator(); !it.isDone(); it.next()){

        stream.writeStartElement("NoteVersions");
        stream.writeTextElement("T","");// en ajoutant cette ligne le save fonctionne correctement
        for(QList<Note*>::iterator it2=it.getIteratorVersions(); it2!=it.liste()->end(); it2++){
            it2.operator *()->saveNote(&newfile);
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();



    //Partie Relation
    /*stream.writeStartElement("relationmanager");
    RelationManager::Iterator it=RelationManager::getInstance().getIterator();
    while(!it.isDone()){
        stream.writeStartElement("relation");
        stream.writeTextElement("title", it.current().getTitle());
        stream.writeTextElement("description",it.current().getDescription());
        stream.writeStartElement("notecouple");
        Relation::Iterator it2=it.current().getIterator();
        while (!it2.isDone()) {
            stream.writeStartElement("couple");
            stream.writeTextElement("notex",it2.current().getCoupleNoteX()->getId());
            stream.writeTextElement("notey",it2.current().getCoupleNoteY()->getId());
            stream.writeTextElement("label",it2.current().getLabel());
            if(it2.current().getSymetric()) stream.writeTextElement("symetric","true");//est-ce utile ? (les deux couples seront marqué donc on s'en fiche)
            else stream.writeTextElement("symetric","false");
            stream.writeEndElement();
        }
        stream.writeEndElement();
        stream.writeEndElement();
        it.next();
    }
    stream.writeEndElement();*/

    stream.writeEndDocument();
    newfile.close();
    cout<<endl<<"Save effectuee"<<endl;
}


void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "NoteManager") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                //addArticle(identificateur,titre,text);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}


ostream& operator<<(ostream& f, const Note& n){
    f<<n.getId().toStdString()<<"\n";
    f<<n.getTitle().toStdString()<<"\n";
    return f;
}


NotesManager::Handler NotesManager::handler=NotesManager::Handler();

NotesManager *NotesManager::getInstance(){
    //if (instanceUnique==0)
        //instanceUnique=new NotesManager;
    if(handler.instance==0) handler.instance=new NotesManager;
    return handler.instance;
}

void NotesManager::libererInstance(){
    delete handler.instance;
    handler.instance=0;
}


void NotesManager::deleteNote(const QString& id){
    NotesManager::Iterator it=NotesManager::getIterator();
    //Suppression de la dernière version
    //Faut il modifier pour mettre CHAQUE version d'une note à isDeleted ?
    //Voir comment naviguer dans les relations avec displayAllVersion
    std::cout<<id.toStdString()<<" : id en cours a supprimer\n";
    Note& n=getNote(id);
    if (n.getNbIsRef()!=0){
        std::cout<<"La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée.\n";
        QMessageBox msgBox;
        msgBox.setText("La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée.\n");
        msgBox.exec();
        n.setIsArchive(true);
    }
    else{
        //Relation manager applique removeNoteRelation sur toutes les relations
        RelationManager& m=RelationManager::getInstance();
        //Supprimer toutes les présences d'une note dans l'ensemble des relations
        for(RelationManager::Iterator it= m.getIterator(); !it.isDone(); it.next()){
            it.current().removeNoteRelation(&n);
        }
        std::cout<<"toutes les relations sont supprimées\n";
        if(n.getNbRef()!=0) n.deleteAllReference();
        n.setIsDeleted(true);
    }
}

//DECHETS DE DELETENOTE
//    while(!it.isDone()){
//        cout<<"etape 2 "<<id.toStdString()<<" it.current().getId() "<<it.current().getId().toStdString()<<"\n";
//        if (it.current().getId()==id){
//            cout<<"etape 3\n";
//            Note* n=&it.current();
//            cout<<"etape 4 : n->getNbIsRef"<<n->getNbIsRef()<<"\n";
//            if (n->getNbIsRef()!=0){
//                std::cout<<"La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée.";
//                QMessageBox msgBox;
//                msgBox.setText("La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée");
//                msgBox.exec();
//                n->setIsArchive(true);
//            }
//            else{
//                //Relation manager applique removeNoteRelation sur toutes les relations
//                RelationManager& m=RelationManager::getInstance();
//                //Supprimer toutes les présences d'une note dans l'ensemble des relations
//                for(RelationManager::Iterator it= m.getIterator(); !it.isDone(); it.next()){
//                    it.current().removeNoteRelation(n);
//                }
//                if(n->getNbRef()!=0) n->deleteAllReference();
//                n->setIsDeleted(true);
//            }
//        }
//    }
//}

//void NotesManager::emptyTrash(){
//    NotesManager::Iterator it=NotesManager::getIterator();
//    int i=0;
//    while(!it.isDone()){
//        if (it.current().getIsDeleted()){
//            it.current().setNbRef(0);
//            delete &it.current();
//            notes[i]=notes[--nbNotes];
//            i++;
//        }
//    }
//}



void NotesManager::emptyTrash(){
    NotesManager* m=NotesManager::getInstance();
    std::cout<<"\nEMPTY TRASH DEMANDE\n";
    NotesManager::Iterator itNote=m->getIterator();
    while(!itNote.isDone()){
        if (itNote.current().getIsDeleted()){
            //Note& n=NotesManager::getNote(itNote.current().getId());
            cout<<endl<<"// Note en cours de suppression : "<<itNote.current().getId().toStdString()<<" \\\\"<<endl;
            //===V1
            //std::cout<<"get the ListeVersion\n";
            //QList<Note*>* listVersion=getListeVersions(itNote.current().getId());
            std::cout<<"qDeleteALl\n";
            qDeleteAll(itNote.liste()->begin(),itNote.liste()->end());
            std::cout<<"Clear\n";
            itNote.liste()->clear();
            std::cout<<"done\n";

            //===V2
            /*
            QList<Note*>::iterator itVersion=(itNote.liste())->begin();
            while (itVersion!=itNote.liste()->end()) {
                //TODO : il faut supprimer chaque version de note de la liste courrante
                itVersion.operator *()->removeAt();
                itVersion++;
            }
            TODO : il faut supprimer la liste entière de cette note.
            */

            //== V3
            /*
            std::cout<<"while isEmpty\n";
            while (!listVersion->isEmpty())
                delete listVersion->takeFirst();
            */
        }
        itNote.next();
    }
}


void NotesManager::editNote(const QString &id){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone() && it.current().getId()!=id) it.next();
    if (it.isDone()){
        throw NotesException("error, impossible to edit note, non existent note");
    }
    else{
        Note* ncopy(&it.current());   //last modif date automatiquement mis à jour dans la copie
        //a definir avec l'interface
    }
}

void NotesManager::restoreNoteTrash(const QString& id){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone() && it.current().getId()!=id) it.next();
    if (it.isDone()){
        throw NotesException("error, non existent note");
    }
    else{
        if (it.current().getIsDeleted()) it.current().setIsDeleted(false);
    }
}


/*************RelationManager*******************/


RelationManager::RelationManager():tabrelations(0),nbRelations(0),nbMaxRelations(0){}

RelationManager::~RelationManager(){
//    save();
    for(unsigned int i=0; i<nbRelations; i++) delete tabrelations[i];
    delete[] tabrelations;
}

Relation& RelationManager::getNewRelation(const QString& title,const QString& desc){
    Relation* n=new Relation(title,desc);
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabrelations[i]->getTitle()==title) throw NotesException("error, creation of an already existent relation");
    }
    if (nbRelations==nbMaxRelations){
        Relation** newRelationTab= new Relation*[nbMaxRelations+5];
        for(unsigned int i=0; i<nbRelations; i++) newRelationTab[i]=tabrelations[i];
        Relation** oldRelations=tabrelations;
        tabrelations=newRelationTab;
        nbMaxRelations+=5;
        if (oldRelations) delete[] oldRelations;
    }
    int i=nbRelations;
    tabrelations[nbRelations++]=n;
    return *tabrelations[i];
}


Relation& RelationManager::getRelation(const QString& title){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabrelations[i]->getTitle()==title) return *tabrelations[i];
    }
    throw NotesException("error, impossible to get relation, non existent relation");
}

void RelationManager::deleteRelation(const QString &title){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabrelations[i]->getTitle()==title){
            delete tabrelations[i];
            tabrelations[i]=tabrelations[--nbRelations];
            return;
        }
    }
    throw NotesException ("error, impossible to delete, non existent relation");
}


QList<Note*> NotesManager::getListAscendants(const QString& id){
//void NotesManager::getListAscendants(const QString& id){
//   std::cout<<"\nLes relations ascendantes de "<<id.toStdString()<<" sont :\n";
   RelationManager& rm=RelationManager::getInstance();
//   QList<Note*>* listAsc;
   QList<Note*> listAscendants;
   for(RelationManager::Iterator itManager=rm.getIterator(); !itManager.isDone(); itManager.next()){
       Relation& r=itManager.current();
        for(Relation::Iterator itRel=r.getIterator(); !itRel.isDone(); itRel.next()){
            if (itRel.current().getCoupleNoteX()->getId()==id){
                Note& ny=NotesManager::getInstance()->getNote(itRel.current().getCoupleNoteY()->getId());
//                std::cout<<"  - "<<ny.getId().toStdString()<<"\n";
                  listAscendants.append(&ny);
            }
        }
   }
   return listAscendants;
}

QList<Note*> NotesManager::getListDescendants(const QString& id){
//void NotesManager::getListDescendants(const QString& id){
//   std::cout<<"\nLes relations descendantes de "<<id.toStdString()<<" sont :\n";
   RelationManager& rm=RelationManager::getInstance();
   QList<Note*> listDescendants;
   for(RelationManager::Iterator itManager=rm.getIterator(); !itManager.isDone(); itManager.next()){
       Relation& r=itManager.current();
        for(Relation::Iterator itRel=r.getIterator(); !itRel.isDone(); itRel.next()){
            if (itRel.current().getCoupleNoteY()->getId()==id){
                Note& nx=NotesManager::getInstance()->getNote(itRel.current().getCoupleNoteX()->getId());
//                std::cout<<"  - "<<nx.getId().toStdString()<<"\n";
                listDescendants.append(&nx);
            }
        }
   }
   return listDescendants;
}

//void NotesManager::displayRelAscDesc(const QString id){
//    QList<Note*> listAscendants=m->getListAscendants("test");
//    QList<Note*> listDescendants=m->getListDescendants("test");

//    QList<Note*>::iterator i;
//    std::cout<<"\nLes relations ascendantes de "<<id.toStdString()<<" sont :\n";
//    for (i = listAscendants.begin(); i != listAscendants.end(); ++i)
//        cout << " - "<<(*i)->getId().toStdString() << endl;
//    std::cout<<"\nLes relations descendantes de "<<id.toStdString()<<" sont :\n";
//    for (i = listDescendants.begin(); i != listDescendants.end(); ++i)
//        cout << " - "<<(*i)->getId().toStdString() << endl;
//}


RelationManager::Handler RelationManager::handler=RelationManager::Handler();

 RelationManager& RelationManager::getInstance(){
    if(handler.instance==0) handler.instance=new RelationManager;
    return *handler.instance;
}
void RelationManager::libererInstance(){
    delete handler.instance;
    handler.instance=0;
}

QString NotesManager::updateId(QString Id2)const {
    QString Id=Id2;
    int i=Id.length()-1;
    if(Id[i]=='9')
    {
//        QChar c(Id[i-1].toAscii()+1);
        QChar c(Id[i-1].toLatin1()+1);
        Id[i-1]=c;
        Id[i]='0';
    }
    else
    {
//        QChar c(Id[i].toAscii()+1);
        QChar c(Id[i].toLatin1()+1);
        Id[i]=c;
    }
    return Id;
}
