#pragma once
#include <stdbool.h>
#include "openList.h"

typedef struct edge {
    int to_vertex;
    int weight;
} Edge;

typedef struct edgeNode {
    Edge edge;
    struct edgeNode* next;
} *EdgeNodePtr;

typedef struct edgeList {
    EdgeNodePtr head;
} EdgeList;

typedef struct graph {
    int V;
    EdgeList* edges;
} Graph;

Graph create_graph(int v);
EdgeList route_finder_option_dijkstra(Graph* self, int source, int goal, int* totalDistance);
EdgeList route_finder_option_astar(Graph* self, int** zz, int source, int goal, int size, int* totalDistance);
void Dijkstra_solution(Graph* self, int initial_vertex, int* distance, int* previous);
int find_min_vertex(Graph* self, int* distance, bool* set);
void astar_solution(Graph* self, int** city, int start, int goal, int size, int* distance, int* predecessor);
int menhattan_distance(int vertex, int size);
void add_edge(Graph* self, int weight, int fromV, int toV);
void crush_graph(Graph* self);
EdgeList test_create_Edge_list();
EdgeList test_reverse_Edge_list(EdgeList* self);
void test_insert_route_at_front(EdgeList* self, int data);
void test_print_solution(Graph* self, int startVertex, int* distance, int* previous);
void test_print_path(int terminalVertex, int* predecessor);