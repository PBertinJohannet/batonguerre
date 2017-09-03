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
        allocateds = list_create();
        allocateds_inited = 1;
    }
    to_ret = malloc(size);
    list_add(allocateds, allocation_init(size, to_ret, message));
    return to_ret;
}

int counted_free(void* to_free, const char* message){
    int error = 1;
    if (to_free != NULL) {
        for (unsigned int i = 0; i < allocateds->size; i++) {
            allocation *all = list_at(allocateds, i);
            if (to_free == all->pointer) {
                //printf("freeing : %s\n", message);
                list_rm_at(allocateds, i);
                free(to_free);
                error = 0;
                break;
            }
        }
    }
    if (error) {
        printf("error on counted_free :\n    message : %s\n        exiting\n", message);
        int wait = 0;
        while (!wait){
            if (scanf("%d",&wait)){
                printf("pls error gut");
            }
        }
        counted_show_allocateds();
        exit(0);
    } else {
        return 1;
    }
}
void counted_show_allocateds(){
    printf("allocations are : \n");
    int next;
    for (unsigned int i=0; i<allocateds->size;i++){
        allocation* all = list_at(allocateds, i);
        next = scanf("next : %d\n", &next);
        allocation_show(all);
    }
}