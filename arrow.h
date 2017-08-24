//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_ARROW_H
#define STICKWAR_ARROW_H

#include "projectile.h"
typedef struct arrow arrow;
struct arrow {
    projectile* parent;
    int damage;
    int lifetime;
};
projectile* arrow_create(int pos, int team, int facing, int damage);

int arrow_projectile_play(void* arrow, list* entities);
int arrow_projectile_destroy(projectile* proj);
#endif //STICKWAR_ARROW_H
