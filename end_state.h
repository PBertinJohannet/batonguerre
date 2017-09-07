//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_END_STATE_H
#define STICKWAR_END_STATE_H



#include "game_state.h"
#include "team.h"
#include "battle_state.h"
#include "battle.h"
typedef struct game_state game_state;
typedef struct battle battle;
typedef struct battle_state battle_state;
typedef struct end_state end_state;
struct end_state{
    game_state* super;
    battle* ended_battle;
};
end_state* end_state_init(battle_state* );
void end_state_draw(void* state);
void end_state_update(void* ps);
void end_state_process_event(void* state, sfEvent* event);


#endif //STICKWAR_END_STATE_H
