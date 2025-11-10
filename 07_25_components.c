// Write functions to identify all the strongly connected components, biconnected components, articulation 
// points and bridges in a given directed graph.  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int n, m;
int graph[MAX][MAX];

// =============== Strongly Connected Components (Kosaraju) ===============
int visited[MAX], stack[MAX], top = -1;

void dfs1(int v) {
    visited[v] = 1;
    for(int i=0;i<n;i++)
        if(graph[v][i] && !visited[i])
            dfs1(i);
    stack[++top] = v;
}

void dfs2(int v, int rev[MAX][MAX]) {
    printf("%d ", v);
    visited[v] = 1;
    for(int i=0;i<n;i++)
        if(rev[v][i] && !visited[i])
            dfs2(i, rev);
}

void SCCs() {
    memset(visited,0,sizeof(visited));
    for(int i=0;i<n;i++)
        if(!visited[i]) dfs1(i);

    int rev[MAX][MAX];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            rev[i][j] = graph[j][i]; // reverse graph

    memset(visited,0,sizeof(visited));
    printf("\nStrongly Connected Components:\n");
    while(top!=-1) {
        int v = stack[top--];
        if(!visited[v]) {
            dfs2(v, rev);
            printf("\n");
        }
    }
}

// =============== Articulation Points and Bridges (Tarjan) ===============
int disc[MAX], low[MAX], parent[MAX], timeD;

void APBUtil(int u) {
    int children=0;
    visited[u]=1;
    disc[u]=low[u]=++timeD;

    for(int v=0;v<n;v++) {
        if(!graph[u][v]) continue;

        if(!visited[v]) {
            children++;
            parent[v]=u;
            APBUtil(v);
            low[u]= (low[u]<low[v])?low[u]:low[v];

            if(parent[u]==-1 && children>1)
                printf("Articulation Point: %d\n",u);
            if(parent[u]!=-1 && low[v]>=disc[u])
                printf("Articulation Point: %d\n",u);
            if(low[v]>disc[u])
                printf("Bridge: %d-%d\n",u,v);
        }
        else if(v!=parent[u])
            low[u]= (low[u]<disc[v])?low[u]:disc[v];
    }
}

void AP_Bridges() {
    memset(visited,0,sizeof(visited));
    memset(parent,-1,sizeof(parent));
    timeD=0;
    printf("\nArticulation Points and Bridges:\n");
    for(int i=0;i<n;i++)
        if(!visited[i]) APBUtil(i);
}

// =============== Biconnected Components (DFS stack method) ===============
int edgeStack[MAX][2], etop=-1;

void BCCUtil(int u) {
    visited[u]=1;
    disc[u]=low[u]=++timeD;
    int children=0;

    for(int v=0;v<n;v++) {
        if(!graph[u][v]) continue;

        if(!visited[v]) {
            children++;
            parent[v]=u;
            edgeStack[++etop][0]=u;
            edgeStack[etop][1]=v;

            BCCUtil(v);
            low[u]= (low[u]<low[v])?low[u]:low[v];

            if((parent[u]==-1 && children>1) || (parent[u]!=-1 && low[v]>=disc[u])) {
                printf("Biconnected Component: ");
                while(edgeStack[etop][0]!=u || edgeStack[etop][1]!=v) {
                    printf("(%d-%d) ",edgeStack[etop][0],edgeStack[etop][1]);
                    etop--;
                }
                printf("(%d-%d)\n",edgeStack[etop][0],edgeStack[etop][1]);
                etop--;
            }
        }
        else if(v!=parent[u] && disc[v]<disc[u]) {
            low[u]= (low[u]<disc[v])?low[u]:disc[v];
            edgeStack[++etop][0]=u;
            edgeStack[etop][1]=v;
        }
    }
}

void BCCs() {
    memset(visited,0,sizeof(visited));
    memset(parent,-1,sizeof(parent));
    timeD=0; etop=-1;
    printf("\nBiconnected Components:\n");
    for(int i=0;i<n;i++) {
        if(!visited[i]) {
            BCCUtil(i);
            if(etop!=-1) {
                printf("Biconnected Component: ");
                while(etop!=-1) {
                    printf("(%d-%d) ",edgeStack[etop][0],edgeStack[etop][1]);
                    etop--;
                }
                printf("\n");
            }
        }
    }
}

// ================= Main ==================
int main() {
    scanf("%d %d",&n,&m);
    memset(graph,0,sizeof(graph));
    for(int i=0;i<m;i++) {
        int u,v; scanf("%d %d",&u,&v);
        graph[u][v]=1;
        graph[v][u]=1; // for articulation/bcc/bridges (undirected)
    }

    SCCs();
    AP_Bridges();
    BCCs();

    return 0;
}
