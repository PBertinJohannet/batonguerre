//
// Created by pierre on 30/08/17.
//

#include "ai.h"
#include "dumb_ai.h"
#include "team.h"
#include "counted_allocations.h"
ai* get_ai_by_name(const char* name, team* t){
    ai* to_ret = counted_malloc(sizeof(ai), "init ai by name");
    if (strcmp(name, "dumb")==0){
        to_ret->play = dumb_ai_play;
        to_ret->ai = dumb_ai_init(t);
        return to_ret;
    } else {
        printf("error no ai with name : %s\n",name);
        exit(0);
    }
}