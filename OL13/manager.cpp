/**
 * \file      manager.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définitions des fonctions déclarées dans le manager.h
 *
 * \details   Domaines des méthodes comprises dans ce fichier :
 *              - Méthodes relatives au NotesManager
 *              - Méthodes relatives au RelationManager
 *           Le détail est donné dans la suite du fichier.
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
 * \param     const QString& ti         Titre de l'article à créer
 * \param     const QString& de         Text de l'article a créer
 * \return    Article&
 */
Article& NotesManager::getNewArticle(const QString& id, const QString& ti,const QString& te){
    Article* n=new Article(id,ti,te);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!(it.isDone() || it.liste()->isEmpty())){
            if (it.current().getId()==id){
                throw NotesException("error, creation of an already existent note");
                return (Article&)it.current();
            }
        it.next();
    }
    if (!it.isDone()){it.liste()->push_front(n); return *n;}
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
 * \param     const QString& id         ID de la note à créer.
 * \param     const QString& ti         Titre de la tache à créer.
 * \param     const QString& a          Action de la tache à créer.
 * \param     ENUM::StatusType s        Status de la tache à créer.
 * \param     unsigned int p            Priority de la tache à créer.
 * \param     const QDateTime d         Date limite de la tache à créer.
 */
Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d){
    Task* n=new Task(id,ti,a,s,p,d);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!(it.isDone()||it.liste()->isEmpty())){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (!it.isDone()){it.liste()->push_front(n); return *n;}
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
 * \param     const QString& ti         Titre de la tache a créer
 * \param     const QString& a          Action de la tache a créer
 * \param     ENUM::StatusType s        Status de la tache a créer
 * \param     unsigned int p            Priority de la tache à créer
 */
Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p){
    Task* n=new Task(id,ti,a,s,p);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!(it.isDone()||it.liste()->isEmpty())){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (!it.isDone()){it.liste()->push_front(n); return *n;}
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
 * \param     const QString& ti         Titre de la tache a créer
 * \param     const QString& a          Action de la tache a créer
 * \param     ENUM::StatusType s     Status de la tache a créer
 * \param     const QDateTime d         Date limite de la tache à créer
 */
Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, const QDateTime d){
    Task* n=new Task(id,ti,a,s,d);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!(it.isDone()||it.liste()->isEmpty())){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (!it.isDone()){it.liste()->push_front(n); return *n;}
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
 * \param     const QString& ti         Titre de la tache a créer
 * \param     const QString& a          Action de la tache a créer
 * \param     ENUM::StatusType s     Status de la tache a créer
 */
Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s){
    Task* n=new Task(id,ti,a,s);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!(it.isDone()||it.liste()->isEmpty())){
        if ((*it.liste()->begin())->getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Task&)it.current();
        }
        it.next();
    }
    if (!it.isDone()){it.liste()->push_front(n); return *n;}
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
 * \param     const QString& ti         Titre du recording a créer
 * \param     const QString& d          Description du recording a créer
 * \param     ENUM::RecordingType r     Type du recording a créer
 * \param     QString l                 Link du recording a créer
 */
Recording& NotesManager::getNewRecording(const QString& id, const QString& ti,const QString& d, ENUM::RecordingType r, QString l){
    Recording* n=new Recording(id,ti,d,r,l);
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!(it.isDone()||it.liste()->isEmpty())){
        if (it.current().getId()==id){
            throw NotesException("error, creation of an already existent note");
            return (Recording&)it.current();
        }
        it.next();
    }
    if (!it.isDone()){it.liste()->push_front(n); return *n;}
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
        if(!it.liste()->isEmpty()) if (it.current().getId()==id) return it.current();
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
        if(!it.liste()->isEmpty()) if (it.current().getId()==id) return it.liste();
        it.next();
    }
    throw NotesException("error, non existent note");
}

/**
 * \fn        QList<Note*> NotesManager::getListDeleted()
 * \brief     Retourne la liste des notes supprimée
 */
QList<Note*> NotesManager::getListDeleted(){
   QList<Note*> listDeleted;
   NotesManager::Iterator it=NotesManager::getIterator();
   while(!it.isDone()){
       if(!it.liste()->isEmpty()) if(it.current().getIsDeleted()) listDeleted.append(&it.current());
       it.next();
   }
   return listDeleted;
}


