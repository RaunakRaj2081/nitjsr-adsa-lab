// Write a program for determining whether a graph with n vertices and e edges contains a clique of size m 
// (m <= n). Check for what values of n, e, and m your program gives output in reasonable time.
 #include <stdio.h>
#include <math.h>

int adj[20][20], n, e, m, vertices[20];

// Function to check if a subset is a clique
int isClique(int subset[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (!adj[subset[i]][subset[j]])
                return 0;
    return 1;
}

// Recursive function to find clique
int findClique(int start, int size) {
    if (size == m) return isClique(vertices, m);
    for (int i = start; i < n; i++) {
        vertices[size] = i;
        if (findClique(i + 1, size + 1))
            return 1;
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
    printf("Enter size of clique (m): ");
    scanf("%d", &m);

    if (findClique(0, 0))
        printf("Graph contains a clique of size %d.\n", m);
    else
        printf("Graph does not contain a clique of size %d.\n", m);

    return 0;
}
