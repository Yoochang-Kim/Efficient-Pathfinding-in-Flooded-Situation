#include <iso646.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "openList.h"

#define MAP_TYPE_HOUSE 2
#define MAP_TYPE_WALL 3
#define MAP_TYPE_ROAD 4
#define ROUTE 6
#define GOAL 7
#define INFINITVE 9999

/// <summary>
/// initialise graph to make a new Graph instance
/// </summary>
/// <param name="v">the number of vertices</param>
/// <returns>new graph</returns>
Graph create_graph(int v) {
    Graph new_graph;

    new_graph.V = v;
    new_graph.edges = malloc(new_graph.V * sizeof * new_graph.edges);

    int vertex = 0;
    for (vertex; vertex < new_graph.V; vertex++) {
        new_graph.edges[vertex].head = NULL;
    }

    return new_graph;
}

/// <summary>
/// Find the shortest path from the given graph with dijstra solution
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
/// <param name="source">source vertex</param>
/// <param name="goal">destination</param>
/// <returns>List that contains the shortest path</returns>
EdgeList route_finder_option_dijkstra(Graph* self, int source, int goal,
    int* totalDistance) {
    int* distance = malloc(sizeof * distance * self->V);
    int* predecessor = malloc(sizeof * distance * self->V);
    int target = goal;

    /*
    //Test the computational performance
    long n;
    clock_t start = clock();
    */

    // get solution
    Dijkstra_solution(self, source, distance, predecessor);
    *totalDistance = distance[target];

    /*
    //Test the computational performance
    clock_t diff = clock() - start;
    long msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Operation took %d milliseconds\n\n", msec);
    */

    // save the route from dijstra finder
    EdgeList route;
    route.head = NULL;
    // traverse will be end when the target vertex's value is -1
    // because the parent of the root(== source vertex) is -1 or the case where
    // source node can not raech the destination
    while (target != -1) {
        EdgeNodePtr new_node = malloc(sizeof * new_node);
        new_node->edge.to_vertex = target;
        new_node->edge.weight = 1;

        // add each vertex imformation at the beggining of the list
        new_node->next = route.head;
        route.head = new_node;
        target = predecessor[target]; // traverse from target to source vertex
    }

    free(distance);
    free(predecessor);
    return route;
}

/// <summary>
/// path finder to reach the destination with asatr solution
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
/// <param name="city">city matrix</param>
/// <param name="source">start vertex</param>
/// <param name="goal">terminal vertex</param>
/// <param name="size">city size</param>
/// <param name="totalDistance">the set of distance from vertex to
/// destination</param> <returns></returns>
EdgeList route_finder_option_astar(Graph* self, int** city, int source,
    int goal, int size, int* totalDistance) {
    int* distance = malloc(sizeof * distance * self->V);
    int* predecessor = malloc(sizeof * predecessor * self->V);
    int target = goal;

    /*
    //Test the computational performance
    long n;
    clock_t start = clock();
    */

    astar_solution(self, city, source, goal, size, distance, predecessor);
    *totalDistance = distance[target];

    /*
    //Test the computational performance
    clock_t diff = clock() - start;
    long msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Operation took %d milliseconds\n\n", msec);
    */

    // save the route from astar algorithm
    EdgeList route;
    route.head = NULL;

    // traverse will be end when the target vertex's value is -1
    // because the parent of the root(== source vertex) is -1 or source node can
    // not raech the destination
    while (target != -1) {
        EdgeNodePtr new_node = malloc(sizeof * new_node);
        new_node->edge.to_vertex = target;
        new_node->edge.weight = 1;

        // add each vertex imformation at the beggining of the list
        new_node->next = route.head;
        route.head = new_node;
        // traverse from target to source vertex
        target = predecessor[target];
    }
    free(distance);
    free(predecessor);
    return route;
}
/// <summary>
/// dijkstra algorithm to get distances, predecessor list between source vertex
/// and other vertices
/// </summary>
/// <param name="self">city graph</param>
/// <param name="src">initial vertex</param>
/// <param name="distance">the set of distances from vertex to
/// destination</param> <param name="predecessor">predecessor array</param>
void Dijkstra_solution(Graph* self, int src, int* distance, int* predecessor) {
    bool* explored = malloc(sizeof(int) * self->V);

    // initialise all the vertexes
    for (int v = 0; v < self->V; v++) {
        distance[v] = INFINITVE;
        predecessor[v] = -1;
        explored[v] = false;
    }

    // initialise source vertex
    distance[src] = 0;

    // for all vertices
    for (int count = 0; count < self->V; count++) {
        // Search the vertex containing the shortest path from source vertex
        int currentVertex = find_min_vertex(self, distance, explored);

        // building or wall found
        if (currentVertex == INFINITVE)
            continue; // skip to next vertex
        else {

            // vertex is explored
            explored[currentVertex] = true;

            // make pair with neighbor vertixes
            EdgeNodePtr current = self->edges[currentVertex].head;
            while (current != NULL) {
                int neighbor = current->edge.to_vertex;
                int neighborWeight = current->edge.weight;
                int tentative = distance[currentVertex] + neighborWeight;
                // neighbor is not explored and the new path is shorter
                if (explored[neighbor] == false && tentative < distance[neighbor]) {
                    // set distance of neighbour
                    distance[neighbor] = tentative;
                    // set parent node of neighbour
                    predecessor[neighbor] = currentVertex;
                }

                current = current->next;
            }
        }
    }

    free(explored);
}

