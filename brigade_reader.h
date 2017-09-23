//
// Created by Pierre on 30/08/2017
// This contains the functions to read something but I dont know what
//

#ifndef STICKWAR_BRIGADE_READER_H
#define STICKWAR_BRIGADE_READER_H

#include "array_list.h"
#include "brigade.h"
#include "parson.h"

typedef struct ninja_stats ninja_stats;
typedef struct kicker_stats kicker_stats;
typedef struct archer_stats archer_stats;
typedef struct mineworker_stats mineworker_stats;
typedef struct brigade brigade;
typedef struct team team;

struct mineworker_stats {
    int range;
    int gold_harvested;
    int max_gold;
    int harvesting_speed;
};

struct kicker_stats {
    int range;
    int punch_chance;
    int punch_damage;
    int kick_damage;
    int base_attack_speed;
    int punch_attack_speed;
};

struct ninja_stats {
    int range;
    int hit_chance;
    int hit_damage;
    int slash_damage;
    int jump_chance;
    int jump_range;
    int basic_attack_speed;
};
struct archer_stats {
    int range;
    int range_short;
    int normal_damage;
    int critical_damage;
    int short_range_damage;
    int critical_chance;
    int number_of_arrows;
    int arrow_speed;
    float arrow_size;
    int basic_attack_speed;
};


brigade* brigades_reader_read_brigade(JSON_Object* obj, team*);
mineworker_stats* brigades_reader_read_mineworker(JSON_Object* obj);
kicker_stats* brigades_reader_read_kicker(JSON_Object* obj);
ninja_stats* brigades_reader_read_ninja(JSON_Object* obj);
archer_stats* brigades_reader_read_archer(JSON_Object* obj);
void brigades_reader_set_specific_stats(JSON_Object* obj, brigade* brg);
list* brigades_reader_get_brigades(JSON_Object* brigades, team* t);

#endif //STICKWAR_BRIGADE_READER_H
