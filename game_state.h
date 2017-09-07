//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_game_state_H
#define STICKWAR_game_state_H

#include "game_state.h"
#include "battle.h"
#include "end_state.h"
#include <SFML/Graphics.h>
typedef struct battle_end battle_end;
typedef struct game_state game_state;



struct game_state {
    sfRenderWindow* window;
    void* current_state;
    void (*update)(void* state);
    void (*process_event)(void* state, sfEvent* event);
    void (*draw)(void* state);
};





void game_state_start(game_state* state);

game_state* battle_init(void);



#endif //STICKWAR_game_state_H
