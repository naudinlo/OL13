/**
 * \file      aff_notes.h
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Page Principale de l'application.
 * \details    Class :
 *                  -page_notes: Permet l'affichage d'une note, des docks associées et actions.
 *                      Attributs :
*
*                                QNote* note;
*                                 Note& n;
*                                 Note* newNote;                 //pointeur vers la nouvelle version d'une note
*                                 QWidget* dock_editer;         //dock permetant l'edition/restauration d'une note
*                                 QDockRelation* dock_aff_Rel; //dock permetant la vue arborescente des relations
*                                 Qreference* widget_ref;     //Indication des références de la note.
*
 *                  -page_vide : Affichage de la page d'acceuil.
 */




#ifndef AFF_NOTES_H
#define AFF_NOTES_H
#include "QInclude.h"
#include "notes.h"
#include "qnote.h"
#include "manager.h"
#include "qrelations.h"
#include "quirelation.h"
#include "qreference.h"
class page_notes: public QWidget
{
    Q_OBJECT

protected:
    QNote* note;
    Note& n;
    Note* newNote;
    QWidget* dock_editer;
    QDockRelation* dock_aff_Rel;
    QPushButton* savebutton;
    Qreference* widget_ref;
    //QLineEdit* titre;
    QLabel* info;
    QHBoxLayout* layout_info;
    QVBoxLayout* layout_p;
    QVBoxLayout* L_titre;
public:
    page_notes(Note &N);
    ~page_notes();
    /**
     * @fn getdock_editer
     * @brief Accesseur de l'attribut dock_editer
     * @return QWidget&
     */
    QWidget& getdock_editer(){
        return *dock_editer;
    }
    /**
     * @fn getdock_aff_rel
     * @brief Accesseur de l'attribut dock_aff_Rel
     * @return
     */
    QDockRelation* getdock_aff_rel(){
        return dock_aff_Rel;
    }

signals:
    void supp_dock_editer();
    void update_model();
    void supp_dock_aff_rel();
    void close_page();
public slots:
    /**
     * @fn on_savebutton_clicked
     * \brief Editer les changement sur la nouvelle version de la note
     * \details demande la mise à jour des docks
     */
    void on_savebutton_clicked(){
        if(newNote!=nullptr){ //normalement impossible
            try{
            note->saveNote(*newNote);
            }
            catch(NotesException e){

            }
        }
        emit(update_model());
        widget_ref->update_model();
    }
    /**
     * \nf editer_note
     * @param status
     * \brief permet d'edité une nouvelle versions de la note
     * \details si la note est archivé, supprimé on effectue sa restauration.
     * On demande la mis à jours des docks
     */
    /**
     * @fn editer_note
     * @param status
     * \brief Créer une nouvelle version de la note en cours
     * \details si elle était archivé/supprimé la restaure et créer une nouvelle versions
     * demmande donc la mis à jours des docks
     *
     */
    void editer_note(bool status){
        note->readOnly(status);
        delete dock_editer;
        if(n.getIsDeleted() ){
            n.setIsDeleted(false);
        }
        else if(n.getIsArchive()){
            n.setIsArchive(false);
        }
        emit(supp_dock_editer());
        if(n.getType()=="Article"){
            newNote =&(NotesManager::getInstance()->editArticle(dynamic_cast<Article&>(n)));
        }
        else if(n.getType()=="Recording"){
            newNote =&NotesManager::getInstance()->editRecording(dynamic_cast<Recording&>(n));
        }
        else
        {
            newNote =&NotesManager::getInstance()->editTask(dynamic_cast<Task&>(n));
        }
        savebutton->setHidden(false);
        emit(update_model());
    }/**
     * @fn Archiver_page_note
     * \brief Archive la note courante.
     * \details demande une mis à jour des docks
     */
    void Archiver_page_note(){
        n.setIsArchive(true);
        n.setIsDeleted(false);
        emit(update_model());
        emit(close_page());
    }
    /**
     * @fn aff_Relation
     * @param titre
     * \brief permet d'afficher une relation depuis le dock de la vue des relations
     * \details demande la mis à jour des docks en cas de modifications de la relations
     */
    void aff_Relation(QString titre){ //permet d'afficher une relation depuis le dock
        QUiRelation showR(RelationManager::getInstance().getRelation(titre),this);
        connect(&showR,SIGNAL(newCouple()),this->getdock_aff_rel(),SLOT(updateModels()));
        showR.exec();

    }
};

class page_vide: public QWidget{
public:
    page_vide();
};

#endif // AFF_NOTES_H
