//
// Created by pierre on 23/08/17.
//
#include "paused_state.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
#include "battle_state.h"
#include "button.h"
paused_state* paused_state_init(battle_state* bs){
    paused_state* ps = counted_malloc(sizeof(paused_state), "creating paused state");
    ps->super = bs->super;
    ps->paused_battle = bs->battle;
    ps->menu = clickable_menu_init();
    ps->switch_to = DONT_SWITCH;
    int xpos = 400;
    printf("xpos : %d\n", xpos);
    clickable_menu_add_button(ps->menu, button_inline_init((void(*)(void*))paused_state_switch_to_battle,
                                                           (void*)ps, xpos, 200, 25, "resume game", NULL));
    clickable_menu_add_button(ps->menu, button_inline_init((void(*)(void*))paused_state_switch_to_main,
                                                           (void*)ps, xpos, 300, 25, "main menu", NULL));
    return ps;
}

void paused_state_draw(game_state_union* state){
    view* v =state->paused->paused_battle->view;
    screen_drawer_clear(v->drawer);
    window_config* win_conf = get_window_config();
    battle_draw(state->paused->paused_battle);
    sfVector2f position = {win_conf->window_height/4, win_conf->window_width/4};
    screen_drawer_write_text(v->drawer, " ", sfRed, 75, position);
    clickable_menu_draw(state->paused->menu, v->drawer);
}


__attribute_const__ void paused_state_update(game_state_union* ps){
    if (ps->paused->switch_to == SWITCH_TO_MENU){
        paused_state_to_main_menu(ps->paused);
    } else if (ps->paused->switch_to == SWITCH_TO_BATTLE){
        paused_state_to_battle(ps->paused);
    }
}
void paused_state_process_event(game_state_union* state, sfEvent* event){
    paused_state* ps = state->paused;
    switch (event->type) {
        case sfEvtClosed:
            sfRenderWindow_close(ps->super->window);
            break;
        case sfEvtKeyPressed:
            if (sfKeyboard_isKeyPressed(sfKeySpace)) {
                paused_state_to_battle(ps);
            }
            break;
        case sfEvtMouseButtonPressed:
            printf("mouse clicked \n");
            clickable_menu_click_event(ps->menu, sfMouse_getPositionRenderWindow(ps->super->window));
        default:
            break;
    }
}

void paused_state_to_battle(paused_state* ps){
    ps->super->current_state->battle = battle_state_init_from_pause(ps);
    ps->super->draw = battle_state_draw;
    ps->super->update = battle_state_update;
    ps->super->process_event = battle_state_process_event;
    clickable_menu_destroy(ps->menu);
    counted_free(ps, "freeing paused state to battle ! ");
}
void paused_state_switch_to_main(paused_state* ps){
    ps->switch_to = SWITCH_TO_MENU;
}
void paused_state_switch_to_battle(paused_state* ps){
    ps->switch_to = SWITCH_TO_BATTLE;
}

void paused_state_to_main_menu(paused_state* ps){
    ps->super->current_state->main_menu = main_menu_state_init(ps->super);
    clickable_menu_destroy(ps->menu);
    battle_destroy(ps->paused_battle);
    counted_free(ps, "freeing paused state to battle ! ");
}