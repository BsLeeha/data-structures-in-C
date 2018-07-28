#pragma once

#include <stdio.h>
#include "../headers/queue.h"
#include "../headers/print.h"

void queue_test(){
    printf("queue test:\n");

    int arr[] = {1, 2, 4, 3, 5};
    size_t len = sizeof(arr)/sizeof(arr[0]);

    Queue *queue = NULL;
    queue = queue_init(queue, NULL);
    for(size_t i = 0; i < len; ++i) queue_enqueue(queue, &arr[i]);
    for(size_t i = 0; i < len; ++i) {
        printf("%d ", *(int *)queue_peek(queue));
        queue_dequeue(queue, NULL);
    }    

    printf("\n\n");
}