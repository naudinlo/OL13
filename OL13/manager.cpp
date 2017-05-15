#include "manager.h"


Manager::Manager():notes(nullptr),nbNotes(0),nbMaxNotes(0){}

Manager::~Manager(){
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}
