//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_PAUSED_STATE_H
#define STICKWAR_PAUSED_STATE_H

#include "game_state.h"
#include "battle_state.h"
#include "clickable_menu.h"
typedef struct clickable_menu clickable_menu;
typedef struct paused_state paused_state;
typedef struct battle_state battle_state;
typedef struct game_state game_state;
typedef struct battle battle;
typedef union game_state_union game_state_union;
enum switch_to {
    DONT_SWITCH,
    SWITCH_TO_MENU,
    SWITCH_TO_BATTLE,
};
struct paused_state{
    game_state* super;
    battle* paused_battle;
    clickable_menu* menu;
    unsigned int switch_to;
};
paused_state* paused_state_init(battle_state* );
void paused_state_draw(game_state_union* state);
void paused_state_update(game_state_union* ps);
void paused_state_process_event(game_state_union* state, sfEvent* event);
void paused_state_to_main_menu(paused_state* ps);
void paused_state_to_battle(paused_state* ps);
void paused_state_switch_to_main(paused_state* ps);
void paused_state_switch_to_battle(paused_state* ps);
#endif //STICKWAR_PAUSED_STATE_H
