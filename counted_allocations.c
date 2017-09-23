//
// Created by pierre on 02/09/17.
//

#include "counted_allocations.h"
#include "stdlib.h"
int allocateds_inited = 0;
list* allocateds;



allocation* allocation_init(size_t size, void* pointer, const char* message){
    allocation* all = malloc(sizeof(allocation));
    all->size = size;
    all->pointer = pointer;
    all->message = message;
    return all;
}
void allocation_show(allocation* all){
    printf("allocated memory of size : %zu\n", all->size);
    printf("    %s\nat %p\n", all->message, all->pointer);
}
int allocation_destroy(allocation* all){
    free(all);
    return 1;
}
void* counted_malloc(size_t size, const char* message){
    void* to_ret;
    if (!allocateds_inited){
        allocateds = list_init();
        allocateds_inited = 1;
    }
    to_ret = malloc(size);
    list_add(allocateds, allocation_init(size, to_ret, message));
    return to_ret;
}
int counted_free_check(void* to_free, const char* message){
    char* error_mes = "error on list allocation";
    if (to_free != NULL) {
        for (unsigned int i = 0; i < allocateds->size; i++) {
            allocation *all = list_at(allocateds, i);
            if (to_free == all->pointer) {
                return i;
            }
        }
        error_mes = "pointer not found";
    } else {
        error_mes = "pointer is null";
    }
    printf("error on counted_free :\n    with message : %s\n    at : %s\n        exiting\n", error_mes, message);
    counted_show_allocateds();
    exit(0);
}
void counted_free(void* to_free, const char* message){
    int to_free_id = counted_free_check(to_free, message);
    allocation *all = list_at(allocateds, to_free_id);
    list_rm_at(allocateds, to_free_id);
    free(all->pointer);
    all->pointer = 0;
}
void counted_show_allocateds(){
    printf("%u still allocated : \n", allocateds->size);
    printf("allocations are : \n");
    for (unsigned int i=0; i<allocateds->size;i++){
        allocation* all = list_at(allocateds, i);
        allocation_show(all);
    }
}

sfText* sfText_counted_malloc(char* message){
    sfText* to_ret;
    if (!allocateds_inited){
        allocateds = list_init();
        allocateds_inited = 1;
    }
    to_ret = sfText_create();
    list_add(allocateds, allocation_init(0, to_ret, message));
    return to_ret;
}
void sfText_counted_free(sfText* text, char* message){
    int to_free_id = counted_free_check(text, message);
    allocation *all = list_at(allocateds, to_free_id);
    list_rm_at(allocateds, to_free_id);
    sfText_destroy(all->pointer);
    all->pointer = 0;
}
sfSprite* sfSprite_counted_malloc(char* message){
    sfSprite* to_ret;
    if (!allocateds_inited){
        allocateds = list_init();
        allocateds_inited = 1;
    }
    to_ret = sfSprite_create();
    list_add(allocateds, allocation_init(0, to_ret, message));
    return to_ret;
}
void sfSprite_counted_free(sfSprite* sprite,  char* message){
    int to_free_id = counted_free_check(sprite, message);
    allocation *all = list_at(allocateds, to_free_id);
    list_rm_at(allocateds, to_free_id);
    sfSprite_destroy(all->pointer);
    all->pointer = 0;
}
