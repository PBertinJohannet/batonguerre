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
    unsigned int id;
    int gold;
    int pop;
    int gold_per_sec;
    list* brigades;
    entity* base;
};
team* team_init(unsigned int team_number, int pop, int gold_start, int gold_per_sec);
void team_set_brigades(team* t, list* l);
void team_launch_entity(team* t,struct battle* g, unsigned int id);
void team_play(team* t, unsigned int frame);
void team_order_entity(team* t,battle* g, unsigned int id);
void team_destroy(team* t);
#endif //STICKWAR_TEAM_H
