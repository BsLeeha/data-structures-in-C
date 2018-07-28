#pragma once

#include <stdio.h>
#include "../headers/stack.h"
#include "../headers/print.h"

void stack_test(){
    printf("stack test:\n");

    int arr[] = {1, 2, 4, 3, 5};
    size_t len = sizeof(arr)/sizeof(arr[0]);    
    Stack *stack = NULL;
    stack = stack_init(stack, NULL);
    for(size_t i = 0; i < len; ++i) stack_push(stack, &arr[i]);
    for(size_t i = 0; i < len; ++i) {
        printf("%d ", *(int *)stack_peek(stack));
        stack_pop(stack, NULL);
    }    

    printf("\n\n");
}