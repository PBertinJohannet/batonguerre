#include "utils.h"

char* string_concat(char* a, char* b){
    char* nouv = malloc(sizeof(char)*(strlen(a)+strlen(b)));
    sprintf(nouv,"%s%s",a,b);
    return a;
}


json_t* start_json(char* source){
    json_t *json;
    json_error_t error;
    json = json_load_file(source, 0, &error);
    if (!json_is_object(json)){
        printf("error reading json for : %s\n",source);
        json_decref(json);
    }
    return json;
}
json_t* read_elem(json_t* parent, char* elem, char* message, json_type desired){
    json_t* found = json_object_get(parent, elem);
    if (found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}
json_t* read_index(json_t* parent, int index, char* message, json_type desired){
    json_t* found = json_array_get(parent, index);
    if (found != 0 && found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}
