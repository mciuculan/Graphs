#ifndef _HOME_STUDENT_HEADERS_DGRAPH_H_
#define _HOME_STUDENT_HEADERS_DGRAPH_H_

#define GRAPH_MAXSIZE 1001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DNode {
    int index;
    struct DNode* next;
    int isSource;
    int activated;
    int weight;
    int counterweight;
} DNode;

typedef struct DGraph {
    int maxSize;
    int currSize;
    struct DNode** adjList;
} DGraph;

typedef struct Edge {
    int src;
    int dest;
    int weight;
    int counterweight;
} Edge;

typedef struct Distance {
    int dist;
    int index;
} Distance;

/*functie care initializeaza un graf*/
struct DGraph* initGraph(int currSize);

/*functie care initializeaza un nod*/
struct DNode* initNode(int index);

/*functie care face free la graf*/
void freeDGraph(DGraph** graph);

/*functie care face free la un nod*/
void freeDNode(DNode** node);

/*functie care adauga o muchie in lista de adiacenta a grafului*/
void addEdge(DGraph** graph, int src, int dest, int weight, int);

/*functie care afiseaza graful*/
void displayGraph(DGraph** graph);

/*functie care dezactiveaza o muchie*/
void disableEdge(DGraph** graph, int src, int dest, int weight);

/*functie care activeaza o muchie*/
void enableEdge(DGraph** graph, int src, int dest, int weight);

/*functie care exploreaza un graf si extrage muchiile intr-un vector*/
void extractEdges(DGraph** graph, Edge* edges, int nodes_count);

/*functie care afiseaza muchiile din vector*/
void displayEdges(Edge* edges, int edges_count);

#endif  // _HOME_STUDENT_HEADERS_DGRAPH_H_
