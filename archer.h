//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_ARCHER_H
#define STICKWAR_ARCHER_H

#include "entity_behaviour.h"
typedef struct archer archer;
typedef struct entity_behaviour entity_type;
typedef struct entity entity;
enum archer_attack {
    ARCHER_NONE,
    ARCHER_SHORT_HIT,
    ARCHER_CRIT,
    ARCHER_NORMAL,
};

void set_archer_class(entity*);

animation* archer_get_dying_animation(entity* ent);
animation* archer_get_walking_animation(entity* ent);
void archer_attacking(entity* ent, game* g);
int archer_get_current_range(entity* ent);
void archer_to_attack(entity* ent,entity* target);

#endif //STICKWAR_ARCHER_H
