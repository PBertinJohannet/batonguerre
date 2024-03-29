//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_ARROW_H
#define STICKWAR_ARROW_H

#include "object.h"
typedef struct arrow arrow;
struct arrow {
    unsigned int speed;
    object* parent;
    int damage;
    float lifetime;
};
object* arrow_init(int pos,unsigned int range, unsigned int speed, float size, team* team, unsigned int facing, int damage);

int arrow_object_play(void* object, list* entities);
void arrow_object_destroy(object* proj);
#endif //STICKWAR_ARROW_H
