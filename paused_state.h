//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_PAUSED_STATE_H
#define STICKWAR_PAUSED_STATE_H

#include "game.h"
typedef struct paused_state paused_state;

struct paused_state{
    game* paused_game;
};

void paused_game_display_message(paused_state* g);
void paused_game_next_loop(paused_state* ps);
void paused_game_update(paused_state* ps);
#endif //STICKWAR_PAUSED_STATE_H
