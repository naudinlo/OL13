/**
 * \file      notes.cpp
 * \author    Garnier Maxime, Naudin Louise, Pépin Hugues
 * \version   1.0
 * \date      14 Juin 2017
 * \brief     Définitions des fonctions déclarées dans le notes.h
 *
 * \details  Domaines des méthodes comprises dans ce fichier :
 *              - Opérateur d'affectation et constructeur de recopie
 *              - Constructeur
 *              - Destructeur
 *              - Affichage
 *              - Référencement de notes
 *           Le détail est donné dans la suite du fichier.
 *
 */

#include "notes.h"
#include "sstream"
#include "manager.h"
#include "QInclude.h"
#include "QString"


/**************OPERATEUR AFFECTATION, CONSTRUCTEUR DE RECOPIE********************/


/**
 * \fn        Note::Note(const Note& n)
 * \brief     Constructeur de recopie
 * \details   Recopie l'ensemble des informations d'une note
 *            Mets à jour la date de dernière modification avec currentDateTime.
 * \param    const Note& n         La note a recopier.
 */
Note::Note(const Note& n):id(n.id),title(n.title),creation_date(n.creation_date),lastmodif_date(QDateTime::currentDateTime()),nbIsRef(n.nbIsRef),isDeleted(false),isArchive(false){
};

/**
 * \fn      Note::operator=(const Note& n)
 * \brief    Surcharge de l'opérateur = dans le cas nouvelle note B=A
 */
Note& Note::operator=(const Note& n){
    if (this!=&n){  //empecher l'auto-affectation
        title=n.title;
    }
    return *this;
};

/**
 * \fn      Article(const Article& a)
 * \brief    Surcharge la méthode constructeur dans le cas nouvel article Article B(A)
 */
Article::Article(const Article& a):Note(a), text(a.text.toPlainText()){};

/**
 * \fn      Article::operator=(const Article& a)
 * \brief    Surcharge de l'opérateur = dans le cas nouvel article Article B=A
 */
Article& Article::operator=(const Article& a){
    if (this!=&a){  //empecher l'auto-affectation
        Note::operator=(a);
        text.setPlainText(a.text.toPlainText());
    }
    return *this;
};


/**
 * \fn      Task::Task(const Task& t)
 * \brief    Surcharge la méthode constructeur dans le cas nouvelle task B(A)
 */
Task::Task(const Task& t):Note(t), action(t.action),status(t.status),priority(t.priority),dueDate(t.dueDate){};

/**
 * \fn      Task& Task::operator=(const Task& t)
 * \brief    Surcharge de l'opérateur = dans le cas nouvelle task B=A
 */
Task& Task::operator=(const Task& t){
    if (this!=&t){  //empecher l'auto-affectation
        Note::operator=(t);
        action=t.action;
        priority=t.priority;
        dueDate=t.dueDate;
        status=t.status;
    }
    return *this;
};

/**
 * \fn       Recording(const Recording& r)
 * \brief    Surcharge de l'opérateur = dans le cas nouveau recording B(A)
 */
Recording::Recording(const Recording& r):Note(r),description(r.description.toPlainText()),type(r.type){};

/**
 * \fn       Recording& Recording::operator=(const Recording& r)
 * \brief    Surcharge de l'opérateur = dans le cas nouveau recording B=A
 */
Recording& Recording::operator=(const Recording& r){
    if (this!=&r){  //empecher l'auto-affectation
        Recording::operator=(r);
        description.setPlainText(r.description.toPlainText());
        type=r.type;
    }
    return *this;
};



/**************CONSTRUCTEUR********************/

/**
 * \fn          Note::Note(const QString& i, const QString& ti)
 * \brief       Constructeur des classes notes, articles task et recording
 * \details     Les classes dérivées Article, Task, Recording utilise en premier lieu le constructeur de Note.
 *              Dans le constructeur de Note, la date de création et de dernière modification sont mises à jours avec la date courrante.
 */
Note::Note(const QString& i, const QString& ti):id(i), title(ti), isArchive(false), isDeleted(false),nbIsRef(0){
    creation_date=QDateTime::currentDateTime();
    lastmodif_date=creation_date;
    this->generateRef(i);
    this->generateRef(ti);
}

/**
 * \fn          Article(const QString& i, const QString& ti, const QString &te)
 * \brief       Constructeur de la classe Article
 * \details     La classe dérivé Article utilise en premier lieu le constructeur de Note.
 */
Article::Article(const QString& i, const QString& ti, const QString &te):Note(i,ti), text(te){
    this->generateRef(te);
}

