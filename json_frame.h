//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_JSON_FRAME_H
#define STICKWAR_JSON_FRAME_H

#include <SFML/Graphics/Rect.h>

#include <jansson.h>
#include "animation.h"
typedef struct animation animation;
json_t* read_elem(json_t* parent, char* elem, char* message, json_type desired);
json_t* read_index(json_t* parent, int index, char* message, json_type desired);
json_t* start_json(char* source);
void read_frames(char* source, animation* anim);


#endif //STICKWAR_JSON_FRAME_H
