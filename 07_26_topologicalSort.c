// Write a function to perform topological sort on a given directed graph. 

#include <stdio.h>
#include <string.h>
#define MAX 20

int n, graph[MAX][MAX], visited[MAX], stack[MAX], top=-1;

void dfs(int v) {
    visited[v] = 1;
    for(int i=0;i<n;i++) {
        if(graph[v][i] && !visited[i])
            dfs(i);
    }
    stack[++top] = v;  // push after visiting children
}

void topoSort() {
    memset(visited,0,sizeof(visited));
    top=-1;
    for(int i=0;i<n;i++)
        if(!visited[i]) dfs(i);

    printf("Topological Order: ");
    while(top!=-1) printf("%d ",stack[top--]);
}

int main() {
    int m,u,v;
    scanf("%d %d",&n,&m);   // vertices, edges
    memset(graph,0,sizeof(graph));

    for(int i=0;i<m;i++) {
        scanf("%d %d",&u,&v);
        graph[u][v]=1;      // directed edge
    }

    topoSort();
    return 0;
}
