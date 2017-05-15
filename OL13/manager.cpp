#include "Manager.h"
#include<fstream>

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

Note& NotesManager::getNote(const string& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("error, non existent note");

}

/*Note& NotesManager::getNewNote(const string& id){
    Note* n=new Note(id," ");
    createNote(n);
    return *n;
}*/

NotesManager::NotesManager():notes(nullptr),nbNotes(0),nbMaxNotes(0){}

NotesManager::~NotesManager(){
    save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void NotesManager::save() const {
    ofstream fout(filename);
    for(unsigned int i=0; i<nbNotes; i++){
        fout<<*notes[i];
    }
    fout.close();
}

ostream& operator<<(ostream& f, const Note& n){
    f<<n.getId()<<"\n";
    f<<n.getTitle()<<"\n";
    return f;
}

/*void NotesManager::load(const string& f) {
    if (filename!=f) save();
    filename=f;
    ifstream fin(filename); // open file
    if (!fin) throw NotesException("error, file does not exist");
    while(!fin.eof()&&fin.good()){
        char tmp[1000];
        fin.getline(tmp,1000); // get id on the first line
        if (fin.bad()) throw NotesException("error reading note id on file");
        string id=tmp;
        fin.getline(tmp,1000); // get title on the next line
        if (fin.bad()) throw NotesException("error reading note title on file");
        string title=tmp;
        fin.getline(tmp,1000); // get text on the next line
        if (fin.bad()) throw NotesException("error reading note text on file");
        string text=tmp;
        Note* n=new Note(id,title,text);
        createNote(n);
        if (fin.peek()=='\r') fin.ignore();
        if (fin.peek()=='\n') fin.ignore();
    }
    fin.close(); // close file
}*/

NotesManager::Handler NotesManager::handler=NotesManager::Handler();

NotesManager& NotesManager::getInstance(){
    //if (instanceUnique==0)
        //instanceUnique=new NotesManager;
    if(handler.instance==nullptr) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}


void NotesManager::deleteNote(const Note& n){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==n.getId()) delete notes[i];//comportement précis à définir
    }
}

void NotesManager::editNote(string& id, string& title){
    //à définir
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

Note& ArchiveManager::getArchive(const string& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("error, non existent note");

}

ArchiveManager::ArchiveManager():notes(nullptr),nbNotes(0),nbMaxNotes(0){}

ArchiveManager::~ArchiveManager(){
    save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void ArchiveManager::save() const {
    ofstream fout(filename);
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

void ArchiveManager::restoreArchive(const string& id){
    //à définir
}

ArchiveManager::Handler ArchiveManager::handler=ArchiveManager::Handler();

ArchiveManager& ArchiveManager::getInstance(){
    //if (instanceUnique==0)
        //instanceUnique=new NotesManager;
    if(handler.instance==nullptr) handler.instance=new ArchiveManager;
    return *handler.instance;
}

void ArchiveManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
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

Note& TrashManager::getTrash(const string& id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("error, non existent note");

}

TrashManager::TrashManager():notes(nullptr),nbNotes(0),nbMaxNotes(0){}

TrashManager::~TrashManager(){
    save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void TrashManager::save() const {
    ofstream fout(filename);
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

void TrashManager::restoreTrash(const string& id){
    //à définir
}

TrashManager::Handler TrashManager::handler=TrashManager::Handler();

TrashManager& TrashManager::getInstance(){
    //if (instanceUnique==0)
        //instanceUnique=new NotesManager;
    if(handler.instance==nullptr) handler.instance=new TrashManager;
    return *handler.instance;
}

void TrashManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}
