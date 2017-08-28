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
typedef struct game game;
typedef struct entity entity;
typedef enum entity_state entity_state;
typedef struct team team;
typedef struct brigade brigade;
struct entity {
    drawable_entity* drawable;
    struct entity_behaviour* type;
    entity* target;
    int hp;
    float speed;
    team* team;
    float pos;
    int facing;
    int state;
};
enum entity_state{
    ENTITY_STATE_ASSAULT,
    ENTITY_STATE_ATTACKING,
    ENTITY_STATE_ATTACK_FAILING,
    ENTITY_STATE_RETREATING,
    ENTITY_STATE_DYING,
    ENTITY_STATE_DEAD,
};
entity* entity_init(int hp, float speed, team* team, float size, float pos, animation_frame* frame);
void set_entity_type(entity* ent, struct entity_behaviour* type);
void entity_destroy(entity* ent);
int entity_destroy_void(void* ent);
command* entity_get_command(entity* ent);
brigade* entity_get_brigade(entity* ent);
#endif //STICKWAR_ENTITY_H
