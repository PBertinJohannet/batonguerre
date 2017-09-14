//
// Created by pierre on 09/09/17.
//

#ifndef STICKWAR_GOLD_HEAP_H
#define STICKWAR_GOLD_HEAP_H
#include "counted_allocations.h"
#include "global.h"
#include "object.h"
typedef struct gold_heap gold_heap;
struct gold_heap{
    object* parent;
    int gold_start;
    int gold_current;
};

object* gold_heap_create(int pos, int gold, float size);


int gold_heap_play(void* self, list* entities);
int gold_heap_destroy(object* obj);
#endif //STICKWAR_GOLD_HEAP_H
