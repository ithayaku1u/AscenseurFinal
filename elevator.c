#include <stdlib.h>
#include <stdio.h>
#include "elevator.h"

Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *e = (Elevator*)malloc(sizeof(Elevator));
    e->capacity = capacity;
    e->currentFloor = currentFloor;
    e->persons = persons;
    return e;
}

Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building *b = (Building*)malloc(sizeof(Building));
    b->nbFloor = nbFloor;
    b->elevator = elevator;
    b->waitingLists = waitingLists;
    return b;
}

PersonList* exitElevator(Elevator *e){
    PersonList *copy = e->persons; //Eviter les clignotements dû à des permutations dans la cabine
    PersonList *temp = e->persons;
    PersonList *exit = NULL;
    e->persons = NULL;
    while (temp != NULL){
        if (temp->person->dest != e->targetFloor){
        e->persons = insert(temp->person, e->persons);              
        }
        else{
            exit = insert(temp->person, exit);
        }
        temp = temp->next;
    } 
    if (exit == NULL){//Eviter les clignotements dû à des permutations dans la cabine
        e->persons = copy; 
    }
    return exit;
}




PersonList* enterElevator(Elevator *e, PersonList *list){
    int capacity = e->capacity;
    int occupation = 0;
    int modif = 0;
    PersonList *temp = e->persons;
    PersonList *copy = e->persons; //Eviter les clignotements dû à des permutations dans la cabine
    e->persons = NULL;
    while (temp != NULL){
        e->persons = insert(temp->person, e->persons);  
        temp = temp ->next;
        occupation++;      
    }
    modif = occupation;
    while (occupation < capacity && list != NULL){
        e->persons = insert(list->person, e->persons);
        list = list->next;
        occupation ++;
    }

    if (modif == occupation){
        e->persons = copy;
    }    
    return list;
}

void stepElevator(Building *b){
    int curFloor = b->elevator->currentFloor;
    int tarFloor = b->elevator->targetFloor;
    if (curFloor > tarFloor){
        b->elevator->currentFloor = curFloor-1;
    }
    else if(curFloor < tarFloor){
        b->elevator->currentFloor = curFloor+1;
    }
    else{
        b->waitingLists[b->elevator->targetFloor] = enterElevator(b->elevator, b->waitingLists[b->elevator->targetFloor]);
        PersonList *exit = exitElevator(b->elevator);
    }
}