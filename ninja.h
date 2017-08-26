//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_NINJA_H
#define STICKWAR_NINJA_H

#include "entity_type.h"

/**
 * ninja jump from 23 to 33  = 10 frames at 4* speed
 */
typedef struct ninja ninja;
typedef struct entity_type entity_type;
typedef struct entity entity;
enum ninja_attack {
    NINJA_NONE,
    SLASH,
    NINJA_JUMP,
    HIT,
};

struct ninja{
    int range;
    int attack_type;
    int will_jump;
};
ninja* ninja_init(int level);
void ninja_retreating(entity* ent, list* entities);
void set_ninja_class(entity*, int level);
void ninja_play(game* g, entity* player, list* entities);
void ninja_attack(entity* ent, game* g);
int ninja_get_current_range(entity*);
void ninja_to_attack(entity* ent,entity* target);
void ninja_to_dying(entity* ent);
void ninja_to_aggro(entity* ent);
void ninja_jumping(entity* ent);
void ninja_to_short_attack(entity* ent, entity* target);
void ninja_to_jump_attack(entity* ent, entity* target);
#endif //STICKWAR_NINJA_H
