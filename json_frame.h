//
// Created by pierre on 21/08/17.
//

#ifndef STICKWAR_JSON_FRAME_H
#define STICKWAR_JSON_FRAME_H

#include <SFML/Graphics/Rect.h>

#include "animation.h"

typedef struct animation animation;
void read_frames(char* source, animation* anim);


#endif //STICKWAR_JSON_FRAME_H
