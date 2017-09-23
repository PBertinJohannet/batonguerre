//
// Created by pierre on 10/09/17.
//

#ifndef STICKWAR_MINEWORKER_H
#define STICKWAR_MINEWORKER_H


#include "entity_behaviour.h"
typedef struct entity entity;
typedef struct battle battle;
typedef struct mineworker_current_state mineworker_current_state;
struct mineworker_current_state {
    unsigned int is_harvesting;
    int gold_harvested;
    object* targeted_heap;
};
void set_mineworker_class(entity*);
animation* mineworker_get_dying_animation(entity* ent);
animation* mineworker_get_walking_animation(entity* ent);
void mineworker_attacking(entity* ent, battle* g);
void mineworker_retreating(entity* player,__attribute__ ((unused))list* entities );
int mineworker_get_current_range(entity* ent);
void mineworker_to_attack(entity* ent,entity* target);
void mineworker_assaulting(entity* player, list* entities, list* objects);
int mineworker_find_target(entity* player, list* objects);
void mineworker_to_harvest(entity* ent,object* target);
void mineworker_harvesting(entity* ent);
void mineworker_returning_gold(entity* player);


#endif //STICKWAR_MINEWORKER_H
