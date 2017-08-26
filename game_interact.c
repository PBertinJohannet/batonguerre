//
// Created by pierre on 24/08/17.
//
#include "game_interact.h"

void game_order_retreat(game* g, int team_id){
    team* t = game_get_team(g,team_id);
    for (int i = 0;i<t->spawners->size;i++){
        entity_launcher* sp = list_at(t->spawners,i);
        sp->command = ENTITY_STATE_RETREATING;
    }
    for (int i =0;i<g->entities->size;i++) {
        entity *ent = (entity *) (list_at(g->entities, i));
        if (ent->team == team_id && ent->state != ENTITY_STATE_DYING) {
            ent->state = ENTITY_STATE_RETREATING;
        }
    }
}

void game_order_assault(game* g, int team_id){
    game_command_all(g,team_id,MAP_SIZE*team_id);
}

void game_command_one(game* g, int team_id, int entity_type, int target){
    team* t = game_get_team(g,team_id);
    for (int i = 0;i<t->spawners->size;i++){
        entity_launcher* sp = list_at(t->spawners,i);
        if (sp->ent_type == entity_type) {
            sp->target_command = target;
            sp->command = ENTITY_STATE_ASSAULT;
        }
    }
    for (int i =0;i<g->entities->size;i++) {
        entity *ent = (entity *) (list_at(g->entities, i));
        if (ent->team == team_id && ent->state != ENTITY_STATE_DYING && ent->type->type == entity_type) {
            ent->commanded_target = target;
            ent->state = ENTITY_STATE_ASSAULT;
        }
    }
}


void game_command_all(game* g, int team_id, int target){
    team* t = game_get_team(g,team_id);
    for (int i = 0;i<t->spawners->size;i++){
        entity_launcher* sp = list_at(t->spawners,i);
        sp->target_command = target;
        sp->command = ENTITY_STATE_ASSAULT;
    }
    for (int i =0;i<g->entities->size;i++) {
        entity *ent = (entity *) (list_at(g->entities, i));
        if (ent->team == team_id && ent->state != ENTITY_STATE_DYING) {
            ent->commanded_target = target;
            ent->state = ENTITY_STATE_ASSAULT;
        }
    }
}