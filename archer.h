//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_ARCHER_H
#define STICKWAR_ARCHER_H

#include "entity_type.h"
typedef struct archer archer;
typedef struct entity_type entity_type;
typedef struct entity entity;
enum archer_attack {
    ARCHER_NONE,
    ARCHER_SHORT_HIT,
    ARCHER_CRIT,
    ARCHER_NORMAL,
};

struct archer{
    int range;
    int range_short;
    int damage;
    int attack_type;
};
archer* archer_init(int level);
void archer_retreating(entity* ent, list*);
void set_archer_class(entity*, int level);
void archer_play(entity* player, list* entities);
void archer_attack(entity* ent, game* g);
int archer_get_current_range(entity*);
void archer_to_attack(entity* ent,entity* target);
void archer_to_dying(entity* ent);
void archer_to_aggro(entity* ent);

#endif //STICKWAR_ARCHER_H
