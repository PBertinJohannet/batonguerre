//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_DRAWABLE_ENTITY_H
#define STICKWAR_DRAWABLE_ENTITY_H

#include "animation.h"
enum drawable_enum {
    ANIM,
    RECTANGLE,
};
union drawable_union {
    animation_frame* anim;
    sfRectangleShape* rectangle;
};
typedef struct drawable_entity drawable_entity;
struct drawable_entity {
    float* pos;
    unsigned int* facing;
    animation_frame* anim;
    float size;
};
void drawable_entity_animation_forward(drawable_entity* ent, float forward);
drawable_entity* drawable_entity_init(animation_frame* anim_frame, float* pos, unsigned int* facing, float size);
void drawable_entity_destroy(drawable_entity* ent);
unsigned int drawable_entity_get_frame(drawable_entity* ent);
#endif //STICKWAR_DRAWABLE_ENTITY_H
