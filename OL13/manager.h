#ifndef MANAGER_H
#define MANAGER_H
#include <string>
#include <iostream>
#include "notes.h"
#include "relations.h"
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
        Handler():instance(0){}
        ~Handler(){delete instance; instance=0;}
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
    string filename;

    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);
    struct Handler{
        NotesManager* instance;
        Handler():instance(0){}
        ~Handler(){delete instance; instance=0;}
    };
    static Handler handler;
public:
    Note& getNewNote(const QString& id); //Revoir pour la déclaration suivant le type de note
    Note& getNote(const QString& id);
    void deleteNote(Note *n);
    void createNote(Note* n); //je l'ai déplacé en privé pour pourvoir ajouté une note créer par interface
    void editNote(QString& id);
    void setFilename(string f){filename=f;}
    string getFilename()const {return filename;}
    void load();
    void save() const;

    static NotesManager* getInstance();
    static void libererInstance();

    //Utile de faire un manager de trash ?
    void emptyTrash();

    /*Autres méthodes singleton:
        static NotesManager& getInstance(){
        //crée et donne accès à l'unique instance
        static NotesManager instance;
        return instance;
    }
    */
};

/*class ArchiveManager {
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
        Handler():instance(0){}
        ~Handler(){delete instance; instance=0;}
    };
    static Handler handler;
public:
    Note& getArchive(const QString& id);
    void deleteArchive(const Note& n);
    void restoreArchive(const QString& id);

    void load(const QString& f);
    void save() const;

    static ArchiveManager& getInstance();
    static void libererInstance();

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
        Handler():instance(0){}
        ~Handler(){delete instance; instance=0;}
    };
    static Handler handler;
public:
    Note& getTrash(const QString& id);
    void emptyTrash();
    void restoreTrash(const QString& id);

    void load(const QString& f);
    void save() const;

    static TrashManager& getInstance();
    static void libererInstance();


};*/



class RelationManager {
private:
    Relation** tabrelations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    void addRelation(Relation* r);

   /* RelationManager();
    ~RelationManager();
    RelationManager(const RelationManager& m);
    RelationManager& operator=(const RelationManager& m);
    */
    struct Handler{
        RelationManager* instance;
        Handler():instance(0){}
        ~Handler(){delete instance; instance=0;}
    };
    static Handler handler;
public:
    Relation &getRelation(const QString& title);
    void deleteRelation(const Relation& r);

    static RelationManager& getInstance();
    static void libererInstance();

    //Iterator
    class Iterator{
    private:
        Relation** tab;  //adresse du tableau de pointeur
        unsigned int nb;        //nb élément dans le tableau
        unsigned int index;     //indice courant
        Iterator(Relation** t, unsigned int n):tab(t), nb(n), index(0){}
        friend class RelationManager;
    public:
        void next(){
            if (index==nb) throw NotesException("incrémentation invalide");
            index++;
        }
        bool isDone()const {return nb==index;}
        Relation& current() const {return *tab[index];}
    };
    Iterator getIterator(){
        return Iterator(tabrelations, nbRelations);
    }
};


ostream& operator<<(ostream& f, const Note& n);

#endif // MANAGER_H
