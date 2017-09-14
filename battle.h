//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_battle_H
#define STICKWAR_battle_H

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
#include "object.h"
#include "ai.h"
typedef struct ai ai;
typedef struct battle battle;
typedef struct game_state game_state;
typedef struct entity entity;
typedef struct team team;
typedef struct dumb_ai dumb_ai;
typedef struct object object;
typedef struct controller controller;
struct battle{
    controller* controller;
    game_state* state;
    team* player;
    team* ennemy;
    struct view * view;
    list* entities;
    list* objects;
    unsigned int frame;
    ai* ennemy_ai;
    unsigned int map_size;
};

battle* battle_from_level(game_state* state, char* level_name, char* saved_battle);
sfRenderWindow* battle_get_view_window(battle* g);
void battle_test(battle* g);
void battle_init_teams(battle* g);
void battle_update(battle* g);
list* battle_get_drawables(battle* g);
void battle_draw(battle* g) ;
void battle_add_entity(battle* g, entity* ent);
team* battle_get_team(battle* g, int team_id);
void battle_init_team(battle* g, team* t);
void end_update(battle* g);
void battle_destroy(battle* g);
void battle_add_object(battle* g, object* proj);
void battle_process_event(battle* b, sfEvent* e);
#endif //STICKWAR_battle_H
