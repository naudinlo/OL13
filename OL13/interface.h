#ifndef INTERFACE_H
#define INTERFACE_H
//#include "include.h"
//#include "QInclude.h"
#include "Creation_Note.h"
class interface:public QMainWindow
{
    Q_OBJECT
    Creation_Note fen_creerNote;

public:
    interface();

public slots:
   void OuvrirFichier();
   void CreerNote();


};




#endif // INTERFACE_H
