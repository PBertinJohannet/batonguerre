//
// Created by pierre on 23/08/17.
//
#include "game_state.h"
#include "paused_state.h"
#include "battle_state.h"
#include "window_conf_reader.h"
#include "end_state.h"
#include "counted_allocations.h"
#include "main_menu_state.h"

void game_state_start(game_state* state){
    while (sfRenderWindow_isOpen(state->window)) {
        sfRenderWindow_clear(state->window, sfBlack);
        state->draw(state->current_state);
        sfRenderWindow_display(state->window);
        state->update(state->current_state);
        sfEvent* event = counted_malloc(sizeof(sfEvent), "sfevent init in controller process");
        while (sfRenderWindow_pollEvent(state->window, event)) {
            state->process_event(state->current_state, event);
        }
        counted_free(event, "freeing sf event in controller");
    }
}



game_state* battle_init(){
    game_state* state = counted_malloc(sizeof(game_state), "playing state init");
    window_config* win_conf = get_window_config();
    sfVideoMode mode = {win_conf->window_width, win_conf->window_height, 16};
    state->window = sfRenderWindow_create(mode, "Stickwar",  sfResize | sfClose, NULL);
    state->current_state = counted_malloc(sizeof(union game_state_union), "union state created");
    sfRenderWindow_setFramerateLimit(state->window, win_conf->fps);
    state->current_state->battle = battle_state_init_from_level(state, "mm0", "01");
    state->draw = battle_state_draw;
    state->process_event = battle_state_process_event;
    state->update = battle_state_update;
    return state;
}

game_state* menu_init(){
    game_state* state = counted_malloc(sizeof(game_state), "playing state init");
    window_config* win_conf = get_window_config();
    sfVideoMode mode = {win_conf->window_width, win_conf->window_height, 16};
    state->window = sfRenderWindow_create(mode, "Stickwar",  sfResize | sfClose, NULL);
    state->current_state = counted_malloc(sizeof(union game_state_union), "union state created");
    sfRenderWindow_setFramerateLimit(state->window, win_conf->fps);
    state->current_state->main_menu = main_menu_state_init(state);
    state->draw = main_menu_state_draw;
    state->process_event = main_menu_state_process_event;
    state->update = main_menu_state_update;
    return state;
}




/*

// battle end
void battle_to_battle(game_state* state, team* winner){
    battle* new_state = counted_malloc(sizeof(paused_state), "battle end state create");
    new_state->ended_battle = state->state;
    new_state->winning_team = winner;
    battle_end_display_message(new_state);
    state->state = new_state;
    state->next_loop = battle_next_loop;
    for (unsigned int i = 0;i<new_state->ended_battle->entities->size;i++){
        entity* ent = list_at(new_state->ended_battle->entities,i);
        if (ent->team!=new_state->winning_team){
            ent->type->to_dying(ent);
        }
    }
}
*/