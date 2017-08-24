//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_NINJA_H
#define STICKWAR_NINJA_H

#include "entity_type.h"
typedef struct ninja ninja;
typedef struct entity_type entity_type;
typedef struct entity entity;
enum ninja_attack {
    NINJA_NONE,
    SLASH,
    HIT,
};

struct ninja{
    int range;
    int damage;
    int attack_type;
};
ninja* ninja_init(int level);
void ninja_retreating(entity* ent, struct animation_list* anims);
void set_ninja_class(entity*, int level);
void ninja_play(game* g, entity* player, list* entities, struct animation_list* anims);
void ninja_attack(entity* ent, game* g);
int ninja_get_current_range(entity*);
void ninja_to_attack(entity* ent,entity* target, struct animation_list* anims);
void ninja_to_dying(entity* ent, struct animation_list* anims);
void ninja_to_aggro(entity* ent, struct animation_list* anims);
#endif //STICKWAR_NINJA_H
