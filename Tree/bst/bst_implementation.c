#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))


typedef struct bst_node {
    int data;
    struct bst_node* left;
    struct bst_node* right;
} Node;



Node* insert(Node* root, int data) {
    if (root == NULL){
        Node* newNode = (Node*)malloc(sizeof(Node));
         if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
         }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    printf("%d inserted \n", data);
    return newNode;
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else 
        root->right = insert(root->right, data);

    return root;
}

void search (Node* root,int value)
{
    if (root==NULL)
        printf("%d not present in the tree!!\n", value);
    else if(value==root->data)
        printf("Element %d is present in the tree!!\n", value);
    else if(value<root->data)
        search (root->left, value);
    else
        search (root->right, value);
}
Node* findmax(Node* root){
      if (root == NULL){
        return NULL;
      }
      if(root->right==NULL){
          return root;
      }

      return findmax(root->right);
}
Node* findMin(Node* root) {
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;

    return root;
}

Node* delete(Node* root, int value) {
    if (root == NULL) {
        printf("Empty Tree!\n");
        return root;
    }
    
    if (value < root->data) {
        root->left = delete(root->left, value);
    } else if (value > root->data) {
        root->right = delete(root->right, value);
    } else {
        Node *ptr;
        // Case 1 & 2: Node with only one child or no child
        if (root->left == NULL) {
            ptr = root;
            root = root->right;
            free(ptr);
            printf("%d is Deleted!\n", value);
            return root;
        } else if (root->right == NULL) {
            ptr = root;
            root = root->left;
            free(ptr);
            printf("%d is Deleted!\n", value);
            return root;
        }
        
        // Case 3: Node with two children
        // Using inorder successor (smallest in the right subtree)
        ptr = root->right;
        while (ptr->left != NULL) {
            ptr = ptr->left;
        }
        
        root->data = ptr->data;
        root->right = delete(root->right, ptr->data);
    }
    return root;
}
void mirror(Node* root) {
    if (root == NULL)
        return;

    // swap
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}
int countNodes(Node* root) {
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}
int countLeafNodes(Node* root) {
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeafNodes(root->left) + countLeafNodes(root->right);
}
int nodewith_onechild(Node* root){
    if(root==NULL){
        return 0;
    }
    if((root->left==NULL && root->right !=NULL)|| (root->left!=NULL && root->right ==NULL)){
        return 1;
    }
    return nodewith_onechild(root->right) + nodewith_onechild(root->left);
}
int sumNodes(Node* root) {
    if (root == NULL)
        return 0;

    return root->data + sumNodes(root->left) + sumNodes(root->right);
}
int height(Node* root){
    if(root == NULL){
        return 0;

    }

    return 1 + MAX(height(root->right), height(root->left));
}
int isBalanced(Node* root) {
    if (root == NULL) return 1;

    int lh = height(root->left);
    int rh = height(root->right);

    if (abs(lh - rh) <= 1 && isBalanced(root->left) && isBalanced(root->right))
        return 1;

    return 0;
}

void inorder(Node * root)
    { 
        if (root != NULL)
        {
            inorder(root->left);
            printf("%d ", root->data);
            inorder(root->right);
        }
}

void printDecreasing(Node* root) {
    if (root == NULL)
        return;

    printDecreasing(root->right);
    printf("%d ", root->data);
    printDecreasing(root->left);
}
/*Inorder → increasing
Reverse inorder → decreasing*/

void preorder(Node* root) {
    if (root != NULL){
        printf("%d ", root->data);
    preorder(root->left);
    
    preorder(root->right);
    }
}// Corrected Post-order: Left -> Right -> Root
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void display (Node* root ){
    if (root == NULL) return;
    if(root->left!=NULL){
        display(root->left);
    }
    printf("%d " ,root->data);
    if(root->right!=NULL){
        display(root->right);
    }
}

void freeTree(Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() // Changed to int main() as per C standards
{
    Node* root = NULL; // Type set to Node* to match your struct
    root = insert(root, 50);
    root = insert(root, 38);
    root = insert(root, 78);
    root = insert(root, 20);
    root = insert(root, 48);
    root = insert(root, 68);
    root = insert(root, 88);

    printf("In-order before deletion: ");
    inorder(root);
    printf("\n");
    printf("Pre-order before deletion: ");
    preorder(root);
    printf("\n");
    printf("Post-order before deletion: ");
    postorder(root);
    printf("\n");

    search(root, 68); // Should be found
    search(root, 100); // Should NOT be found

    root = delete(root, 20); // Using the deleteNode function from your code
    printf("In-order after deleting 20: ");
    inorder(root);
    printf("\n");

    // Delete a node with one child
    printf("Deleting 30 (node with one child)...\n");
    root = delete(root, 30);
    printf("In-order after deleting 30: ");
    inorder(root);
    printf("\n");

    // Delete a node with two children
    printf("Deleting 50 (node with two children)...\n");
    root = delete(root, 50);
    printf("In-order after deleting 50: ");
    inorder(root);
    printf("\n");

    printf("Displaying Tree: ");
    display(root);
    printf("\n");

    root = insert(root, 65);
    root = insert(root, 55);
    root = insert(root, 75);

    printf("Total Nodes: %d\n", countNodes(root));

    printf("Leaf Nodes: %d\n", countLeafNodes(root));

    printf("Leaf Nodes with one child: %d\n", nodewith_onechild(root));

    printf("Sum of Nodes: %d\n", sumNodes(root));

    printf("Height of the   tree: %d\n", height(root));

    printf("Total Nodes in left subtree: %d\n", countNodes(root->left));

    printf("Total Nodes in right subtree: %d\n", countNodes(root->right));

    printf("Is the tree balanced -------%s\n",(isBalanced(root)==1)? "Yes":"No");

        printf("In-order after inserting 65, 55, 75: ");
    inorder(root);
    printf("\n");

    printf("Searching 55: \n");
    search(root, 55); 
    printf("Searching 22: \n");
    search(root, 22); 

    printf("Final Pre-order: ");
    preorder(root);
    printf("\n");

    printf("Final Post-order: ");
    postorder(root);
    printf("\n");

    mirror(root);
    display(root);

    return 0;
}