/**
 * \fn          Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d)
 * \brief       Constructeur de la classe task
 * \details     La classe dérivé Task utilise en premier lieu le constructeur de Note.
 *              Task possède 4 constructeurs différents car deux de ses attributs sont optionnels.
 */
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s):Note(i, ti), action(a), status(s), priority(-1){
    this->generateRef(a);
};  //Premier type de constructeur : les deux optionels oubliés
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p):Note(i, ti), action(a), status(s), priority(p){
    this->generateRef(a);
}; //Deuxième type de constructeur : priorité ajoutée
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, const QDateTime d):Note(i, ti), action(a), status(s), priority(-1), dueDate(d){
    this->generateRef(a);
};  //Troisième type : dueDate ajoutée
Task::Task(const QString& i, const QString& ti, const QString& a, ENUM::StatusType s, unsigned int p, const QDateTime d):Note(i, ti), action(a), status(s), priority(p), dueDate(d){
    this->generateRef(a);
} //Quatrième type : prio et dueDate ajoutés

/**
 * \fn          Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l)
 * \brief       Constructeur de la classe Recording
 * \details     La classe dérivé Recording utilise en premier lieu le constructeur de Note.
 */
Recording::Recording(const QString i, const QString& ti, const QString d, ENUM::RecordingType r, QString l):Note(i, ti), description(d), type(r), link(l){
    this->generateRef(d);
};



/**************DESTRUCTEUR********************/

/**
 * \fn        Note::~Note()
 * \brief     Destructeur de la classe Note
 */
Note::~Note(){
//    save();
}


/**************MÉTHODES ET SURCHARGES********************/

/**
 * \fn        std::string Note::toString() const
 * \brief     Transforme une note en un flux ostream a afficher
 * \return    Le flux ostream
 */
std::string Note::toString()const {
    std::stringstream f;
    f<<"ID: "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString()<<"\n - Title : "<<getTitle().toStdString()<<"\n";
    return f.str();
}

/**
 * \fn        std::string Article::toString() const
 * \brief     Transforme un article en un flux ostream a afficher
 * \return    Le flux ostream
 */
std::string Article::toString()const {
    std::stringstream f;
    f<<"\n=== ARTICLE "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString()<<"\n - Title : "<<getTitle().toStdString()<<"\n - Text : "<<text.toPlainText().toStdString()<<"\n - Creation date : "<<getCreation_date().toString("dd.MM.yyyy").toStdString()<<"\n - Last modification date : "<<getLastmodif_date().toString("dd.MM.yyyy").toStdString()<<"\n";

    f<<"\n - Reference :";
    if(this->references.size()==0) f<<" none";
    for(unsigned int i=0; i<this->references.size(); i++){
        f<<"\n   - "<<this->references.at(i).toStdString();
    }
    f<<"\n - Article reférencé par "<<getNbIsRef()<<" note(s).";

    if (getIsArchive()) f<<"\n - Note Archivée.";
    if (getIsDeleted()) f<<"\n - Note Supprimée.";

    f<<"\n";
    return f.str();
}

/**
 * \fn        std::string Task::toString()const
 * \brief     Transforme une task en un flux ostream a afficher
 * \return    Le flux ostream
 */
std::string Task::toString() const {
    std::stringstream f;
    f<<"\n=== TASK "<<getId().toStdString()<<" ===\n";
    f<<"ID : "<<getId().toStdString() <<"\n - Title : "<<getTitle().toStdString()<<"\n - Action : "<<action.toStdString()<<"\n - Creation date : "<<getCreation_date().toString("dd.MM.yyyy").toStdString()<<"\n - Last modification date : "<<getLastmodif_date().toString("dd.MM.yyyy").toStdString();
    if(priority!=-1)
        f<<"\n - Priority : "<<priority;
    else
        f<<"\n - No Priority";
    f<<"\n - Status : ";
    switch(status){
    case 0 :
        f<<"Pending";
        break;
    case 1 :
        f<<"On going";
        break;
    case 2 :
        f<<"Completed";
        break;
    default :
        f<<"None";
    }

    if(dueDate.isNull()){f<<"\n - No due date.";}
    else {f<<"\n - Due date : "<<dueDate.toString("dd.MM.yyyy").toStdString();}

    f<<"\n - Reference :";
    if(this->references.size()==0) f<<" none";
    for(unsigned int i=0; i<this->references.size(); i++){
        f<<"\n   - "<<this->references.at(i).toStdString();
    }
    f<<"\n - Tâche reférencée par "<<getNbIsRef()<<" note(s).";


    if (getIsArchive()) f<<"\n - Note Archivée.";
    if (getIsDeleted()) f<<"\n - Note Supprimée.";

    f<<"\n";
    return f.str();
}

/**
 * \fn        std::string Recording::toString()const
 * \brief     Transforme un recording en un flux ostream a afficher
 * \return    Le flux ostream
 */
