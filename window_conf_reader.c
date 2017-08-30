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
        global_window_config->window_width = (int) json_integer_value(
                read_elem(config, "window_width", "reading window width", JSON_INTEGER));
        global_window_config->window_height = (int) json_integer_value(
                read_elem(config, "window_height", "reading window height", JSON_INTEGER));
        global_window_config->fps = (int) json_integer_value(read_elem(config, "fps", "reading config", JSON_INTEGER));
        window_config_loaded = 1;
    }
    return global_window_config;
}