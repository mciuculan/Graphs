#include "headers/bonus_utils.h"

#define BUFLEN 100

int cmpEdges(const void* first, const void* second) {
    int w1 = ((Edge*)first)->weight;
    int w2 = ((Edge*)second)->weight;
    return w1 - w2;
}

int main() {
    FILE* rp;
    FILE* wp;
    rp = fopen("bonus.in", "r");
    wp = fopen("bonus.out", "w");

    /*----------------Deschiderea fisierelor--------------------*/

    if (rp == NULL) {
        printf("Fisierul nu a putut fi deschis\n");
        return 0;
    }

    /* ------------- Citirea fisierului ----------------------*/

    int nodes_count = 0;
    int edges_count = 0;
    int queries_count = 0;

    char buf[BUFLEN];
    memset(buf, 0, BUFLEN);

    fgets(buf, BUFLEN, rp);
    char* rest = buf;
    char* token = __strtok_r(rest, " ", &rest);
    nodes_count = atoi(token);
    edges_count = atoi(__strtok_r(rest, " ", &rest));
    queries_count = atoi(__strtok_r(rest, " ", &rest));

    int i, j;

    Edge* edges = (Edge*)calloc(edges_count + 1, sizeof(Edge));

    for (i = 0; i < edges_count; i++) {
        memset(buf, 0, BUFLEN);
        fgets(buf, BUFLEN, rp);
        rest = buf;
        int a = atoi(__strtok_r(rest, " ", &rest));
        int b = atoi(__strtok_r(rest, " ", &rest));
        int weight = atoi(__strtok_r(rest, " ", &rest));

        edges[i].a = a;
        edges[i].b = b;
        edges[i].weight = weight;
    }

    Query* queries = (Query*)calloc(queries_count + 1, sizeof(Query));

    for (i = 0; i < queries_count; i++) {
        memset(buf, 0, BUFLEN);
        fgets(buf, BUFLEN, rp);
        rest = buf;
        int a = atoi(__strtok_r(rest, " ", &rest));
        int b = atoi(__strtok_r(rest, " ", &rest));

        queries[i].a = a;
        queries[i].b = b;
        queries[i].answer = -1;
    }

    /*-------------------Solving the problem--------------------*/

    int* parent = (int*)calloc(nodes_count + 1, sizeof(int));
    qsort(edges, edges_count, sizeof(Edge), cmpEdges);

    for (j = 0; j <= nodes_count; j++) {
        parent[j] = j;
    }

    int mstCount = 0;

    int queriesCheckIndex = 0;

    for (j = 0; j < edges_count; j++) {
        if (mstCount >= nodes_count - 1) {
            break;
        }
        Edge currEdge = edges[j];
        int a = currEdge.a;
        int b = currEdge.b;
        int weight = currEdge.weight;

        int root_a = find(parent, a);
        int root_b = find(parent, b);

        if (root_a == root_b) {
            continue;
        }

        mstCount += 1;
        merge(parent, root_a, root_b);

        for (i = queriesCheckIndex; i < queries_count; i++) {
            if (queries[i].answer != -1) {
                continue;
            }
            int src = queries[i].a;
            int dest = queries[i].b;
            if (find(parent, src) == find(parent, dest)) {
                queries[i].answer = weight;
            }
        }

        int result = checkQueries(queries, queriesCheckIndex, queries_count);

        if (result == -1) {
            writeAnswers(queries, queries_count, wp);

            free(parent);
            free(edges);
            free(queries);

            fclose(rp);
            fclose(wp);

            return 0;
        } else {
            queriesCheckIndex = result;
        }
    }

    writeAnswers(queries, queries_count, wp);

    free(parent);
    free(edges);
    free(queries);

    fclose(rp);
    fclose(wp);

    return 0;
}
