//
// Created by pierre on 31/08/17.
//
#include "window_conf_reader.h"
#include "jansson.h"
int window_config_loaded = 0;
struct window_config* get_window_config(){
    if (!window_config_loaded) {
        json_t *config = start_json("confs/global_conf.json");
        global_window_config = malloc(sizeof(window_config));
        global_window_config->window_width = json_read_int(config, "window_width");
        global_window_config->window_height = json_read_int(config, "window_height");
        global_window_config->fps = json_read_int(config, "fps");
        window_config_loaded = 1;
    }
    return global_window_config;
}