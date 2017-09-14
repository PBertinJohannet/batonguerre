//
// Created by pierre on 24/08/17.
// This contains the objects : an object foesnt follow commands from any team and has no life point.
//

#ifndef STICKWAR_object_H
#define STICKWAR_object_H

#include "array_list.h"
#include "animation.h"
#include "drawable_entity.h"
#include "team.h"
typedef struct object object;
/**
 * This is the enum containing every different object of the game.
 */
enum object_type {
    OBJECT_ARROW,
    OBJECT_GOLD_HEAP,
};
/**
 * this is the structure containing the objects.
 * the fields are used as following :
 * object type is the type of the object( as defined in the object_type enum).
 * pos is the posiiton on the map
 * facing is the side the object is facing (0 for player, 1 for ennemy)
 * team is the team of the object (if it has one, else it is NULL)
 * play is the function defining the behaviour of the object
 * destroy is the function freeing the object.
 * self is a structure containing more informations about the object (if necessary).
 */
struct object {
    int object_type;
    float pos;
    unsigned int facing;
    team* team;
    int(*play)(void* ,list*);
    int(*destroy)(object*);
    drawable_entity* drawable;
    void* self;
};
/**
 * This is the fucntion assigning basic informations about the object. this can be used but there must be a function
 * creating the object and assigning the play and destroy functions (see arrow.c for an example).
 * @param pos : the position of the object on the map
 * @param team : the team of the object
 * @param facing : the side the object is facing
 * @return the newly created object
 */
object* object_create(int pos, team* team, unsigned int facing, int type);


#endif //STICKWAR_object_H
