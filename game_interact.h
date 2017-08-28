//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_GAME_INTERACT_H
#define STICKWAR_GAME_INTERACT_H

#include "game.h"

#include "team.h"
typedef struct team team;
void game_order_retreat(game* g, team* t);
void game_order_assault(game* g, team* t);
void game_command_one(game* g, team* t, int entity_type, int target);
void game_command_all(game* g, team* t, int target);

#endif //STICKWAR_GAME_INTERACT_H
