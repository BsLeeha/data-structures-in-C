#include "../headers/graph.h"

bool graph_match(const void *key1, const void *key2){
    return ((AdjList *)key1)->vertex == ((AdjList *)key2)->vertex;
}

void graph_test(){
    int arr[] = {1, 2, 3, 4, 5};
    int len = sizeof arr / sizeof arr[0];
    Graph graph;
    graph_init(&graph, NULL, graph_match);
    for(size_t i = 0; i < len; ++i){
        graph_ins_vertex(&graph, &arr[i]);
    }

}

