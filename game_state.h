//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_GAME_STATE_H
#define STICKWAR_GAME_STATE_H

#include "game.h"
#include "game_end_state.h"
typedef struct game_state game_state;
struct game_state {
    sfRenderWindow* window;
    void* state;
    void (*next_loop)(void* state);
};

game_state* playing_state_init();
void game_state_loop(game_state*);
void playing_state_next_loop(void* state);

void playing_state_to_paused_state(game_state*);
void paused_state_to_playing_state(game_state*);
void paused_state_next_loop(void* state);


void playing_state_to_game_end_state(game_state* state, team* winner);
void game_end_state_next_loop(void* state);
void game_end_state_to_playing_state(game_state* state);
#endif //STICKWAR_GAME_STATE_H
