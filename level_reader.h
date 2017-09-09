//
// Created by Pierre on 30/08/2017
// This contains the functions to read a saved battle state.
//
#ifndef LEVEL_READER_H
#define LEVEL_READER_H
#include "jansson.h"
#include "team.h"
#include "array_list.h"
#include "ai.h"
typedef struct level_reader level_reader;
typedef struct ai ai;
typedef struct battle_config battle_config;
/**
 * the struct containing the temporary conf.
 */
struct battle_config {
    unsigned int map_size;
    unsigned int ground_pos;
    unsigned int nb_teams;
    unsigned int player_team;
};
/**
 * This is the structure used to store the battle infos and the json_t pointer.
 * config : the json element containing the config.
 * ennemy_army : the json element containing the e.a
 */
struct level_reader {
    json_t* config;
    json_t* armys;
};

level_reader* level_reader_init(char* lvl_name);
battle_config* level_reader_read_conf(level_reader* reader);
team* level_reader_read_team(level_reader* reader, unsigned int team_number);
list* level_reader_read_armies(level_reader* reader);
ai* level_reader_read_ai(level_reader* reader, team* t);
list* level_reader_read_entities(level_reader* reader, battle* b);

#endif