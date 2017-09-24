//
// Created by pierre on 31/08/17.
//
#include "brigade_reader.h"
#include "counted_allocations.h"
#include "stdlib.h"
mineworker_stats* brigades_reader_read_mineworker(JSON_Object* obj){
    mineworker_stats* k = counted_malloc(sizeof(mineworker_stats), "create kicker stats");
    k->range = (int)json_object_get_number(obj, "range");
    k->gold_harvested = (int)json_object_get_number(obj, "gold_harvested");
    k->max_gold = (int)json_object_get_number(obj, "max_gold");
    k->harvesting_speed = (int)json_object_get_number(obj, "harvesting_speed");
    return k;
}
kicker_stats* brigades_reader_read_kicker(JSON_Object* obj){
    kicker_stats* k = counted_malloc(sizeof(kicker_stats), "create kicker stats");
    k->range = (int)json_object_get_number(obj, "range");
    k->punch_chance = (int)json_object_get_number(obj, "punch_chance");
    k->punch_damage = (int)json_object_get_number(obj, "punch_damage");
    k->kick_damage = (int)json_object_get_number(obj, "kick_damage");
    k->base_attack_speed = (int)json_object_get_number(obj, "base_attack_speed");
    k->punch_attack_speed = (int)json_object_get_number(obj, "punch_attack_speed");
    return k;
}
ninja_stats* brigades_reader_read_ninja(JSON_Object* obj){
    ninja_stats* n = counted_malloc(sizeof(ninja_stats), "create ninja stats");
    n->range = (int)json_object_get_number(obj, "range");
    n->hit_chance = (int)json_object_get_number(obj, "hit_chance");
    n->slash_damage = (int)json_object_get_number(obj, "slash_damage");
    n->hit_damage = (int)json_object_get_number(obj, "hit_damage");
    n->jump_chance = (int)json_object_get_number(obj, "jump_chance");
    n->jump_range = (int)json_object_get_number(obj, "jump_range");
    n->basic_attack_speed = (int)json_object_get_number(obj, "basic_attack_speed");
    n->jump_damage = (int)json_object_get_number(obj, "jump_damage");
    return n;
}
archer_stats* brigades_reader_read_archer(JSON_Object* obj){
    archer_stats* a = counted_malloc(sizeof(archer_stats), "create archer stats");
    a->range = (int)json_object_get_number(obj, "range");
    a->range_short = (int)json_object_get_number(obj, "range_short");
    a->normal_damage = (int)json_object_get_number(obj, "normal_damage");
    a->critical_damage = (int)json_object_get_number(obj, "critical_damage");
    a->short_range_damage = (int)json_object_get_number(obj, "short_range_damage");
    a->critical_chance = (int)json_object_get_number(obj, "critical_chance");
    a->number_of_arrows = (int)json_object_get_number(obj, "number_of_arrows");
    a->arrow_speed = (int)json_object_get_number(obj, "arrow_speed");
    a->arrow_size = json_object_get_number(obj, "arrow_size");
    a->basic_attack_speed = (int)json_object_get_number(obj, "basic_attack_speed");
    return a;
}

void brigades_reader_set_specific_stats(JSON_Object* obj, brigade* brig){
    const char* type = json_object_get_string(obj, "type");
    if (strcmp(type, "kicker")==0){
        brigade_set_type(brig, KICKER, brigades_reader_read_kicker(obj));
    } else if (strcmp(type, "ninja")==0){
        brigade_set_type(brig, NINJA, brigades_reader_read_ninja(obj));
    } else if (strcmp(type, "archer")==0){
        brigade_set_type(brig, ARCHER, brigades_reader_read_archer(obj));
    } else if (strcmp(type, "mineworker")==0){
        brigade_set_type(brig, MINEWORKER, brigades_reader_read_mineworker(obj));
    } else {
        printf("error : entity type not found %s \n   exiting \n",type);
        exit(0);
    }
}

brigade* brigades_reader_read_brigade(JSON_Object* obj, team* t){
    brigade* bg= brigade_init((int)json_object_get_number(obj, "cooldown"),
                              (int)json_object_get_number(obj, "cost"),
                              (int)json_object_get_number(obj, "base_life"),
                              (int)json_object_get_number(obj, "base_speed"),
                              (int)json_object_get_number(obj, "random_speed"),
                              json_object_get_number(obj, "base_size"),
                              (int)json_object_get_number(obj, "base_armor"), t);
    brigades_reader_set_specific_stats(obj, bg);
    return bg;
}
list* brigades_reader_get_brigades(JSON_Object* army, team* t){
    JSON_Array* brigades = json_object_get_array(army,"brigades");
    list* to_ret = list_init();
    for (unsigned int i = 0;i<json_array_get_count(brigades);i++){
        list_add(to_ret, brigades_reader_read_brigade(json_array_get_object(brigades, i), t));
    }
    return to_ret;
}