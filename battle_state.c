//
// Created by pierre on 04/09/17.
//
#include "battle_state.h"
#include "end_state.h"
#include "paused_state.h"
battle_state* battle_state_init_from_level(game_state* super, char* level, char* campaign_id){
    battle_state* bs = counted_malloc(sizeof(battle_state), "creating battle state");
    bs->super = super;
    bs->battle = battle_from_level(super, level, campaign_id);
    super->current_state->battle = bs;
    super->process_event = battle_state_process_event;
    super->update = battle_state_update;
    super->draw = battle_state_draw;
    return bs;
}


battle_state* battle_state_init_from_pause(paused_state* ps){
    battle_state* bs = counted_malloc(sizeof(battle_state), "creating paused state");
    bs->super = ps->super;
    bs->battle = ps->paused_battle;
    return bs;
}
void battle_state_draw(game_state_union* state){
    battle_draw(state->battle->battle);
}

void battle_state_process_event(game_state_union* state, sfEvent* event){
    battle_process_event(state->battle->battle, event);
}

void battle_state_update(game_state_union* state){
    battle_update(state->battle->battle);
}


void battle_state_to_paused_state(game_state* state){
    battle_state* bs = state->current_state->battle;
    bs->super->current_state->paused = paused_state_init(bs);
    bs->super->update = paused_state_update;
    bs->super->process_event = paused_state_process_event;
    bs->super->draw = paused_state_draw;
    counted_free(bs, "destoying battle state going into pause");
}

void battle_state_to_end_state(game_state* state, int won){
    battle_state* bs = state->current_state->battle;
    bs->super->current_state->end = end_state_init(bs, won);
    bs->super->update = end_state_update;
    bs->super->process_event = end_state_process_event;
    bs->super->draw = end_state_draw;
    counted_free(bs, "destoying battle state going into end");
}
