//
// Created by pierre on 23/08/17.
//

#include "dumb_ai.h"
#include "brigade.h"
dumb_ai* dumb_ai_init(team* t){
    dumb_ai* dai = malloc(sizeof(dumb_ai));
    dai->team = t;
    dai->target_id = rand()%t->brigades->size;
    dai->last_ass = 0;
    return dai;
}

void dumb_ai_play(ai* my_ai, game* g){
    dumb_ai* dai = my_ai->ai;
    entity_launcher* launcher_target = ((brigade*)list_at(dai->team->brigades, dai->target_id))->launcher;
    if (dai->team->gold > launcher_target->cost && launcher_target->curr_cd == launcher_target->cd){
        entity_launcher_launch(launcher_target, g);
        dai->target_id = rand()%dai->team->brigades->size;
    }
    if (!choose_mode(dai, g->entities)){
        dai->last_ass = 0;
        game_command_one(g,dai->team,g->map_size-500,ARCHER);
        game_command_one(g,dai->team,g->map_size-550,KICKER);
        game_command_one(g,dai->team,g->map_size-450,NINJA);
    } else {
        if (!dai->last_ass) {
            game_order_assault(g, dai->team);
        }
        dai->last_ass = 1;
    }
}

int choose_mode(dumb_ai* ai, list* entities){
    int my_units = 0, his_units = 0;
    for (int i = 0;i<entities->size;i++){
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
    return (my_units-5) > his_units;
}


void dumb_ai_destroy(dumb_ai* dai){
    free(dai);
}