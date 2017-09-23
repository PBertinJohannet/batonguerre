//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_TYPE_H
#define STICKWAR_TYPE_H

#include "entity.h"
#include "array_list.h"
#include "game_state.h"
#include "math.h"
typedef struct entity_behaviour entity_behaviour;
typedef struct entity entity;
typedef struct battle battle;
typedef struct animation_list animation_list;
/**
 * This is where the entity behaviour is implemented.
 * it contains the functions that defines the entity behaviour on the battlefield.
 * in The .c file, some generic behaviours are implemented. however, the units can use their own behaviour
 * defined in their own .c file (eg : ninja.c for ninjas).
 *
 * To work the following functions are used :
 * Get current range :
 *      returns the current range of the entity, used to know when the unit can attack.
 * get availables attacks :
 *      returns a list of attacks with their % chance of happening.
 *      The attacks should be in an enum defined in the entity's file (ninja.h for ninjas)
 *
 * get animation for :
 *      Returns the appropriate attacking animation for an attack.
 *
 * get walking animation :
 *      returns the walking animation of the unit, used when the unit needs to walk.
 * play :
 *      this is the main function :
 *      it will make the entity performs all of his actions according to the battle state and team orders.
 *
 * to attack :
 *      this functions will be called when the unit wasnt attacking and starts attacking an ennemy unit.
 *
 * to assault :
 *      this function will be called when the unit was doing something else than moving aggressively and is asked to do so.
 *
 * to dying :
 *      this function will be called when the unit was doing something and it's health has gone under 1.
 *
 * to retreat :
 *      This function will be called when the unit was doing something and it needs to stop and start retreating.
 *
 * attacking :
 *      this function will be called every frame when the unit is attacking.
 *
 * retreating :
 *      this function will be called every frame when the unit is retreating.
 *
 * assaulting :
 *      this function will be called every frame when the unit is assaulting.
 *
 * This file provides basic behaviours for the following functions :
        attack_failing
        dying
        assaulting
        retreating
        to_assault
        to_retreat
        play
        to_dying
   wich means the following must still be implemented for every new type of entity :
        get current range
        get dying animation
        get walking animation
        to attack
        attacking
 *
 */
struct entity_behaviour {
    unsigned int type;
    int (*get_current_range)(entity*);
    animation* (*get_dying_animation)(entity*);
    struct animation* (*get_walking_animation)(entity*);
    void (*play) (battle* g, entity*, list*);
    void (*to_attack)(entity*,entity*);
    void (*to_assault)(entity*);
    void (*to_dying)(entity*);
    void (*to_retreat)(entity*);
    void (*attacking)( entity*, battle*);
    void (*attack_failing)( entity*, list*);
    void (*retreating)(entity*, list*);
    void (*assaulting)(entity*, list*, list*);
    void (*dying)(entity*);
    void (*take_damage)(entity*, int dmg);
    void* current_state;
};
void set_basic_behaviour(entity_behaviour* b);

void entity_base_assaulting(entity* player, list* entities, list* objects);

int entity_base_find_target(entity* player, list* entities);

void entity_base_dying(entity* player);

void entity_base_attack_failing(entity* player, list* entities);

void entity_base_to_retreat(entity* player);

void entity_base_retreating(entity* player, list* entities);

void entity_base_to_dying(entity* player);

void entity_base_to_assault(entity* player);

void entity_base_play(battle* g, entity* player, list* entities);

void entity_behaviour_destroy(entity_behaviour* ent);

void entity_base_take_damage(entity* ent, int damages);
#endif //STICKWAR_TYPE_H
