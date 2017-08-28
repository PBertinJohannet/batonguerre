//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_ANIMATION_H
#define STICKWAR_ANIMATION_H

#include <SFML/Graphics.h>
#include <SFML/Graphics/Rect.h>
#include "stdlib.h"
#include "string.h"
#include "json_frame.h"
typedef struct animation_frame animation_frame;
typedef struct animation animation;
struct animation{
    sfTexture* texture;
    int nb_frames;
    sfIntRect* frames;
};
struct animation_frame{
    animation* anim;
    float frame;
};

animation* animation_init(char* name);
animation_frame* animation_frame_init(animation*);
sfSprite* animation_frame_next(animation_frame* anim, int flip);
void animation_frame_destroy(animation_frame*);
void flip_rect(sfIntRect* rect);
void animation_destroy(animation*);
#endif //STICKWAR_ANIMATION_H
