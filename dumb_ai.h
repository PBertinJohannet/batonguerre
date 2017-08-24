//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_DUMB_AI_H
#define STICKWAR_DUMB_AI_H

#include "game.h"
#include "team.h"
#include "entity_launcher.h"
#include "game_interact.h"

typedef struct team team;
typedef struct dumb_ai dumb_ai;
struct dumb_ai{
    team* team;
    int last_ass;
    int target_id;
};

dumb_ai* dumb_ai_init(team* t);
int choose_mode(dumb_ai* ai, list* entities);
void dumb_ai_play(dumb_ai* dai, game* g);
void dumb_ai_destroy(dumb_ai* dai);
#endif //STICKWAR_DUMB_AI_H
