//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_GAME_INTERACT_H
#define STICKWAR_GAME_INTERACT_H

#include "game.h"


void game_order_retreat(game* g, int team_id);
void game_order_assault(game* g, int team_id);
void game_command_one(game* g, int team_id, int entity_type, int target);
void game_command_all(game* g, int team_id, int target);

#endif //STICKWAR_GAME_INTERACT_H
