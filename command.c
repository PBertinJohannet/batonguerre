//
// Created by pierre on 27/08/17.
//
#include "command.h"
#include "counted_allocations.h"
command* command_init(){
    command* c = counted_malloc(sizeof(command), "command init");
    c->entity_state = ENTITY_STATE_RETREATING;
    return c;
}