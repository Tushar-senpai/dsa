#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int adj[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int n; // Number of vertices

void dfs(int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int edges, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1; // For undirected graph
    }

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("DFS traversal starting from vertex 0:\n");
    dfs(0);

    return 0;
}