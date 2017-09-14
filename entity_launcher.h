//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_ENTITY_LAUNCHER_H
#define STICKWAR_ENTITY_LAUNCHER_H

#include "entity_factory.h"
#include "animation.h"
#include "team.h"
#include "brigade.h"
typedef struct brigade brigade;
typedef struct team team;
typedef struct entity_launcher entity_launcher;
typedef struct battle battle;
struct entity_launcher{
    int cost;
    int cd;
    float curr_cd;
    brigade* brigade;
    animation_frame* anim;
};



entity_launcher* entity_launcher_init(brigade* ,int cost, int cd);
void entity_launcher_set_type(entity_launcher*, int);
sfSprite* entity_launcher_get_icon(entity_launcher* ent);
void entity_launcher_launch(entity_launcher* launcher, battle* g);
void entity_launcher_update(entity_launcher* ent);
int can_launch(entity_launcher* ent);
void entity_launcher_destroy(void* ent);
#endif //STICKWAR_ENTITY_LAUNCHER_H
