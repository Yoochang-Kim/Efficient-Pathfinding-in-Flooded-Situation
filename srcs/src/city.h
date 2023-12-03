#pragma once
#include <stdbool.h>
#include "graph.h"

// to represent a current position
typedef struct position {
	int row;
	int column;
} Position;

int** create_city(int size);
void print_city(int** city, int size);
bool isValid(int x, int y, int size);
void create_graph_from_city_matrix(Graph* self, int** city, int size);
int** deep_copy_city_matrix(int** city, int size);
void leave_route_on_city(int** city, EdgeList route, int size);
void demolish_city(int** self, int size);
void demolish_route(EdgeList route);
void print_path(EdgeList route, int size);