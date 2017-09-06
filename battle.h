//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_battle_state_H
#define STICKWAR_battle_state_H

#include <SFML/Graphics.h>
#include "view.h"
#include "entity.h"
#include "drawable_entity.h"
#include "array_list.h"
#include "controller.h"
#include "animation_list.h"
#include "team.h"
#include "dumb_ai.h"
#include "game_state.h"
#include "projectile.h"
#include "ai.h"
typedef struct ai ai;
typedef struct battle_state battle_state;
typedef struct game_state game_state;
typedef struct entity entity;
typedef struct team team;
typedef struct dumb_ai dumb_ai;
typedef struct projectile projectile;
typedef struct controller controller;
struct battle_state{
    controller* controller;
    game_state* state;
    team* player;
    team* ennemy;
    struct view * view;
    list* entities;
    list* projectiles;
    unsigned int frame;
    ai* ennemy_ai;
    unsigned int map_size;
};

battle_state* battle_state_from_level(game_state* state, char* level_name, char* saved_battle);
battle_state* battle_state_load_saved(game_state* state);
sfRenderWindow* battle_state_get_view_window(battle_state* g);
void battle_state_test(battle_state* g);
void battle_state_init_teams(battle_state* g);
void battle_state_update(battle_state* g);
list* battle_state_get_drawables(battle_state* g);
void battle_state_draw(battle_state* g) ;
void battle_state_add_entity(battle_state* g, entity* ent);
team* battle_state_get_team(battle_state* g, int team_id);
void battle_state_init_team(battle_state* g, team* t);
void end_update(battle_state* g);
void battle_state_destroy(battle_state* g);
void battle_state_add_projectile(battle_state* g, projectile* proj);
#endif //STICKWAR_battle_state_H
