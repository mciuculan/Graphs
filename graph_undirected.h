#ifndef _HOME_STUDENT_HEADERS_GRAPH_UNDIRECTED_H_
#define _HOME_STUDENT_HEADERS_GRAPH_UNDIRECTED_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
    // Nodul cu care are muchie detinatorul listei
    int node;
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

// Adauga muchia (`v1`, `v2`) in graf
void insert_edge(graph *g, int v1, int v2);

// Sterge muchia (`v1`, `v2`) (daca exista) in graf
void remove_edge(graph *g, int v1, int v2);

// Distruge graful cu liste de adiacenta
void destroy_graph(graph *g);

// Aplica parcurgerea bfs, returneaza cel mai scurt drum de la
// starting node la search. Calculeaza, de asemenea, distanta minima
// de la start la toate nodurile
int bfs(graph *g, int starting_node, int search, int *level);

// Selecteaza nodurile cu distante unice
void rec_bfs(graph *g, int final_node, int first_node, int *level, FILE *out);

#endif  // _HOME_STUDENT_HEADERS_GRAPH_UNDIRECTED_H_