/**
 * \fn        QList<Note*> NotesManager::getListArchive()
 * \brief     Retourne la liste des notes archivée
 */
QList<Note*> NotesManager::getListArchive(){
   QList<Note*> listArchive;
   NotesManager::Iterator it=NotesManager::getIterator();
   while(!it.isDone()){
       if(!it.liste()->isEmpty()) if(it.current().getIsArchive()) listArchive.append(&it.current());
       it.next();
   }
   return listArchive;
}


/**
 * \fn        NotesManager::NotesManager()
 * \brief     Constructeur de la classe NotesManager
 */
NotesManager::NotesManager():notes(0),nbNotes(0),nbMaxNotes(0),filename("default.xml"){}

/**
 * \fn        NotesManager::~NotesManager()
 * \brief     Destructeur de la classe NotesManager
 */
NotesManager::~NotesManager(){
    //save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

/**
 * \fn        void NotesManager::save() const
 * \brief     Sauvegarde des notes dans un fichier XML
 * \details   Cette fonction sauvegarde les notes ainsi que les relations.
 *              Le nom du fichier XML est stocké dans le NotesManager.
 */
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
        if(!it.liste()->isEmpty()){
            stream.writeStartElement("NoteVersions");
            stream.writeTextElement("T","");// en ajoutant cette ligne le save fonctionne correctement
            for(QList<Note*>::iterator it2=it.getIteratorVersions(); it2!=it.liste()->end(); it2++){
                it2.operator *()->saveNote(&newfile);
            }
            stream.writeEndElement();
        }
    }

    //Partie Relation
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
            it2.next();
        }
        stream.writeEndElement();
        stream.writeEndElement();
        it.next();
    }
    stream.writeEndElement();

    stream.writeEndDocument();
    newfile.close();
    cout<<endl<<"Save effectuee"<<endl;
}

