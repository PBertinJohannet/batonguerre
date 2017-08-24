//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_GAME_END_STATE_H
#define STICKWAR_GAME_END_STATE_H



#include "game.h"
#include "team.h"
typedef struct game_end_state game_end_state;

struct game_end_state{
    game* ended_game;
    team* winning_team;
};

void game_end_display_message(game_end_state* g);
void game_end_next_loop(game_end_state* ps);
int game_end_update(game_end_state* ps);

#endif //STICKWAR_GAME_END_STATE_H
