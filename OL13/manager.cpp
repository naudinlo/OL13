#include "manager.h"
#include<fstream>
#include <QMessageBox>
#include "QInclude.h"


/**************NotesManager********************/
void NotesManager::createNote(Note* n){
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

Note& NotesManager::getNote(const QString& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("error, non existent note");

}

/*Note& NotesManager::getNewNote(const QString& id){
    Note* n=new Note(id," ");
    createNote(n);
    return *n;
}*/

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
            Article a=dynamic_cast<Article>(**notes[i]);
            stream.writeStartElement("article");
            stream.writeTextElement("id",a.getId());
            stream.writeTextElement("title",a.getTitle());
            stream.writeTextElement("c_date",a.getCreation_date());
            stream.writeTextElement("lm_date",a.getLastmodif_date());
            if(a.getIsArchive()) stream.writeTextElement("isArchive","true");
            else stream.writeTextElement("isArchive","false");
            if(a.getIsDeleted()) stream.writeTextElement("isDeleted","true");
            else stream.writeTextElement("isDeleted","false");
            stream.writeTextElement("text",a.getText());
            stream.writeEndElement();
        }

        if(notes[i]->getType()=="Task"){
            Task t=dynamic_cast<Task>(notes[i]);
            stream.writeStartElement("Task");
            stream.writeTextElement("id",t.getId());
            stream.writeTextElement("title",t.getTitle());
            stream.writeTextElement("c_date",t.getCreation_date());
            stream.writeTextElement("lm_date",t.getLastmodif_date());
            if(t.getIsArchive()) stream.writeTextElement("isArchive","true");
            else stream.writeTextElement("isArchive","false");
            if(t.getIsDeleted()) stream.writeTextElement("isDeleted","true");
            else stream.writeTextElement("isDeleted","false");
            stream.writeTextElement("action",t.getAction());
            stream.writeTextElement("priority",t.getPriority());
            stream.writeTextElement("d_date",t.getDueDate());
            stream.writeTextElement("status",t.getStatus());
            stream.writeEndElement();
        }

        if(notes[i]->getType()=="Recording"){
            Recording r=dynamic_cast<Recording>(notes[i]);
            stream.writeStartElement("Task");
            stream.writeTextElement("id",r.getId());
            stream.writeTextElement("title",r.getTitle());
            stream.writeTextElement("c_date",r.getCreation_date());
            stream.writeTextElement("lm_date",r.getLastmodif_date());
            if(r.getIsArchive()) stream.writeTextElement("isArchive","true");
            else stream.writeTextElement("isArchive","false");
            if(r.getIsDeleted()) stream.writeTextElement("isDeleted","true");
            else stream.writeTextElement("isDeleted","false");
            stream.writeTextElement("description",r.getDescription());
            stream.writeTextElement("type",r.getType());
            stream.writeTextElement("link",r.getLink());
            stream.writeEndElement();
        }
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


void NotesManager::deleteNote(Note* n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==n->getId()){
            if (n->getNbIsRef()!=0){
                std::cout<<"La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée.";
                QMessageBox msgBox;
                msgBox.setText("La note est référencée par d'autres notes et ne peut donc être supprimée. Elle est automatiquement archivée");
                msgBox.exec();
                n->setIsArchive(true);
            }
            else{
                /* LE MANAGER NE MARCHE PAS POUR LES RELATIONS ! Pq ?
                //Il faut un relation manager pour appliquer removeNoteRelation sur toutes les relations
                //removeNoteRelation(n);
                RelationManager& m=RelationManager::getInstance();
                //Supprimer toutes les présences d'une note dans l'ensemble des relations
                for(RelationManager::Iterator it= m.getIterator(); !it.isDone(); it.next()){
                    it.current().removeNoteRelation(n);
                };*/

                n->setIsDeleted(true);
                //delete notes[i];//comportement précis à définir
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


Relation& RelationManager::getRelation(const QString& title){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabrelations[i]->getTitle()==title) return *tabrelations[i];
    }
    throw NotesException("error, non existent relation");
}

void RelationManager::deleteRelation(const Relation& r){
    for(unsigned int i=0; i<nbRelations; i++){
        if (tabrelations[i]->getTitle()==r.getTitle()){
            delete tabrelations[i];
        }
    }
}

/* RELATION MANAGER NE MARCHE PAS
 RelationManager& RelationManager::getInstance(){
    if(handler.instance==nullptr) handler.instance=new RelationManager;
    return *handler.instance;
}
void RelationManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}
*/
