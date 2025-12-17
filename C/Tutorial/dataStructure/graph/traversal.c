#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DEGREE 2
#define MAX_LANES 32

#define COL_RESET   "\x1b[0m"
#define COL_RED     "\x1b[31m"
#define COL_GREEN   "\x1b[32m"
#define COL_YELLOW  "\x1b[33m"
#define COL_BLUE    "\x1b[34m"
#define COL_MAGENTA "\x1b[35m"
#define COL_CYAN    "\x1b[36m"

typedef struct Node {
    int id;
    char *label;
    int degree;
    int neighbors[MAX_DEGREE];
} Node;

Node *graph[100];
int graph_size = 0;

void add_node(int id, char *label, int n1, int n2) {
    Node *n = malloc(sizeof(Node));
    n->id = id;
    n->label = strdup(label);
    n->degree = 0;
    
    if (n1 != -1) n->neighbors[n->degree++] = n1;
    if (n2 != -1) n->neighbors[n->degree++] = n2;
    
    graph[graph_size++] = n;
}

int find_lane(int *lanes, int lane_count, int id) {
    for (int i = 0; i < lane_count; i++) {
        if (lanes[i] == id) return i;
    }
    return -1;
}

void traverse_graph() {
    int lanes[MAX_LANES];
    int lane_count = 0;
    
    for (int i = 0; i < graph_size; i++) {
        Node *n = graph[i];
        
        // ---------------------------------------------------------
        // Phase 1: Pre-Node Convergence (Merge branches into one)
        // ---------------------------------------------------------
        int target_idx = find_lane(lanes, lane_count, n->id);
        
        if (target_idx != -1) {
            bool has_merge = false;
            for (int k = target_idx + 1; k < lane_count; k++) {
                if (lanes[k] == n->id) {
                    has_merge = true;
                    break;
                }
            }
            
            if (has_merge) {
                printf("  "); 
                for (int k = 0; k < lane_count; k++) {
                    if (k == target_idx) {
                        printf("%s|%s ", COL_CYAN, COL_RESET);
                    } else if (lanes[k] == n->id) {
                        printf("%s/%s ", COL_MAGENTA, COL_RESET);
                    } else {
                        printf("%s|%s ", COL_CYAN, COL_RESET);
                    }
                }
                printf("\n");
                
                int compacted[MAX_LANES];
                int compacted_count = 0;
                
                for (int k = 0; k < lane_count; k++) {
                    if (lanes[k] == n->id && k != target_idx) {
                        continue; 
                    }
                    compacted[compacted_count++] = lanes[k];
                }
                
                memcpy(lanes, compacted, compacted_count * sizeof(int));
                lane_count = compacted_count;
                
                target_idx = find_lane(lanes, lane_count, n->id);
            }
        }
        
        // If it's a new root/start node
        if (target_idx == -1) {
            lanes[lane_count] = n->id;
            target_idx = lane_count;
            lane_count++;
        }

        // ---------------------------------------------------------
        // Phase 2: Draw the Node itself
        // ---------------------------------------------------------
        printf("  "); 
        for (int k = 0; k < lane_count; k++) {
            if (k == target_idx) {
                printf("%s*%s ", COL_RED, COL_RESET);
            } else {
                printf("%s|%s ", COL_CYAN, COL_RESET);
            }
        }
        printf(" %s%s%s (ID: %d)\n", COL_YELLOW, n->label, COL_RESET, n->id);

        // ---------------------------------------------------------
        // Phase 3: Post-Node Divergence (Split or Death)
        // ---------------------------------------------------------
        int next_lanes[MAX_LANES];
        int next_count = 0;
        
        for (int k = 0; k < lane_count; k++) {
            if (k == target_idx) {
                if (n->degree > 0) {
                    next_lanes[next_count++] = n->neighbors[0];
                    if (n->degree > 1) {
                        next_lanes[next_count++] = n->neighbors[1];
                    }
                }
                // If degree is 0, this lane dies here. We do not add anything.
            } else {
                next_lanes[next_count++] = lanes[k];
            }
        }
        
        // VISUALIZE THE TRANSITION
        
        if (next_count > lane_count) {
             // Case: Split / Expansion (1 -> 2)
             printf("  ");
             for (int k = 0; k < target_idx; k++) printf("%s|%s ", COL_CYAN, COL_RESET);
             printf("%s|%s%s\\%s ", COL_CYAN, COL_RESET, COL_MAGENTA, COL_RESET);
             for (int k = target_idx + 1; k < lane_count; k++) printf("%s|%s ", COL_CYAN, COL_RESET);
             printf("\n");
        } 
        else if (next_count < lane_count) {
            // Case: Death / Contraction (1 -> 0)
            // Lanes to the right must shift left to fill the gap.
            printf("  ");
            for (int k = 0; k < lane_count; k++) {
                if (k < target_idx) {
                    printf("%s|%s ", COL_CYAN, COL_RESET);
                } else if (k == target_idx) {
                    // This lane died. We print nothing (or space) here.
                    printf("  "); 
                } else {
                    // This lane (k) is shifting to (k-1).
                    // We draw a slash to indicate leftward movement.
                    printf("%s/%s ", COL_MAGENTA, COL_RESET);
                }
            }
            printf("\n");
        }
        // If equal, straight lines (implicit in next loop iteration)
        
        memcpy(lanes, next_lanes, next_count * sizeof(int));
        lane_count = next_count;
    }
}

int main() {
    printf(COL_GREEN "Initializing Graph Traversal...\n" COL_RESET);
    
    graph_size = 0;
    
    add_node(7, "Merge Node", 6, 5);
    add_node(6, "Process A", 4, -1);
    add_node(5, "Process B", 3, -1);
    add_node(4, "Refactor", 2, -1);
    add_node(3, "Init Sub-task", 2, -1);
    add_node(2, "Base Logic", 1, -1);
    add_node(1, "Root", -1, -1);

    traverse_graph();

    for(int i=0; i<graph_size; i++) {
        free(graph[i]->label);
        free(graph[i]);
    }
    
    return 0;
}
