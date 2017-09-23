//
// Created by pierre on 24/08/17.
//
#include "arrow.h"
#include "entity.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
#include "global.h"
#include "math.h"
object* arrow_init(int pos,unsigned int range, unsigned int speed, float size, team* team, unsigned int facing, int damage){
    arrow* arr = counted_malloc(sizeof(arrow), "create arrow");
    object* obj = object_init(pos, team, facing, OBJECT_ARROW);
    arr->damage = damage;
    arr->speed = speed;
    arr->lifetime = range*get_window_config()->fps/speed;
    arr->parent = obj;
    obj->drawable = drawable_entity_init(animation_frame_init(get_animations()->arrow),&obj->pos, &obj->facing,size);
    obj->play = arrow_object_play;
    obj->self = arr;
    obj->facing = facing;
    obj->destroy = arrow_object_destroy;
    return obj;
}


int arrow_object_play(void* obj, list* entities){
    object* pj = obj;
    arrow* p_arr = pj->self;
    for (unsigned int i = 0;i<entities->size;i++){
        entity* ent = list_at(entities,i);
        if (ent->team != pj->team
                && ent->hp>0
                && abs(ent->pos - pj->pos) < 20){
                ent->type->take_damage(ent,p_arr->damage);
                return 1;
        }
    }
    pj->pos-=(2*(int)pj->facing-1)*(float)p_arr->speed/(float)(get_window_config()->fps);
    p_arr->lifetime--;
    if (p_arr->lifetime<1){
        return 1;
    }
    return 0;
}

void arrow_object_destroy(object* obj){
    counted_free(obj->self, "freeing arrow");
}