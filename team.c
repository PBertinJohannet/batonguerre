//
// Created by pierre on 23/08/17.
//
#include "team.h"
#include "entity_launcher.h"
#include "global.h"
#include "brigade.h"
#include "window_conf_reader.h"
team* team_init(int team_number,int pop, int gold_start, int gold_per_sec){
    team* t = malloc(sizeof(team));
    t->id = team_number;
    t->gold = gold_start;
    t->pop = pop;
    t->gold_per_sec = gold_per_sec;
    t->brigades = list_create();
    return t;
}


void team_init_brigades(team* t){
    list_add(t->brigades,brigade_init(KICKER,2,KICKER_COST,KICKER_COOLDOWN*get_window_config()->fps,get_animations()->kicker_icon,t));
    list_add(t->brigades,brigade_init(NINJA,2,NINJA_COST,NINJA_COOLDOWN*get_window_config()->fps,get_animations()->ninja_icon,t));
    list_add(t->brigades,brigade_init(ARCHER,2,ARCHER_COST,ARCHER_COOLDOWN*get_window_config()->fps,get_animations()->kicker_icon,t));
}


void team_launch_entity(team* t,game* g, int id){
    if (id>=t->brigades->size){
        return;
    }
    brigade* b = list_at(t->brigades, id);
    entity_launcher_launch(b->launcher, g);
}
void team_order_entity(team* t,game* g, int id){
    if (id>=t->brigades->size){
        return;
    }
    brigade* b = list_at(t->brigades, id);
    entity_launcher_launch(b->launcher, g);
}

void team_play(team* t, int frame){
    if (!(frame%get_window_config()->fps)) {
        t->gold += t->gold_per_sec;
    }
    for (int i = 0;i<t->brigades->size;i++){
        entity_launcher_update(((brigade*)list_at(t->brigades,i))->launcher);
    }
}

void team_destroy(team* t){
    list_free(t->brigades, entity_launcher_destroy);
    free(t);
}


