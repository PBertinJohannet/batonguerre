//
// Created by pierre on 23/08/17.
//

#include "dumb_ai.h"
#include "brigade.h"
#include "counted_allocations.h"
dumb_ai* dumb_ai_init(team* t){
    dumb_ai* dai = counted_malloc(sizeof(dumb_ai), "dumb ai create");
    dai->team = t;
    dai->target_id = ((unsigned int)rand())%t->brigades->size;
    dai->last_ass = 0;
    return dai;
}

void dumb_ai_play(ai* my_ai, battle* g){
    dumb_ai* dai = my_ai->ai;
    entity_launcher* launcher_target = ((brigade*)list_at(dai->team->brigades, dai->target_id))->launcher;
    if (can_launch(launcher_target)){
        entity_launcher_launch(launcher_target, g);
        dai->target_id = ((unsigned int)rand())%dai->team->brigades->size;
    }
    if (!choose_mode(dai, g->entities)){
        dai->last_ass = 0;
        battle_command_one(dai->team,(unsigned int)g->map_size-500,ARCHER);
        battle_command_one(dai->team,((unsigned int)g->map_size-550),KICKER);
        battle_command_one(dai->team,(unsigned int)g->map_size-450,NINJA);
    } else {
        if (!dai->last_ass) {
            battle_order_assault(g, dai->team);
        }
        dai->last_ass = 1;
    }
}

int choose_mode(dumb_ai* ai, list* entities){
    int my_units = 0, his_units = 0;
    for (unsigned int i = 0;i<entities->size;i++){
        entity* ent = (entity*)(list_at(entities,i));
        if (ent->team != ai->team){
            his_units++;
            if (ent->state == ENTITY_STATE_ATTACKING){
                return 1;
            }
        } else {
            my_units++;
        }
    }
    return (my_units/2) > his_units;
}


void dumb_ai_destroy(dumb_ai* dai){
    counted_free(dai, "destroy dumb ai");
}