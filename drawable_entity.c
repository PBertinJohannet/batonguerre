//
// Created by pierre on 21/08/17.
//
#include "drawable_entity.h"

drawable_entity* drawable_entity_init(animation_frame* anim_frame, float* pos, int* facing, float size){
    drawable_entity* ent = malloc(sizeof(drawable_entity));
    ent->anim = anim_frame;
    ent->pos = pos;
    ent->facing = facing;
    ent->size = size;
    return ent;
}

void drawable_entity_animation_forward(drawable_entity* ent, float forward){
    ent->anim->frame+=forward;
    if (drawable_entity_get_frame(ent)==ent->anim->anim->nb_frames){
        ent->anim->frame = 0;
    }
}

int drawable_entity_get_frame(drawable_entity* ent){
    return (int)(ent->anim->frame);
}

void drawable_entity_destroy(drawable_entity* ent){
    animation_frame_destroy(ent->anim);
    free(ent);
}
