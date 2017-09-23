//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_battle_INTERACT_H
#define STICKWAR_battle_INTERACT_H

#include "game_state.h"

#include "team.h"
typedef struct team team;
void battle_order_retreat(team* t);
void battle_order_assault(battle* g, team* t);
void battle_command_one(team* t, unsigned int target,unsigned int brigade_id);
void battle_command_all(team* t, unsigned int target);

#endif //STICKWAR_battle_INTERACT_H
