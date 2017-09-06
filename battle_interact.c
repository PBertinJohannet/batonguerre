//
// Created by pierre on 24/08/17.
//
#include "battle_interact.h"
#include "brigade.h"
void battle_order_retreat(team* t){
    for (unsigned int i = 0;i<t->brigades->size;i++){
        brigade* b = list_at(t->brigades,i);
        b->command->entity_state = ENTITY_STATE_RETREATING;
    }
}

void battle_order_assault(battle* g, team* t){
    battle_command_all(t, g->map_size*!t->id);
}
void battle_command_all(team* t, unsigned int target){
    for (unsigned int i = 0;i<t->brigades->size;i++){
        brigade* b = list_at(t->brigades,i);
        b->command->target = target;
        b->command->entity_state = ENTITY_STATE_ASSAULT;
    }
}

void battle_command_one(team* t, unsigned int target, unsigned int ent_type){
    brigade* b = list_at(t->brigades,ent_type);
    b->command->target = target;
    b->command->entity_state = ENTITY_STATE_ASSAULT;
}


