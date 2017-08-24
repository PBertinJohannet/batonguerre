//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_BASE_H
#define STICKWAR_BASE_H

#include "entity_type.h"
typedef struct base base;
typedef struct entity_type entity_type;
typedef struct entity entity;
struct base{
    int range;
    int damage;
};
base* base_init(int level);
void set_base_class(entity*, int level);
int base_play(game* g, entity* player, list* entities );
void base_attack(entity* ent, game* g);
int base_get_current_range(entity*);
void base_to_attack(entity* ent,entity* target );
void base_to_dying(entity* ent );
void base_to_aggro(entity* ent );
#endif //STICKWAR_BASE_H
