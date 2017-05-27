#include "manager.h"
#include<fstream>
#include <QMessageBox>
#include "QInclude.h"



/**************NotesManager********************/
//void NotesManager::createNote(const QString &id){
//    for(unsigned int i=0; i<nbNotes; i++){
//        if (notes[i]->getId()==id->getId()) {
////            std::cout<<"\n erreur dans le throw \n";
//            throw NotesException("error, creation of an already existent note");
//        }
//    }
//    if (nbNotes==nbMaxNotes){
//        Note** newNotes= new Note*[nbMaxNotes+5];
//        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
//        Note** oldNotes=notes;
//        notes=newNotes;
//        nbMaxNotes+=5;
//        if (oldNotes) delete[] oldNotes;
//    }
//    notes[nbNotes++]=id;
//}

Article& NotesManager::getNewArticle(const QString& id, const QString& ti,const QString& te){
    std::cout<<"1";
    Article* n=new Article(id,ti,te);
    std::cout<<"2";
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id){
            std::cout<<"3";
            throw NotesException("error, creation of an already existent note");
//            return dynamic_cast<Article&>(*notes[i]);
            return (Article&)*notes[i];
        }
    }
    std::cout<<"4";
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    std::cout<<"5";
    int i=nbNotes;
    notes[nbNotes++]=n;
    //            return dynamic_cast<Article&>(*notes[i]);
    return (Article&)*notes[i];
}


Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d){
    Task* n=new Task(id,ti,a,s,p,d);
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id){
            throw NotesException("error, creation of an already existent note");
//            return dynamic_cast<Task&>(*notes[i]);
            return (Task&)*notes[i];
        }
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    int i=nbNotes;
    notes[nbNotes++]=n;
    //            return dynamic_cast<Task&>(*notes[i]);
    return (Task&)*notes[i];
}

Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p){
    Task* n=new Task(id,ti,a,s,p);
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id){
            throw NotesException("error, creation of an already existent note");
//            return dynamic_cast<Task&>(*notes[i]);
            return (Task&)*notes[i];
        }
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    int i=nbNotes;
    notes[nbNotes++]=n;
    //            return dynamic_cast<Task&>(*notes[i]);
    return (Task&)*notes[i];
}

Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, const QDateTime d){
    Task* n=new Task(id,ti,a,s,d);
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id){
            throw NotesException("error, creation of an already existent note");
//            return dynamic_cast<Task&>(*notes[i]);
            return (Task&)*notes[i];
        }
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    int i=nbNotes;
    notes[nbNotes++]=n;
    //            return dynamic_cast<Task&>(*notes[i]);
    return (Task&)*notes[i];
}

Task& NotesManager::getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s){
    Task* n=new Task(id,ti,a,s);
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id){
            throw NotesException("error, creation of an already existent note");
//            return dynamic_cast<Task&>(*notes[i]);
            return (Task&)*notes[i];
        }
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    int i=nbNotes;
    notes[nbNotes++]=n;
    //            return dynamic_cast<Task&>(*notes[i]);
    return (Task&)*notes[i];
}

Recording& NotesManager::getNewRecording(const QString& id, const QString& ti,const QString& d, ENUM::RecordingType r, QString l){
    Recording* n=new Recording(id,ti,d,r,l);
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id){
            throw NotesException("error, creation of an already existent note");
//            return dynamic_cast<Recording&>(*notes[i]);
            return (Recording&)*notes[i];
        }
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    int i=nbNotes;
    notes[nbNotes++]=n;
    //            return dynamic_cast<Recording&>(*notes[i]);
    return (Recording&)*notes[i];
}

//Si l'on ne créé uniquement un getNewNote alors comment définir s'il s'agit d'un article, d'une tache ou d'un recording?
//void NotesManager::getNewNote(const QString& id, const QString& ti){
//    Note* n=new Note(id,ti);
//    for(unsigned int i=0; i<nbNotes; i++){
//        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
//    }
//    if (nbNotes==nbMaxNotes){
//        Note** newNotes= new Note*[nbMaxNotes+5];
//        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
//        Note** oldNotes=notes;
//        notes=newNotes;
//        nbMaxNotes+=5;
//        if (oldNotes) delete[] oldNotes;
//    }
//    notes[nbNotes++]=n;
//}

//ATTENTION : faire une fonction pour chaque type ? Ou un dynamic cast ?
Note& NotesManager::getNote(const QString& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("error, non existent note");

}

