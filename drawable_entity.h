//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_DRAWABLE_ENTITY_H
#define STICKWAR_DRAWABLE_ENTITY_H

#include "animation.h"
typedef struct drawable_entity drawable_entity;
struct drawable_entity {
    float* pos;
    int* facing;
    animation_frame* anim;
    float size;
};
drawable_entity* drawable_entity_init(animation_frame* anim_frame, float* pos, int* facing, float size);
void drawable_entity_destroy(drawable_entity* ent);
#endif //STICKWAR_DRAWABLE_ENTITY_H
