//
// Created by pierre on 02/09/17.
//

#ifndef STICKWAR_COUNTED_ALLOCATIONS_H
#define STICKWAR_COUNTED_ALLOCATIONS_H

#include "array_list.h"
#include "stdio.h"

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
int counted_free(void* to_free, const char* message);
void counted_show_allocateds(void);

#endif //STICKWAR_COUNTED_ALLOCATIONS_H