NotesManager::NotesManager():notes(0),nbNotes(0),nbMaxNotes(0){}

NotesManager::~NotesManager(){
    save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void NotesManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("notes");
    for(unsigned int i=0; i<nbNotes; i++){

        if(notes[i]->getType()=="Article"){
            Article& a=dynamic_cast<Article&>(*notes[i]);
            stream.writeStartElement("article");
            stream.writeTextElement("id",a.getId());
            stream.writeTextElement("title",a.getTitle());
            stream.writeTextElement("c_date",a.getCreation_date().toString());
            stream.writeTextElement("lm_date",a.getLastmodif_date().toString());
            if(a.getIsArchive()) stream.writeTextElement("isArchive","true");
            else stream.writeTextElement("isArchive","false");
            if(a.getIsDeleted()) stream.writeTextElement("isDeleted","true");
            else stream.writeTextElement("isDeleted","false");
            stream.writeTextElement("text",a.getText().toPlainText());
            stream.writeEndElement();
        }

        if(notes[i]->getType()=="Task"){
            Task& t=dynamic_cast<Task&>(*notes[i]);
            stream.writeStartElement("Task");
            stream.writeTextElement("id",t.getId());
            stream.writeTextElement("title",t.getTitle());
            stream.writeTextElement("c_date",t.getCreation_date().toString());
            stream.writeTextElement("lm_date",t.getLastmodif_date().toString());
            if(t.getIsArchive()) stream.writeTextElement("isArchive","true");
            else stream.writeTextElement("isArchive","false");
            if(t.getIsDeleted()) stream.writeTextElement("isDeleted","true");
            else stream.writeTextElement("isDeleted","false");
            stream.writeTextElement("action",t.getAction());
            stream.writeTextElement("priority",QString::number(t.getPriority()));
            stream.writeTextElement("d_date",t.getDueDate().toString());
            if(t.getStatus()==ENUM::StatusType::Pending)
            stream.writeTextElement("status","Pending");
            if(t.getStatus()==ENUM::StatusType::OnGoing)
            stream.writeTextElement("status","OnGoing");
            if(t.getStatus()==ENUM::StatusType::Completed)
            stream.writeTextElement("status","Completed");
            stream.writeEndElement();
        }

        if(notes[i]->getType()=="Recording"){
            Recording& r=dynamic_cast<Recording&>(*notes[i]);
            stream.writeStartElement("Task");
            stream.writeTextElement("id",r.getId());
            stream.writeTextElement("title",r.getTitle());
            stream.writeTextElement("c_date",r.getCreation_date().toString());
            stream.writeTextElement("lm_date",r.getLastmodif_date().toString());
            if(r.getIsArchive()) stream.writeTextElement("isArchive","true");
            else stream.writeTextElement("isArchive","false");
            if(r.getIsDeleted()) stream.writeTextElement("isDeleted","true");
            else stream.writeTextElement("isDeleted","false");
            stream.writeTextElement("description",r.getDescription().toPlainText());
            //stream.writeTextElement("type",r.getType()); //à gérer suivant la façon de stocker l'image
            stream.writeTextElement("link",r.getLink());
            stream.writeEndElement();
        }
    }
    stream.writeEndElement();

    stream.writeStartElement("relationmanager");
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
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

/*void NotesManager::load() {
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
            if(xml.name() == "notes") continue;
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
                addArticle(identificateur,titre,text);
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
}*/


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
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id){
            Note* n=notes[i];
            if (n->getNbIsRef()!=0){
                std::cout<<"La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée.";
                QMessageBox msgBox;
                msgBox.setText("La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée");
                msgBox.exec();
                n->setIsArchive(true);
            }
            else{
                //Relation manager applique removeNoteRelation sur toutes les relations
                //removeNoteRelation(n);
                RelationManager& m=RelationManager::getInstance();
                //Supprimer toutes les présences d'une note dans l'ensemble des relations
                for(RelationManager::Iterator it= m.getIterator(); !it.isDone(); it.next()){
                    it.current().removeNoteRelation(n);
                }
                n->setIsDeleted(true);
            }
        }
    }
}

void NotesManager::emptyTrash(){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getIsDeleted()){
            notes[i]->setNbRef(0);
            delete notes[i];
        }
    }
}


