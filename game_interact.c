//
// Created by pierre on 24/08/17.
//
#include "game_interact.h"
#include "brigade.h"
void game_order_retreat(team* t){
    for (unsigned int i = 0;i<t->brigades->size;i++){
        brigade* b = list_at(t->brigades,i);
        b->command->entity_state = ENTITY_STATE_RETREATING;
    }
}

void game_order_assault(game* g, team* t){
    game_command_all(t, g->map_size*!t->id);
}
void game_command_all(team* t, unsigned int target){
    for (unsigned int i = 0;i<t->brigades->size;i++){
        brigade* b = list_at(t->brigades,i);
        b->command->target = target;
        b->command->entity_state = ENTITY_STATE_ASSAULT;
    }
}

void game_command_one(team* t, unsigned int target, unsigned int ent_type){
    brigade* b = list_at(t->brigades,ent_type);
    b->command->target = target;
    b->command->entity_state = ENTITY_STATE_ASSAULT;
}


