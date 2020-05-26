#include "headers/bonus_utils.h"

void writeAnswers(Query* queries, int queries_count, FILE* wp) {
	int i;
	if (queries == NULL) {
        return;
    }
    for (i = 0; i < queries_count; i++) {
        fprintf(wp, "%d\n", queries[i].answer);
    }
}

int find(int* parent, int node) {
    if (parent == NULL) {
        return -1;
    }
    if (node == parent[node]) {
        return node;
    }
    return parent[node] = find(parent, parent[node]);
}

int checkQueries(Query* queries, int start, int queries_count) {
	int i;
    if (queries == NULL) {
        return -1;
    }
    for (i = start; i < queries_count; i++) {
        if (queries[i].answer == -1) {
            return i;
        }
    }
    return -1;
}

void merge(int* parent, int root1, int root2) {
    if (parent == NULL) {
        return;
    }

    if (root1 < root2) {
        parent[root2] = root1;
    } else {
        parent[root1] = root2;
    }
}