void NotesManager::editNote(QString& id){
    unsigned int i=0;
    while(i<nbNotes && notes[i]->getId()!=id) i++;
    if (i==nbNotes){
        throw NotesException("error, non existent note");
    }
    else{
        Note* ncopy(notes[i]);   //last modif date automatiquement mis à jour dans la copie
        //a definir avec l'interface
    }
}

void NotesManager::restoreNoteTrash(const QString& id){
    unsigned int i=0;
    while(i<nbNotes && notes[i]->getId()!=id) i++;
    if (i==nbNotes){
        throw NotesException("error, non existent note");
    }
    else{
        if (notes[i]->getIsDeleted()) notes[i]->setIsDeleted(false);
    }
}



/*************ArchiveManager*******************/

/*void ArchiveManager::addNote(Note* n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==n->getId()) throw NotesException("error, creation of an already existent note");
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=n;
}

Note& ArchiveManager::getArchive(const QString& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("error, non existent note");

}

ArchiveManager::ArchiveManager():notes(0),nbNotes(0),nbMaxNotes(0){}

ArchiveManager::~ArchiveManager(){
    save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void ArchiveManager::save() const {
    ofstream fout(filename.c_str());
    for(unsigned int i=0; i<nbNotes; i++){
        fout<<*notes[i];
    }
    fout.close();
}

void ArchiveManager::deleteArchive(const Note& n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==n.getId()) delete notes[i];//comportement précis à définir
    }
}

void ArchiveManager::restoreArchive(const QString& id){
    //à définir
}

ArchiveManager::Handler ArchiveManager::handler=ArchiveManager::Handler();

ArchiveManager& ArchiveManager::getInstance(){
    //if (instanceUnique==0)
        //instanceUnique=new NotesManager;
    if(handler.instance==0) handler.instance=new ArchiveManager;
    return *handler.instance;
}

void ArchiveManager::libererInstance(){
    delete handler.instance;
    handler.instance=0;
}*/

/*************TrashManager*******************/

/*void TrashManager::addNote(Note* n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==n->getId()) throw NotesException("error, creation of an already existent note");
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=n;
}

Note& TrashManager::getTrash(const QString& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("error, non existent note");

}

TrashManager::TrashManager():notes(0),nbNotes(0),nbMaxNotes(0){}

TrashManager::~TrashManager(){
    save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void TrashManager::save() const {
    ofstream fout(filename.c_str());
    for(unsigned int i=0; i<nbNotes; i++){
        fout<<*notes[i];
    }
    fout.close();
}

void TrashManager::emptyTrash(){
    for(unsigned int i=0; i<nbNotes; i++){
        delete notes[i];
    }
}

void TrashManager::restoreTrash(const QString& id){
    //à définir
}

TrashManager::Handler TrashManager::handler=TrashManager::Handler();

TrashManager& TrashManager::getInstance(){
    //if (instanceUnique==0)
        //instanceUnique=new NotesManager;
    if(handler.instance==0) handler.instance=new TrashManager;
    return *handler.instance;
}

void TrashManager::libererInstance(){
    delete handler.instance;
    handler.instance=0;
}*/

/*************RelationManager*******************/

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
    throw NotesException("error, non existent relation");
}

void RelationManager::deleteRelation(const QString &title){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabrelations[i]->getTitle()==title){
            delete tabrelations[i];
        }
    }
}

RelationManager::Handler RelationManager::handler=RelationManager::Handler();

 RelationManager& RelationManager::getInstance(){
    if(handler.instance==0) handler.instance=new RelationManager;
    return *handler.instance;
}
void RelationManager::libererInstance(){
    delete handler.instance;
    handler.instance=0;
}


//void RelationManager::createRelation(Relation* r){
//    for(unsigned int i=0; i<nbRelations; i++){
//        if (tabrelations[i]->getTitle()==r->getTitle()) throw NotesException("error, creation of an already existent relation");
//    }
//    if (nbRelations==nbMaxRelations){
//        Relation** newTab= new Relation*[nbMaxRelations+5];
//        for(unsigned int i=0; i<nbRelations; i++) newTab[i]=tabrelations[i];
//        Relation** oldTab=tabrelations;
//        tabrelations=newTab;
//        nbMaxRelations+=5;
//        if (oldTab) delete[] oldTab;
//    }
//    tabrelations[nbRelations++]=r;
//}

