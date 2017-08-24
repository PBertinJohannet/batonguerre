//
// Created by pierre on 23/08/17.
//
#include "texture_list.h"

texture_list* texture_list_load() {
    texture_list *t = malloc(sizeof(texture_list));
    t->background = sfTexture_createFromFile("background.png", NULL);
    t->assault = sfTexture_createFromFile("assault.png", NULL);
    t->retreat = sfTexture_createFromFile("retreat.png", NULL);
    return t;
}


int texture_list_destroy(texture_list*t){
    sfTexture_destroy(t->retreat);
    sfTexture_destroy(t->background);
    sfTexture_destroy(t->assault);
    free(t);
    return 0;
}