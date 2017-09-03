//
// Created by pierre on 30/08/17.
//

#ifndef STICKWAR_AI_H
#define STICKWAR_AI_H

#include "game.h"
#include "team.h"
typedef struct team team;
typedef struct game game;
typedef struct ai ai;
struct ai {
    void (*play)(ai*,game*);
    void* ai;
};

ai* get_ai_by_name(const char* name, team* t);

#endif //STICKWAR_AI_H
