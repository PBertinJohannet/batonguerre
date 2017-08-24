//
// Created by pierre on 23/08/17.
//

#include "dumb_ai.h"
dumb_ai* dumb_ai_init(team* t){
    dumb_ai* dai = malloc(sizeof(dumb_ai));
    dai->team = t;
    dai->target_id = rand()%t->spawners->size;
    dai->last_ass = 0;
    return dai;
}

void dumb_ai_play(dumb_ai* dai, game* g){
    entity_launcher* launcher_target = list_at(dai->team->spawners, dai->target_id);
    if (dai->team->gold > launcher_target->cost && launcher_target->curr_cd == launcher_target->cd){
        entity_launcher_launch(launcher_target, g);
        dai->target_id = rand()%dai->team->spawners->size;
    }
    if (!choose_mode(dai, g->entities)){
        game_order_retreat(g,1);
        dai->last_ass = 0;
    } else {
        if (!dai->last_ass) {
            game_order_assault(g, 1);
        }
        dai->last_ass = 1;
    }
}

int choose_mode(dumb_ai* ai, list* entities){
    int my_units = 0, his_units = 0;
    for (int i = 0;i<entities->size;i++){
        entity* ent = (entity*)(list_at(entities,i));
        if (ent->team == 0){
            his_units++;
            if ((POP_PLAYER_TWO - ent->pos) <500){
                return 1;
            }
        } else {
            my_units++;
        }
    }
    return (my_units/2) > his_units;
}


void dumb_ai_destroy(dumb_ai* dai){
    free(dai);
}