#include "utils.h"
#include "counted_allocations.h"
char* string_concat(char* a, char* b){
    char* nouv = counted_malloc(sizeof(char)*(strlen(a)+strlen(b)), "concat string new");
    sprintf(nouv,"%s%s",a,b);
    counted_free(nouv, "strnig concat free ");
    return a;
}


json_t* start_json(char* source){
    json_t *json;
    json_error_t error;
    json = json_load_file(source, 0, &error);
    if (!json_is_object(json)){
        printf("error reading json for : %s\n",source);
        fprintf(stderr,"     on line %d: %s\n", error.line, error.text);
        json_decref(json);
    }
    return json;
}
json_t* json_read_elem(json_t* parent, char* elem, char* message, json_type desired){
    json_t* found = json_object_get(parent, elem);
    if (found==0 || found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}
json_t* json_read_index(json_t* parent, unsigned int index, char* message, json_type desired){
    json_t* found = json_array_get(parent, index);
    if (found == 0 || found->type!=desired){
        fprintf(stderr,"error at : %s\n",message);
        json_decref(found);
    }
    return found;
}


int json_read_int(json_t* parent, char* elem){
    char* error_message = counted_malloc(sizeof(char)*(strlen("error reading ")+strlen(elem)+1), "read int json");
    sprintf(error_message, "error reading %s",elem);
    int to_ret =  (int)json_integer_value(json_read_elem(parent, elem, error_message, JSON_INTEGER));
    counted_free(error_message, "freeing error message int read int json");
    return to_ret;
}
unsigned int json_read_uint(json_t* parent, char* elem){
    return (unsigned int)(json_read_int(parent, elem));
}
float json_read_float(json_t* parent, char* elem){
    char* error_message = counted_malloc(sizeof(char)*(strlen("error reading ")+strlen(elem)+1), "read float json");
    float to_ret =  (float)json_real_value(json_read_elem(parent, elem, error_message, JSON_REAL));
    counted_free(error_message, "freeing error message float read int json");
    return to_ret;
}
float json_read_float_index(json_t* parent, unsigned int elem, char* message){
    return (float)json_real_value(json_read_index(parent, elem, message, JSON_REAL));
}
const char* json_read_string(json_t* parent, char* elem){
    char* error_message = counted_malloc(sizeof(char)*(strlen("error reading ")+strlen(elem)+1), "read string json");
    sprintf(error_message, "error reading %s",elem);
    const char* to_ret =  json_string_value(json_read_elem(parent, elem, error_message, JSON_STRING));
    counted_free(error_message, "freeing error message string read int json");
    return to_ret;
}
