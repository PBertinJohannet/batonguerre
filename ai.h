//
// Created by pierre on 30/08/17.
//

#ifndef STICKWAR_AI_H
#define STICKWAR_AI_H

#include "game_state.h"
#include "team.h"
typedef struct team team;
typedef struct battle battle;
typedef struct ai ai;
struct ai {
    void (*play)(ai*,battle*);
    void* ai;
    void (*destroy)(void*);
};

ai* get_ai_by_name(const char* name, team* t);
void ai_destroy(ai*);
#endif //STICKWAR_AI_H
