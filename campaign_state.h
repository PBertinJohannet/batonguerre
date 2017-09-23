//
// Created by pierre on 16/09/17.
//

#ifndef STICKWAR_CAMPAIGN_STATE_H
#define STICKWAR_CAMPAIGN_STATE_H

#include "array_list.h"
#include "brigade.h"
#include "game_state.h"

typedef struct campaign_state campaign_state;
struct campaign_state{
    game_state* super;
    clickable_menu* menu;
    screen_drawer* drawer;
    char* game_id;
    int to_main;
};

campaign_state* campaign_state_new_game(game_state* state, char* game_id);
campaign_state* campaign_state_load(game_state* state, char* game_id);
campaign_state* campaign_state_next_level(game_state* super, char* game_id);
clickable_menu* campaign_state_menu_init(campaign_state* state);
char* campaign_state_get_camp_path(char* game_id);
char* campaign_state_get_army_path(char* game_id);
void campaign_state_draw(game_state_union* state);
__attribute_const__ void campaign_state_update(__attribute__((unused))game_state_union* ps);
void campaign_state_process_event(game_state_union* state, sfEvent* event);
int campaign_state_get_current_level(char* game_id);
void campaign_state_to_battle(campaign_state* campaign);
void campaign_state_copy_base_stats(char* game_id);
void campaign_state_switch_to_battle(campaign_state* ps);
#endif //STICKWAR_CAMPAIGN_STATE_H
