#ifndef _HOME_STUDENT_HEADERS_GRAPH_H_
#define _HOME_STUDENT_HEADERS_GRAPH_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct list_node {
	// Nodul cu care are muchie detinatorul listei
	int node;
	// Costul muchiei
	int cost;
	struct list_node *next;
} list_node;

typedef struct graph {
	// Numarul de noduri ale grafului
	int no_nodes;
	// Vector de pointer la capul listelor inlantuite de dimensiune <no_nodes>
	// adj_heads[i] -> lista de adiacenta a nodului i
	list_node **adj_heads;
} graph;

// Creeaza un graf cu liste de adiacenta de dimensiune 'no_nodes'
graph *create_graph(int no_nodes);

// Adauga muchia (`v1`, `v2`) in graful `gl`
void insert_edge(graph *gl, int v1, int v2, int cost);

// Distruge graful
void destroy_graph(graph *gl);

int **floyd_warshall(graph *g);

#endif  // _HOME_STUDENT_HEADERS_GRAPH_H_
