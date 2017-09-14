//
// Created by pierre on 22/08/17.
//
#include "global.h"
#include "entity_factory.h"
#include "ninja.h"
#include "base.h"
#include "archer.h"
#include "mineworker.h"
entity* factory_new_entity(brigade* brigade){
    entity* ent = entity_init(brigade);
    switch (brigade->entity_type)
    {
        case KICKER :
            set_kicker_class(ent);
            break;
        case NINJA :
            set_ninja_class(ent);
            break;
        case ARCHER :
            set_archer_class(ent);
            break;
        case BASE :
            exit(0);
            break;
        case MINEWORKER :
            set_mineworker_class(ent);
            break;
        default:
            break;
    }
    ent->type->to_retreat(ent);
    return ent;
}