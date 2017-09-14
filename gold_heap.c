//
// Created by pierre on 10/09/17.
//
#include "gold_heap.h"

object* gold_heap_create(int pos, int gold, float size){
    gold_heap* heap = counted_malloc(sizeof(gold_heap), "creating gold heap struct");
    object* obj = object_create(pos, NULL, 0, OBJECT_GOLD_HEAP);
    heap->gold_current = gold;
    heap->gold_start = gold;
    heap->parent = obj;
    obj->self = heap;
    obj->drawable = drawable_entity_init(animation_frame_init(get_animations()->gold_heap),&obj->pos, &obj->facing,size);
    obj->play = gold_heap_play;
    obj->destroy = gold_heap_destroy;
    obj->facing = 0;
    return obj;
}



int gold_heap_play(void* obj, __attribute__ ((unused)) list* entities){
    object* pj = obj;
    gold_heap* heap = pj->self;
    heap->parent->drawable->anim->frame = (float)heap->parent->drawable->anim->anim->nb_frames-(
                                            (float)heap->parent->drawable->anim->anim->nb_frames
                                          *(float)heap->gold_current/(float)heap->gold_start);
    if (heap->gold_current<1){
        return 1;
    } else return 0;
}
int gold_heap_destroy(object* obj){
    return counted_free(obj, "freeing gold heap object");
}