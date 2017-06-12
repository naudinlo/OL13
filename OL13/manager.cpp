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

/**
 * \fn        Article& NotesManager::getNewArticle(const QString& id, const QString& ti,const QString& te)
 * \brief     Créer une nouvelle note de type article
 *              La première version de cette note est ajoutée à la liste des versions d'une note
 * \param     const QString& id         ID de la note à créer
 *            const QString& ti         Titre de l'article à créer
 *            const QString& de         Text de l'article a créer
 */
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

/**
 * \fn        Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s)
 * \brief     Créer une nouvelle note de type task
 *              La première version de cette note est ajoutée à la liste des versions d'une note
 * \param     const QString& id         ID de la note à créer
 *            const QString& ti         Titre de la tache à créer
 *            const QString& a          Action de la tache à créer
 *            ENUM::StatusType s     Status de la tache à créer
 *            unsigned int p            Priority de la tache à créer
 *            const QDateTime d         Date limite de la tache à créer
 */
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
/**
 * \fn        Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s)
 * \brief     Créer une nouvelle note de type task
 *              La première version de cette note est ajoutée à la liste des versions d'une note
 * \param     const QString& id         ID de la note a créer
 *            const QString& ti         Titre de la tache a créer
 *            const QString& a          Action de la tache a créer
 *            ENUM::StatusType s     Status de la tache a créer
 *            unsigned int p            Priority de la tache à créer
 */
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
/**
 * \fn        Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s)
 * \brief     Créer une nouvelle note de type task
 *              La première version de cette note est ajoutée à la liste des versions d'une note
 * \param     const QString& id         ID de la note a créer
 *            const QString& ti         Titre de la tache a créer
 *            const QString& a          Action de la tache a créer
 *            ENUM::StatusType s     Status de la tache a créer
 *            const QDateTime d         Date limite de la tache à créer
 */
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

/**
 * \fn        Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s)
 * \brief     Créer une nouvelle note de type task
 *              La première version de cette note est ajoutée à la liste des versions d'une note
 * \param     const QString& id         ID de la note a créer
 *            const QString& ti         Titre de la tache a créer
 *            const QString& a          Action de la tache a créer
 *            ENUM::StatusType s     Status de la tache a créer
 */
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

/**
 * \fn        Recording& NotesManager::getNewRecording(const QString& id, const QString& ti,const QString& d, ENUM::RecordingType r, QString l)
 * \brief     Créé une nouvelle note de type recording
 *              La première version de cette note est ajoutée à la liste des versions d'une note
 * \param     const QString& id         ID de la note a créer
 *            const QString& ti         Titre du recording a créer
 *            const QString& d          Description du recording a créer
 *            ENUM::RecordingType r     Type du recording a créer
 *            QString l                 Link du recording a créer
 */
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

/**
 * \fn        Article& NotesManager::editArticle(Article& A)
 * \brief     Créé une nouvelle instance d'un article passé en paramètre
 * \details   Recopie une note passée en paramètre en modifiant sa date de dernière mise à jour
 *              et l'insère en première position dans la liste des versions d'une note
 * \param     Article& A          Référence sur l'article a éditer
 */
Article& NotesManager::editArticle(Article& A){
    if (A.getIsDeleted())
        throw NotesException("Impossible d'éditer, la note est actuellement dans la corbeille");
    Article* n=new Article(A);
    QList<Note*>* liste=getListeVersions(n->getId());
    liste->push_front(n);
    return *n;
}

/**
 * \fn        Task& NotesManager::editTask(Task& T)
 * \brief     Créé une nouvelle instance d'une task passée en paramètre
 * \details   Recopie une note passée en paramètre en modifiant sa date de dernière mise à jour
 *              et l'insère en première position dans la liste des versions d'une note
 * \param     Task& T          Référence sur la tache a éditer
 */
Task& NotesManager::editTask(Task& T){
    if (T.getIsDeleted())
        throw NotesException("Impossible d'éditer, la note est actuellement dans la corbeille");
    Task* n=new Task(T);
    QList<Note*>* liste=getListeVersions(n->getId());
    liste->push_front(n);
    return *n;
}

/**
 * \fn        Recording& NotesManager::editRecording(Recording& R)
 * \brief     Créé une nouvelle instance d'un recording passé en paramètre
 * \details   Recopie une note passée en paramètre en modifiant sa date de dernière mise à jour
 *              et l'insère en première position dans la liste des versions d'une note
 * \param     Recording& R          Référence sur le recording a éditer
 */
Recording& NotesManager::editRecording(Recording& R){
    if (R.getIsDeleted())
        throw NotesException("Impossible d'éditer, la note est actuellement dans la corbeille");
    Recording* n=new Recording(R);
    QList<Note*>* liste=getListeVersions(n->getId());
    liste->push_front(n);
    return *n;
}

