#include "headers/DGraph.h"

struct DGraph* initGraph(int currSize) {
    int i;
    struct DGraph* graph = (struct DGraph*)calloc(1, sizeof(struct DGraph));
    graph->currSize = currSize;
    graph->maxSize = GRAPH_MAXSIZE;
    graph->adjList = (struct DNode**)calloc(GRAPH_MAXSIZE,
				sizeof(struct DNode*));

    for (i = 1; i <= graph->currSize; i++) {
        graph->adjList[i] = initNode(i);
        graph->adjList[i]->activated = 0;
        graph->adjList[i]->isSource = 1;
    }
    return graph;
}

struct DNode* initNode(int index) {
    struct DNode* node = (struct DNode*)calloc(1, sizeof(struct DNode));
    node->index = index;
    node->next = NULL;
    node->isSource = 0;
    node->activated = 0;
    node->weight = -1;
    return node;
}

void addEdge(DGraph** graph, int src, int dest, int weight, int counterweight) {
    if ((*graph) == NULL) {
        return;
    }
    DNode* head = (*graph)->adjList[src];
    if (head == NULL) {
        printf("Cannot add edge to NULL head: %d\n", src);
        return;
    }

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = initNode(dest);
    head->next->activated = 1;
    head->next->isSource = 0;
    head->next->next = NULL;
    head->next->weight = weight;
    head->next->counterweight = counterweight;
}

void freeDGraph(DGraph** graph) {
    int i;
    if ((*graph) == NULL) {
        return;
    }
    if ((*graph)->adjList != NULL) {
        int totalSize = (*graph)->maxSize;

        for (i = 0; i < totalSize; i++) {
            freeDNode(&((*graph)->adjList[i]));
        }
        free((*graph)->adjList);
    }
    free((*graph));
}

void freeDNode(DNode** node) {
    if ((*node) == NULL) {
        return;
    }

    DNode* tmp;
    while ((*node) != NULL) {
        tmp = (*node);
        (*node) = (*node)->next;
        free(tmp);
    }
}

void displayGraph(DGraph** graph) {
    int i;
    if ((*graph) == NULL) {
        return;
    }

    printf("\nDisplaying graph of size %d\n", (*graph)->currSize);

    for (i = 1; i <= (*graph)->currSize; i++) {
        printf("Nod %d: ", i);
        DNode* head = (*graph)->adjList[i];

        if (head->next == NULL) {
            printf("Nu are muchii\n");
        } else {
            DNode* tmp = head->next;
            while (tmp != NULL) {
                printf("%d (%d , ", tmp->index, tmp->weight);

                if (tmp->activated) {
                    printf("TRUE),");
                } else {
                    printf("FALSE),");
                }
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}

void disableEdge(DGraph** graph, int src, int dest, int weight) {
    if ((*graph) == NULL) {
        return;
    }

    if (src > (*graph)->currSize) {
        printf("[disableEdge] Src is not a valid node: %d\n", src);
        return;
    }

    if (dest > (*graph)->currSize) {
        printf("[disableEdge] Dest is not a valid node: %d\n", dest);
        return;
    }

    DNode* head = (*graph)->adjList[src];
    if (head == NULL) {
        printf("[disableEdge] Head is NULL: %d\n", src);
        return;
    }

    head = head->next;
    while (head != NULL) {
        if (head->index == dest && head->weight == weight) {
            head->activated = 0;
            return;
        }

        head = head->next;
    }
}

void enableEdge(DGraph** graph, int src, int dest, int weight) {
    if ((*graph) == NULL) {
        return;
    }

    if (src > (*graph)->currSize) {
        printf("[disableEdge] Src is not a valid node: %d\n", src);
        return;
    }

    if (dest > (*graph)->currSize) {
        printf("[disableEdge] Dest is not a valid node: %d\n", dest);
        return;
    }

    DNode* head = (*graph)->adjList[src];
    if (head == NULL) {
        printf("[disableEdge] Head is NULL: %d\n", src);
        return;
    }

    head = head->next;
    while (head != NULL) {
        if (head->index == dest && head->weight == weight) {
            head->activated = 1;
            return;
        }
        head = head->next;
    }
}

void extractEdges(DGraph** graph, Edge* edges, int nodes_count) {
    int i;
    if ((*graph) == NULL) {
        return;
    }
    if (edges == NULL) {
        return;
    }

    int currEdgeIndex = 0;

    for (i = 1; i <= nodes_count; i++) {
        DNode* head = (*graph)->adjList[i];
        if (head == NULL) {
            continue;
        }
        if (head->next == NULL) {
            continue;
        }
        head = head->next;
        while (head != NULL) {
            int dest = head->index;
            edges[currEdgeIndex].src = i;
            edges[currEdgeIndex].dest = dest;
            edges[currEdgeIndex].weight = head->weight;
            edges[currEdgeIndex].counterweight = head->counterweight;
            head = head->next;
            currEdgeIndex += 1;
        }
    }
}

void displayEdges(Edge* edges, int edges_count) {
    int i;
    printf("Displaying edges:\n");

    for (i = 0; i < 2 * edges_count; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        printf("Edge: %d -> %d\n", src, dest);
    }
}
