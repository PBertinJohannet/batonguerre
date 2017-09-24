//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_ENTITY_H
#define STICKWAR_ENTITY_H

#include "drawable_entity.h"
#include "entity_behaviour.h"
#include "team.h"
#include "command.h"
#include "brigade.h"
typedef struct command command;
typedef struct battle battle;
typedef struct entity entity;
typedef struct team team;
typedef struct brigade brigade;
struct entity {
    drawable_entity* drawable;
    struct entity_behaviour* type;
    entity* target;
    int hp;
    int base_hp;
    float speed;
    team* team;
    float pos;
    unsigned int facing;
    unsigned int state;
    brigade* brigade;
};

enum entity_state{
    ENTITY_STATE_ASSAULT,
    ENTITY_STATE_ATTACKING,
    ENTITY_STATE_ATTACK_FAILING,
    ENTITY_STATE_RETREATING,
    ENTITY_STATE_DYING,
    ENTITY_STATE_DEAD,
};
entity* entity_init(brigade* b);
void set_entity_type(entity* ent, struct entity_behaviour* type);
void entity_destroy(entity* ent);
void entity_destroy_void(void* ent);
command* entity_get_command(entity* ent);
brigade* entity_get_brigade(entity* ent);
#endif //STICKWAR_ENTITY_H
