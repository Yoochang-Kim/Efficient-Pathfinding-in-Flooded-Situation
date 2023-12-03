#pragma once

typedef struct openNode {
	int fScore;
	int vertex;
	struct OpenNodePtr* next;
} *OpenNodePtr;

typedef struct openList {
	OpenNodePtr head;
} OpenList;

OpenList create_list();
int isEmpty(OpenList self);
void insert_at_front(OpenList* self, int fScore, int nodeNum);
void delete_openList(OpenList* self, int data);
void destroy_openList(OpenList* self);
int find_node(OpenList* self, int target);
int find_min_fScore(OpenList* ol);
void add_fscore(OpenList* self, int fscore, int target);