/// <summary>
/// Find a vertex having the shortest distance from the source vertex
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
/// <param name="distance">distance of each veretex from source vertex</param>
/// <param name="set">a set of boolean to check the vertex is explored</param>
/// <returns></returns>
int find_min_vertex(Graph* self, int* distance, bool* set) {
    int min = INFINITVE, min_index;

    for (int v = 0; v < self->V; v++) {
        if (!set[v] && distance[v] < min) {
            min = distance[v];
            min_index = v;
        }
    }

    return min == INFINITVE ? INFINITVE : min_index;
}

/// <summary>
/// a star algorithm is used to find the shortest path
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
/// <param name="city">city matrix</param>
/// <param name="start">start vertex</param>
/// <param name="goal">terminal vertex</param>
/// <param name="size">city size</param>
/// <param name="distance">the set of distance information of the vertex</param>
/// <param name="predecessor">the set of parent node</param>
void astar_solution(Graph* self, int** city, int start, int goal, int size,
    int* distance, int* predecessor) {
    int close_len = 0; // the number of elements in the close list
    int src = start;   // source vertex
    int found = 0;     // key to find destination
    int* fScore = malloc(sizeof * fScore * self->V); // F score = G score + H score
    int* hScore = malloc(sizeof * hScore * self->V); // H score
    bool* closeList = malloc(sizeof * closeList * self->V); // the set of nodes already evaluated
    OpenList ol = create_list(); // the set of nodes to be evaluated (open list)

    // initialise all vertex
    for (int v = 0; v < self->V; v++) {
        closeList[v] = false;
        // menhattan distance messure is used as a heuristic function
        hScore[v] = menhattan_distance(v, size);
        fScore[v] = 0;
        distance[v] = INFINITVE;
        predecessor[v] = -1;
    }

    // initialise source vertex
    distance[src] = 0;
    fScore[src] = distance[src] + hScore[src];
    closeList[src] = true;
    // source vertex added to the open list
    insert_at_front(&ol, fScore[src], 0);

    // open list is not empty
    while (!isEmpty(ol)) {
        // vertex in open list with the lowest f score
        int currentVertex = find_min_fScore(&ol);
        int currentX = currentVertex / size;
        int currentY = currentVertex % size;

        // path has been found
        if (currentVertex == goal) {
            found = 1;
            break;
        }

        // destination can not reachable
        if (city[currentX][currentY] == MAP_TYPE_HOUSE ||
            city[currentX][currentY] == MAP_TYPE_WALL) {
            break;
        }

        // remove current vertex from open list
        delete_openList(&ol, currentVertex);

        // add current vertex in close list
        closeList[currentVertex] = true;
        // count the length of the close list
        close_len++;

        // Find neighbors from the current vertex
        EdgeNodePtr currentNode = self->edges[currentVertex].head;

        // for neighbour vertices
        while (currentNode != NULL) {
            int neighbor = currentNode->edge.to_vertex;
            int neighborWeight = currentNode->edge.weight;
            int tentative = distance[currentVertex] + neighborWeight;
            int neighborX = neighbor / size;
            int neighborY = neighbor % size;

            // if a neighbour node is already in close list or neighbour can not
            // traversal (building or wall)
            if (closeList[neighbor] == true ||
                city[neighborX][neighborY] == MAP_TYPE_HOUSE ||
                city[neighborX][neighborY] == MAP_TYPE_WALL) {
                // skip to the next neighbour
                currentNode = currentNode->next;
                continue;
            }

            // neighbour is already in open list
            if (find_node(&ol, neighbor) == true) {
                // new path to neighbour is shorter
                if (tentative < distance[neighbor]) {
                    // update f score of neighbor
                    distance[neighbor] = tentative;
                    fScore[neighbor] = hScore[neighbor] + distance[neighbor];
                    add_fscore(&ol, fScore[neighbor], neighbor);
                    // update parent of neighbour to current vertex
                    predecessor[neighbor] = currentVertex;
                }
                // new path to neighbour is longer
                else {
                    // skip to the next neighbour
                    currentNode = currentNode->next;
                    continue;
                }
            } // neighbour is not in open list
            else {
                // set f score of neighbour
                distance[neighbor] = tentative;
                fScore[neighbor] = hScore[neighbor] + distance[neighbor];
                // set parent of neighbour to current
                predecessor[neighbor] = currentVertex;
                // add neighbor to open list
                insert_at_front(&ol, fScore[neighbor], neighbor);
            }
            currentNode = currentNode->next;
        }
    }
    free(fScore);
    free(hScore);
    free(closeList);
}

