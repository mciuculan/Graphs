#!/bin/bash
build: build-p1 build-p2 build-p3 build-p4 build-bonus
build-p1:
	gcc -std=c99 -Wall schimbare.c DGraph.c -o p1
build-p2:
	gcc -std=c99 -Wall reprezentanti.c graph.c -o p2 -g
build-p3:
	gcc -std=c99 -Wall drumuri.c graph_undirected.c queue.c -o p3 -g
build-p4:
	gcc -std=c99 -Wall labirint.c utils.c -o p4
build-bonus:
	gcc -std=c99 -Wall bonus.c bonus_utils.c -o bonus
run-p1:
	./p1
run-p2:
	./p2
run-p3:
	./p3
run-p4:
	./p4
run-p5:
	./bonus
clean:
	p* bonus
