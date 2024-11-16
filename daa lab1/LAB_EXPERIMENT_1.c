#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

// Define structure for a node in the BST
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* newNode(int key) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

// Recursive function to insert a new key in the Binary search tree
struct Node* insertRec(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insertRec(node->left, key);
    else if (key > node->key)
        node->right = insertRec(node->right, key);

    return node;
}

// Iterative function to insert a new key in the Binary Search Tree
struct Node* insertIter(struct Node* root, int key) {
    struct Node* new_node = newNode(key);

    if (root == NULL)
        return new_node;

    struct Node* parent = NULL;
    struct Node* current = root;

    while (current != NULL) {
        parent = current;

        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return root; 
    }

    if (key < parent->key)
        parent->left = new_node;
    else
        parent->right = new_node;

    return root;
}

// In-order traversal of the tree to display elements in sorted order
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
// post oder traversal of the tree
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}
// pre order traversal of the tree 
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to input user data
void manualDataInput(struct Node** root, int mode) {
    int n, key;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);

    // Start the clock timing
    start = clock();

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &key);

        if (mode == 1) {
            // Recursive insertion
            *root = insertRec(*root, key);
        } else if (mode == 2) {
            // Iterative insertion
            *root = insertIter(*root, key);
        } else {
            printf("Invalid mode!\n");
            return;
        }
    }
    end = clock();

    // to Calculate the time taken for the insertion 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken for insertion: %f seconds\n", cpu_time_used);
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice;

    printf("Choose insertion method:\n");
    printf("1. Recursive Insertion\n");
    printf("2. Iterative Insertion\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Manual data input and measure time
    manualDataInput(&root, choice);

    // Display the BST using in-order traversal
    printf("In-order traversal of the BST   : ");
    inorder(root);
    printf("\n");
    printf("post order traversal of the BST : ");
    postorder(root);
    printf("\n");
    printf("pre order traversal of the BST  : ");
    preorder(root);
    return 0;
}