/// <summary>
/// Menhattan distance is used as a heuristic function to calculate distance
/// from the given vertex to destination
/// </summary>
/// <param name="vertex">given vertex</param>
/// <param name="terminalVertex">destination</param>
/// <param name="size">city size</param>
/// <returns>calculated distance</returns>
int menhattan_distance(int vertex, int size) {
    int distance = 1;
    int vertexX = vertex / size;
    int vertexY = vertex % size;
    int terminalVertexX = size - 1;
    int terminalVertexY = size - 1;

    int xDiff = terminalVertexX - vertexX;
    int yDiff = terminalVertexY - vertexY;

    if (xDiff < 0)
        xDiff = -xDiff;
    if (yDiff < 0)
        yDiff = -yDiff;

    return xDiff + yDiff;
}

/// <summary>
/// Add edges between nodes with weight information
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
/// <param name="weight">weight between vertexes</param>
/// <param name="fromV">initial vertex</param>
/// <param name="toV">terminal vertex</param>
void add_edge(Graph* self, int weight, int fromV, int toV) {

    EdgeNodePtr newNode = malloc(sizeof * newNode);

    newNode->edge.to_vertex = toV;
    newNode->edge.weight = weight;
    newNode->next = self->edges[fromV].head;
    self->edges[fromV].head = newNode;

}

/// <summary>
/// Remove the given graph
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
void crush_graph(Graph* self) {

    for (int v = 0; v < self->V; v++) {

        EdgeNodePtr currentNode = self->edges[v].head;

        while (currentNode != NULL) {
            EdgeNodePtr freeNode = currentNode;
            currentNode = currentNode->next;
            free(freeNode);
        }
    }

    free(self->edges);
}

// This function is used to debug A*
EdgeList test_create_Edge_list() {

    EdgeList temp;
    temp.head = NULL;

    return temp;
}

// This function is used to debug A* to check which vertex is added to
// the close list
void test_insert_route_at_front(EdgeList* self, int data) {

    EdgeNodePtr node = malloc(sizeof * node);
    node->edge.to_vertex = data;
    node->next = self->head;

    self->head = node;
}

// This function is used to debug A* to check which vertex is added to
// the close list
EdgeList test_reverse_Edge_list(EdgeList* self) {

    EdgeList reverse = test_create_Edge_list();
    EdgeNodePtr current = self->head;

    while (current != NULL) {
        test_insert_route_at_front(&reverse, current->edge.to_vertex);
        current = current->next;
    }

    return reverse;
}

/// <summary>
/// (Testing only) print distance, all possible paths from source vertices to
/// terminal vertices (destination)
/// </summary>
/// <param name="self">graph that contains the vertex information</param>
/// <param name="startVertex">initial vertex</param>
/// <param name="distance">distance of each veretex from source vertex</param>
/// <param name="predecessor">predecessor array</param>
void test_print_solution(Graph* self, int startVertex, int* distance, int* predecessor) {
   
    for (int vertexIndex = 0; vertexIndex < self->V; vertexIndex++) {

        if (vertexIndex != startVertex) {

            printf("%d -> %d\t\t %d \t\t", startVertex, vertexIndex,
                distance[vertexIndex]);
            test_print_path(vertexIndex, predecessor);
            printf("\n");
        }
    }
}

/// <summary>
/// (Testing only)print all possible paths from source vertices to terminal
/// vertices (destination)
/// </summary>
/// <param name="terminalVertex">destination</param>
/// <param name="predecessor">predecessor array</param>
void test_print_path(int terminalVertex, int* predecessor) {

    if (terminalVertex == -1) {
        return;
    }

    test_print_path(predecessor[terminalVertex], predecessor);
    printf("%d ", terminalVertex);
}