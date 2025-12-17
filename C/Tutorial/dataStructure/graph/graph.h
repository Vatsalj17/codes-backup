#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct mygraph graph;

graph* create_graph(int numnodes);
void destroy_graph(graph* g);
void print_graph(graph* g);
bool add_edge(graph* g, unsigned int from_node, unsigned int to_node);
bool remove_edge(graph* g, unsigned int from_node, unsigned int to_node);
bool has_edge(graph* g, unsigned int from_node, unsigned int to_node);

#endif
