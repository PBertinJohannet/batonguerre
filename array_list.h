//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_ARRAY_LIST_H
#define STICKWAR_ARRAY_LIST_H

typedef struct array_list list;

struct array_list {
    void** list;
    unsigned int size;
    unsigned int max_size;
};

void list_reserve(list* l,unsigned int size);
list* list_create(void);
void list_add(list* l,void* elem);
void* list_at(list* l,unsigned int index);
void* list_last(list* l);
void list_free(list* l, int (*destructor)(void*));
void* list_rm_at(list* l, unsigned int index);
void* list_random(list* l);
void list_destroy(list* l);
#endif //STICKWAR_ARRAY_LIST_H
