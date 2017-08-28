//
// Created by pierre on 26/08/17.
//

#ifndef STICKWAR_COMMAND_H
#define STICKWAR_COMMAND_H

#include "stdlib.h"
#include "entity.h"

typedef struct command command;
struct command {
    int target;
    int entity_state;
    int entity_type;
};
command* command_init(int entity_type);
void change_command_to(int entity_state, int target);

#endif //STICKWAR_COMMAND_H
