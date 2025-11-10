// Write a program for determining whether there exists a Hamiltonian cycle in a graph with n vertices and 
// e edges.

#include <stdio.h>

int n, e, adj[20][20], path[20];

// Check if next vertex v can be added
int isSafe(int v, int pos) {
    if (!adj[path[pos - 1]][v]) return 0;
    for (int i = 0; i < pos; i++)
        if (path[i] == v) return 0;
    return 1;
}

// Recursive function to find Hamiltonian cycle
int hamCycle(int pos) {
    if (pos == n)
        return adj[path[pos - 1]][path[0]]; // check last edge to first

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamCycle(pos + 1)) return 1;
            path[pos] = -1;
        }
    }
    return 0;
}

int main() {
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    for (int i = 0; i < e; i++) {
        int u, v;
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;
    }

    for (int i = 0; i < n; i++) path[i] = -1;
    path[0] = 0; // start from vertex 0

    if (hamCycle(1)) {
        printf("Hamiltonian Cycle exists.\nPath: ");
        for (int i = 0; i < n; i++) printf("%d ", path[i]);
        printf("%d\n", path[0]);
    } else
        printf("No Hamiltonian Cycle exists.\n");

    return 0;
}
