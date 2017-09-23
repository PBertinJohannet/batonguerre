//
// Created by pierre on 21/09/17.
//

#ifndef STICKWAR_FINAL_AI_H
#define STICKWAR_FINAL_AI_H

#include "battle.h"
#include "ai.h"
#include "team.h"
typedef struct final_ai{
    int ninjas;
    int cur_order;
    int boss_launched;
    int stamp;
    team* team;
} final_ai;
final_ai* final_ai_init(team* t);
void final_ai_play(ai*, battle*);
void final_ai_destroy(final_ai*);


#endif //STICKWAR_FINAL_AI_H
