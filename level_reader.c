//
// Created by pierre on 30/08/17.
//
#include "level_reader.h"
#include "string.h"
#include "stdio.h"
#include "utils.h"
#include "brigade_reader.h"
#include "counted_allocations.h"
#include "gold_heap.h"
#include "math.h"
level_reader* level_reader_init(char* lvl_name){
    level_reader* lv = counted_malloc(sizeof(level_reader), "level reader init");
    char * conf_path = counted_malloc(sizeof(char)*(strlen(lvl_name)+strlen("confs/levels//configuration.json")+1), "level configuration path");
    sprintf(conf_path, "confs/levels/%s/configuration.json",lvl_name);
    char * army_path = counted_malloc(sizeof(char)*(strlen(lvl_name)+strlen("confs/levels//army.json")+1), "create army path");
    sprintf(army_path, "confs/levels/%s/army.json",lvl_name);
    printf("%s\n",conf_path);
    lv->config = start_json(conf_path);
    lv->armys = start_json(army_path);
    counted_free(conf_path, "level configuration path destroy");
    counted_free(army_path, "army path destroy");
    return lv;
}

battle_config* level_reader_read_conf(level_reader* reader){
    battle_config* btl = counted_malloc(sizeof(battle_config), "battle config init");
    btl->map_size = json_read_uint(reader->config, "map_size");
    btl->ground_pos = json_read_uint(reader->config, "ground_pos");
    btl->nb_teams = json_read_uint(reader->config, "nb_teams");
    btl->player_team = json_read_uint(reader->config, "player_team");
    return btl;
}

list* level_reader_read_entities(level_reader* reader, battle* b){
    list* entities_list = list_create();
    json_t* entities_json = json_read_elem(reader->config,"entities", "reading entities", JSON_ARRAY);
    for (unsigned int i = 0;i<json_array_size(entities_json); i++){
        json_t* group = json_read_index(entities_json, i, "reading index of entities", JSON_OBJECT);
        int team_number = json_read_int(group, "team");
        brigade* brig =list_at(battle_get_team(b, team_number)->brigades, json_read_uint(group, "brigade_id"));
        for (int j=0;j<json_read_int(group, "number");j++){
            list_add(entities_list, factory_new_entity(brig));
        }
    }
    return entities_list;
}


list* level_reader_read_gold(level_reader* lvl, battle* b){
    list* objects = list_create();
    json_t* gold_list = json_read_elem(lvl->config, "gold_heaps", "reading gold heaps", JSON_ARRAY);
    int gold_size = json_read_int(lvl->config, "gold_heaps_size");
    for (unsigned int i = 0;i<json_array_size(gold_list); i++){
        float pos = json_read_float_index(gold_list, i, "reading gold heap index");
        list_add(objects, gold_heap_create((int)(b->map_size*pos), gold_size, 0.5*log(gold_size)));
    }
    return objects;
}


team* level_reader_read_team(level_reader* reader, unsigned int number) {
    json_t *teams = json_read_elem(reader->config, "teams", "reading teams", JSON_ARRAY);
    json_t *json_team = json_read_index(teams, number, "reading team", JSON_OBJECT);
    team* t =  team_init(number,
                     json_read_int(json_team, "pop"),
                     json_read_int(json_team, "gold_start"),
                     json_read_int(json_team, "gold_per_sec"));
    if ((int)(number)!=json_read_int(reader->config, "player_team")){
        team_set_brigades(t, brigades_reader_get_brigades(reader->armys, t));
    }
    return t;
}

ai* level_reader_read_ai(level_reader* reader, team* t){
    json_t *teams = json_read_elem(reader->config, "teams", "reading teams", JSON_ARRAY);
    json_t *team = json_read_index(teams, t->id, "reading team", JSON_OBJECT);
    return get_ai_by_name(json_read_string(team, "ai"),t);
}

void level_reader_destroy(level_reader* lvl){
    counted_free(lvl, "destroying lvl reader");
}
void battle_config_destroy(battle_config* lvl){
    counted_free(lvl, "destroying lvl reader");
}