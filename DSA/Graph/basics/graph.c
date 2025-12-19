#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct mygraph {
	int numnodes;
	bool** edges;
};

graph* create_graph(int numnodes) {
	graph* g = malloc(sizeof(graph));
	if (g == NULL) return NULL;
	g->numnodes = numnodes;
	g->edges = calloc(g->numnodes, sizeof(bool*));
	if (g->edges == NULL) {
		free(g);
		return NULL;
	}
	for (int i = 0; i < g->numnodes; i++) {
		g->edges[i] = calloc(g->numnodes, sizeof(bool));
		if (g->edges[i] == NULL) {
			destroy_graph(g);
			return NULL;
		}
	}
	return g;
}

void destroy_graph(graph* g) {
	if (g == NULL || g->edges == NULL) return;
	for (int i = 0; i < g->numnodes; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

void print_graph(graph* g) {
	printf("digraph {\n");
	for (int from = 0; from < g->numnodes; from++) {
		for (int to = 0; to < g->numnodes; to++) {
			if (g->edges[from][to]) {
				printf("    %d -> %d;\n", from, to);
			}
		}
	}
	printf("}\n");
}

bool add_edge(graph* g, unsigned int from_node, unsigned int to_node) {
	assert(g != NULL);
	assert(from_node < g->numnodes);
	assert(to_node < g->numnodes);
	if (has_edge(g, from_node, to_node))
		return false;
	g->edges[from_node][to_node] = true;
	return true;
}

bool remove_edge(graph* g, unsigned int from_node, unsigned int to_node) {
	assert(g != NULL);
	assert(from_node < g->numnodes);
	assert(to_node < g->numnodes);
	if (!has_edge(g, from_node, to_node))
		return false;
	g->edges[from_node][to_node] = false;
	return true;
}

bool has_edge(graph* g, unsigned int from_node, unsigned int to_node) {
	assert(g != NULL);
	assert(from_node < g->numnodes);
	assert(to_node < g->numnodes);
	return g->edges[from_node][to_node];
}
