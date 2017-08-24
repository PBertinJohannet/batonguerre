//
// Created by pierre on 23/08/17.
//
#include "team.h"
#include "entity_launcher.h"
#include "global.h"
team* team_init(int team_number){
    team* t = malloc(sizeof(team));
    t->gold = GOLD_START;
    t->spawners = list_create();
    t->right = team_number;
    t->order = RETREAT;
    return t;
}


void team_init_spawners(team* t, int team_id){
    list_add(t->spawners,entity_launcher_init(NINJA,2,NINJA_COST,NINJA_COOLDOWN*FPS,get_animations()->ninja_icon,team_id));
    list_add(t->spawners,entity_launcher_init(KICKER,2,KICKER_COST,KICKER_COOLDOWN*FPS,get_animations()->kicker_icon,team_id));
    list_add(t->spawners,entity_launcher_init(ARCHER,2,ARCHER_COST,ARCHER_COOLDOWN*FPS,get_animations()->kicker_icon,team_id));
}

void team_launch_entity(team* t,game* g, int id){
    if (id>=t->spawners->size){
        return;
    }
    entity_launcher* launcher = list_at(t->spawners, id);
    entity_launcher_launch(launcher, g);
}

void team_play(team* t, int frame){
    if (!(frame%FPS)) {
        t->gold += GOLD_PER_SEC;
    }
    for (int i = 0;i<t->spawners->size;i++){
        entity_launcher_update(list_at(t->spawners,i));
    }
}

void team_destroy(team* t){
    list_free(t->spawners, entity_launcher_destroy);
    free(t);
}