std::string Recording::toString() const {
    std::stringstream f;
    f<<"\n=== RECORDING "<<getId().toStdString()<<" ===\n";
    f<<"\n - ID : "<<getId().toStdString() <<"\n - Title : "<<getTitle().toStdString()<<"\n - Description : "<<description.toPlainText().toStdString()<<"\n - Creation date : "<<getCreation_date().toString("dd.MM.yyyy").toStdString()<<"\n - Last modification date : "<<getLastmodif_date().toString("dd.MM.yyyy").toStdString();
    f<<"\n - Type : ";
    switch(type){
    case 0 :
        f<<"Image";
        break;
    case 1 :
        f<<"Audio";
        break;
    case 2 :
        f<<"Video";
        break;
    }

    f<<"\n - Reference :";
    if(this->references.size()==0) f<<" none";
    for(unsigned int i=0; i<this->references.size(); i++){
        f<<"\n   - "<<this->references.at(i).toStdString();
    }
    f<<"\n - Enregistrement reférencé par "<<getNbIsRef()<<" note(s).";

    if (getIsArchive()) f<<"\n - Note Archivée.";
    if (getIsDeleted()) f<<"\n - Note Supprimée.";

    f<<"\n";
    return f.str();
}

/**
* \fn        std::ostream& operator<<(std::ostream& f, const Article& a)
* \brief     Surcharge opérateur <<
* \details   Version personnalisée pour le type article, task et recording.
*/
std::ostream& operator<<(std::ostream& f, const Article& a){
    a.display(f);
    return f;
}

std::ostream& operator<<(std::ostream& f, const Task& t){
    t.display(f);
    return f;
}

std::ostream& operator<<(std::ostream& f, const Recording& r){
    r.display(f);
    return f;
}

/**
* \fn        QString getStatustoStr(ENUM::StatusType status)
* \brief     Retourner directement le statut de int à string
*/
QString getStatustoStr(ENUM::StatusType status) {
    QString statusName[] = {"Pending", "OnGoing", "Completed"};
    return statusName[status];
}

/**
* \fn        QString getRecordingtoStr(ENUM::StatusType recording)
* \brief     Retourner directement le recording de int à string
*/
QString getRecordingtoStr(ENUM::StatusType recording) {
    QString recordingName[] = {"Image", "Audio", "Video"};
    return recordingName[recording];
}



/**************GESTION DES RÉFÉRENCES********************/

/**
 * \fn       Note& Note::setNewRef(const QString& id)
 * \brief     Définie une note comme référence d'une autre
 * \details   Lorsqu'une note prend comme référence une autre, cette autre note augmente son attribut
 *              nbIsRef lui permettant de connaître le nombre de notes qui la référencent.
 * \param    const QString&         L'ID de la note référencée.
 */
void Note::setNewRef(const QString& id){
    bool alreadyInRef=false;
    if (this->getId()!=id){
        for(unsigned int i=0; i<references.size(); i++){
            if (references.at(i)==id){ alreadyInRef=true;
            }
        }
        if (!alreadyInRef){
            references.append(id);
            //Incrémente de un le nombre de note qui référence this
            Note& nRef=NotesManager::getInstance()->getNote(id);
            nRef.setNbIsRef(nRef.getNbIsRef()+1);
        }
    }
};


/**
 * \fn       Note& Note::getReference(const QString& id) const
 * \brief    Retourne une note référencée par une autre
 * \param    const QString& id         L'ID de la note référencée.
 */
Note& Note::getReference(const QString& id)const{
    for(unsigned int i=0; i<references.size(); i++){
        if (references.at(i)==id){
            Note& nRef=NotesManager::getInstance()->getNote(id);
            return nRef;
        }
    }
    throw NotesException("erreur, ID inexistant");
};


/**
 * \fn        void Note::deleteReference(const QString& id)
 * \brief     Supprime la référence sur une note spécifiée par son ID
 * \param    const QString& id         L'ID de la note référencée a supprimer.
 */
void Note::deleteReference(const QString& id){
    for(unsigned int i=0; i<references.size(); i++){
        if (references.at(i)==id){
            Note& nRef=NotesManager::getInstance()->getNote(references.at(i));
            nRef.setNbIsRef(nRef.getNbIsRef()-1);
            references.removeAt(i);
        }
    }
}


/**
 * \fn        void Note::deleteAllReference()
 * \brief     Supprime l'ensemble des références d'une note
 * \details   À chaque suppression, les notes anciennement référencées par cette note diminuent
 *              le nombre de notes qui les référence.
 */
