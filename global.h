//
// Created by pierre on 24/08/17.
//

#ifndef STICKWAR_GLOBAL_H
#define STICKWAR_GLOBAL_H

#include "animation_list.h"
#include "texture_list.h"
// anims
animation_list * loaded_animations;
animation_list* get_animations();
// textures
texture_list* loaded_textures;
texture_list* get_textures();

#endif //STICKWAR_GLOBAL_H

