//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_battle_H
#define STICKWAR_battle_H



#include "game_state.h"
#include "team.h"
struct end_state{
    game_state* super;
    battle* ended_battle;
};
end_state* end_state_init(battle_state* );
void end_state_draw(void* state);
void end_state_update(void* ps);
void end_state_process_event(void* state, sfEvent* event);

void end_state_to_battle(end_state* ps);

#endif //STICKWAR_battle_H