/**
 * \fn        void NotesManager::load()
 * \brief     Charge les notes d'un fichier XML dans l'application
 * \details   Cette fonction ne charge que les notes une fonction dédiée aux relations est définie dans la
 *              classe RelationManager. Le nom du fichier XML est stocké dans le NotesManager.
 */
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

            if(xml.name() == "NoteVersions") {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "NoteVersions")) {
                    if (xml.name()=="T") xml.readNextStartElement();
                    unsigned int flag=0;
                    QString identificateur;
                    QString titre;
                    QDateTime creation_date;
                    QDateTime lastmodif_date;
                    bool isArchive;
                    bool isDeleted;
                    if(xml.name() == "article") {
                        qDebug()<<"new article\n";
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

                                //We've found creation_date
                                if(xml.name() == "c_date") {
                                    xml.readNext(); creation_date=QDateTime::fromString(xml.text().toString());
                                    qDebug()<<"creation_date="<<creation_date.toString()<<"\n";
                                }

                                //We've found lastmodif_date
                                if(xml.name() == "lm_date") {
                                    xml.readNext(); lastmodif_date=QDateTime::fromString(xml.text().toString());
                                    qDebug()<<"lastmodif_date="<<lastmodif_date.toString()<<"\n";
                                }

                                //We've found isArchive
                                if(xml.name() == "isArchive") {
                                    xml.readNext(); if (xml.text() == "false") isArchive=false; else isArchive=true;
                                    qDebug()<<"isArchive="<<isArchive<<"\n";
                                }

                                //We've found isDeleted
                                if(xml.name() == "isDeleted") {
                                    xml.readNext(); if (xml.text() == "false") isDeleted=false; else isDeleted=true;
                                    qDebug()<<"isDeleted="<<isDeleted<<"\n";
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
                        qDebug()<<"ajout article "<<identificateur<<"\n";
                        Article* n=new Article(identificateur,titre,creation_date,lastmodif_date,isArchive,isDeleted,text);
                        NotesManager::Iterator it=NotesManager::getIterator();
                        while(!it.isDone()){
                            if(!it.liste()->isEmpty())
                            if (it.current().getId()==identificateur){
                                it.liste()->push_back(n);
                                flag=1;
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
                        if (flag==0){
                            notes[nbNotes]= new QList<Note*>;
                            QList<Note*>* liste=notes[nbNotes++];
                            (*liste).push_front(n);
                        }
                    }

                    if(xml.name() == "task") {
                        qDebug()<<"new task\n";
                        QString action;
                        ENUM::StatusType status;
                        unsigned int priority;
                        QDateTime dueDate;
                        QXmlStreamAttributes attributes = xml.attributes();
                        xml.readNext();
                        //We're going to loop over the things because the order might change.
                        //We'll continue the loop until we hit an EndElement named article.
                        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "task")) {
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

                                //We've found creation_date
                                if(xml.name() == "c_date") {
                                    xml.readNext(); creation_date=QDateTime::fromString(xml.text().toString());
                                    qDebug()<<"creation_date="<<creation_date.toString()<<"\n";
                                }

                                //We've found lastmodif_date
                                if(xml.name() == "lm_date") {
                                    xml.readNext(); lastmodif_date=QDateTime::fromString(xml.text().toString());
                                    qDebug()<<"lastmodif_date="<<lastmodif_date.toString()<<"\n";
                                }

                                //We've found isArchive
                                if(xml.name() == "isArchive") {
                                    xml.readNext(); if (xml.text() == "false") isArchive=false; else isArchive=true;
                                    qDebug()<<"isArchive="<<isArchive<<"\n";
                                }

                                //We've found isDeleted
                                if(xml.name() == "isDeleted") {
                                    xml.readNext(); if (xml.text() == "false") isDeleted=false; else isDeleted=true;
                                    qDebug()<<"isDeleted="<<isDeleted<<"\n";
                                }

                                // We've found action
                                if(xml.name() == "action") {
                                    xml.readNext();
                                    action=xml.text().toString();
                                    qDebug()<<"action="<<action<<"\n";
                                }

                                // We've found priority
                                if(xml.name() == "priority") {
                                    xml.readNext();
                                    priority=xml.text().toUInt();
                                    qDebug()<<"priority="<<priority<<"\n";
                                }

                                // We've found dueDate
                                if(xml.name() == "d_date") {
                                    xml.readNext();
                                    dueDate=QDateTime::fromString(xml.text().toString());
                                    qDebug()<<"action="<<action<<"\n";
                                }

                                // We've found status
                                if(xml.name() == "status") {
                                    xml.readNext();
                                    if (xml.text().toString() == "OnGoing") status=ENUM::OnGoing;
                                    if (xml.text().toString() == "Completed") status=ENUM::Completed;
                                    if (xml.text().toString() == "Pending") status=ENUM::Pending;
                                    qDebug()<<"priority="<<priority<<"\n";
                                }
                            }
                            // ...and next...
                            xml.readNext();
                        }
                        qDebug()<<"ajout note "<<identificateur<<"\n";
                        Task* n=new Task(identificateur,titre,creation_date,lastmodif_date,isArchive,isDeleted,action,status,priority,dueDate);
                        NotesManager::Iterator it=NotesManager::getIterator();
                        while(!it.isDone()){
                            if(!it.liste()->isEmpty())
                            if (it.current().getId()==identificateur){
                                it.liste()->push_back(n);
                                flag=1;
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
                        if (flag==0){
                            notes[nbNotes]= new QList<Note*>;
                            QList<Note*>* liste=notes[nbNotes++];
                            (*liste).push_front(n);
                        }
                    }

                    if(xml.name() == "recording") {
                        qDebug()<<"new recording\n";
                        QString description;
                        ENUM::RecordingType type;
                        QString link;
                        QXmlStreamAttributes attributes = xml.attributes();
                        xml.readNext();
                        //We're going to loop over the things because the order might change.
                        //We'll continue the loop until we hit an EndElement named article.
                        while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "task")) {
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

                                //We've found creation_date
                                if(xml.name() == "c_date") {
                                    xml.readNext(); creation_date=QDateTime::fromString(xml.text().toString());
                                    qDebug()<<"creation_date="<<creation_date.toString()<<"\n";
                                }

                                //We've found lastmodif_date
                                if(xml.name() == "lm_date") {
                                    xml.readNext(); lastmodif_date=QDateTime::fromString(xml.text().toString());
                                    qDebug()<<"lastmodif_date="<<lastmodif_date.toString()<<"\n";
                                }

                                //We've found isArchive
                                if(xml.name() == "isArchive") {
                                    xml.readNext(); if (xml.text() == "false") isArchive=false; else isArchive=true;
                                    qDebug()<<"isArchive="<<isArchive<<"\n";
                                }

                                //We've found isDeleted
                                if(xml.name() == "isDeleted") {
                                    xml.readNext(); if (xml.text() == "false") isDeleted=false; else isDeleted=true;
                                    qDebug()<<"isDeleted="<<isDeleted<<"\n";
                                }

                                // We've found description
                                if(xml.name() == "description") {
                                    xml.readNext();
                                    description=xml.text().toString();
                                    qDebug()<<"description="<<description<<"\n";
                                }

                                // We've found type
                                if(xml.name() == "type") {
                                    xml.readNext();
                                    if (xml.text().toString() == "Audio") type=ENUM::Audio;
                                    if (xml.text().toString() == "Video") type=ENUM::Video;
                                    if (xml.text().toString() == "Image") type=ENUM::Image;
                                    qDebug()<<"type="<<type<<"\n";
                                }

                                // We've found link
                                if(xml.name() == "link") {
                                    xml.readNext();
                                    link=xml.text().toString();
                                    qDebug()<<"link="<<link<<"\n";
                                }
                            }
                            // ...and next...
                            xml.readNext();
                        }
                        qDebug()<<"ajout recording "<<identificateur<<"\n";
                        Recording* n=new Recording(identificateur,titre,creation_date,lastmodif_date,isArchive,isDeleted,description,type,link);
                        NotesManager::Iterator it=NotesManager::getIterator();
                        while(!it.isDone()){
                            if(!it.liste()->isEmpty())
                            if (it.current().getId()==identificateur){
                                it.liste()->push_back(n);
                                flag=1;
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
                        if (flag==0){
                            notes[nbNotes]= new QList<Note*>;
                            QList<Note*>* liste=notes[nbNotes++];
                            (*liste).push_front(n);
                        }
                    }
                    xml.readNextStartElement();
                }
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

void NotesManager::save_fichier(){
    QFile newfile("fichier.xml");
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    NotesManager* m=NotesManager::getInstance();
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    if(m->getFilename()!="") stream.writeTextElement("Fichier",m->getFilename());
    else stream.writeTextElement("Fichier","default.xml");
    stream.writeEndDocument();
}

void NotesManager::load_fichier() const{
    QFile fin("fichier.xml");
    QString fichier;
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
                // We've found Fichier.
                if(xml.name() == "Fichier") {
                    xml.readNext(); fichier=xml.text().toString();
                    qDebug()<<"fichier="<<fichier<<"\n";
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
        NotesManager* m=NotesManager::getInstance();
        if(fichier=="") m->setFilename("default.xml");
        m->setFilename(fichier);
        m->load();
        RelationManager& rm=RelationManager::getInstance();
        rm.load(getFilename());
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
 * \brief     Fonctions relatives au Design Pattern Singleton sur le NotesManager
 */
NotesManager::Handler NotesManager::handler=NotesManager::Handler();


/**
 * \fn        NotesManager *NotesManager::getInstance()
 * \brief     Permet d'obtenir un pointeur sur le manager de notes.
 */
NotesManager *NotesManager::getInstance(){
    //if (instanceUnique==0)
        //instanceUnique=new NotesManager;
    if(handler.instance==0) handler.instance=new NotesManager;
    return handler.instance;
}

/**
 * \fn        void NotesManager::libererInstance()
 * \brief     Permet de libérer le manager de note.
 */
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
   //NotesManager::Iterator it=NotesManager::getIterator();
    //Suppression de la dernière version
//    std::cout<<id.toStdString()<<" : id en cours a supprimer\n";
    Note& n=getNote(id);
    if (n.getNbIsRef()!=0){
        std::cout<<"La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée.\n";
//        QMessageBox msgBox;
//        msgBox.setText("La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée.\n");
//        msgBox.exec();
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
//        if(n.getNbRef()!=0) n.deleteAllReferenceOLD();
        if(n.references.size()!=0) n.deleteAllReference();
        n.setIsDeleted(true);
    }
}

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
        if(!itNote.liste()->isEmpty())
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
        }
        itNote.next();
    }
}

