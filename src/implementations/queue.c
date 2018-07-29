#include "../headers/queue.h"

int queue_enqueue(Queue *queue, const void *data){
    list_ins_next(queue, list_tail(queue), data);
}

int queue_dequeue(Queue *queue, void **data){
    list_rem_next(queue, NULL, data);
}