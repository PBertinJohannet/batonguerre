//
// Created by pierre on 31/08/17.
//
#include "window_conf_reader.h"
#include "counted_allocations.h"
#include "parson.h"
int window_config_loaded = 0;
struct window_config* get_window_config(){
    if (!window_config_loaded) {
        JSON_Object *config = json_value_get_object(json_parse_file(("confs/global_conf.json")));
        global_window_config = counted_malloc(sizeof(window_config), "create window config");
        global_window_config->window_width =(unsigned int)json_object_get_number(config, "window_width");
        global_window_config->window_height =(unsigned int)json_object_get_number(config, "window_height");
        global_window_config->fps =(unsigned int)json_object_get_number(config, "fps");
        window_config_loaded = 1;
    }
    return global_window_config;
}