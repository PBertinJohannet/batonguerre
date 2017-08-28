//
// Created by pierre on 27/08/17.
//

#ifndef STICKWAR_BRIGADE_H
#define STICKWAR_BRIGADE_H

#include "command.h"
#include "entity_launcher.h"
typedef struct brigade brigade;
typedef struct command command;
typedef struct entity_launcher entity_launcher;
typedef struct game game;
struct brigade {
    command* command;
    entity_launcher* launcher;
};

brigade* brigade_init(int ent_type, int level, int cost, int cd, animation* anim, team* team);
void brigade_change_order(game* g, int order);

#endif //STICKWAR_BRIGADE_H
