#include "headers/graph.h"

// Creeaza un graf cu liste de adiacenta de dimensiune 'no_nodes'
graph *create_graph(int no_nodes) {
	graph *gl = (graph *)malloc(sizeof(graph));

	gl->no_nodes = no_nodes;
	gl->adj_heads = (list_node **)calloc(no_nodes, sizeof(list_node *));

	return gl;
}

// Adauga muchia (`v1`, `v2`) in graful `gl`
void insert_edge(graph *gl, int v1, int v2, int cost) {
	list_node *it, *new_v2, *new_v1;
	int found = 0;

	for (it = gl->adj_heads[v1]; it != NULL; it = it->next)
		if (it->node == v2) {
			found = 1;
			break;
		}

	if (found == 1)
		return;

	new_v2 = (list_node *)malloc(sizeof(list_node));
	new_v2->node = v2;
	new_v2->cost = cost;
	new_v2->next = gl->adj_heads[v1];
	gl->adj_heads[v1] = new_v2;

	new_v1 = (list_node *)malloc(sizeof(list_node));
	new_v1->node = v1;
	new_v1->cost = cost;
	new_v1->next = gl->adj_heads[v2];
	gl->adj_heads[v2] = new_v1;
}

static void free_list(list_node *list) {
	list_node *it = list, *prev;

	while (it != NULL) {
		prev = it;
		it = it->next;
		free(prev);
	}
}

// Distruge graful
void destroy_graph(graph *gl) {
	int i;

	for (i = 0; i < gl->no_nodes; i++)
		free_list(gl->adj_heads[i]);

	free(gl->adj_heads);

	free(gl);
}

int **floyd_warshall(graph *g) {
	int i, j, k;
	int **d = (int **)malloc((g->no_nodes + 1) * sizeof(int *));
	for (i = 1; i <= g->no_nodes; i++)
		d[i] = (int *)malloc((g->no_nodes + 1) * sizeof(int));
	for (i = 1; i <= g->no_nodes; i++) {
		for (j = 1; j <= g->no_nodes; j++) {
			d[i][j] = 100000000;
		}
		list_node *it = g->adj_heads[i];
		while (it != NULL) {
			d[i][it->node] = it->cost;
			it = it->next;
		}
	}

	for (k = 1; k <= g->no_nodes; k++) {
		for (i = 1; i <= g->no_nodes; i++) {
			for (j = 1; j <= g->no_nodes; j++) {
				if (d[i][j] > d[i][k] + d[k][j])
					d[i][j] = d[i][k] + d[k][j];
			}
		}
		d[k][k] = 0;
	}
	return d;
}
