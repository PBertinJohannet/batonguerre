//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_TYPE_H
#define STICKWAR_TYPE_H

#include "entity.h"
#include "array_list.h"
#include "game.h"
typedef struct entity_type entity_type;
typedef struct entity entity;
typedef enum entity_class entity_class;
typedef struct game game;
typedef struct animation_list animation_list;
struct entity_type {
    int (*play) (game* g, entity*, list*);
    int (*get_current_range)(entity*);
    void (*to_attack)(entity*,entity*);
    void (*to_aggro)(entity*);
    void (*to_dying)(entity*);
    void (*attack)( entity*, game*);
    void (*retreating)(entity*);
    void* type_stats;
};
int entity_base_play(game* g, entity*, list*);
void entity_type_destroy(entity_type* ent);
int entity_base_agg_moving(entity* player, list* entities);
int entity_base_attack(game* g, entity* player, list* entities);
int entity_base_dying(entity* player, list* entities);
int entity_base_attack_failing(entity* player, list* entities);
#endif //STICKWAR_TYPE_H
