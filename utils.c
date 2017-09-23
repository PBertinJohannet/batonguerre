//
// Created by pierre on 22/09/17.
//
#include "stdlib.h"
#include "string.h"
#include "counted_allocations.h"
void copy_json_to(char* path1, char* path2){
#ifdef _WIN32
    char* sys_com = "xcopy  ";
#endif
#ifdef __linux__
    char* sys_com = "cp  ";
#endif
    char* command = counted_malloc(sizeof(char)*(strlen(path1)+strlen(path2)+strlen(sys_com)+1),// +1 for null term
                                   "malloc for copy command");
    sprintf(command, "cp %s %s", path1, path2);
    system(command);
    counted_free(command, "freeing command from copy_to");
}

char* int_to_str(int to_conv){
    int len = snprintf(NULL, 0, "%d", to_conv);
    char* to_ret = counted_malloc(sizeof(char)*(len+1), "int to str to back");
    snprintf(to_ret, len+1, "%d", to_conv);
    return to_ret;
}
