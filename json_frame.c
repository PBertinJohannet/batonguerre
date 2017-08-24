//
// Created by pierre on 21/08/17.
//

#include "json_frame.h"

void read_frames(char* source, animation* anim){
    json_t* json = start_json(source);
    json_t* frames  = read_elem(json,"frames","reading frames array",JSON_ARRAY);
    anim->nb_frames = json_array_size(frames);
    anim->frames = malloc(anim->nb_frames*sizeof(sfIntRect));
    for(int i = 0; i < anim->nb_frames; i++)
    {
        json_t* elem = read_index(frames,i,"reading index ",JSON_OBJECT);
        json_t* frame_coord = read_elem(elem,"frame", "reading inner frame",JSON_OBJECT);
        anim->frames[i].left  = (int)json_integer_value(read_elem(frame_coord,"x","reading coord x",JSON_INTEGER));
        anim->frames[i].top = (int)json_integer_value(read_elem(frame_coord,"y","reading coord y",JSON_INTEGER));
        anim->frames[i].width = (int)json_integer_value(read_elem(frame_coord,"w","reading coord w",JSON_INTEGER));
        anim->frames[i].height = (int)json_integer_value(read_elem(frame_coord,"h","reading coord h",JSON_INTEGER));
    }
}

json_t* start_json(char* source){
    json_t *json;
    json_error_t error;
    json = json_load_file(source, 0, &error);
    if (!json_is_object(json)){
        printf("error reading json for : %s\n",source);
        json_decref(json);
    }
    return json;
}
json_t* read_elem(json_t* parent, char* elem, char* message, json_type desired){
    json_t* found = json_object_get(parent, elem);
    if (found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}
json_t* read_index(json_t* parent, int index, char* message, json_type desired){
    json_t* found = json_array_get(parent, index);
    if (found != 0 && found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}