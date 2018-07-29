#pragma once

#include <stdio.h>
#include "list.h"

// implement stacks as linked lists
typedef List Stack;

// public interface
#define stack_init    list_init

#define stack_destory list_destory

int     stack_push(Stack *stack, const void *data);

int     stack_pop(Stack *stack, void **data);

#define stack_peek(stack) (((stack)->head == NULL) ? NULL : (stack)->head->data)

#define stack_size    list_size

