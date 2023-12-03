#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "openList.h"

#define INFINITE 9999

/// <summary>
/// Initialise the list to create the open list instance 
/// </summary>
/// <returns>new open list</returns>
OpenList create_list() {
    OpenList temp;
    temp.head = NULL;
    return temp;
}

/// <summary>
/// check the open list has the node 
/// </summary>
/// <param name="self">open list</param>
/// <returns>list is empty or not</returns>
int isEmpty(OpenList self) {
    // open list is empty
    if (self.head == NULL) {
        return 1;
    }
    // not empty
    return 0;
}

/// <summary>
/// f-score value is added to the taget node in open list
/// </summary>
/// <param name="self">open list</param>
/// <param name="fscore">given f-score value</param>
/// <param name="target">target node</param>
void add_fscore(OpenList* self, int fscore, int target) {
    OpenNodePtr current = self->head;

    while (current) {
        if (current->vertex = target) {
            current->fScore = fscore;
        }
        current = current->next;
    }
}

/// <summary>
/// Find the node in the open list
/// </summary>
/// <param name="self">open list</param>
/// <param name="target">target node</param>
/// <returns>true or false</returns>
int find_node(OpenList* self, int target) {
    OpenNodePtr current = self->head;
    bool found = false;

    while (current) {
        if (current->vertex == target) {
            found = true;
            return found;
        }
        current = current->next;
    }
    return found;
}

/// <summary>
/// Find the vertex having the least f score in open list
/// </summary>
/// <param name="ol">open list</param>
/// <returns>vertex</returns>
int find_min_fScore(OpenList* ol) {
    int minvalue, minIndex;
    OpenNodePtr current = ol->head;
    minvalue = current->fScore;
    minIndex = current->vertex;

    while (current != NULL) {
        if (current->fScore <= minvalue) {
            minvalue = current->fScore;
            minIndex = current->vertex;
        }
        current = current->next;
    }
    return minIndex;
}

/// <summary>
/// insert the given node to the beginning of the list
/// </summary>
/// <param name="self">open list</param>
/// <param name="fScore">f-score value</param>
/// <param name="nodeNum">given node</param>
void insert_at_front(OpenList* self, int fScore, int nodeNum) {
    OpenNodePtr node = malloc(sizeof * node);

    node->fScore = fScore;
    node->vertex = nodeNum;

    node->next = self->head;
    self->head = node;
}

/// <summary>
/// delete the given node in open list
/// </summary>
/// <param name="self">open list</param>
/// <param name="target">target node</param>
void delete_openList(OpenList* self, int target) {
    OpenNodePtr current = self->head;
    OpenNodePtr prev = NULL;

    while (current != NULL) {

        if (current->vertex == target) {

            if (prev == NULL) {
                self->head = current->next;
                free(current);
                current = self->head;
            }
            else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }

        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

/// <summary>
/// remove the open list 
/// </summary>
/// <param name="self">open list</param>
void destroy_openList(OpenList* self) {
    OpenNodePtr current = self->head;

    while (current != NULL) {
        OpenNodePtr freeNode = current;
        current = current->next;
        free(freeNode);
    }
    self->head = NULL;
}
