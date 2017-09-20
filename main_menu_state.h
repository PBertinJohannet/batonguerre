//
// Created by pierre on 12/09/17.
//

#ifndef STICKWAR_MAIN_MENU_STATE_H
#define STICKWAR_MAIN_MENU_STATE_H

#include "game_state.h"
#include "battle_state.h"
#include "clickable_menu.h"
#include "screen_drawer.h"
typedef struct main_menu_state main_menu_state;
typedef struct battle_state battle_state;
typedef union game_state_union game_state_union;
typedef struct clickable_menu clickable_menu;
struct main_menu_state{
    game_state* super;
    clickable_menu* menu;
    screen_drawer* drawer;
    int switch_to;
};
main_menu_state* main_menu_state_init(game_state* );
void main_menu_state_draw(game_state_union* state);
void main_menu_state_update(game_state_union* ps);
void main_menu_state_process_event(game_state_union* state, sfEvent* event);
void main_menu_state_to_campaign(main_menu_state* ps);
void main_menu_switch_to_battle(main_menu_state* menu);
void main_menu_state_quit(main_menu_state* menu);
void test_suck_button(main_menu_state* state);
void test_print_pos(void* state);

#endif //STICKWAR_MAIN_MENU_STATE_H
