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
typedef union game_state_union game_state_union;
struct end_state{
    game_state* super;
    battle* ended_battle;
    char* text;
    int timer;
    int won;
};
end_state* end_state_init(battle_state*, int );
void end_state_draw(game_state_union* state);
void end_state_update(game_state_union* ps);
void end_state_process_event(game_state_union* state, sfEvent* event);
void end_state_to_campaign_state(end_state* end);


#endif //STICKWAR_END_STATE_H
