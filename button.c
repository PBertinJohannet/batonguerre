//
// Created by pierre on 12/09/17.
//
#include "button.h"

button* button_init(void(*callback)(void*), void* args, sfVector2i* position, sfVector2i* size, char* txt, animation* anim){
    button* b = counted_malloc(sizeof(button), "creating button");
    b->args = args;
    b->callback = callback;
    b->position = position;
    b->size = size;
    b->text =txt;
    b->anim = animation_frame_init(anim);
    return b;
}