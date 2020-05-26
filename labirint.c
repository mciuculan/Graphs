#include "headers/utils.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("labirint.in", "r");
    if (fp == NULL) {
        printf("Nu exista fisierul %s\n", argv[1]);
        exit(1);
    }

    int i = 0, j, w, h = 1, nr;
    int n = 0, m = 0, k = 0;
    int **matrix, *movements, vizitat[106][106];
    char *aux, line[2001], *rest;

    /*pentru mutari*/
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    /*pt pozitia initiala*/
    casuta initial;

    /*folosesc 2 cozi pentru a nu se suprapune mutarile*/
    Queue *q;
    init_queue(&q);
    Queue *nq;
    init_queue(&nq);

    /*citire*/
    while (fgets(line, 2001, fp)) {
        if (i == 0) {
            rest = line;
            nr = 1;
            while ((aux = __strtok_r(rest, " \n", &rest))) {
                if (nr == 1) {
                    n = atoi(aux);
                } else if (nr == 2) {
                    m = atoi(aux);
                } else {
                    k = atoi(aux);
                }
                nr++;
            }
            matrix = (int **)malloc((n + 2) * sizeof(int *));
            for (j = 0; j <= n + 1; j++) {
                matrix[j] = (int *)malloc((m + 2) * sizeof(int));
            }
            for (j = 0; j <= n + 1; j++) {
                matrix[j][0] = matrix[j][m + 1] = 1;
            }
            for (j = 0; j <= m + 1; j++) {
                matrix[0][j] = matrix[n + 1][j] = 1;
            }
        } else if (i != n + 1) {
            w = 1;
            rest = line;
            while ((aux = __strtok_r(rest, " \n", &rest))) {
                matrix[h][w] = atoi(aux);
                if (matrix[h][w] == 2) {
                    /*pun pozitia initiala in queue*/
                    initial.x = h;
                    initial.y = w;
                    enqueue(q, initial);
                }
                w++;
            }
            h++;
        } else if (i == n + 1) {
            w = 0;
            movements = (int *)malloc(k * sizeof(int));
            rest = line;
            while ((aux = __strtok_r(rest, " \n", &rest))) {
                movements[w] = atoi(aux);
                w++;
            }
        }
        i++;
    }

    /*pentru a nu se pune de 2 ori pe aceeasi pozitie*/
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++)
            vizitat[i][j] = -1;
    }

    int dir, x, y;
    for (i = 0; i < k; i++) {
        dir = movements[i];
        while (!is_empty_queue(q)) {
            /*ma mut in directia data*/
            x = front(q).x + dx[dir];
            y = front(q).y + dy[dir];
            while (matrix[x][y] != 1) {
                /*daca pozitia pe care ajung nu este vizitata*/
                if (vizitat[x][y] < i) {
                    vizitat[x][y] = i;
                    casuta aux;
                    aux.x = x;
                    aux.y = y;
                    /*adaug in queue-ul auxiliar*/
                    enqueue(nq, aux);
                }
                /*ma mut in directia respectiva cat pot*/
                x = x + dx[dir];
                y = y + dy[dir];
            }
            /*scot din queue pasul respectiv*/
            dequeue(q);
        }
        while (!is_empty_queue(nq)) {
            /*adaug in queue pozitiile finale pentru a porni
			de la fiecare dintre ele la urmatorii pasi*/
            enqueue(q, front(nq));
            dequeue(nq);
        }
    }
    FILE *fo = fopen("labirint.out", "w");
    if (fo == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(fo, "%d", size_queue(q));
    fclose(fo);
    free(q);
    free(nq);
    for (i = 0; i < n + 2; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(movements);
    fclose(fp);
    return 0;
}
