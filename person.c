#include <stdlib.h>
#include "person.h"

Person* createPerson(int src, int dest){
    Person* p = (Person*)malloc(sizeof(Person));
    p->dest = dest;
    p->src = src;
    return p;
}
PersonList* insert(Person *p, PersonList *list){
    PersonList *L = (PersonList*)malloc(sizeof(PersonList));
    L->next = list;
    L->person = p;
    return L;
}