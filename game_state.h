//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_game_state_H
#define STICKWAR_game_state_H

#include "game_state.h"
#include "battle.h"
#include "end_state.h"
#include <SFML/Graphics.h>
#include "main_menu_state.h"
typedef struct game_state game_state;
typedef struct battle_state battle_state;
typedef struct paused_state paused_state;
typedef struct end_state end_state;
typedef struct main_menu_state main_menu_state;
typedef union game_state_union game_state_union;

union game_state_union {
    battle_state* battle;
    paused_state* paused;
    end_state* end;
    main_menu_state* main_menu;
};

struct game_state {
    sfRenderWindow* window;
    game_state_union* current_state;
    void (*update)(game_state_union* state);
    void (*process_event)(game_state_union* state, sfEvent* event);
    void (*draw)(game_state_union* state);
};


void game_state_start(game_state* state);
game_state* battle_init(void);
game_state* menu_init(void);



#endif //STICKWAR_game_state_H
