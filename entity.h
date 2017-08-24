//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_ENTITY_H
#define STICKWAR_ENTITY_H

#include "drawable_entity.h"
#include "entity_type.h"
typedef struct entity entity;
typedef enum entity_state entity_state;
typedef struct entity_stats entity_stats;
struct entity {
    entity_stats* stats;
    drawable_entity* drawable;
    struct entity_type* type;
    entity* target;
};
struct entity_stats{
    int hp;
    float speed;
    int team;
    float pos;
    int facing;
    int state;
};
enum entity_state{
    AGG_MOVING,
    ATTACKING,
    ATTACK_FAILING,
    RETREATING,
    DYING
};
entity* entity_init(int hp, float speed, int team, float size, float pos, int state, animation_frame* frame);
void set_entity_type(entity* ent, struct entity_type* type);
void entity_destroy(entity* ent);
int entity_destroy_void(void* ent);
#endif //STICKWAR_ENTITY_H
