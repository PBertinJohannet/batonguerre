//
// Created by pierre on 21/08/17.
//

#include <SFML/Graphics/Rect.h>
#include "animation.h"
animation* animation_init(char* name){
    animation* anim = malloc(sizeof(animation));
    char* img_name = malloc((strlen(name)+strlen(".png"))*sizeof(char));
    strcpy(img_name,name);
    strcat(img_name,".png");
    char* json_name = malloc((strlen(name)+strlen(".json")+2)*sizeof(char));
    strcpy(json_name,name);
    strcat(json_name,".json");
    read_frames(json_name, anim);
    anim->texture = sfTexture_createFromFile(img_name,NULL);
    return anim;
}

animation_frame* animation_frame_init(animation* target){
    animation_frame* anim = malloc(sizeof(animation_frame));
    anim->anim = target;
    anim->frame = 0;
    return anim;
}


sfSprite* animation_frame_next(animation_frame* anim, int flip){
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, anim->anim->texture, sfTrue);
    sfIntRect target = anim->anim->frames[(int)(anim->frame)];
    if (flip){
        flip_rect(&target);
    }
    sfSprite_setTextureRect(sprite, target);
    if (anim->frame==anim->anim->nb_frames){
        anim->frame = 0;
    }
    return sprite;
}

void flip_rect(sfIntRect* rect){
    rect->left+=rect->width;
    rect->width*=-1;
}


void animation_frame_destroy(animation_frame* an){
    free(an);
}


void animation_destroy(animation* anim){
    sfTexture_destroy(anim->texture);
    free(anim->frames);
    free(anim);
}