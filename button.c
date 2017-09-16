//
// Created by pierre on 12/09/17.
//
#include "button.h"
#include "global.h"
button* button_init(void(*callback)(void*), void* args, sfVector2i* position, sfVector2i* size, char* txt, animation* anim){
    button* b = counted_malloc(sizeof(button), "creating button");
    b->args = args;
    b->callback = callback;
    b->position = position;
    b->size = size;
    b->text =txt;
    if (anim != NULL) {
        b->anim = animation_frame_init(anim);
    } else {
        b->anim = animation_frame_init(get_animations()->button);
    }
    return b;
}

button* button_inline_init(void(*callback)(void*), void* args, int pos_x, int pos_y, int size_x, int size_y, char* txt, animation* anim){
    sfVector2i* position = counted_malloc(sizeof(sfVector2i), "creating vector2i for button");
    position->y = pos_y;
    position->x = pos_x;
    sfVector2i* size = counted_malloc(sizeof(sfVector2i), "creating vector2i for button");
    size->y = size_y;
    size->x = size_x;
    return button_init(callback, args, position, size, txt, anim);
}

void button_destroy(button* b){
    free(b->position);
    free(b->size);
    free(b);
}