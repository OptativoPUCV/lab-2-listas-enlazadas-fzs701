#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
     List* lista = (List*)malloc(sizeof(List));
     if(lista == NULL){
        return NULL;
     }
     lista->head = NULL;
     lista->tail = NULL;
     lista->current = NULL;
     return lista;
}

void * firstList(List * list) {
    if(list == NULL || list->head == NULL){
        return NULL;
    }
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL || list->current->next == NULL){
        return NULL;
    }
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list == NULL || list->tail == NULL){
        return NULL;
    }
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list == NULL || list->current == NULL || list->current->prev == NULL){
        return NULL;
    }
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNodo = (Node*)malloc(sizeof(Node));
    newNodo->data = data;
    newNodo->next = list->head;
    newNodo->prev = NULL;
    if(list->head == NULL){
        list->tail = newNodo;
    }
    list->current = newNodo;
    if(list->head != NULL){
        list->head->prev = newNodo;
    }
    list->head = newNodo;
    

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list->head == NULL){
        return;
    }
    Node* newNodo = (Node*)malloc(sizeof(Node*));
    newNodo->data = data;
    newNodo ->prev = list->current;
    newNodo->next = list->current->next;
    if(list->current->next != NULL){
        list->current->next->prev = newNodo;
    }
    list->current->next = newNodo;
    if(newNodo->next == NULL){
        list->tail = newNodo;
    }
    list->current = newNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->head == NULL){
        return NULL;
    }
    void *dato = list->current->data;
    if(list->current->prev == NULL){
        list->head = list->current->next;
        if(list->head != NULL){
            list->head->prev = NULL;
        }
    } else if(list->current->next == NULL){
        list->tail = list->current->prev;
        list->tail->next = NULL;
    } else {
        list->current->prev->next = list->current->next;
        list->current->next->prev =list->current->prev;
    }
    Node *eliminar = list->current;
    list->current = list->current->next;
    free(eliminar);
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}