/**
 * \file      manager.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Regroupe les manager nécessaires pour la gestion des notes et des relations
 *
 * \details   Classes présentes :
 *                  - NotesManager
 *                      Un manager sur l'ensemble des notes, qu'elles soient articles, taches, enregistrement.
 *                      Qu'elles soient archivées ou supprimées.
 *                      Manager multi-fonction qui permet de traiter l'ensemble des notes depuis d'un seul élément.
 *
 *                      Possède un attribut QList<Note*>** notes qui regroupe l'ensemble des notes et de leurs versions.
 *
 *                  - RelationManager
 *                      Un manager sur l'ensemble des relations.
 *                      Possède un Handler pour assurer l'unité de l'accès aux données.
 *                      Possède un Iterator pour faciliter la manipulation des relations.
 *
 *                      Possède un attribut Relation** tabrelations permettant d'accéder à chaque relation
 *                      et à l'ensemble de ses couples de notes associé.
 *
 *             L'ensemble des méthodes définies dans ce fichier sont explicitées dans le fichier .cpp associé.
 */


#ifndef MANAGER_H
#define MANAGER_H
#include <string>
#include <iostream>
#include "notes.h"
#include "relations.h"
#include "QInclude.h"


using namespace std;

class TupleNote_Relation{
    Note& n;
    Relation& r;
public:
    /**
     * @fn getNote
     * @brief Accesseur de l'attribut n
     * @return Note&
     */
    Note& getNote(){return n;}
    /**
     * @fn getRelation
     * @brief Accesseur de l'attribut r
     * @return Relation&
     */
    Relation& getRelation(){return r;}
    /**
     * @fn TupleNote_Relation
     * @brief Constructeur de la classe TupleNote_Relation
     * @param Note& N
     * @param Relation& R
     */
    TupleNote_Relation(Note& N, Relation& R):n(N),r(R){}

};


class NotesManager {
private:
    QList<Note*>** notes;
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
    Article& getNewArticle(const QString& id, const QString& ti,const QString& te);
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d);
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, unsigned int p);
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s, const QDateTime d);
    Task& getNewTask(const QString& id, const QString& ti,const QString& a, ENUM::StatusType s);
    Recording& getNewRecording(const QString& id, const QString& ti,const QString& d, ENUM::RecordingType r, QString l);

    Article& editArticle(Article& A);
    Task& editTask(Task& T);
    Recording& editRecording(Recording& R);

    Note& getNote(const QString& id);
    Note& getNoteVersion(const QString& id, int indice);
    QList<Note*>* getListeVersions(const QString& id);
    void deleteNote(const QString& id);

    /**
     * \fn        void setFilename(const QString f)
     * \brief     Affectation de l'attribut filename du manager à f.
     * \param       const QString f
     */
    void setFilename(const QString f){filename=f;}
    /**
     * \fn        QString getFilename()
     * \brief     Accesseur de l'attribut filename du manager.
     * \return    Qstring
     */
    QString getFilename()const {return filename;}
    void load();
    void save() const;
    void load_fichier() const;
    void save_fichier();

    QList<TupleNote_Relation*> getListTupleAscendants(const QString& id);
    QList<TupleNote_Relation*> getListTupleDescendants(const QString& id);

    QList<Note*> getListAscendants(const QString& id);
    QList<Note*> getListDescendants(const QString& id);

    QList<Note*> getListArchive();
    QList<Note*> getListDeleted();


    static NotesManager* getInstance();
    static void libererInstance();

    void emptyTrash();
    void restoreNoteTrash(const QString& id);

    /**
     * \fn        int getnbNote()
     * \brief     Accesseur du nombre de notes.
     */
    int getnbNote(){return nbNotes;}

    class Iterator{
        private:
            QList<Note*>** tab;  //adresse du tableau de pointeur
            unsigned int nb;        //nb élément dans le tableau
            unsigned int index;     //indice courant
            /**
             * @fn Iterator
             * @fn Constructeur de la Classe Iterator
             * @param QList<Note*>** t
             * @param unsigned int n
             */
            Iterator(QList<Note*>** t, unsigned int n):tab(t), nb(n), index(0){}
            friend class NotesManager;
        public:
            /**
             * @fn next
             * @brief Incrémentation de l'itérateur
             */
            void next(){
                if (index==nb){
                    std::cout<<"incrémentation invalide";
                    throw NotesException("incrémentation invalide");
                }
                index++;
            }
            /**
             * @fn isDone
             * @brief Vérifie si l'itérateur est arrivé à la fin de la liste
             * @return bool
             */
            bool isDone()const {return nb==index;}
            /**
             * @fn current
             * @brief Retourne la dernière version de la note courante
             * @return Note&
             */
            Note& current() const {return *(*tab[index]).begin().operator *();}
            /**
             * @fn liste
             * @brief Retourne la liste des toutes les versions de la note courante
             * @return QList<Note*>**
             */
            QList<Note*>* liste() {return tab[index];}
            /**
             * @fn getIteratorVersions
             * @brief Renvoie un itérateur sur les versions de la note courante
             * @return QList<Note*>::iterator
             */
            QList<Note*>::iterator getIteratorVersions(){
                return (*liste()).begin();
            }
        };
        /**
         * \fn        Iterator getIterator()
         * \brief     Permet d'accéder à l'itérateur de notes.
         */
        Iterator getIterator(){
            return Iterator(notes, nbNotes);
        }

};


class RelationManager {
private:
    Relation** tabrelations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    void addRelation(Relation* r);

    RelationManager();
    ~RelationManager();
    RelationManager(const RelationManager& r);
    RelationManager& operator=(const RelationManager& r);

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

    /**
     * \fn        int getNbRelations()
     * \brief     Accesseur du nombre de relations.
     */
    unsigned int getNbRelations() const{return nbRelations;}

    static RelationManager& getInstance();
    static void libererInstance();
    void load(const QString& file);

    //Iterator
    class Iterator{
    private:
        Relation** tab;  //adresse du tableau de pointeur
        unsigned int nb;        //nb élément dans le tableau
        unsigned int index;     //indice courant
        Iterator(Relation** t, unsigned int n):tab(t), nb(n), index(0){}
        friend class RelationManager;
    public:
        /**
         * @fn next
         * @brief Incrémentation de l'itérateur
         */
        void next(){
            if (index==nb) throw NotesException("incrémentation invalide");
            index++;
        }
        /**
         * @fn isDone
         * @brief Vérifie si on a fini d'itéré
         * @return bool
         */
        bool isDone()const {return nb==index;}
        /**
         * @fn current
         * @brief Renvoi la Relation courante
         * @return Relation&
         */
        Relation& current() const {return *tab[index];}
        /**
         * @fn listeRel
         * @brief Renvoi la liste de Relation courante
         * @return Relation*
         */
        Relation* listeRel() {return tab[index];}
    };
    /**
     * @fn getIterator
     * @brief Renvoi l'itérateur de la classe RelationManager
     * @return Iterator
     */
    Iterator getIterator(){
        return Iterator(tabrelations, nbRelations);
    }
};


ostream& operator<<(ostream& f, const Note& n);

#endif // MANAGER_H
