//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_BASE_H
#define STICKWAR_BASE_H

#include "entity_behaviour.h"
typedef struct entity_behaviour entity_type;
typedef struct entity entity;
void set_base_class(entity*);

entity* base_init(int pos, int hp, team* team);
animation* base_get_dying_animation(entity* ent);
animation* base_get_walking_animation(entity* ent);
void base_play(game* g, entity* player, list* entities);
void base_attacking(entity* ent, game* g);
int base_get_current_range(entity* ent);
void base_to_attack(entity* ent,entity* target);
#endif //STICKWAR_BASE_H