/**
 * \fn        Note& NotesManager::getNote(const QString& id)
 * \brief     Retourne une réfèrence sur l'ID d'une note spécifiée en paramètre
 * \param     const QString& id         ID de la note a retourner
 */
Note& NotesManager::getNote(const QString& id){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id) return it.current();
        it.next();
    }
    throw NotesException("error, non existent note");

}

/**
 * \fn        Note& NotesManager::getNoteVersion(const QString& id, int indice)
 * \brief     Retourne la i-ième versions d'une note spécifiée en paramètre
 * \param     const QString& id         ID de la note concernée
 *            int indice                Numéro de la version à retourner
 */
Note& NotesManager::getNoteVersion(const QString& id, int indice){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (!it.liste()->isEmpty())
            if (it.current().getId()==id && it.liste()->length()>indice) return *(it.liste()->at(indice));
        it.next();
    }
    throw NotesException("error, non existent note version");
}

/**
 * \fn        QList<Note*>* NotesManager::getListeVersions(const QString& id)
 * \brief     Retourne la liste des versions d'une note spécifiée en paramètre
 * \param     const QString& id         ID de la note dont les versions doivent être retournée
 */
QList<Note*>* NotesManager::getListeVersions(const QString& id){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()){
        if (it.current().getId()==id) return it.liste();
        it.next();
    }
    throw NotesException("error, non existent note");
}

/**
 * \fn        NotesManager::NotesManager()
 * \brief     Constructeur de la classe NotesManager
 */
NotesManager::NotesManager():notes(0),nbNotes(0),nbMaxNotes(0){}

/**
 * \fn        NotesManager::~NotesManager()
 * \brief     Destructeur de la classe NotesManager
 */
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


/**
 * \fn        ostream& operator<<(ostream& f, const Note& n)
 * \brief     Surcharge de l'opérateur << d'affichage d'une note
 */
ostream& operator<<(ostream& f, const Note& n){
    f<<n.getId().toStdString()<<"\n";
    f<<n.getTitle().toStdString()<<"\n";
    return f;
}

/**
 * \fn        NotesManager::Handler NotesManager::handler=NotesManager::Handler()
 *              NotesManager *NotesManager::getInstance()
 *              void NotesManager::libererInstance()
 * \brief     Fonctions relatives au Design Pattern Singleton sur le NotesManager
 */
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

/**
 * \fn        void NotesManager::deleteNote(const QString& id)
 * \brief     Action de suppression d'une note spécifiée en paramètre
 * \details   Lorsque la suppression d'une note est demandée,
 *              celle ci est archivée si elle est référencée par d'autres notes (l'attribut isArchive est mis à true).
 *              Sinon, supprime sa présence dans l'ensemble des relations,
 *                  puis supprime l'ensemble des références qu'à cette note,
 *                  puis déplace la note dans la corbeille (l'attribut siDeleted est mis à true).
 * \param    const QString& id          ID de la note a supprimer
 */
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
        std::cout<<"Toutes les relations sont supprimées\n";
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


/**
 * \fn        void NotesManager::emptyTrash()
 * \brief     Supprime définitivement l'ensemble des notes déclarées comme supprimées
 * \details   Parcourt l'ensemble des notes,
 *              lorsqu'une note est reconnue comme supprimée chaque version de cette note est supprimée
 *              puis la liste des versions elle-même est vidée et supprimée
 */
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


//void NotesManager::editNote(const QString &id){
//    NotesManager::Iterator it=NotesManager::getIterator();
//    while(!it.isDone() && it.current().getId()!=id) it.next();
//    if (it.isDone()){
//        throw NotesException("error, impossible to edit note, non existent note");
//    }
//    else{
//        Note* ncopy(&it.current());   //last modif date automatiquement mis à jour dans la copie
//        //a definir avec l'interface
//    }
//}


/**
 * \fn        void NotesManager::restoreNoteTrash(const QString& id)
 * \brief     Restaure une note supprimée en passant à false son attribut isDeleted
 * \param     const QString& id             ID de la note supprimée à restaurer
 */
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

/**
 * \fn        RelationManager::RelationManager()
 * \brief     Constructeur de la classe RelationManager
 */
RelationManager::RelationManager():tabrelations(0),nbRelations(0),nbMaxRelations(0){}

/**
 * \fn        RelationManager::~RelationManager()
 * \brief     Destructeur de la classe RelationManager
 * \details   Détruit chaque élément relation avant de les désallouer.
 */
RelationManager::~RelationManager(){
//    save();
    for(unsigned int i=0; i<nbRelations; i++) delete tabrelations[i];
    delete[] tabrelations;
}

