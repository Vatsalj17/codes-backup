#include "graph.h"

int main(void) {
    graph* g = create_graph(5);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 3);
    add_edge(g, 1, 4);
    add_edge(g, 2, 4);
    add_edge(g, 3, 0);
    print_graph(g);
    destroy_graph(g);
}
