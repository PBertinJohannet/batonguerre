//
// Created by pierre on 04/09/17.
//

#ifndef STICKWAR_BATTLE_STATE_H
#define STICKWAR_BATTLE_STATE_H

#include "counted_allocations.h"
#include "battle.h"
#include "game_state.h"
#include "paused_state.h"
typedef struct paused_state paused_state;
typedef struct battle_state battle_state;
typedef union game_state_union game_state_union;

struct battle_state {
    game_state* super;
    battle* battle;
    char* current_save;
};

battle_state* battle_state_init_from_level(game_state* super, char* level, char* campaign_id);

battle_state* battle_state_init_from_pause(paused_state* ps);

void battle_state_draw(game_state_union* state);

void battle_state_process_event(game_state_union* state, sfEvent* event);

void battle_state_update(game_state_union* state);
void battle_state_to_paused_state(game_state* state);
void battle_state_to_end_state(game_state* bs, int won);


#endif //STICKWAR_battle_H
