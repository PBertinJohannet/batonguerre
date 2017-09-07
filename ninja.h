//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_NINJA_H
#define STICKWAR_NINJA_H

#include "entity_behaviour.h"
#include "brigade_reader.h"

/**
 * ninja jump from 23 to 33  = 10 frames at 4* speed
 */
typedef struct ninja ninja;
typedef struct entity_behaviour entity_type;
typedef struct entity entity;
enum ninja_attack {
    NINJA_NONE,
    SLASH,
    NINJA_JUMP,
    HIT,
};

struct ninja{
    int attack_type;
    int will_jump;
};
ninja* ninja_init(ninja_stats*);
void set_ninja_class(entity*);
animation* ninja_get_dying_animation(entity* ent);
animation* ninja_get_walking_animation(entity* ent);
void ninja_attacking(entity* ent, battle* g);

void ninja_jumping(entity* ent);
int ninja_get_current_range(entity* ent);
void ninja_to_attack(entity* ent,entity* target);

void ninja_to_short_attack(entity* ent, entity* target);
void ninja_to_jump_attack(entity* ent, entity* target);
#endif //STICKWAR_NINJA_H
