//
// Created by pierre on 23/08/17.
//

#ifndef STICKWAR_TEXTURES_H
#define STICKWAR_TEXTURES_H

#include <SFML/Graphics.h>
typedef struct texture_list texture_list;
struct texture_list {
    sfTexture* background;
    sfTexture* assault;
    sfTexture* retreat;
    sfTexture* flag;
};
texture_list* texture_list_load(void);
int texture_list_destroy(texture_list*);
#endif //STICKWAR_TEXTURES_H
