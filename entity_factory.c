//
// Created by pierre on 22/08/17.
//
#include "global.h"
#include "entity_factory.h"
#include "ninja.h"
#include "base.h"
#include "archer.h"
entity* factory_new_entity(int type, int team, int level, int state, int command, game* g){
    entity* ent;
    animation_frame* walking;
    float position = (team)?POP_PLAYER_TWO:POP_PLAYER_ONE;
    switch (type)
    {
        case KICKER :
            walking = animation_frame_init(get_animations()->stick_walk);
            ent = entity_init(KICKER_BASE_LIFE, KICKER_BASE_SPEED, team, KICKER_BASE_SIZE, position, state, command, walking);
            set_kicker_class(ent,level);
            break;
        case NINJA :
            walking = animation_frame_init(get_animations()->ninja_walk);
            ent = entity_init(NINJA_BASE_LIFE, NINJA_BASE_SPEED, team, NINJA_BASE_SIZE, position, state, command, walking);
            set_ninja_class(ent,level);
            break;
        case ARCHER :
            walking = animation_frame_init(get_animations()->archer_walk);
            ent = entity_init(ARCHER_BASE_LIFE, ARCHER_BASE_SPEED, team, ARCHER_BASE_SIZE, position, state, command, walking);
            set_archer_class(ent,level);
            break;
        case BASE :
            walking = animation_frame_init(get_animations()->stick_walk);
            ent = entity_init(250, 0, team, 3.8, position, state, command, walking);
            set_base_class(ent,level);
            break;
        default:
            break;
    }
    return ent;
}