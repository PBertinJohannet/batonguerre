//
// Created by pierre on 23/08/17.
//
#include "paused_state.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
#include "battle_state.h"

paused_state* paused_state_init(battle_state* bs){
    paused_state* ps = counted_malloc(sizeof(paused_state), "creating paused state");
    ps->super = bs->super;
    ps->paused_battle = bs->battle;
    return ps;
}

void paused_state_draw(game_state_union* state){
    view* v =state->paused->paused_battle->view;
    sfText_destroy(v->text);
    v->text = sfText_create();
    sfText_setString(v->text, " PAUSED \n press SPACE to continue ");
    window_config* win_conf = get_window_config();
    sfVector2f position = {win_conf->window_height/4, win_conf->window_width/4};
    sfText_setPosition(v->text, position);
    sfText_setFont(v->text, v->font);
    sfText_setCharacterSize(v->text, 75);
    sfText_setColor(v->text, sfRed);
    sfRenderWindow_drawText(v->window, v->text, NULL);
    sfRenderWindow_display(v->window);
}
__attribute_const__ void paused_state_update(__attribute__ ((unused)) game_state_union* ps){

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
        default:
            break;
    }
}

void paused_state_to_battle(paused_state* ps){
    ps->super->current_state->battle = battle_state_init_from_pause(ps);
    ps->super->draw = battle_state_draw;
    ps->super->update = battle_state_update;
    ps->super->process_event = battle_state_process_event;
    counted_free(ps, "freeing paused state to battle ! ");
}