void Note::deleteAllReference(){
    for(unsigned int i=0; i<references.size(); i++){
        Note& nRef=NotesManager::getInstance()->getNote(references.at(i));
        nRef.setNbIsRef(nRef.getNbIsRef()-1);
    }
    this->references.clear();
}

/**
 * \fn        void Note::generateRef(const QString& champTexte)
 * \brief     Détecte la présence d'une expression régulière dans un champ de text
 *              et ajoute une référence en conséquence
 * \details   Cette méthode est appelée par le constructeur de notes et
 *              par les setters de champ de texte de notes.
 *            Si l'expression régulière \:ref{(.+)} est repérée,
 *              et si l'ID retourné correspond à celui d'une note active,
 *              la note correspondant à l'ID est ajoutée en référence de la note this.
 * \param     const QString& champTexte     champ de texte dans laquelle la regex doit être repérée
 */
void Note::generateRef(const QString& champTexte){
    // définition expression regulière pour capturer reference
        QRegExp rx("\\\\ref\\{(.+)\\}");
        rx.setMinimal(true); // setMinimal : true

        // récupération liste id notes actives
        QList<QString> listNotes;
        NotesManager::Iterator it=NotesManager::getInstance()->getIterator();
        while(!it.isDone()){
            if(!it.liste()->isEmpty())
            if(!it.current().getIsDeleted()){
                listNotes.append(it.current().getId());
            }
            it.next();
        }

        // intialisation position pour parcours des resultats capturés
        QStringList list;
        int pos = 0;

        // parcours de toutes les ref capturées, dans QString id= rx.cap(1)
        while ((pos = rx.indexIn(champTexte, pos)) != -1){
            QString id = rx.cap(1);
            if(listNotes.contains(id)){
                this->setNewRef(id);
            }
            pos += rx.matchedLength();
        }
}


/**************SAUVEGARDE********************/


void Note::saveNote(QFile* file){}


void Article::saveNote(QFile* file){
    QXmlStreamWriter stream(file);
    stream.writeStartElement("article");
    stream.writeTextElement("id",getId());
    stream.writeTextElement("title",getTitle());
    stream.writeTextElement("c_date",getCreation_date().toString());
    stream.writeTextElement("lm_date",getLastmodif_date().toString());
    if(getIsArchive()) stream.writeTextElement("isArchive","true");
    else stream.writeTextElement("isArchive","false");
    if(getIsDeleted()) stream.writeTextElement("isDeleted","true");
    else stream.writeTextElement("isDeleted","false");
    stream.writeTextElement("text",getText().toPlainText());
    stream.writeEndElement();
}


void Task::saveNote(QFile* file){
    QXmlStreamWriter stream(file);
    stream.writeStartElement("task");
    stream.writeTextElement("id",getId());
    stream.writeTextElement("title",getTitle());
    stream.writeTextElement("c_date",getCreation_date().toString());
    stream.writeTextElement("lm_date",getLastmodif_date().toString());
    if(getIsArchive()) stream.writeTextElement("isArchive","true");
    else stream.writeTextElement("isArchive","false");
    if(getIsDeleted()) stream.writeTextElement("isDeleted","true");
    else stream.writeTextElement("isDeleted","false");
    stream.writeTextElement("action",getAction());
    stream.writeTextElement("priority",QString::number(getPriority()));
    stream.writeTextElement("d_date",getDueDate().toString());
    //if(t.getStatus()==ENUM::StatusType::Pending)
    if(getStatus()==0)
        stream.writeTextElement("status","Pending");
    //if(t.getStatus()==ENUM::StatusType::OnGoing)
    if(getStatus()==1)
        stream.writeTextElement("status","OnGoing");
    //if(t.getStatus()==ENUM::StatusType::Completed)
    if(getStatus()==2)
        stream.writeTextElement("status","Completed");
    stream.writeEndElement();
}


void Recording::saveNote(QFile* file){
    QXmlStreamWriter stream(file);
    stream.writeStartElement("recording");
    stream.writeTextElement("id",getId());
    stream.writeTextElement("title",getTitle());
    stream.writeTextElement("c_date",getCreation_date().toString());
    stream.writeTextElement("lm_date",getLastmodif_date().toString());
    if(getIsArchive()) stream.writeTextElement("isArchive","true");
    else stream.writeTextElement("isArchive","false");
    if(getIsDeleted()) stream.writeTextElement("isDeleted","true");
    else stream.writeTextElement("isDeleted","false");
    stream.writeTextElement("description",getDescription().toPlainText());
    if(getType()==0)
        stream.writeTextElement("type","Image");
    if(getType()==1)
        stream.writeTextElement("type","Audio");
    if(getType()==2)
        stream.writeTextElement("type","Video");
    stream.writeTextElement("link",getLink());
    stream.writeEndElement();
}





