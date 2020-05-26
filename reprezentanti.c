#include "headers/graph.h"

typedef struct costuri {
    int val;
    int reprezentant;
} costuri;

int main() {
    FILE *fin = fopen("reprezentanti.in", "r");
    FILE *fout = fopen("reprezentanti.out", "w");

    if (fin == NULL || fout == NULL) {
        printf("Nu exista fisierul!\n");
        exit(1);
    }
    // nr noduri, nr muchii, nr de reprezentati
    int n, m, x;
    // muchie intre nodul u si v de costul cost
    int u, v, cost;
    // fiecare nod are atasat un cost
    costuri *costs;
    int *reprezentanti;
    graph *g;
    char line[60000], *aux, *rest;
    int i = 0, nr, j = 0;

    while (fgets(line, 60000, fin)) {
        if (i == 0) {
            rest = line;
            nr = 1;
            while ((aux = __strtok_r(rest, " \n", &rest))) {
                if (nr == 1) {
                    n = atoi(aux);
                } else if (nr == 2) {
                    m = atoi(aux);
                } else {
                    x = atoi(aux);
                }
                nr++;
            }
            reprezentanti = (int *)malloc(x * sizeof(int));
            costs = (costuri *)malloc((n + 1) * sizeof(costuri));
            g = create_graph(n);
        } else if (i != m + 1) {
            rest = line;
            nr = 1;
            while ((aux = __strtok_r(rest, " \n", &rest))) {
                if (nr == 1) {
                    u = atoi(aux);
                } else if (nr == 2) {
                    v = atoi(aux);
                } else {
                    cost = atoi(aux);
                }
                nr++;
            }
            insert_edge(g, u, v, cost);
        } else if (i == m + 1) {
            j = 0;
            rest = line;
            while ((aux = __strtok_r(rest, " \n", &rest))) {
                reprezentanti[j] = atoi(aux);
                j++;
            }
        }
        i++;
    }

    int **d = floyd_warshall(g);
    for (i = 1; i <= n; i++) {
        costs[i].val = 1000000;
    }
    for (i = 0; i < x; i++) {
        for (j = 1; j <= n; j++) {
            if (d[reprezentanti[i]][j] < costs[j].val) {
                costs[j].val = d[reprezentanti[i]][j];
                costs[j].reprezentant = reprezentanti[i];
            }
        }
    }
    for (i = 1; i <= n; i++) {
        fprintf(fout, "%d %d\n", costs[i].reprezentant, costs[i].val);
    }
    for (i = 1; i <= n; i++) {
        free(d[i]);
    }
    free(d);
    free(costs);
    free(reprezentanti);
    destroy_graph(g);
    fclose(fin);
    fclose(fout);
}
