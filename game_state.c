//
// Created by pierre on 23/08/17.
//
#include "game_state.h"
#include "paused_state.h"
#include "game_end_state.h"
game_state* playing_state_init(){
    game_state* state = malloc(sizeof(game_state));
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 16};
    state->window = sfRenderWindow_create(mode, "Stickwar",  sfResize | sfClose, NULL);
    state->state = game_init(state);
    state->next_loop = playing_state_next_loop;
    return state;
}
void game_state_loop(game_state* state){
    while (sfRenderWindow_isOpen(state->window)) {
        state->next_loop(state->state);
    }
}
void playing_state_next_loop(void* state){
    game* g = (game*)state;
    game_next_loop(g);
}

// paused state

void playing_state_to_paused_state(game_state* state){
    paused_state* new_state = malloc(sizeof(paused_state));
    new_state->paused_game = state->state;
    paused_game_display_message(new_state);
    state->state = new_state;
    state->next_loop = paused_state_next_loop;
}

void paused_state_next_loop(void* state){
    paused_state* paused = state;
    paused_game_next_loop(paused);
}



void paused_state_to_playing_state(game_state* state){
    paused_state* old = state->state;
    game* g = old->paused_game;
    state->state = g;
    state->next_loop = playing_state_next_loop;
    free(old);
}


// game end
void playing_state_to_game_end_state(game_state* state, team* winner){
    game_end_state* new_state = malloc(sizeof(paused_state));
    new_state->ended_game = state->state;
    new_state->winning_team = winner;
    game_end_display_message(new_state);
    state->state = new_state;
    state->next_loop = game_end_state_next_loop;
    for (int i = 0;i<new_state->ended_game->entities->size;i++){
        entity* ent = list_at(new_state->ended_game->entities,i);
        if (game_get_team(new_state->ended_game, ent->team)!=new_state->winning_team){
            ent->type->to_dying(ent);
        }
    }
}

void game_end_state_next_loop(void* state){
    game_end_state* paused = state;
    game_end_next_loop(paused);
}



void game_end_state_to_playing_state(game_state* state){
    game_end_state* old = state->state;
    game* g = old->ended_game;
    game_destroy(g);
    free(old);
    state->state = game_init(state);
    state->next_loop = playing_state_next_loop;
}