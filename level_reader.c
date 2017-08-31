//
// Created by pierre on 30/08/17.
//
#include "stdlib.h"
#include "level_reader.h"
#include "string.h"
#include "stdio.h"
#include "utils.h"
level_reader* level_reader_init(char* lvl_name){
    level_reader* lv = malloc(sizeof(level_reader));
    char * conf_path = malloc(sizeof(char)*(strlen(lvl_name)+strlen("confs/levels//configuration.json")));
    sprintf(conf_path, "confs/levels/%s/configuration.json",lvl_name);
    char * army_path = malloc(sizeof(char)*(strlen(lvl_name)+strlen("confs/levels//army.json")));
    sprintf(army_path, "confs/levels/%s/army.json",lvl_name);
    lv->config = start_json(conf_path);
    lv->armys = start_json(army_path);
    free(conf_path);
    free(army_path);
    return lv;
}

battle_config* level_reader_read_conf(level_reader* reader){
    battle_config* btl = malloc(sizeof(battle_config));
    btl->map_size = json_read_int(reader->config, "map_size");
    btl->ground_pos = json_read_int(reader->config, "ground_pos");
    btl->nb_teams = json_read_int(reader->config, "nb_teams");
    btl->player_team = json_read_int(reader->config, "player_team");
    return btl;
}

team* level_reader_read_team(level_reader* reader, int number) {
    json_t *teams = json_read_elem(reader->config, "teams", "reading teams", JSON_ARRAY);
    json_t *team = json_read_index(teams, number, "reading team", JSON_OBJECT);
    return team_init(number,
                     json_read_int(team, "pop"),
                     json_read_int(team, "gold_start"),
                     json_read_int(team, "gold_per_sec"));
}

ai* level_reader_read_ai(level_reader* reader, team* t){
    json_t *teams = json_read_elem(reader->config, "teams", "reading teams", JSON_ARRAY);
    json_t *team = json_read_index(teams, t->id, "reading team", JSON_OBJECT);
    return get_ai_by_name(json_read_string(team, "ai"),t);
}

list* level_reader_read_rmys(level_reader* reader){
    return list_create();
}