//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_PROJECTILE_H
#define STICKWAR_PROJECTILE_H

#include "array_list.h"
#include "animation.h"
#include "drawable_entity.h"

typedef struct projectile projectile;
enum projectile_type {
    PROJECTILE_ARROW,
};

struct projectile {
    float pos;
    int facing;
    int team;
    int(*play)(void* ,list*);
    int(*destroy)(projectile*);
    drawable_entity* drawable;
    void* self;
};
projectile* projectile_create(int pos, int team, int facing);


#endif //STICKWAR_PROJECTILE_H
