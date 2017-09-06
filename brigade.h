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
typedef struct battle battle;
/**
 * The brigade struct.
 * Contains :
 * command : the command given to the brigade
 * launcher : the launcher to train entities.
 */
struct brigade {
    command* command;
    entity_launcher* launcher;
    int entity_type;
    team* team;
    int cooldown;
    int cost;
    int base_life;
    int base_speed;
    int random_speed;
    float base_size;
    int base_armor;
    void* specific_stats;
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
brigade* brigade_init(int, int, int, int, int, float, int, team*);

void brigade_set_type(brigade* b, int type, void* stats);


#endif //STICKWAR_BRIGADE_H