//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_TEAM_H
#define STICKWAR_TEAM_H

#include "array_list.h"
#include "kicker.h"
#include "entity_factory.h"

typedef struct team team;
typedef struct animation_list animation_list;
struct team {
    int id;
    int gold;
    list* brigades;
    entity* base;
};
team* team_init(int team_number);
void team_init_brigades(team* t);
void team_launch_entity(team* t,struct game* g, int id);
void team_play(team* t, int frame);
void team_order_entity(team* t,game* g, int id);
void team_destroy(team* t);
#endif //STICKWAR_TEAM_H
