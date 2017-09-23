//
// Created by pierre on 21/09/17.
//
#include "final_ai.h"

final_ai* final_ai_init(team* t){
    final_ai* fai = counted_malloc(sizeof(final_ai), "dumb ai create");
    fai->ninjas = 0;
    fai->boss_launched = 0;
    fai->stamp = 0;
    fai->cur_order = 0;
    fai->team = t;
    if (fai->cur_order == 2){
        fai->cur_order = 0;
    }
    return fai;
}
void final_ai_play(ai* my_ai, battle* b) {
    final_ai* fai = my_ai->ai;
    battle_order_assault(b, fai->team);
    battle_command_one(fai->team, (unsigned int) b->map_size - 250, 1);
    battle_command_one(fai->team, (unsigned int) b->map_size - 200, 4);
    battle_command_one(fai->team, (unsigned int) b->map_size - 50, 5);
    if (fai->stamp++ ==2000 && !fai->boss_launched){
        fai->stamp = -100*fai->team->gold_per_sec;
        fai->team->gold_per_sec++;
        printf("curr gps : %d\n", fai->team->gold_per_sec);
        if (fai->ninjas>10){
            fai->ninjas = 0;
        }
    }
    entity_launcher* launcher_target = ((brigade*)list_at(fai->team->brigades, fai->cur_order))->launcher;
    if (fai->ninjas>10){
        battle_order_assault(b, fai->team);
    }
    if (can_launch(launcher_target)){
        if (fai->cur_order == 5){
            fai->ninjas+=1;
        }
        entity_launcher_launch(launcher_target, b);
        fai->cur_order = rand()%7;
        if (fai->cur_order == 2){
            fai->cur_order = 5;
        }
    }
    for (unsigned int i = 0;i<b->entities->size; i++){
        entity* e = list_at(b->entities, i);
        if (e->type->type == MINEWORKER && e->team == fai->team && e->state == ENTITY_STATE_DYING && fai->boss_launched==0){
            fai->team->gold+=2000;
            printf("launch boss !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            entity_launcher* launcher_target = ((brigade*)list_at(fai->team->brigades, 2))->launcher;
            entity_launcher_launch(launcher_target, b);
            fai->boss_launched = 1;
        }
    }
    if (fai->boss_launched){
        battle_order_assault(b, fai->team);
    }
}


void final_ai_destroy(final_ai* ai){
    counted_free(ai, "destroy final ai");
}