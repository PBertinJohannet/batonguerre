//
// Created by pierre on 23/08/17.
//
#include "team.h"
#include "entity_launcher.h"
#include "global.h"
#include "brigade.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
team* team_init(unsigned int team_number,int pop, int gold_start, int gold_per_sec){
    team* t = counted_malloc(sizeof(team), "creating team");
    t->id = team_number;
    t->gold = gold_start;
    t->pop = pop;
    t->gold_per_sec = gold_per_sec;
    t->gold_acc = 0;
    return t;
}


void team_set_brigades(team* t, list* l){
    t->brigades = l;
}


void team_launch_entity(team* t,battle* g, unsigned int id){
    if (id>=t->brigades->size){
        return;
    }
    brigade* b = list_at(t->brigades, id);
    entity_launcher_launch(b->launcher, g);
}
void team_order_entity(team* t,battle* g, unsigned int id){
    if (id>=t->brigades->size){
        return;
    }
    brigade* b = list_at(t->brigades, id);
    entity_launcher_launch(b->launcher, g);
}

void team_play(team* t){
    t->gold_acc+=get_elapsed_sec();
    if (t->gold_acc>1.0) {
        t->gold += t->gold_per_sec;
        t->gold_acc-=1.0;
    }
    for (unsigned int i = 0; i < t->brigades->size; i++) {
        entity_launcher_update(((brigade *) list_at(t->brigades, i))->launcher);
    }
}

void team_destroy(team* t){
    list_free(t->brigades, (void(*)(void*))brigade_destroy);
    counted_free(t, "freeing team");
}


