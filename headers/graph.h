#pragma once

#include "list.h"
#include "set.h"
#include <stdio.h>

// the data type of each node of the glist
typedef struct{
    void  *vertex;           
    Set   *endpoints;       // endpoints or adjencies of vertex
}AdjList;      

typedef enum{false, true} bool;

typedef struct{
    int  vertices;
    int  edges;

    void (*destory_graph)(void *graph);
    void (*destory_data)(void *data);
    bool (*match)(const void *key1, const void *key2);

    List *vlist;           // list of vertices(AdjList type)
}Graph;

typedef enum{white, graph, black} VertexColor;

Graph *graph_init(Graph *graph, void (*destory_data)(void *data),
                                bool (*match)(const void *key1, const void *key2));

int graph_destory(Graph *graph);

int graph_ins_vertex(Graph *graph, const void *vertex);

int graph_ins_edge(Graph *graph, const void *vertex, const void *endpoint);

int graph_rem_vertex(Graph *graph, void *data);

int graph_rem_edge(Graph *graph, const void *data1, const void *data2);