/**
 * \fn        Relation& RelationManager::getNewRelation(const QString& title,const QString& desc)
 * \brief     Créé une nouvelle relation à partir d'un titre et d'une description
 *              si une autre relation du même titre n'existe pas déjà
 * \param    const QString& title         Titre de la nouvelle relation à créer
 *           const QString& desc          Description de la nouvelle relation à créer
 */
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

/**
 * \fn        Relation& RelationManager::getRelation(const QString& title)
 * \brief     Retourne une référence sur une relation dont le titre est donné en paramètre
 * \param    const QString& title         Titre de la relation a retourner
 */
Relation& RelationManager::getRelation(const QString& title){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabrelations[i]->getTitle()==title) return *tabrelations[i];
    }
    throw NotesException("error, impossible to get relation, non existent relation");
}

/**
 * \fn        void RelationManager::deleteRelation(const QString &title)
 * \brief     Supprime une relation dont le titre est passé en paramètre
 * \param    const QString& title         Titre de la relation a supprimer
 */
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


/**
 * \fn        QList<Note*> NotesManager::getListAscendants(const QString& id)
 * \brief     Retourne la liste des notes en relation ascendant avec une note specifiée en paramètre
 * \param    const QString& id         ID de la note dont il faut trouver les notes en relation ascendante.
 */
QList<Note*> NotesManager::getListAscendants(const QString& id){
   RelationManager& rm=RelationManager::getInstance();
   QList<Note*> listAscendants;
   for(RelationManager::Iterator itManager=rm.getIterator(); !itManager.isDone(); itManager.next()){
       Relation& r=itManager.current();
        for(Relation::Iterator itRel=r.getIterator(); !itRel.isDone(); itRel.next()){
            if (itRel.current().getCoupleNoteX()->getId()==id){
                Note& ny=NotesManager::getInstance()->getNote(itRel.current().getCoupleNoteY()->getId());
                  listAscendants.append(&ny);
            }
        }
   }
   return listAscendants;
}
QList<TupleNote_Relation*> NotesManager::getListTupleAscendants(const QString& id){
   RelationManager& rm=RelationManager::getInstance();
   QList<TupleNote_Relation*> listAscendants;
   for(RelationManager::Iterator itManager=rm.getIterator(); !itManager.isDone(); itManager.next()){
       Relation& r=itManager.current();
        for(Relation::Iterator itRel=r.getIterator(); !itRel.isDone(); itRel.next()){
            if (itRel.current().getCoupleNoteX()->getId()==id){
                Note& ny=NotesManager::getInstance()->getNote(itRel.current().getCoupleNoteY()->getId());
                  listAscendants.append(new TupleNote_Relation(ny,r));
            }
        }
   }
   return listAscendants;
}
/**
 * \fn        QList<Note*> NotesManager::getListDescendants(const QString& id)
 * \brief     Retourne la liste des notes en relation descendante avec une note specifiée en paramètre
 * \param    const QString& id         ID de la note dont il faut trouver les notes en relation descendante.
 */
QList<Note*> NotesManager::getListDescendants(const QString& id){
   RelationManager& rm=RelationManager::getInstance();
   QList<Note*> listDescendants;
   for(RelationManager::Iterator itManager=rm.getIterator(); !itManager.isDone(); itManager.next()){
       Relation& r=itManager.current();
        for(Relation::Iterator itRel=r.getIterator(); !itRel.isDone(); itRel.next()){
            if (itRel.current().getCoupleNoteY()->getId()==id){
                Note& nx=NotesManager::getInstance()->getNote(itRel.current().getCoupleNoteX()->getId());
                listDescendants.append(&nx);
            }
        }
   }
   return listDescendants;
}
QList<TupleNote_Relation*> NotesManager::getListTupleDescendants(const QString& id){
   RelationManager& rm=RelationManager::getInstance();
   QList<TupleNote_Relation*> listDescendants;
   for(RelationManager::Iterator itManager=rm.getIterator(); !itManager.isDone(); itManager.next()){
       Relation& r=itManager.current();
        for(Relation::Iterator itRel=r.getIterator(); !itRel.isDone(); itRel.next()){
            if (itRel.current().getCoupleNoteY()->getId()==id){
                Note& nx=NotesManager::getInstance()->getNote(itRel.current().getCoupleNoteX()->getId());
                listDescendants.append(new TupleNote_Relation(nx,r));
            }
        }
   }
   return listDescendants;
}

/**
 * \fn        RelationManager::Handler RelationManager::handler=RelationManager::Handler();
                void RelationManager::libererInstance(){
 * \brief     Fonctions relatives au Design Pattern Singleton sur le RelationManager
 */
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
