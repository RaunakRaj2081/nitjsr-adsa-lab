// Write a program for determining whether a graph with n vertices and e edges is a bipartite graph. 

#include <stdio.h>

int adj[20][20], color[20], n, e;

int isBipartite() {
    int queue[20], front = 0, rear = 0;
    for (int i = 0; i < n; i++) color[i] = -1;

    color[0] = 0;           // Start coloring first vertex
    queue[rear++] = 0;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < n; v++) {
            if (adj[u][v]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                } else if (color[v] == color[u])
                    return 0;  // Same color on adjacent vertices
            }
        }
    }
    return 1;
}

int main() {
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    for (int i = 0; i < e; i++) {
        int u, v;
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        adj[u][v] = adj[v][u] = 1;  // Undirected graph
    }

    if (isBipartite())
        printf("Graph is Bipartite.\n");
    else
        printf("Graph is NOT Bipartite.\n");

    return 0;
}
