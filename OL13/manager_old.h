#ifndef MANAGER_H
#define MANAGER_H
#include <string>
#include <iostream>
#include "notes.h"
#include "relations.h"
#include "QInclude.h"


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
    mutable QString filename;

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
//    Note& getNewNote(const QString& id, const QString& ti); //Revoir pour la déclaration suivant le type de note
    Article& getNewArticle(const QString& id, const QString& ti,const QString& te); //Revoir pour la déclaration suivant le type de note
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d);
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p);
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, const QDateTime d);
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s);
    Recording& getNewRecording(const QString& id, const QString& ti,const QString& d, ENUM::RecordingType r, QString l);

    Note& getNote(const QString& id);
    void deleteNote(const QString& id);
    void createNote(const QString& id); //je l'ai déplacé en privé pour pourvoir ajouté une note créer par interface
    void editNote(QString& id);
    void setFilename(const QString f){filename=f;}
    QString getFilename()const {return filename;}
    void load();
    void save() const;

    static NotesManager* getInstance();
    static void libererInstance();

    //Utile de faire un manager de trash ?
    void emptyTrash();
    void restoreNoteTrash(const QString& id);


    class Iterator{
        private:
            Note** tab;  //adresse du tableau de pointeur
            unsigned int nb;        //nb élément dans le tableau
            unsigned int index;     //indice courant
            //Dans la partie privée
            Iterator(Note** t, unsigned int n):tab(t), nb(n), index(0){}
            friend class NotesManager;
        public:
            void next(){
                if (index==nb){
                    std::cout<<"incrémentation invalide";
                    throw NotesException("incrémentation invalide");
                }
                index++;
            }
            bool isDone()const {return nb==index;}
            Note& current() const {return *tab[index];}
        };
        Iterator getIterator(){
            return Iterator(notes, nbNotes);
        }


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
    Relation &getNewRelation(const QString& title,const QString& desc);
    Relation &getRelation(const QString& title);
    void deleteRelation(const QString& title);

    unsigned int getNbRelations() const{return nbRelations;}

    static RelationManager& getInstance();
    static void libererInstance();

//    void createRelation(const QString& title,const QString& desc);

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