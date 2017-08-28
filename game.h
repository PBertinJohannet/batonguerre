//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_GAME_H
#define STICKWAR_GAME_H

#include <SFML/Graphics.h>
#include "view.h"
#include "entity.h"
#include "drawable_entity.h"
#include "array_list.h"
#include "controller.h"
#include "animation_list.h"
#include "game_params.h"
#include "team.h"
#include "dumb_ai.h"
#include "game_state.h"
#include "projectile.h"
typedef struct game game;
typedef struct game_state game_state;
typedef struct entity entity;
typedef struct team team;
typedef struct dumb_ai dumb_ai;
typedef struct projectile projectile;
typedef struct controller controller;
struct game{
    controller* controller;
    game_state* state;
    team* player;
    team* ennemy;
    struct view * view;
    list* entities;
    list* projectiles;
    int frame;
    dumb_ai* ennemy_ai;
};

game* game_init(game_state* state);
sfRenderWindow* game_get_view_window(game* g);
void game_test(game* g);
void game_init_teams(game* g);
void game_update(game* g);
list* game_get_drawables(game* g);
void game_next_loop(game* g) ;
void game_add_entity(game* g, entity* ent);
team* game_get_team(game* g, int team_id);
void game_init_team(game* g, team* t);
void end_update(game* g);
void game_destroy(game* g);
void game_add_projectile(game* g, projectile* proj);
#endif //STICKWAR_GAME_H
