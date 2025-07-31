#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 2 // Minimum degree (defines the range for number of keys)

typedef struct BTreeNode {
    int *keys;
    int t; // Minimum degree
    struct BTreeNode **C;
    int n;
    int leaf;
} BTreeNode;

// Create a new B-Tree node
BTreeNode *createNode(int t, int leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int *)malloc(sizeof(int) * (2 * t - 1));
    node->C = (BTreeNode **)malloc(sizeof(BTreeNode *) * (2 * t));
    node->n = 0;
    return node;
}

// Traverse the tree
void traverse(BTreeNode *root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->C[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->C[i]);
}

// Search key in subtree rooted with this node
BTreeNode *search(BTreeNode *root, int k) {
    int i = 0;
    while (i < root->n && k > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == k)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->C[i], k);
}

// Split child y of node x
void splitChild(BTreeNode *x, int i, BTreeNode *y) {
    int t = y->t;
    BTreeNode *z = createNode(t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }
    y->n = t - 1;
    for (int j = x->n; j >= i + 1; j--)
        x->C[j + 1] = x->C[j];
    x->C[i + 1] = z;
    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[t - 1];
    x->n += 1;
}

// Insert non-full
void insertNonFull(BTreeNode *x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n += 1;
    } else {
        while (i >= 0 && x->keys[i] > k)
            i--;
        if (x->C[i + 1]->n == 2 * x->t - 1) {
            splitChild(x, i + 1, x->C[i + 1]);
            if (k > x->keys[i + 1])
                i++;
        }
        insertNonFull(x->C[i + 1], k);
    }
}

// Insert key in B-Tree
void insert(BTreeNode **root, int k) {
    BTreeNode *r = *root;
    if (r->n == 2 * r->t - 1) {
        BTreeNode *s = createNode(r->t, 0);
        s->C[0] = r;
        splitChild(s, 0, r);
        int i = 0;
        if (s->keys[0] < k)
            i++;
        insertNonFull(s->C[i], k);
        *root = s;
    } else {
        insertNonFull(r, k);
    }
}

// Free B-Tree
void freeBTree(BTreeNode *root) {
    if (!root) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            freeBTree(root->C[i]);
    }
    free(root->keys);
    free(root->C);
    free(root);
}

// Example usage
int main() {
    BTreeNode *root = createNode(MIN_DEGREE, 1);
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < n; i++)
        insert(&root, keys[i]);
    printf("Traversal of the constructed tree:\n");
    traverse(root);
    printf("\n");
    int k = 6;
    (search(root, k) != NULL) ? printf("%d found\n", k) : printf("%d not found\n", k);
    freeBTree(root);
    return 0;
}