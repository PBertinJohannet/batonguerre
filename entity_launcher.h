//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_ENTITY_LAUNCHER_H
#define STICKWAR_ENTITY_LAUNCHER_H

#include "entity_factory.h"
#include "animation.h"
#include "team.h"
typedef struct team team;
typedef struct entity_launcher entity_launcher;
typedef struct game game;
struct entity_launcher{
    int ent_type;
    int level;
    int cost;
    int cd;
    int curr_cd;
    team* team;
    animation_frame* anim;
};



entity_launcher* entity_launcher_init(int ent_type, int level, int cost, int cd, animation* anim, team* team);
sfSprite* entity_launcher_get_icon(entity_launcher* ent);
void entity_launcher_launch(entity_launcher* launcher, game* g);
void entity_launcher_update(entity_launcher* ent);

int entity_launcher_destroy(void* ent);
#endif //STICKWAR_ENTITY_LAUNCHER_H
