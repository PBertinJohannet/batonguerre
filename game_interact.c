//
// Created by pierre on 24/08/17.
//
#include "game_interact.h"
#include "brigade.h"
void game_order_retreat(game* g, team* t){
    for (int i = 0;i<t->brigades->size;i++){
        brigade* b = list_at(t->brigades,i);
        b->command->entity_state = ENTITY_STATE_RETREATING;
    }
}

void game_order_assault(game* g, team* t){
    game_command_all(g,t,g->map_size*!t->id);
}
void game_command_all(game* g, team* t, int target){
    for (int i = 0;i<t->brigades->size;i++){
        brigade* b = list_at(t->brigades,i);
        b->command->target = target;
        b->command->entity_state = ENTITY_STATE_ASSAULT;
    }
}

void game_command_one(game* g, team* t, int target, int ent_type){
    brigade* b = list_at(t->brigades,ent_type);
    b->command->target = target;
    b->command->entity_state = ENTITY_STATE_ASSAULT;
}


