#include "manager.h"
#include<fstream>
#include <QMessageBox>


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
    ofstream fout(filename.c_str());
    for(unsigned int i=0; i<nbNotes; i++){
        fout<<*notes[i];
    }
    fout.close();
}

ostream& operator<<(ostream& f, const Note& n){
    f<<n.getId().toStdString()<<"\n";
    f<<n.getTitle().toStdString()<<"\n";
    return f;
}

/*void NotesManager::load(const QString& f) {
    if (filename!=f) save();
    filename=f;
    ifstream fin(filename); // open file
    if (!fin) throw NotesException("error, file does not exist");
    while(!fin.eof()&&fin.good()){
        char tmp[1000];
        fin.getline(tmp,1000); // get id on the first line
        if (fin.bad()) throw NotesException("error reading note id on file");
        QString id=tmp;
        fin.getline(tmp,1000); // get title on the next line
        if (fin.bad()) throw NotesException("error reading note title on file");
        QString title=tmp;
        fin.getline(tmp,1000); // get text on the next line
        if (fin.bad()) throw NotesException("error reading note text on file");
        QString text=tmp;
        Note* n=new Note(id,title,text);
        createNote(n);
        if (fin.peek()=='\r') fin.ignore();
        if (fin.peek()=='\n') fin.ignore();
    }
    fin.close(); // close file
}*/

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
                };
                */
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

void ArchiveManager::addNote(Note* n){
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
}

/*************TrashManager*******************/

void TrashManager::addNote(Note* n){
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
}

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
