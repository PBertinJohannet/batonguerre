//
// Created by pierre on 02/09/17.
//

#ifndef STICKWAR_COUNTED_ALLOCATIONS_H
#define STICKWAR_COUNTED_ALLOCATIONS_H

#include "array_list.h"
#include "stdio.h"
#include <SFML/Graphics.h>
typedef struct allocation allocation;
struct allocation {
    void* pointer;
    size_t size;
    const char* message;
};

allocation* allocation_init(size_t size, void* pointer, const char* message);
void allocation_show(allocation* all);
int allocation_destroy(allocation* all);
void* counted_malloc(size_t size, const char* message);
void counted_free(void* to_free, const char* message);
int counted_free_check(void* to_free, const char* message);
void counted_show_allocateds(void);
sfText* sfText_counted_malloc(char* message);
void sfText_counted_free(sfText* text, char* message);
sfSprite* sfSprite_counted_malloc(char* message);
void sfSprite_counted_free(sfSprite* text, char* message);

#endif //STICKWAR_COUNTED_ALLOCATIONS_H
