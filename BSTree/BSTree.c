#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "BSTree.h"

/* Helper to wipe out the whole tree from the bottom up */
static void freeRecursive(BSTree node) {
    if (node == NULL) {
        return;
    }
    
    freeRecursive(node->left);
    freeRecursive(node->right);
    free(node);
}

/* Recursive helper to fill the array in sorted order (Inorder) */
static void arrayInOrder (BSTree tree, int* array, int *index)
{
    if (tree == NULL) {
        return;
    }
    
    arrayInOrder(tree->left, array, index);
    
    array[*index] = tree->data;
    (*index)++;
    
    arrayInOrder(tree->right, array, index);
}

/* Allocate memory for a new node and reset pointers */
static struct treeNode* createNode(int data)
{
    struct treeNode* newNode = malloc(sizeof(struct treeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        return NULL;
    }
    
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    
    return newNode;
}

/* Convert tree to a sorted array so we can rebuild it balanced later */
static int* writeSortedToArray(const BSTree tree)
{
    int length = numberOfNodes(tree);
    int* newData = malloc(length * sizeof(int));
    
    if (newData == NULL) {
        printf("Memory allocation failed!");
        return NULL;
    }
    
    int index = 0;
    arrayInOrder(tree, newData, &index);
    
    return newData;
}

/* Rebuild the tree by picking the middle element of the sorted array */
static void buildTreeSortedFromArray(BSTree* tree, const int arr[], int size)
{
    if (tree == NULL || size <= 0) {
        return;
    }
    
    int mid = size / 2;
    *tree = createNode(arr[mid]);
    
    // Split the array into two halves for the children
    buildTreeSortedFromArray(&((*tree)->left), arr, mid);
    buildTreeSortedFromArray(&((*tree)->right), arr + mid + 1, size - mid - 1);
}

/* Starts an empty tree */
BSTree emptyTree(void)
{
    return NULL;
}

int isEmpty(const BSTree tree)
{
    if (tree == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

/* Standard iterative insertion */
void insertSorted(BSTree* tree, int data)
{
    BSTree current = *tree;
    BSTree parent = NULL;
    
    // Find where the new node belongs
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        }
        else if (data > current->data) {
            current = current->right;
        }
        else {
            return; // Already exists, skipping
        }
    }
    
    struct treeNode* newNode = createNode(data);
    
    if (parent == NULL) {
        *tree = newNode; // Tree was empty
    }
    else if (data < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    
    assert(find(*tree, data));
}

/* Printing traversals */
void printPreorder(const BSTree tree, FILE *textfile)
{
    if (tree == NULL) return;

    fprintf(textfile, "%d\n", tree->data);
    printPreorder(tree->left, textfile);
    printPreorder(tree->right, textfile);
}

void printInorder(const BSTree tree, FILE *textfile)
{
    if (tree == NULL) return;
    
    printInorder(tree->left, textfile);
    fprintf(textfile, "%d\n", tree->data);
    printInorder(tree->right, textfile);
}

void printPostorder(const BSTree tree, FILE *textfile)
{
    if (tree == NULL) return;
    
    printPostorder(tree->left, textfile);
    printPostorder(tree->right, textfile);
    fprintf(textfile, "%d\n", tree->data);
}

/* Quick BST search */
int find(const BSTree tree, int data)
{
    if (tree == NULL) {
        return 0;
    }
    else if (tree->data == data) {
        return 1;
    }
    
    if (data < tree->data) {
        return find(tree->left, data);
    }
    else {
        return find(tree->right, data);
    }
}

/* Handles the 3 cases for removal */
void removeElement(BSTree* tree, int data)
{
    if (tree == NULL || *tree == NULL) {
        return;
    }
    
    if (data < (*tree)->data) {
        removeElement(&(*tree)->left, data);
    }
    else if (data > (*tree)->data) {
        removeElement(&(*tree)->right, data);
    }
    else {
        BSTree nodeToDelete = *tree;
        
        // Cases for 0 or 1 child
        if (nodeToDelete->left == NULL) {
            *tree = nodeToDelete->right;
            free(nodeToDelete);
        }
        else if (nodeToDelete->right == NULL) {
            *tree = nodeToDelete->left;
            free(nodeToDelete);
        }
        // Case for 2 children
        else {
            BSTree successor = nodeToDelete->right;
            BSTree prevSuccessor = nodeToDelete;
            
            // Look for the smallest on the right side
            while (successor->left != NULL) {
                prevSuccessor = successor;
                successor = successor->left;
            }
            
            nodeToDelete->data = successor->data;
            
            // Fix pointers so we don't lose children of the successor
            if (prevSuccessor == nodeToDelete) {
                prevSuccessor->right = successor->right;
            }
            else {
                prevSuccessor->left = successor->right;
            }
            free(successor);
        }
    }
}

/* Count total nodes in the tree */
int numberOfNodes(const BSTree tree)
{
    if (tree == NULL) {
        return 0;
    }
   return 1 + numberOfNodes(tree->left) + numberOfNodes(tree->right);
}

/* Get the depth of the tree */
int depth(const BSTree tree)
{
    if (tree == NULL) {
        return 0;
    }
    
    int leftdepth = depth(tree->left);
    int rightdepth = depth(tree->right);
    
    return (leftdepth > rightdepth) ? (leftdepth + 1) : (rightdepth + 1);
}

/* Calculate the ideal min depth based on node count */
int minDepth(const BSTree tree)
{
    int nodes = numberOfNodes(tree);
    if (nodes == 0) return 0;
   return 1 + (int)log2(nodes);
}

/* Rebuild the tree so it is balanced */
void balanceTree(BSTree* tree)
{
    if (tree == NULL || *tree == NULL) {
        return;
    }
    
    int size = numberOfNodes(*tree);
    int *arr = writeSortedToArray(*tree);
    
    freeTree(tree); // Wipe the old mess
    buildTreeSortedFromArray(tree, arr, size); // Build it back nicely
    
    free(arr);
}

/* Cleanup function */
void freeTree(BSTree* tree)
{
    if (tree == NULL || *tree == NULL) {
        return;
    }
    
    freeRecursive(*tree);
    *tree = NULL;
    assert(*tree == NULL);
}
