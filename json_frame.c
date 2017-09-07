//
// Created by pierre on 21/08/17.
//

#include "json_frame.h"
#include "utils.h"
#include "counted_allocations.h"
void read_frames(char* source, animation* anim){
    json_t* json = start_json(source);
    json_t* frames  = json_read_elem(json,"frames","reading frames array",JSON_ARRAY);
    anim->nb_frames = (unsigned int)json_array_size(frames);
    anim->frames = counted_malloc((size_t)(anim->nb_frames)*(sizeof(sfIntRect)), "create animation frames ");
    for(unsigned int i = 0; i < anim->nb_frames; i++)
    {
        json_t* elem = json_read_index(frames,i,"reading index ",JSON_OBJECT);
        json_t* frame_coord = json_read_elem(elem,"frame", "reading inner frame",JSON_OBJECT);
        anim->frames[i].left  = json_read_int(frame_coord,"x");
        anim->frames[i].top = json_read_int(frame_coord,"y");
        anim->frames[i].width = json_read_int(frame_coord,"w");
        anim->frames[i].height = json_read_int(frame_coord,"h");
    }
}
