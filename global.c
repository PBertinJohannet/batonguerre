//
// Created by pierre on 24/08/17.
//
#include "global.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
int text_loaded = 0;
int anims_loaded = 0;
animation_list* get_animations(){
    if (!anims_loaded) {
        loaded_animations = animation_list_load();
        anims_loaded = 1;
    }
    return loaded_animations;
}

texture_list* get_textures(){
    if (!text_loaded){
        loaded_textures = texture_list_load();
        text_loaded = 1;
    }
    return loaded_textures;
}
void free_ressources(void){
    printf("free ressources");
    if (text_loaded) {
        texture_list_destroy(loaded_textures);
    }
    counted_free(get_window_config(), "free windows conf");
    if (anims_loaded) {
        animation_list_destroy(loaded_animations);
    }
}

unsigned int elapsed_us = 0;
int clock_started = 0;
sfClock* clock;
void update_time(){
    if (!clock_started){
        clock = sfClock_create();
        clock_started = 1;
    }
    elapsed_us = sfClock_restart(clock).microseconds;
}
float get_elapsed_sec(){
    return ((float)elapsed_us)/1000000.f;
}
