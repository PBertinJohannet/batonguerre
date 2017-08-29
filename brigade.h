//
// Created by pierre on 22/08/17.
// A brigade is a unit type available by the team.
// It contains the spawners to train and send units.
// And also the orders given to these units.
//

#ifndef STICKWAR_BRIGADE_H
#define STICKWAR_BRIGADE_H

#include "command.h"
#include "entity_launcher.h"
typedef struct brigade brigade;
typedef struct command command;
typedef struct entity_launcher entity_launcher;
typedef struct game game;
/**
 * The brigade struct.
 * Contains :
 * command : the command given to the brigade
 * launcher : the launcher to train entities.
 */
struct brigade {
    command* command;
    entity_launcher* launcher;
};
/**
 * Creates the brigade.
 * @param  ent_type : the type of entities in the brigade.
 * @param  level : the level of the entities.
 * @param  cost : the cost of launching one entity.
 * @param  cd : the cooldown of launching one entity.
 * @param  anim : the anim to give to that entity.
 * @param  team : the team of the brigade.
 */
brigade* brigade_init(int ent_type, int level, int cost, int cd, animation* anim, team* team);


/**
 * change the order.
 */
void brigade_change_order(game* g, int order);

#endif //STICKWAR_BRIGADE_H