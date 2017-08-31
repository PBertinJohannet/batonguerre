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
json_t* json_read_elem(json_t* parent, char* elem, char* message, json_type desired){
    json_t* found = json_object_get(parent, elem);
    if (found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}
json_t* json_read_index(json_t* parent, int index, char* message, json_type desired){
    json_t* found = json_array_get(parent, index);
    if (found != 0 && found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}


int json_read_int(json_t* parent, char* elem){
    char* error_message = malloc(sizeof(char)*(strlen("error reading ")+strlen(elem)));
    sprintf(error_message, "error reading %s",elem);
    int to_ret =  (int)json_integer_value(json_read_elem(parent, elem, error_message, JSON_INTEGER));
    return to_ret;
}
float json_read_float(json_t* parent, char* elem){
    char* error_message = malloc(sizeof(char)*(strlen("error reading ")+strlen(elem)));
    sprintf(error_message, "error reading %s",elem);
    float to_ret =  (float)json_real_value(json_read_elem(parent, elem, error_message, JSON_REAL));
    return to_ret;
}
char* json_read_string(json_t* parent, char* elem){
    char* error_message = malloc(sizeof(char)*(strlen("error reading ")+strlen(elem)));
    sprintf(error_message, "error reading %s",elem);
    char* to_ret =  (char*)json_string_value(json_read_elem(parent, elem, error_message, JSON_STRING));
    return to_ret;
}