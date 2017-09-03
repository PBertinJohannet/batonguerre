//
// Created by pierre on 31/08/17.
//
#include "brigade_reader.h"
#include "counted_allocations.h"
kicker_stats* brigades_reader_read_kicker(json_t* obj){
    kicker_stats* k = counted_malloc(sizeof(kicker_stats), "create kicker stats");
    k->range = json_read_int(obj, "range");
    k->punch_chance = json_read_int(obj, "punch_chance");
    k->punch_damage = json_read_int(obj, "punch_damage");
    k->kick_damage = json_read_int(obj, "kick_damage");
    k->base_attack_speed = json_read_int(obj, "base_attack_speed");
    k->punch_attack_speed = json_read_int(obj, "punch_attack_speed");
    return k;
}
ninja_stats* brigades_reader_read_ninja(json_t* obj){
    ninja_stats* n = counted_malloc(sizeof(ninja_stats), "create ninja stats");
    n->range = json_read_int(obj, "range");
    n->hit_chance = json_read_int(obj, "hit_chance");
    n->slash_damage = json_read_int(obj, "slash_damage");
    n->hit_damage = json_read_int(obj, "hit_damage");
    n->jump_chance = json_read_int(obj, "jump_chance");
    n->jump_range = json_read_int(obj, "jump_range");
    n->basic_attack_speed = json_read_int(obj, "basic_attack_speed");
    return n;
}
archer_stats* brigades_reader_read_archer(json_t* obj){
    archer_stats* a = counted_malloc(sizeof(archer_stats), "create archer stats");
    a->range = json_read_int(obj, "range");
    a->range_short = json_read_int(obj, "range_short");
    a->normal_damage = json_read_int(obj, "normal_damage");
    a->critical_damage = json_read_int(obj, "critical_damage");
    a->short_range_damage = json_read_int(obj, "short_range_damage");
    a->critical_chance = json_read_int(obj, "critical_chance");
    a->number_of_arrows = json_read_int(obj, "number_of_arrows");
    a->arrow_speed = json_read_int(obj, "arrow_speed");
    a->arrow_size = json_read_int(obj, "arrow_size");
    return a;
}

void brigades_reader_set_specific_stats(json_t* obj, brigade* brig){
    const char* type = json_read_string(obj, "type");
    if (strcmp(type, "kicker")==0){
        brigade_set_type(brig, KICKER, brigades_reader_read_kicker(obj));
    } else if (strcmp(type, "ninja")==0){
        brigade_set_type(brig, NINJA, brigades_reader_read_ninja(obj));
    } else if (strcmp(type, "archer")==0){
        brigade_set_type(brig, ARCHER, brigades_reader_read_archer(obj));
    } else {
        printf("error : entity type not found %s \n   exiting \n",type);
        exit(0);
    }
}

brigade* brigades_reader_read_brigade(json_t* obj, team* t){
    brigade* bg= brigade_init(json_read_int(obj, "cooldown"),
                              json_read_int(obj, "cost"),
                              json_read_int(obj, "base_life"),
                              json_read_int(obj, "base_speed"),
                              json_read_int(obj, "random_speed"),
                              json_read_float(obj, "base_size"),
                              json_read_int(obj, "base_armor"), t);
    brigades_reader_set_specific_stats(obj, bg);
    return bg;
}
list* brigades_reader_get_brigades(json_t* army, team* t){
    json_t* brigades = json_read_elem(army,"brigades","reading brigades",JSON_ARRAY);
    list* to_ret = list_create();
    for (unsigned int i = 0;i<json_array_size(brigades);i++){
        list_add(to_ret, brigades_reader_read_brigade(json_read_index(brigades, i, "reading brigades array",JSON_OBJECT), t));
    }
    return to_ret;
}