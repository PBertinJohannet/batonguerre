//
// Created by pierre on 12/09/17.
//
#include "main_menu_state.h"
#include "global.h"
void test_suck_button(clickable_menu* menu){
    sfVector2i* position = malloc(sizeof(sfVector2i));
    position->x = 10;
    position->y = 12;
    sfVector2i* size = malloc(sizeof(sfVector2i));
    size->x = 100;
    size->y = 120;
    button* but = button_init(test_print_pos, (void*)2, position, size, "this is a test", get_animations()->gold_heap);
    clickable_menu_add_button(menu, but);
}

void test_print_pos(__attribute__((unused))void* integer){
    printf("I the one who have been chosen\n");
}

main_menu_state* main_menu_state_init(game_state* super){
    main_menu_state* menu = counted_malloc(sizeof(battle_state), "creating battle state");
    menu->super = super;
    menu->menu = clickable_menu_init();
    test_suck_button(menu->menu);
    super->current_state->main_menu = menu;
    super->process_event = main_menu_state_process_event;
    super->update = main_menu_state_update;
    super->draw = main_menu_state_draw;
    return menu;
}

void main_menu_state_draw(game_state_union* state){
    main_menu_state* menu = state->main_menu;
    //clickable_menu_draw(menu->menu, );
    sfRenderWindow_display(menu->super->window);
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
//void main_menu_state_to_battle(main_menu_state* ps);