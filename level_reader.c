//
// Created by pierre on 30/08/17.
//
#include "level_reader.h"
#include "string.h"
#include "stdio.h"

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
    printf("%s\n",army_path);
    lv->config = json_value_get_object(json_parse_file(conf_path));
    lv->armys = json_value_get_object(json_parse_file(army_path));
    counted_free(conf_path, "level configuration path destroy");
    counted_free(army_path, "army path destroy");
    return lv;
}

battle_config* level_reader_read_conf(level_reader* reader){
    battle_config* btl = counted_malloc(sizeof(battle_config), "battle config init");
    btl->map_size =(unsigned int)json_object_get_number(reader->config, "map_size");
    btl->ground_pos =(unsigned int)json_object_get_number(reader->config, "ground_pos");
    btl->nb_teams =(unsigned int)json_object_get_number(reader->config, "nb_teams");
    btl->player_team =(unsigned int)json_object_get_number(reader->config, "player_team");
    return btl;
}

list* level_reader_read_entities(level_reader* reader, battle* b){
    list* entities_list = list_init();
    JSON_Array* entities_json = json_object_get_array(reader->config,"entities");
    for (unsigned int i = 0;i<json_array_get_count(entities_json); i++){
        JSON_Object* group = json_array_get_object(entities_json, i);
        int team_number = (int)json_object_get_number(group, "team");
        brigade* brig =list_at(battle_get_team(b, team_number)->brigades,(unsigned int)json_object_get_number(group, "brigade_id"));
        for (int j=0;j<(int)json_object_get_number(group, "number");j++){
            list_add(entities_list, factory_new_entity(brig));
        }
    }
    return entities_list;
}


list* level_reader_read_gold(level_reader* lvl, battle* b){
    list* objects = list_init();
    JSON_Array* gold_list = json_object_get_array(lvl->config, "gold_heaps");
    int gold_size = (int)json_object_get_number(lvl->config, "gold_heaps_size");
    for (unsigned int i = 0;i<json_array_get_count(gold_list); i++){
        float pos = json_array_get_number(gold_list, i);
        list_add(objects, gold_heap_init((int)(b->map_size*pos), gold_size, 0.5*log(gold_size)));
    }
    return objects;
}


team* level_reader_read_team(level_reader* reader, unsigned int number) {
    JSON_Array *teams = json_object_get_array(reader->config, "teams");
    JSON_Object *json_team = json_array_get_object(teams, number);
    team* t =  team_init(number,
                     (int)json_object_get_number(json_team, "pop"),
                     (int)json_object_get_number(json_team, "gold_start"),
                     (int)json_object_get_number(json_team, "gold_per_sec"));
    if ((int)(number)!=(int)json_object_get_number(reader->config, "player_team")){
        team_set_brigades(t, brigades_reader_get_brigades(reader->armys, t));
    }
    return t;
}

ai* level_reader_read_ai(level_reader* reader, team* t){
    JSON_Array *teams = json_object_get_array(reader->config, "teams");
    JSON_Object *team = json_array_get_object(teams, t->id);
    return get_ai_by_name(json_object_get_string(team, "ai"),t);
}

void level_reader_destroy(level_reader* lvl){
    counted_free(lvl, "destroying lvl reader");
}
void battle_config_destroy(battle_config* lvl){
    counted_free(lvl, "destroying lvl reader");
}