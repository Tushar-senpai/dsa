#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 4 // Maximum number of keys in a node
#define MIN (MAX/2) // Minimum number of keys in a node

typedef struct BPTreeNode {
    int keys[MAX];
    struct BPTreeNode *children[MAX+1];
    struct BPTreeNode *next; // For leaf node chaining
    int count;
    bool isLeaf;
} BPTreeNode;

BPTreeNode* createNode(bool isLeaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->isLeaf = isLeaf;
    node->count = 0;
    node->next = NULL;
    for (int i = 0; i < MAX+1; i++)
        node->children[i] = NULL;
    return node;
}

// Utility function to find the index for insertion
int findIndex(BPTreeNode* node, int key) {
    int idx = 0;
    while (idx < node->count && node->keys[idx] < key)
        idx++;
    return idx;
}

// Split child node
void splitChild(BPTreeNode* parent, int idx) {
    BPTreeNode* child = parent->children[idx];
    BPTreeNode* newChild = createNode(child->isLeaf);
    int mid = MIN;

    newChild->count = child->count - mid;
    for (int i = 0; i < newChild->count; i++)
        newChild->keys[i] = child->keys[mid + i];

    if (!child->isLeaf) {
        for (int i = 0; i <= newChild->count; i++)
            newChild->children[i] = child->children[mid + i];
    } else {
        newChild->next = child->next;
        child->next = newChild;
    }

    child->count = mid;

    for (int i = parent->count; i > idx; i--)
        parent->children[i+1] = parent->children[i];
    parent->children[idx+1] = newChild;

    for (int i = parent->count; i > idx; i--)
        parent->keys[i] = parent->keys[i-1];
    parent->keys[idx] = newChild->keys[0];
    parent->count++;
}

// Insert non-full
void insertNonFull(BPTreeNode* node, int key) {
    int idx = findIndex(node, key);
    if (node->isLeaf) {
        for (int i = node->count; i > idx; i--)
            node->keys[i] = node->keys[i-1];
        node->keys[idx] = key;
        node->count++;
    } else {
        if (node->children[idx]->count == MAX) {
            splitChild(node, idx);
            if (key > node->keys[idx])
                idx++;
        }
        insertNonFull(node->children[idx], key);
    }
}

// Insert key into B+ Tree
void insert(BPTreeNode** root, int key) {
    BPTreeNode* r = *root;
    if (r->count == MAX) {
        BPTreeNode* s = createNode(false);
        s->children[0] = r;
        splitChild(s, 0);
        int idx = (key > s->keys[0]) ? 1 : 0;
        insertNonFull(s->children[idx], key);
        *root = s;
    } else {
        insertNonFull(r, key);
    }
}

// Search key in B+ Tree
bool search(BPTreeNode* node, int key) {
    int idx = findIndex(node, key);
    if (node->isLeaf) {
        if (idx < node->count && node->keys[idx] == key)
            return true;
        return false;
    }
    return search(node->children[idx], key);
}

// Print B+ Tree (level order)
void printTree(BPTreeNode* root) {
    BPTreeNode* curr = root;
    while (!curr->isLeaf)
        curr = curr->children[0];
    while (curr) {
        for (int i = 0; i < curr->count; i++)
            printf("%d ", curr->keys[i]);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    BPTreeNode* root = createNode(true);
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < n; i++)
        insert(&root, keys[i]);
    printTree(root);

    int searchKey = 12;
    if (search(root, searchKey))
        printf("Key %d found.\n", searchKey);
    else
        printf("Key %d not found.\n", searchKey);

    return 0;
}