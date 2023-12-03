#include <stdio.h>
#include <stdlib.h>
#include "city.h"
#include "graph.h"

#define SIZE 20
#define INFINITIVE 9999
int main() {
    printf("\n----------------------------FYI-----------------------------------\n");
    printf("'H' : House, 'W' : Wall, '~' : Water hole, '-' : Road, ¡Ú : Route ");
    printf("\n------------------------------------------------------------------\n\n");

    int** city = create_city(SIZE);
    print_city(city, SIZE);

    printf("\n\n");
    printf(" Dijkstra Algorithm\n\n");
    shortest_path_A(city, SIZE);
    printf("\n\n");

    printf(" A* Algorithm\n\n");
    shortest_path_B(city, SIZE);
    demolish_city(city, SIZE);
    return 0;
}

shortest_path_A(int** city, int size) {

    Graph g = create_graph(size * size);
    // total distance from start to goal
    int BetteryUsage;

    //create the graph as adjacency list from the city matrix 
    create_graph_from_city_matrix(&g, city, size);

    // find the shortest path with dijkstra algorithm
    EdgeList route = route_finder_option_dijkstra(&g, 0, size * size - 1, &BetteryUsage);

    // deep copy the city
    int** cityCopy = deep_copy_city_matrix(city, size);

    // can not reach the goal
    if (BetteryUsage >= INFINITIVE)
        printf("Can not reach the destination\n");

    // can reach the goal
    else {

        // leave the route on the city matrix
        leave_route_on_city(cityCopy, route, SIZE);
        // display the city
        print_city(cityCopy, SIZE);
        // information
        printf("Total battery usage: %d \n\n", BetteryUsage);
        printf("Path\n");
        print_path(route, size);
    }

    // free memory
    demolish_city(cityCopy, SIZE);
    demolish_route(route);
    crush_graph(&g);
}

shortest_path_B(int** city, int size) {
    Graph g = create_graph(size * size);
    int BetteryUsage; // total distance from start to goal

    //create the graph as adjacency list from the city matrix 
    create_graph_from_city_matrix(&g, city, size);

    // find the shortest path
    EdgeList route = route_finder_option_astar(&g, city, 0, size * size - 1, size, &BetteryUsage);
    // deep copy the city
    int** cityCopy = deep_copy_city_matrix(city, size);

    // can not reach the goal
    if (BetteryUsage >= INFINITIVE || BetteryUsage == NULL)
        printf("Can not reach the destination\n");

    // can reach the goal
    else {

        // leave the route on the city matrix
        leave_route_on_city(cityCopy, route, SIZE);
        // display the city
        print_city(cityCopy, SIZE);
        // information
        printf("Total battery usage: %d \n\n", BetteryUsage);
        printf("Path\n");
        print_path(route, size);
    }
    // free memory
    demolish_city(cityCopy, SIZE);
    demolish_route(route);
    crush_graph(&g);
}
