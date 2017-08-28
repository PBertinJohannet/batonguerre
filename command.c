//
// Created by pierre on 27/08/17.
//
#include "command.h"

command* command_init(int entity_type){
    command* c = malloc(sizeof(command));
    c->entity_state = ENTITY_STATE_RETREATING;
    return c;
}