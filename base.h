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
int base_play(entity* player, list* entities, struct animation_list* anims);
void base_attack(entity* ent);
int base_get_current_range(entity*);
void base_to_attack(entity* ent,entity* target, struct animation_list* anims);
void base_to_dying(entity* ent, struct animation_list* anims);
void base_to_aggro(entity* ent, struct animation_list* anims);
#endif //STICKWAR_BASE_H
