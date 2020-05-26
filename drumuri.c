#include "headers/graph_undirected.h"

typedef struct query {
    int initial;
    int final;
} query;

int main() {
    // citire
    FILE *fin = fopen("drumuri.in", "r");
    FILE *fout = fopen("drumuri.out", "w");

    if (fin == NULL || fout == NULL) {
        printf("Nu exista fisierul!\n");
        exit(1);
    }
    // numar noduri, muchii, query-uri
    int n, m, q;
    char *aux, line[20], *rest;
    int nr, i = 0, nod1, nod2;
    graph *g;
    query *list;
    while (fgets(line, 20, fin)) {
        if (i == 0) {
            rest = line;
            nr = 1;
            while ((aux = __strtok_r(rest, " ", &rest))) {
                if (nr == 1) {
                    n = atoi(aux);
                } else if (nr == 2) {
                    m = atoi(aux);
                } else {
                    q = atoi(aux);
                }
                nr++;
            }
            g = create_graph(n);
            list = (query *)malloc(q * sizeof(query));
        } else if (i <= m) {
            rest = line;
            nr = 1;
            while ((aux = __strtok_r(rest, " ", &rest))) {
                if (nr == 1) {
                    nod1 = atoi(aux);
                } else if (nr == 2) {
                    nod2 = atoi(aux);
                }
                nr++;
            }
            insert_edge(g, nod1, nod2);
        } else if (i > m) {
            nr = 1;
            rest = line;
            while (((aux = __strtok_r(rest, " ", &rest)))) {
                if (nr == 1) {
                    list[i - m - 1].initial = atoi(aux);
                } else if (nr == 2) {
                    list[i - m - 1].final = atoi(aux);
                }
                nr++;
            }
        }
        i++;
    }
    // rezolvare
    for (i = 0; i < q; i++) {
        int *level = (int *)calloc((g->no_nodes + 1), sizeof(int));
        int d_min = bfs(g, list[i].initial, list[i].final, level);
        if (d_min > 0) {
            rec_bfs(g, list[i].final, list[i].initial, level, fout);
        } else {
            fprintf(fout, "0\n");
        }

        free(level);
    }
    free(list);
    destroy_graph(g);
    fclose(fin);
    fclose(fout);
    return 0;
}
