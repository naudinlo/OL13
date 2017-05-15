#ifndef MANAGER_H
#define MANAGER_H
#include <string>
#include <iostream>
#include "notes.h"
using namespace std;


class Manager{
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
};

#endif // MANAGER_H
