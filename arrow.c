//
// Created by pierre on 24/08/17.
//
#include "arrow.h"
#include "entity.h"
#include "window_conf_reader.h"
#include "counted_allocations.h"
projectile* arrow_create(int pos,unsigned int range, unsigned int speed, float size, team* team, unsigned int facing, int damage){
    arrow* arr = counted_malloc(sizeof(arrow), "create arrow");
    projectile* proj = projectile_create(pos, team, facing);
    arr->damage = damage;
    arr->speed = speed;
    arr->lifetime = range*get_window_config()->fps/speed + get_window_config()->fps;
    arr->parent = proj;
    proj->drawable = drawable_entity_init(animation_frame_init(animation_init("arrow")),&proj->pos, &proj->facing,size);
    proj->play = arrow_projectile_play;
    proj->self = arr;
    proj->facing = facing;
    proj->destroy = arrow_projectile_destroy;
    return proj;
}


int arrow_projectile_play(void* proj, list* entities){
    projectile* pj = proj;
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
    pj->pos-=(2*pj->facing-1)*p_arr->speed/(get_window_config()->fps);
    p_arr->lifetime--;
    if (p_arr->lifetime<1){
        return 1;
    }
    return 0;
}

int arrow_projectile_destroy(projectile* proj){
    projectile* pj = proj;
    arrow* p_arr = pj->self;
    drawable_entity_destroy(pj->drawable);
    counted_free(p_arr, "freeing arrow");
    counted_free(proj, "freeing projectile containing arrow");
    return 0;
}