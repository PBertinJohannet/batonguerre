//
// Created by pierre on 30/08/17.
//

#include "ai.h"
#include "final_ai.h"
#include "dumb_ai.h"
#include "team.h"
#include "counted_allocations.h"
#include "stdlib.h"
ai* get_ai_by_name(const char* name, team* t){
    ai* to_ret = counted_malloc(sizeof(ai), "init ai by name");
    if (strcmp(name, "dumb")==0){
        to_ret->play = dumb_ai_play;
        to_ret->destroy = (void(*)(void*))dumb_ai_destroy;
        to_ret->ai = dumb_ai_init(t);
        return to_ret;
    } else if (strcmp(name, "final")==0){
        to_ret->play = final_ai_play;
        to_ret->destroy = (void(*)(void*))final_ai_destroy;
        to_ret->ai = final_ai_init(t);
        return to_ret;
    }{
        printf("error no ai with name : %s\n",name);
        exit(0);
    }
}
void ai_destroy(ai* a){
    a->destroy(a->ai);
    counted_free(a, "destroying ai");
}