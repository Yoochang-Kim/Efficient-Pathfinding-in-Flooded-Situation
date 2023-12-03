#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "city.h"

#define MAP_TYPE_HOUSE 2
#define MAP_TYPE_WALL 3
#define MAP_TYPE_ROAD 4
#define MAP_TYPE_WATER 5
#define ROUTE 6
#define GOAL 7
#define INFINITVE 9999

/// <summary>
/// create the type of objects and end point on the city
/// </summary>
/// <param name="size">city size</param>
/// <returns>city matrix</returns>
int** create_city(int size) {

    int** city = malloc(sizeof(int*) * (size));
    int ObjectNum = size;
    int waterNum = size + 100;
    int i, j;
    int flowdy;

    for (i = 0; i < size; i++) {
        city[i] = (int*)malloc(size * sizeof(int));
    }

    // create water
    for (i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            city[i][j] = MAP_TYPE_ROAD;
        }
    }

    // create building, wall
    srand(time(NULL));
    for (int z = 0; z < ObjectNum; z++) {
        int bx = rand() % (size - 1) + 1;
        int by = rand() % (size - 2) + 2;
        int wx = rand() % (size - 1) + 1;
        int wy = rand() % (size - 2) + 2;

        city[bx][by] = MAP_TYPE_HOUSE;
        city[wx][wy] = MAP_TYPE_WALL;
    }

    // create water
    for (int i = 0; i < waterNum; i++) {
        int rx = rand() % (size - 3) + 2;
        int ry = rand() % (size - 3) + 2;
        city[rx][ry] = MAP_TYPE_WATER;
    }

    city[0][size - 1] = MAP_TYPE_HOUSE;
    city[0][size - 2] = MAP_TYPE_WATER;
    // end point
    city[size - 1][size - 1] = GOAL;
    return city;
}

/// <summary>
/// deep copy from city matrix
/// </summary>
/// <param name="city">city matrix</param>
/// <param name="size">city size</param>
/// <returns>copied city</returns>
int** deep_copy_city_matrix(int** city, int size) {

    int** copy = malloc(size * sizeof * copy);
    for (int i = 0; i < size; i++)
        copy[i] = (int*)malloc(size * sizeof(int));

    // deep copy
    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            copy[i][j] = city[i][j];

        }
    }
    return copy;
}

/// <summary>
/// print the city map based on the type of the object
/// </summary>
/// <param name="city">city matrix</param>
/// <param name="size">city size</param>
void print_city(int** city, int size) {

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            // print object
            switch (city[i][j]) {

                // For final route
            case ROUTE:
                printf("¡Ú");
                break;

                // For water
            case MAP_TYPE_WATER:
                printf("~ ");
                break;

                // For house
            case MAP_TYPE_HOUSE:
                printf("H ");
                break;

                // For wall
            case MAP_TYPE_WALL:
                printf("w ");
                break;

                // For road
            default:
                printf("- ");
            }
        }
        printf("\n");
    }
}

/// <summary>
/// print the route on the console
/// </summary>
/// <param name="route"></param>
/// <param name="size"></param>
void print_path(EdgeList route, int size) {

    EdgeNodePtr currentNode = route.head;

    while (currentNode != NULL) {

        int route = currentNode->edge.to_vertex;
        int routeX = route / size;
        int routeY = route % size;

        printf("(%d,%d)", routeX, routeY);
        currentNode = currentNode->next;

        if (currentNode != NULL)
            printf("->");
    }
    printf("\n");
}

/// <summary>
/// create a graph from the 2d array as an adjacency list 
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
/// <param name="city">city matrix</param>
/// <param name="size">city size</param>
void create_graph_from_city_matrix(Graph* self, int** city, int size) {

    // for all vertices
    for (int current = 0; current < size * size; current++) {

        // Current vertex row, colum
        int currentX = current / size;
        int currentY = current % size;

        // Only move to up,down, east,west to find neighbour
        int neighbours[4];
        int step = 0;
        for (int i = 0; i < 4; i++)
            neighbours[i] = 0;

        // find near neighbours from a vertex
        // go down but not below the city bottom boundary
        if (currentX != size - 1) {
            neighbours[step] = current + size;
            step++;
        }

        // go left but not above the left side of city boundary
        if (currentY != 0) {
            neighbours[step] = current - 1;
            step++;
        }
        // go right but not above the right side of city boundary
        if (currentY != size - 1) {
            neighbours[step] = current + 1;
            step++;
        }
        // go up but not above the city top boundary
        if (currentX != 0) {
            neighbours[step] = current - size;
            step++;
        }

        // For neighbours found(up,down,left or right)
        for (int t = 0; t < step; t++) {
            int neighbour = neighbours[t];
            int neighbourX = neighbour / size;
            int neighbourY = neighbour % size;
            int distance = neighbour - current;
            int weight = 1;

            // neighbour is not out of bound
            if (isValid(neighbourX, neighbourY, size)) {

                // Give a weight to the object
                switch (city[neighbourX][neighbourY]) {
                    // For road
                case MAP_TYPE_ROAD:
                    weight = road_cost(city[neighbourX][neighbourY] -
                        city[currentX][currentY]);
                    break;

                    // For water
                case MAP_TYPE_WATER:
                    weight = water_cost(city[neighbourX][neighbourY] -
                        city[currentX][currentY]);
                    break;

                    // For house
                case MAP_TYPE_HOUSE:
                    weight = INFINITVE;
                    break;
                    // For wall
                case MAP_TYPE_WALL:
                    weight = INFINITVE;
                    break;
                }
                // add wight to edge between the current vertex and neighbour
                add_edge(self, weight, current, neighbour);
            }
        }
    }
}
/// <summary>
/// Give a high cost for water hole
/// </summary>
/// <param name="value">given value</param>
/// <returns>generated cost</returns>
int water_cost(int value) {

    int weight = 30;

    if (value > 0)
        weight += (value * value);

    return weight;
}

/// <summary>
/// Give a low cost for road
/// </summary>
/// <param name="value">given value</param>
/// <returns>generated cost</returns>
int road_cost(int value) {

    int weight = 1;

    if (value > 0)
        weight += (value * value);

    return weight;
}

/// <summary>
/// check the Given x, y is out of bound
/// </summary>
/// <param name="x">position x</param>
/// <param name="y">position y</param>
/// <param name="size">city size</param>
/// <returns></returns>
bool isValid(int x, int y, int size) {
    return (x >= 0 && x < size&& y >= 0 && y < size);
}

/// <summary>
/// Leave route on city matrix
/// </summary>
/// <param name="city">city matrix</param>
/// <param name="route">foot prints</param>
/// <param name="size">city size</param>
void leave_route_on_city(int** city, EdgeList route, int size) {
    EdgeNodePtr currentNode = route.head;
    while (currentNode != NULL) {
        int footprint = currentNode->edge.to_vertex;
        int footprintRow = footprint / size;
        int footprintColumn = footprint % size;

        city[footprintRow][footprintColumn] = ROUTE;
        currentNode = currentNode->next;
    }
}

/// <summary>
/// Remove city matrix
/// </summary>
/// <param name="self">city matrix</param>
/// <param name="size">city size</param>
void demolish_city(int** self, int size) {
    for (int v = 0; v < size; v++) {
        free(self[v]);
    }
    free(self);
}

/// <summary>
/// Remove route
/// </summary>
/// <param name="route">route</param>
void demolish_route(EdgeList route) {
    EdgeNodePtr currentNode = route.head;
    while (currentNode != NULL) {
        EdgeNodePtr freeNode = currentNode;
        currentNode = currentNode->next;
        free(freeNode);
    }
}