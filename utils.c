#include "utils.h"

char* string_concat(char* a, char* b){
    char* nouv = malloc(sizeof(char)*(strlen(a)+strlen(b)));
    sprintf(nouv,"%s%s",a,b);
    return a;
}