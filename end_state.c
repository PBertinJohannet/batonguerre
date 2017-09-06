//
// Created by pierre on 23/08/17.
//

#include "battle.h"
#include "end_state.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
/*
void battle_end_next_loop(battle* ps){
    if (!battle_end_update(ps)) {
        for (unsigned int i = 0; i < ps->ended_battle->entities->size; i++) {
            entity *ent = list_at(ps->ended_battle->entities, i);
            if (ent->team != ps->winning_team &&
                drawable_entity_get_frame(ent->drawable) == ent->drawable->anim->anim->nb_frames - 2) {
                ent->drawable->anim->frame -= 1;
            }
        }
        view_draw_map(ps->ended_battle->view);
        view_draw_launchers(ps->ended_battle->view, ps->ended_battle->player->brigades);
        battle_end_display_message(ps);
        view_draw_entities(ps->ended_battle->view, battle_get_drawables(ps->ended_battle));
    }
}*/

int battle_end_update(battle* es) {
    battle* g = es->ended_battle;
    int to_battle = 0;
    sfEvent *event = counted_malloc(sizeof(sfEvent), "battle end create sfevent ");
    while (sfRenderWindow_pollEvent(battle_get_view_window(g), event)) {
        switch (event->type) {
            case sfEvtClosed:
                sfRenderWindow_close(battle_get_view_window(g));
                break;
            case sfEvtKeyPressed:
                if (sfKeyboard_isKeyPressed(sfKeySpace)) {
                    to_battle = 1;
                }
                break;
            default:
                break;
        }
    }
    counted_free(event, "freeing event in end state");
    if (to_battle) {
        battle_to_battle(es->ended_battle->state);
        return 1;
    }
    return 0;
}

end_state* end_state_init(battle_state* bs){
    end_state* ps = counted_malloc(sizeof(end_state), "creating end state");
    ps->super = bs->super;
    ps->end_battle = bs->battle;
    return ps;
}

void end_state_draw(void* state){
    view* v =( (end_state*) state)->end_battle->view;
    sfText_destroy(v->text);
    v->text = sfText_create();
    sfText_setString(v->text, " end \n press SPACE to continue ");
    window_config* win_conf = get_window_config();
    sfVector2f position = {win_conf->window_height/4, win_conf->window_width/4};
    sfText_setPosition(v->text, position);
    sfText_setFont(v->text, v->font);
    sfText_setCharacterSize(v->text, 75);
    sfText_setColor(v->text, sfRed);
    sfRenderWindow_drawText(v->window, v->text, NULL);
    sfRenderWindow_display(v->window);
}
__attribute_const__ void end_state_update(__attribute__ ((unused)) void* ps){

}
void end_state_process_event(void* state, sfEvent* event){
    end_state* ps = state;
    switch (event->type) {
        case sfEvtClosed:
            sfRenderWindow_close(ps->super->window);
            break;
        case sfEvtKeyPressed:
            if (sfKeyboard_isKeyPressed(sfKeySpace)) {
                end_state_to_battle(ps);
            }
            break;
        default:
            break;
    }
}

void end_state_to_battle(end_state* ps){
    ps->super->current_state = battle_state_init_from_pause(ps);
    ps->super->draw = battle_state_draw;
    ps->super->update = battle_state_update;
    ps->super->process_event = battle_state_process_event;
    counted_free(ps, "freeing end state to battle ! ");
}