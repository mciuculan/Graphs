#include "headers/DGraph.h"

#define BUFLEN 40
#define INF 1000000000
#define HEAP_SIZE 10

int main() {
    int i, j;

    FILE* rp;
    FILE* wp;
    rp = fopen("schimbare.in", "r");
    wp = fopen("schimbare.out", "w+");

    /*----------------Deschiderea fisierelor--------------------*/

    if (rp == NULL || wp == NULL) {
        printf("Fisierul nu a putut fi deschis\n");
        return 0;
    }

    /* ------------- Citirea fisierului ----------------------*/

    int nodes_count = 0;
    int edges_count = 0;

    char buf[BUFLEN], *rest;
    memset(buf, 0, BUFLEN);

    fgets(buf, BUFLEN, rp);
    rest = buf;
    nodes_count = atoi(__strtok_r(rest, " ", &rest));
    edges_count = atoi(__strtok_r(rest, " ", &rest));

    DGraph* graph = initGraph(nodes_count);

    for (i = 0; i < edges_count; i++) {
        memset(buf, 0, BUFLEN);
        fgets(buf, BUFLEN, rp);

        rest = buf;
        int src = atoi(__strtok_r(rest, " ", &rest));
        int dest = atoi(__strtok_r(rest, " ", &rest));
        int weight = atoi(__strtok_r(rest, " ", &rest));

        addEdge(&graph, src, dest, 0, weight);
        addEdge(&graph, dest, src, weight, 0);
    }

    /*se exploreaza graful si se stocheaza muchiile intr-un vector*/
    Edge* edges = (Edge*)calloc(2 * edges_count + 1, sizeof(Edge));
    extractEdges(&graph, edges, nodes_count);

    /*vctorul de distante folosit la Djikstra*/
    Distance* dist = (Distance*)calloc(nodes_count + 1, sizeof(Distance));

    /*vectorul de visited folosit la Djikstra*/
    int* visited = (int*)calloc(nodes_count + 1, sizeof(int));

    /*costul minim al unui ciclu - initial*/
    int minCostCycle = INF;

    /*se itereaza prin fiecare muchie din graf*/
    for (i = 0; i < 2 * edges_count; i++) {
        /*luam o muchie pe rand din graf si o dezactivam*/
        Edge e = edges[i];
        int src = e.src;
        int dest = e.dest;
        int w = e.weight;

        /*dezactivam atat muchia, cat si inversul ei*/
        disableEdge(&graph, src, dest, w);
        disableEdge(&graph, dest, src, e.counterweight);

        /*aplicarea algoritmului Djikstra din nodul-sursa
        spre nodul-destinatie*/
        int start = src;
        int final = dest;

        /*resetarea distantelor...*/
        for (j = 0; j <= nodes_count; j++) {
            dist[j].dist = INF;
            dist[j].index = j;
        }
        dist[start].dist = 0;

        /*marcheaza toate nodurile ca fiind nevizitate*/
        for (j = 0; j <= nodes_count; j++) {
            visited[j] = 0;
        }

        visited[start] = 1;
        int totalSteps = 0;

        /*aplica Djikstra...*/
        while (visited[final] == 0 && totalSteps <= nodes_count) {
            totalSteps += 1;
            int min = INF;
            int newStart = start;

            DNode* head = graph->adjList[start];
            head = head->next;

            while (head != NULL) {
                if (head->activated == 0) {
                    head = head->next;
                    continue;
                }

                int cost = head->weight;
                int neigh = head->index;

                if (visited[neigh] == 0) {
                    if (dist[start].dist + cost < dist[neigh].dist) {
                        dist[neigh].dist = dist[start].dist + cost;
                    }

                    if (dist[neigh].dist < min) {
                        min = dist[neigh].dist;
                        newStart = neigh;
                    }
                }
                head = head->next;
            }

            start = newStart;
            visited[start] = 1;
        }

        int weight = e.counterweight;

        /*daca am gasit un ciclu mai ieftin, updateaza*/
        if (weight + dist[dest].dist < minCostCycle) {
            minCostCycle = dist[dest].dist + weight;
        }

        /*daca ciclul gasit are exact cost 0, inseamna ca aveam deja un ciclu*/
        if (minCostCycle == 0) {
            break;
        }

        /*muchiile disabled sunt acum reactivate*/
        enableEdge(&graph, src, dest, e.weight);
        enableEdge(&graph, dest, src, e.counterweight);
    }

    /*daca graful nu are cicluri, practic nu vom modifica niciodata
	 aceasta variabila*/
    if (minCostCycle == INF) {
        fprintf(wp, "-1\n");
    } else {
        fprintf(wp, "%d\n", minCostCycle);
    }

    /*eliberarea memoriei..*/
    free(edges);
    freeDGraph(&graph);
    free(dist);
    free(visited);

    fclose(rp);
    fclose(wp);

    return 0;
}
