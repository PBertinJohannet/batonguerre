//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_KICKER_H
#define STICKWAR_KICKER_H

#include "entity_behaviour.h"
typedef struct entity_behaviour entity_type;
typedef struct entity entity;
typedef struct battle battle;

enum kicker_attack{
    KICKER_NONE,
    KICK,
    PUNCH,
};
void set_kicker_class(entity*);
animation* kicker_get_dying_animation(entity* ent);
animation* kicker_get_walking_animation(entity* ent);
void kicker_attacking(entity* ent, battle* g);
int kicker_get_current_range(entity* ent);
void kicker_to_attack(entity* ent,entity* target);
#endif //STICKWAR_KICKER_H
