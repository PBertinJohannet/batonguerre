//
// Created by pierre on 12/09/17.
//
#include "main_menu_state.h"
#include "global.h"
void test_suck_button(main_menu_state* state){
    clickable_menu* menu = state->menu;
    sfVector2i* position = malloc(sizeof(sfVector2i));
    position->x = get_window_config()->window_width*0.4;
    position->y = get_window_config()->window_height*0.4;
    sfVector2i* size = malloc(sizeof(sfVector2i));
    size->x = 200;
    size->y = 200;
    button* but = button_init(test_print_pos, state, position, size, "new game", NULL);
    clickable_menu_add_button(menu, but);
}

void test_print_pos(void* state){
    main_menu_state_to_battle(state);
    printf("I the one who have been chosen\n");
}

main_menu_state* main_menu_state_init(game_state* super){
    main_menu_state* menu = counted_malloc(sizeof(main_menu_state), "creating battle state");
    menu->super = super;
    menu->menu = clickable_menu_init();
    menu->drawer = screen_drawer_init(super->window);
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
__attribute_const__ void main_menu_state_update(__attribute__((unused))game_state_union* ps){

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
void main_menu_state_to_battle(main_menu_state* menu){
    game_state* state = menu->super;
    state->current_state = counted_malloc(sizeof(union game_state_union), "union state created");
    state->current_state->battle = battle_state_init_from_level(state, "mm0", "01");
    state->draw = battle_state_draw;
    state->process_event = battle_state_process_event;
    state->update = battle_state_update;
    screen_drawer_destroy(menu->drawer);
    free(menu);
}