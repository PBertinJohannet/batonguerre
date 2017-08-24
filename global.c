//
// Created by pierre on 24/08/17.
//
#include "global.h"

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