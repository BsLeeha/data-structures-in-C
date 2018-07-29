#include "../headers/graph.h"
#include <stdlib.h>
#include <string.h>

Graph *graph_init(Graph *graph, void (*destory_data)(void *data),
                                bool (*match)(const void *key1, const void *key2)){
    if(graph == NULL){
        if((graph == malloc(sizeof *graph)) == NULL) return NULL;
        graph->destory_graph = free;
    }else graph->destory_graph = NULL;

    graph->vertices     = 0;
    graph->edges        = 0;
    graph->destory_data = destory_data;
    graph->match        = match;

    graph->vlist = list_init(graph->vlist, NULL);

    return graph;
}

int graph_destory(Graph *graph);

ListNode *find_vertex(Graph *graph, const void *vertex){
    ListNode *node = NULL;
    for(node = graph->vlist->head; node != NULL; node=node->next)
        if(graph->match(node->data, (const AdjList *)vertex)) return node;
    return NULL;
}

int graph_ins_vertex(Graph *graph, const void *vertex){
    if(graph == NULL) return -1;

    AdjList *adjlist = NULL;
    ListNode *node = NULL;

    // check unique
    if(find_vertex(graph, vertex)) return -1;

    // new adjlist
    if((adjlist = malloc(sizeof *adjlist)) == NULL) return -1;
    adjlist->vertex = vertex;
    if((adjlist->endpoints = set_init(adjlist->endpoints, graph->match, graph->destory_data)) == NULL) 
        return -1;

    list_append(graph->vlist, adjlist);
    ++(graph->vertices);
    return 0;
}

int graph_ins_edge(Graph *graph, const void *vertex, const void *endpoint){
    if(graph == NULL) return -1;
    ListNode *node    = NULL;
    AdjList  *adjlist = NULL;

    if((node = find_vertex(graph, vertex)) == NULL){
        if(graph_ins_vertex(graph, vertex) == -1) return -1;        
        node = graph->vlist->tail;
    }

    adjlist = (AdjList *)node->data;

    set_insert(adjlist->endpoints, endpoint);

    ++(graph->edges);
    return 0;
}

int graph_rem_vertex(Graph *graph, void *vertex){
    if(graph == NULL) return -1;
    ListNode *prev    = NULL;
    ListNode *node    = NULL;
    AdjList  *adjlist = NULL;

    for(node = graph->vlist->head; node != NULL; node = prev->next){
        adjlist = (AdjList *)node->data;
        if(graph->match(adjlist->vertex, vertex)) {
            list_rem_next(graph->vlist, node, NULL);
            break;
        }else if(set_is_member(adjlist->endpoints, vertex)){
            set_remove(adjlist->endpoints, vertex, NULL);
            --(graph->edges);
        }
        prev = node;
    }

    --(graph->vertices);
    return 0;
}

int graph_rem_edge(Graph *graph, const void *vertex, const void *endpoint){
    if(graph == NULL) return -1;
    ListNode *node    = NULL;
    AdjList  *adjlist = NULL;

    if((node = find_vertex(graph, vertex)) == NULL) return -1;
    adjlist = (AdjList *)node->data;

    set_remove(adjlist->endpoints, endpoint, NULL);
    --(graph->edges);
    return 0;
}