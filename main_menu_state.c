//
// Created by pierre on 12/09/17.
//
#include "main_menu_state.h"
#include "campaign_state.h"
#include "global.h"
void test_suck_button(main_menu_state* state){
    clickable_menu_add_button(state->menu, button_inline_init((void(*)(void*))main_menu_switch_to_battle,
                                                              (void*)state, 400, 500, 25, "New game", NULL));
    clickable_menu_add_button(state->menu, button_inline_init((void(*)(void*))main_menu_state_quit,
                                                              (void*)state, 400, 600, 25, "Exit", NULL));
}

void test_print_pos(void* state){
    main_menu_state_to_campaign(state);
    printf("I the one who have been chosen\n");
}

main_menu_state* main_menu_state_init(game_state* super){
    printf("menu state init\n");
    main_menu_state* menu = counted_malloc(sizeof(main_menu_state), "creating battle state");
    menu->super = super;
    menu->menu = clickable_menu_init();
    menu->drawer = screen_drawer_init(super->window);
    menu->switch_to = 0;
    test_suck_button(menu);
    super->current_state->main_menu = menu;
    super->process_event = main_menu_state_process_event;
    super->update = main_menu_state_update;
    super->draw = main_menu_state_draw;
    return menu;
}

void main_menu_state_draw(game_state_union* state){
    main_menu_state* menu = state->main_menu;
    clickable_menu_draw(menu->menu, menu->drawer);
}
__attribute_const__ void main_menu_state_update(game_state_union* ps){
    if (ps->main_menu->switch_to){
        main_menu_state_to_campaign(ps->main_menu);
    }
}
void main_menu_state_process_event(game_state_union* state, sfEvent* event){
    main_menu_state* menu = state->main_menu;
    switch (event->type) {
        case sfEvtClosed:
            sfRenderWindow_close(menu->super->window);
            break;
        case sfEvtMouseButtonPressed:
            clickable_menu_click_event(menu->menu, sfMouse_getPositionRenderWindow(menu->super->window));
            printf("mouse clicked\n");
            break;
        default:
            break;
    }
}

void main_menu_switch_to_battle(main_menu_state* menu){
    menu->switch_to = 1;
}

void main_menu_state_to_campaign(main_menu_state* menu){
    game_state* state = menu->super;
    state->current_state->campaign = campaign_state_new_game(state, "001");
    state->draw = campaign_state_draw;
    state->process_event = campaign_state_process_event;
    state->update = campaign_state_update;
    screen_drawer_destroy(menu->drawer);
    clickable_menu_destroy(menu->menu);
    counted_free(menu, "freeing menu");
}

__attribute__((noreturn)) void main_menu_state_quit(main_menu_state* menu){
    sfRenderWindow_destroy(menu->super->window);
    counted_free(menu->super->current_state,"freeing super state");
    counted_free(menu->super,"freeing super");
    clickable_menu_destroy(menu->menu);
    screen_drawer_destroy(menu->drawer);
    counted_free(menu, "freeing menu state");
    free_ressources();
    counted_show_allocateds();
    exit(0);
}