//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_GAME_INTERACT_H
#define STICKWAR_GAME_INTERACT_H

#include "game.h"

#include "team.h"
typedef struct team team;
void game_order_retreat(team* t);
void game_order_assault(game* g, team* t);
void game_command_one(team* t, unsigned int target,unsigned int entity_type);
void game_command_all(team* t, unsigned int target);

#endif //STICKWAR_GAME_INTERACT_H
