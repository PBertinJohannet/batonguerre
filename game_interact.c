//
// Created by pierre on 24/08/17.
//
#include "game_interact.h"

void game_order_retreat(game* g, int team_id){
    game_get_team(g,team_id)->order = RETREAT;
    for (int i =0;i<g->entities->size;i++) {
        entity *ent = (entity *) (list_at(g->entities, i));
        if (ent->team == team_id && ent->state != DYING) {
            ent->state = RETREATING;
        }
    }
}
void game_order_assault(game* g, int team_id){
    game_get_team(g,team_id)->order = ATTACK;
    for (int i =0;i<g->entities->size;i++) {
        entity *ent = (entity *) (list_at(g->entities, i));
        if (ent->team == team_id && ent->state != DYING) {
            ent->state = AGG_MOVING;
        }
    }
}
