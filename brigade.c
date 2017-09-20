//
// Created by pierre on 27/08/17.
//
#include "brigade.h"
#include "counted_allocations.h"
brigade* brigade_init(int cooldown, int cost, int base_life, int base_speed, int random_speed, float base_size, int base_armor, team* team){
    brigade* b = counted_malloc(sizeof(brigade), "create brigade");
    b->team = team;
    b->base_life = base_life;
    b->base_speed = base_speed;
    b->base_armor = base_armor;
    b->base_size = base_size;
    b->random_speed = random_speed;
    b->command = command_init();
    b->launcher = entity_launcher_init(b,cost,cooldown);
    return b;
}

void brigade_set_type(brigade* b, int type, void* stats){
    b->entity_type = type;
    b->specific_stats = stats;
    entity_launcher_set_type(b->launcher, type);
}

void brigade_destroy(brigade* b){
    counted_free(b->command, "freeing command");
    entity_launcher_destroy(b->launcher);
    counted_free(b->specific_stats, "freeing specific stats");
    counted_free(b, "freeing brigade");
}