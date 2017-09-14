//
// Created by pierre on 23/08/17.
//

#include "end_state.h"
#include "view.h"
#include "window_conf_reader.h"

#include "battle.h"
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

end_state* end_state_init(battle_state* bs){
    end_state* ps = counted_malloc(sizeof(end_state), "creating end state");
    ps->super = bs->super;
    ps->ended_battle = bs->battle;
    return ps;
}

__attribute_const__ void end_state_draw(__attribute__ ((unused)) game_state_union* state){
    battle* b = state->end->ended_battle;
    view* v =b->view;
    screen_drawer_clear(v->drawer);
    window_config* win_conf = get_window_config();
    sfVector2f position = {win_conf->window_height/4, win_conf->window_width/4};
    screen_drawer_write_text(v->drawer, " END \n press SPACE to continue ", sfRed, 75, position);
    sfRenderWindow_display(v->window);
}
__attribute_const__ void end_state_update(__attribute__ ((unused)) game_state_union* ps){
    printf("end state update \n");
}
void end_state_process_event(game_state_union* state, sfEvent* event){
    end_state* ps = state->end;
    switch (event->type) {
        case sfEvtClosed:
            sfRenderWindow_close(ps->super->window);
            break;
        default:
            break;
    }
}
