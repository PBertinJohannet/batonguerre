//
// Created by pierre on 27/08/17.
//
#include "brigade.h"

brigade* brigade_init(int ent_type, int level, int cost, int cd, animation* anim, team* team){
    brigade* b = malloc(sizeof(brigade));
    b->command = command_init(ent_type);
    b->launcher = entity_launcher_init(ent_type, level, cost, cd, anim, team);
    return b;
}
void brigade_change_order(game* g, int order){
    //comm
}