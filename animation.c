//
// Created by pierre on 21/08/17.
//

#include <SFML/Graphics/Rect.h>
#include "animation.h"
#include "counted_allocations.h"
animation* animation_init(char* name){
    animation* anim = counted_malloc(sizeof(animation), "creating animation in animation init");
    char* img_name = counted_malloc((strlen(name)+strlen(".png"))*sizeof(char), "creating img name in animation init");
    strcpy(img_name,name);
    strcat(img_name,".png");
    char* json_name = counted_malloc((strlen(name)+strlen(".json")+2)*sizeof(char), "creating json name in animation init");
    strcpy(json_name,name);
    strcat(json_name,".json");
    read_frames(json_name, anim);
    anim->texture = sfTexture_createFromFile(img_name,NULL);
    return anim;
}

animation_frame* animation_frame_init(animation* target){
    animation_frame* anim = counted_malloc(sizeof(animation_frame), "creating animation frame from animation");
    anim->anim = target;
    anim->frame = 0;
    return anim;
}


sfSprite* animation_frame_next(animation_frame* anim, unsigned int flip){
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, anim->anim->texture, sfTrue);
    sfIntRect target = anim->anim->frames[(int)(anim->frame)];
    if (flip){
        flip_rect(&target);
    }
    sfSprite_setTextureRect(sprite, target);
    if (((unsigned int)anim->frame)==anim->anim->nb_frames){
        anim->frame = 0;
    }
    return sprite;
}

void flip_rect(sfIntRect* rect){
    rect->left+=rect->width;
    rect->width*=-1;
}


void animation_frame_destroy(animation_frame* an){
    counted_free(an, "destroy animation frame");
}


void animation_destroy(animation* anim){
    sfTexture_destroy(anim->texture);
    counted_free(anim->frames, "destroy frames in animation");
    counted_free(anim, "destroy animation");
}