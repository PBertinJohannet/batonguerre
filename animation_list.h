//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_ANIMATION_LIST_H
#define STICKWAR_ANIMATION_LIST_H

#include "animation.h"
typedef struct animation_list animation_list;
struct animation_list{
    animation* stick_walk;
    animation* stick_kick;
    animation* stick_kick_death;
    animation* stick_walk_death;
    animation* ninja_walk;
    animation* ninja_strike;
    animation* ninja_death;
    animation* ninja_icon;
    animation* kicker_icon;
    animation* kicker_punch;
    animation* ninja_slash;
    animation* ninja_jump;
    animation* archer_critical_hit;
    animation* archer_walk;
    animation* archer_hit;
    animation* archer_death;
    animation* archer_short_hit;
    animation* arrow;
    animation* gold_heap;

};
animation_list* animation_list_load(void);
void animation_list_destroy(animation_list* anims);
#endif //STICKWAR_ANIMATION_LIST_H
