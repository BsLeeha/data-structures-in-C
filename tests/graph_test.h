#include "../headers/graph.h"

bool match(AdjList *key1, AdjList *key2){
    return key1->vertex == key2->vertex;
}

void graph_test(){
    int arr[] = {1, 2, 3, 4, 5};
    Graph graph;
    graph_init(&graph, NULL)
}