//
// Created by pierre on 22/08/17.
//

#ifndef STICKWAR_ENTITY_FACTORY_H
#define STICKWAR_ENTITY_FACTORY_H

#include "entity_behaviour.h"
#include "entity.h"
#include "kicker.h"
#include "game.h"
#include "animation.h"
#include "time.h"
#include "team.h"
typedef struct team team;
typedef struct game game;
enum entity_class{
    KICKER,
    NINJA,
    ARCHER,
    BASE,
    NUMBER_OF_CLASSES,
};
entity* factory_new_entity(int type, team* team, int level, game* g);
#endif //STICKWAR_ENTITY_FACTORY_H