/**
 * \fn        void NotesManager::restoreNoteTrash(const QString& id)
 * \brief     Restaure une note supprimée en passant à false son attribut isDeleted
 * \param     const QString& id             ID de la note supprimée à restaurer
 */
void NotesManager::restoreNoteTrash(const QString& id){
    NotesManager::Iterator it=NotesManager::getIterator();
    while(!it.isDone()) {
        if(!it.liste()->isEmpty()){
            if(it.current().getId()!=id) it.next();
            else break;
        }
        else it.next();
    }
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
        if (tabrelations[i]->getTitle()==title) return *tabrelations[i];
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

/**
 * \fn        QList<TupleNote_Relation*> NotesManager::getListTupleAscendants(const QString& id)
 * \brief     Renvoie la liste de tous les couples ascendants de la relation portant l'ID id.
 * \param    const QString& id          ID de la relation concernée
 */
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
/**
 * \fn        QList<TupleNote_Relation*> NotesManager::getListTupleDescendants(const QString& id)
 * \brief     Renvoie la liste de tous les couples descendants de la relation portant l'ID id.
 * \param    const QString& id          ID de la relation concernée
 */
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
 * \brief     Fonctions relatives au Design Pattern Singleton sur le RelationManager
 */
RelationManager::Handler RelationManager::handler=RelationManager::Handler();

/**
 * \fn        RelationManager& RelationManager::getInstance()
 * \brief     Permet d'obtenir un pointeur sur le manager de relations.
 */
 RelationManager& RelationManager::getInstance(){
    if(handler.instance==0) handler.instance=new RelationManager;
    return *handler.instance;
}

 /**
  * \fn        void RelationManager::libererInstance()
  * \brief     Permet de libérer le manager de relation.
  */
 void RelationManager::libererInstance(){
    delete handler.instance;
    handler.instance=0;
}

 /**
  * \fn        void RelationManager::load()
  * \brief     Charge les relations d'un fichier XML dans l'application
  * \details   Cette fonction ne charge que les relations une fonction dédiée aux notes est définie dans la
  *              classe NotesManager.
  * \param     const QString& file      Nom du fichier XML à parser
  */
void RelationManager::load(const QString &file){
    QFile fin(file);
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
            if(xml.name() == "relation") {
                qDebug()<<"new relation\n";
                QString title;
                QString description;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                        // We've found title
                        if(xml.name() == "title") {
                            xml.readNext(); title=xml.text().toString();
                            qDebug()<<"titre="<<title<<"\n";
                        }
                        // We've found description
                        if(xml.name() == "description") {
                            xml.readNext();
                            description=xml.text().toString();
                            qDebug()<<"description="<<description<<"\n";
                        }

                        if(xml.name()=="notecouple") xml.readNext();

                        if(xml.name() == "couple") {
                            Relation& r=getNewRelation(title,description);
                            qDebug()<<"new couple\n";
                            QString notex;
                            QString notey;
                            QString label;
                            bool symetric;
                            QXmlStreamAttributes attributes = xml.attributes();
                            xml.readNext();
                            //We're going to loop over the things because the order might change.
                            //We'll continue the loop until we hit an EndElement named article.
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {

                                    // We've found notex
                                    if(xml.name() == "notex") {
                                        xml.readNext(); notex=xml.text().toString();
                                        qDebug()<<"notex="<<notex<<"\n";
                                    }
                                    // We've found notey
                                    if(xml.name() == "notey") {
                                        xml.readNext();
                                        notey=xml.text().toString();
                                        qDebug()<<"notey="<<notey<<"\n";
                                    }

                                    // We've found label
                                    if(xml.name() == "label") {
                                        xml.readNext();
                                        label=xml.text().toString();
                                        qDebug()<<"label="<<label<<"\n";
                                    }

                                    // We've found symetric
                                    if(xml.name() == "symetric") {
                                        xml.readNext();
                                        if(xml.text().toString()=="false") symetric=false;
                                        else symetric=true;
                                        qDebug()<<"symetric="<<symetric<<"\n";
                                    }
                                }
                                // ...and next...
                                xml.readNext();
                            }
                            qDebug()<<"ajout couple "<<notex<<"  "<<notey<<"\n";
                            NotesManager* m=NotesManager::getInstance();
                            r.getNewCoupleRelation(&m->getNote(notex),&m->getNote(notey),label,symetric);
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout relation "<<title<<"\n";
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

