//
// Created by pierre on 11/09/17.
//

#ifndef STICKWAR_BUTTON_H
#define STICKWAR_BUTTON_H

#include "counted_allocations.h"
#include <SFML/Graphics.h>
#include "drawable_entity.h"
#include "animation.h"
typedef struct button button;
struct button {
    void (*callback)(void*);
    void* args;
    sfVector2i* position;
    sfVector2i* size;
    char* text;
    animation_frame* anim;
};


button* button_init(void(*)(void*), void*, sfVector2i*, sfVector2i*, char*, animation*);


#endif //STICKWAR_BUTTON_H
