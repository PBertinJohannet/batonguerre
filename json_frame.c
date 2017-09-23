//
// Created by pierre on 21/08/17.
//

#include "json_frame.h"
#include "parson.h"
#include "counted_allocations.h"
void read_frames(char* source, animation* anim){
    JSON_Object* json = json_value_get_object(json_parse_file(source));
    JSON_Array* frames  = json_object_get_array(json,"frames");
    anim->nb_frames = (unsigned int)json_array_get_count(frames);
    anim->frames = counted_malloc((size_t)(anim->nb_frames)*(sizeof(sfIntRect)), "create animation frames ");
    for(unsigned int i = 0; i < anim->nb_frames; i++)
    {
        JSON_Object* elem = json_array_get_object(frames,i);
        JSON_Object* frame_coord = json_object_get_object(elem,"frame");
        anim->frames[i].left  = (int)json_object_get_number(frame_coord,"x");
        anim->frames[i].top = (int)json_object_get_number(frame_coord,"y");
        anim->frames[i].width = (int)json_object_get_number(frame_coord,"w");
        anim->frames[i].height = (int)json_object_get_number(frame_coord,"h");
    }
}
