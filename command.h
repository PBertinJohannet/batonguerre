

//
// Created by pierre on 26/08/17.
// This file contains the command structure, used to store current command sent by user.
//

#ifndef STICKWAR_COMMAND_H
#define STICKWAR_COMMAND_H

#include "entity.h"

typedef struct command command;

/**
 * This is the command structure.
 * It contains a command given to a brigade.
 * target : the target on the map.
 * entity_state : the desired state of entities eg : Retreat/assault
 * entity_type : the type of the brigade.
 */
struct command {
    unsigned int target;
    unsigned int entity_state;
};

/**
 * Creates the command.
 * @param entity_type : the type of the brigade.
 */
command* command_init(void);

/**
 * update the command.
 * @param entity_state : the new desired state.
 * @param target : the new target.
 */
void change_command_to(int entity_state, int target);

#endif //STICKWAR_COMMAND_H