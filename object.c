//
// Created by pierre on 24/08/17.
//
#include "object.h"
#include "counted_allocations.h"
object* object_init(int pos, team* team, unsigned int facing, int type){
    object* proj = counted_malloc(sizeof(object), "creating object ");
    proj->object_type = type;
    proj->team = team;
    proj->pos = pos;
    proj->facing = facing;
    return proj;
}


void object_destroy(object* obj){
    drawable_entity_destroy(obj->drawable);
    obj->destroy(obj);
    counted_free(obj, "freeing object");
}