#include "headers/graph_undirected.h"

#include "headers/queue.h"

typedef struct element {
    int level;
    int value;
} element;

// Creeaza un graf cu liste de adiacenta de dimensiune 'no_nodes'
graph *create_graph(int no_nodes) {
    graph *g = (graph *)malloc(sizeof(graph));

    g->no_nodes = no_nodes;
    g->adj_heads = (list_node **)calloc(no_nodes, sizeof(list_node *));

    return g;
}

// Adauga muchia (`v1`, `v2`) in graf
void insert_edge(graph *g, int v1, int v2) {
    list_node *it, *new_v2, *new_v1;
    int found = 0;

    for (it = g->adj_heads[v1]; it != NULL; it = it->next)
        if (it->node == v2) {
            found = 1;
            break;
        }

    if (found == 1)
        return;

    new_v2 = (list_node *)malloc(sizeof(list_node));
    new_v2->node = v2;
    new_v2->next = g->adj_heads[v1];
    g->adj_heads[v1] = new_v2;

    new_v1 = (list_node *)malloc(sizeof(list_node));
    new_v1->node = v1;
    new_v1->next = g->adj_heads[v2];
    g->adj_heads[v2] = new_v1;
}

static void delete_elem_list(list_node **list, int elem) {
    list_node *toDelete, *prev;

    if ((*list)->node == elem) {
        toDelete = *list;
        *list = (*list)->next;
        free(toDelete);
        return;
    }

    for (toDelete = (*list)->next, prev = *list;
         toDelete != NULL && toDelete->node != elem;
         toDelete = toDelete->next, prev = prev->next) {
		continue;
	}

    // No element to remove
    if (toDelete == NULL)
        return;

    prev->next = toDelete->next;
    free(toDelete);
}

// Sterge muchia (`v1`, `v2`) (daca exista) in graf
void remove_edge(graph *g, int v1, int v2) {
    delete_elem_list(&g->adj_heads[v1], v2);
    delete_elem_list(&g->adj_heads[v2], v1);
}

static void free_list(list_node *list) {
    list_node *it = list, *prev;

    while (it != NULL) {
        prev = it;
        it = it->next;
        free(prev);
    }
}

// Distruge graful cu liste de adiacenta
void destroy_graph(graph *g) {
    int i;

    for (i = 0; i < g->no_nodes; i++)
        free_list(g->adj_heads[i]);

    free(g->adj_heads);

    free(g);
}

int bfs(graph *g, int starting_node, int search, int *level) {
    Queue *q;
    init_queue(&q);

    int d_min = 0;

    int *visited = (int *)calloc((g->no_nodes + 1), sizeof(int));
    visited[starting_node] = 1;
    enqueue(q, starting_node);
    while (!is_empty_queue(q)) {
        int node = front(q);
        dequeue(q);
        list_node *it = g->adj_heads[node];
        while (it != NULL) {
            if (visited[it->node] == 0) {
                level[it->node] = level[node] + 1;
                if (it->node == search) {
                    d_min = level[it->node];
                }
                visited[it->node] = 1;
                enqueue(q, it->node);
            }
            it = it->next;
        }
    }
    free(visited);
    free(q);
    return d_min;
}

// returneaza -1 daca elementul nu este unic,
// 1 daca e unic
static int check_unique(int value, int n, element *v) {
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (value == v[i].level) {
            count++;
        }
        if (count > 1) {
            return -1;
        }
    }
    return 1;
}

static int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void rec_bfs(graph *g, int final_node, int first_node, int *level, FILE *out) {
    Queue *q;
    init_queue(&q);

    int *visited = (int *)calloc((g->no_nodes + 1), sizeof(int));
    element *aux = (element *)calloc((g->no_nodes + 1), sizeof(element));
    int *repeated = (int *)calloc(g->no_nodes, sizeof(int));

    visited[final_node] = 1;
    enqueue(q, final_node);

    int i, k = 1, count = 1;

    aux[0].value = final_node;
    aux[0].level = level[final_node];
    repeated[0] = final_node;

    while (!is_empty_queue(q)) {
        int node = front(q);
        dequeue(q);
        list_node *it = g->adj_heads[node];
        while (it != NULL) {
            if (visited[it->node] == 0) {
                if (level[it->node] == level[node] - 1) {
                    aux[count].value = it->node;
                    aux[count].level = level[it->node];
                    count++;
                    enqueue(q, it->node);
                }
                visited[it->node] = 1;
            }
            it = it->next;
        }
    }
    // pornesc de la 1 ptc aux[0] este deja pus in repeated
    for (i = 1; i < count; i++) {
        if (check_unique(aux[i].level, count, aux) > 0) {
            repeated[k] = aux[i].value;
            k++;
        }
    }
    qsort(repeated, k, sizeof(int), cmpfunc);
    fprintf(out, "%d ", k);
    for (i = 0; i < k; i++) {
        fprintf(out, "%d ", repeated[i]);
    }
    fprintf(out, "\n");
    free(repeated);
    free(aux);
    free(visited);
    free(q);
}
