//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_ARROW_H
#define STICKWAR_ARROW_H

#include "projectile.h"
typedef struct arrow arrow;
struct arrow {
    unsigned int speed;
    projectile* parent;
    int damage;
    unsigned int lifetime;
};
projectile* arrow_create(int pos,unsigned int range, unsigned int speed, float size, team* team, unsigned int facing, int damage);

int arrow_projectile_play(void* arrow, list* entities);
int arrow_projectile_destroy(projectile* proj);
#endif //STICKWAR_ARROW_H
