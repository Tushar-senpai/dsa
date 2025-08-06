#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 1000000

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void union_set(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int cmp(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->w - e2->w;
}

void kruskal(Edge edges[], int n, int e) {
    int i, count = 0, cost = 0;
    for (i = 0; i < n; i++)
        parent[i] = i;

    qsort(edges, e, sizeof(Edge), cmp);

    printf("Edges in MST:\n");
    for (i = 0; i < e && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v)) {
            printf("%d - %d : %d\n", u, v, w);
            union_set(u, v);
            cost += w;
            count++;
        }
    }
    printf("Total cost: %d\n", cost);
}

int main() {
    int n, e, i;
    Edge edges[MAX];

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    printf("Enter edges (u v w):\n");
    for (i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    kruskal(edges, n, e);

    return 0;
}
// This code implements Kruskal's algorithm to find the Minimum Spanning Tree (MST) of a graph.
// It uses a union-find data structure to efficiently manage the connected components of the graph.