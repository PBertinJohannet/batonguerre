//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_ENTITY_FACTORY_H
#define STICKWAR_ENTITY_FACTORY_H

#include "entity_behaviour.h"
#include "entity.h"
#include "kicker.h"
#include "game_state.h"
#include "animation.h"
#include "time.h"
#include "team.h"
#include "brigade.h"
typedef struct brigade brigade;
typedef struct team team;
typedef struct battle battle;
typedef struct entity entity;
enum entity_class{
    KICKER,
    NINJA,
    ARCHER,
    BASE,
    MINEWORKER,
    NUMBER_OF_CLASSES,
};
entity* factory_new_entity(brigade*);
#endif //STICKWAR_ENTITY_FACTORY_H
