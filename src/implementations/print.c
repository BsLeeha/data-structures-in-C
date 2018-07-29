#include "../headers/print.h"

void int_print(const void *data){
    printf("%d ", *(int *)data);
}

void char_print(const void *data){
    printf("%c ", *(char *)data);
}

