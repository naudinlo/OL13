# OL13

### **<u>Itérateurs NotesManager</u>**

**Pour l'itérateur de notes:** 

NotesManager::Iterator it=NotesManager::getIterator() it sera l'itérateur de notes avec les méthodes:

it.current() renvoie la dernière version de la note courrante
it.next() incrément it
it.isDone() renvoie vrai si it est à la fin
it.liste() renvoie la list<Note> de toutes les versions d'une note


**Pour l'itérateur de versions:**

list<Note>::iterator itVer=it.liste() itVer sera l'itération de version de la note courante (dans it)
Les méthodes:

itVer++ incrémentation

itVer-- décrémentation
itVer!=a différent
itVer==a égal
*itVer permet de récupérer la version courante

**Si besoin d'utiliser une méthode de Note sur une version de note 2 option:**
(*itVer).<methode>(); ou itVer.operator*().<methode>();