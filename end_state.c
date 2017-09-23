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

end_state* end_state_init(battle_state* bs, int won){
    end_state* end = counted_malloc(sizeof(end_state), "creating end state");
    if (!won){
        end->text = "DEFEAT";
    } else {
        end ->text = "VICTORY";
    }
    end->won = won;
    end->super = bs->super;
    end->ended_battle = bs->battle;
    end->timer = 100;
    return end;
}

__attribute_const__ void end_state_draw(__attribute__ ((unused)) game_state_union* state){
    printf("end state draw \n");
    battle* b = state->end->ended_battle;
    printf("got battle \n");
    screen_drawer_clear(b->view->drawer);
    printf("cleared screen \n");
    battle_draw(b);
    printf("drawed battle\n");
    window_config* win_conf = get_window_config();
    printf("got window config\n");
    sfVector2f position = {win_conf->window_height/4, win_conf->window_width/4};
    printf("calculated position\n");
    screen_drawer_write_text(b->view->drawer, state->end->text, sfRed, 75, position);
    printf("wrote text \n");
}
void end_state_update(game_state_union* ps){
    printf("end update\n");
    ps->end->timer-=1;
    if (ps->end->timer==0){
        end_state_to_campaign_state(ps->end);
    }
}
void end_state_process_event(game_state_union* state, sfEvent* event){
    printf("end process event \n");
    end_state* ps = state->end;
    switch (event->type) {
        case sfEvtClosed:
            sfRenderWindow_close(ps->super->window);
            break;
        default:
            break;
    }
}

void end_state_to_campaign_state(end_state* end){
    game_state* super = end->super;
    if (end->won) {
        super->current_state->campaign = campaign_state_next_level(super, end->ended_battle->campaign_id);
    } else {
        super->current_state->campaign = campaign_state_load(super, end->ended_battle->campaign_id);
    }
    super->draw = campaign_state_draw;
    super->process_event = campaign_state_process_event;
    super->update = campaign_state_update;
    battle_destroy(end->ended_battle);
    counted_free(end, "freeing menu");
}