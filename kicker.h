//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_KICKER_H
#define STICKWAR_KICKER_H

#include "entity_type.h"
typedef struct kicker kicker;
typedef struct entity_type entity_type;
typedef struct entity entity;
struct kicker{
    int range;
    int damage;
    int attack_type;
};
enum kicker_attack{
    KICKER_NONE,
    KICK,
    PUNCH,
};
kicker* kicker_init(int level);
void set_kicker_class(entity*, int level);
void kicker_retreating(entity* ent );
void kicker_play(game* g, entity* player, list* entities );
void kicker_attack(entity* ent, game* g);
int kicker_get_current_range(entity*);
void kicker_to_attack(entity* ent,entity* target );
void kicker_to_dying(entity* ent );
void kicker_to_aggro(entity* ent );
#endif //STICKWAR_KICKER_H
