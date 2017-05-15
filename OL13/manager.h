#ifndef MANAGER_H
#define MANAGER_H
#include <string>
#include <iostream>
#include "notes.h"
using namespace std;


/*class Manager{
private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    //string filename;

    Manager();
    ~Manager();
    Manager(const Manager& m);
    Manager& operator=(const Manager& m);
    struct Handler{
        Manager* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance; instance=nullptr;}
    };
    static Handler handler;
public:
    void load(const string& f);
    void save() const;

    static Manager& getInstance();
    static void libererInstance();
};*/

class NotesManager {
private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void createNote(Note* n);
    string filename;

    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);
    struct Handler{
        NotesManager* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance; instance=nullptr;}
    };
    static Handler handler;
public:
    Note& getNewNote(const string& id); //Revoir pour la déclaration suivant le type de note
    Note& getNote(const string& id);
    void deleteNote(const Note &n);
    void editNote(string& id, string& title);

    void load(const string& f);
    void save() const;

    static NotesManager& getInstance();
    static void libererInstance();

    /*Autres méthodes singleton:
        static NotesManager& getInstance(){
        //crée et donne accès à l'unique instance
        static NotesManager instance;
        return instance;
    }
    */
};

class ArchiveManager {
private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void addNote(Note* n);
    string filename;

    ArchiveManager();
    ~ArchiveManager();
    ArchiveManager(const ArchiveManager& m);
    ArchiveManager& operator=(const ArchiveManager& m);
    struct Handler{
        ArchiveManager* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance; instance=nullptr;}
    };
    static Handler handler;
public:
    Note& getArchive(const string& id);
    void deleteArchive(const Note& n);
    void restoreArchive(const string& id);

    void load(const string& f);
    void save() const;

    static ArchiveManager& getInstance();
    static void libererInstance();

    /*Autres méthodes singleton:
        static NotesManager& getInstance(){
        //crée et donne accès à l'unique instance
        static NotesManager instance;
        return instance;
    }
    */
};

class TrashManager {
private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void addNote(Note* n);
    string filename;

    TrashManager();
    ~TrashManager();
    TrashManager(const TrashManager& m);
    TrashManager& operator=(const TrashManager& m);
    struct Handler{
        TrashManager* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance; instance=nullptr;}
    };
    static Handler handler;
public:
    Note& getTrash(const string& id);
    void emptyTrash();
    void restoreTrash(const string& id);

    void load(const string& f);
    void save() const;

    static TrashManager& getInstance();
    static void libererInstance();

    /*Autres méthodes singleton:
        static NotesManager& getInstance(){
        //crée et donne accès à l'unique instance
        static NotesManager instance;
        return instance;
    }
    */
};

ostream& operator<<(ostream& f, const Note& n);

#endif // MANAGER_H
