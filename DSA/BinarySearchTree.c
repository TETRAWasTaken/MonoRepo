// Created by Anshumaan Soni on 22/09/2025

// Imports
#include <stdio.h>
#include <stdlib.h>

// Defining the structure of a Node
typedef struct node{
    int data;
    struct node *left;
    struct node *right;
} Node;

// Creating and allocating memory for Node
Node* createNode(int val){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Searching a Node in the tree
Node* search(Node *root, int val){
    if(root==NULL || root->data==val) {
        return root;
    }
    if(root->data<val) {
        return search(root->right, val);
    }
    else {
        return search(root->left, val);
    }
}

// Inserting a Node in the tree
Node* insert(Node *root, int val){
    // Creating a new Node
    Node *newNode = createNode(val);

    // Checking is the Tree is Empty
    if(root==NULL){
        root=newNode;
        return root;
    }

    // Finding the best location for the Node
    
    if(root->data<val){
        root->right = insert(root->right, val);
    }
    else if(root->data>val){
        root->left = insert(root->left, val);
    }
    else {
        return root;
    }
}

// Inorder Traversal of the Tree
void inorder(Node *root){
    if(root==NULL) return;

    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}

// Postorder Traversal of the Tree
void postorder(Node *root){
    if(root==NULL) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
}

// Preorder Traversal of the Tree
void preorder(Node *root){
    if(root==NULL) return;
    
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
}

// Main Function
int main(){
    Node *trees[5];
    int select, n=0, treeindex=0;

    // Main Loop
    while (n<5){
        printf("Select from the Options below : \n");
        printf("1 - Create a new Tree \n");
        printf("2 - Insert into Tree \n");
        printf("3 - Print Inorder Traversal of Tree \n");
        printf("4 - Print Preorder Traversal of Tree \n");
        printf("5 - Print Postorder Traversal of Tree \n");
        printf("6 - Search a value in the Tree \n");
        printf("9 - Exit \n");
        printf("Enter your choice : ");
        scanf("%d",&select);

        // Creating a new Tree
        if(select==1){
            trees[treeindex]=NULL;
            printf("---- Tree %d has been created. It is currently empty.\n\n",treeindex);
            treeindex++;
            n++;
        }
        
        // Inserting into a Tree
        else if(select==2){
            int num, treein;
            printf("Enter the ID of the Tree : ");
            scanf("%d",&treein);
            if(treein<0 || treein>=treeindex){
                printf("Invalid Tree ID.\n");
                continue;
            }
            printf("Enter the number of numbers to be inserted : ");
            scanf("%d",&num);
            for(int i=0;i<num;i++){
                int val;
                printf(" Val - ");
                scanf("%d",&val);
                trees[treein] = insert(trees[treein], val);
            }
            n++;
        }

        // Inorder Traversal of a Tree
        else if(select==3){
            int treein;
            printf("Enter the ID of the Tree : ");
            scanf("%d",&treein);
            if(treein<0 || treein>=treeindex){
                printf("Invalid Tree ID.\n");
                continue;
            }
            printf("---- Inorder Traversal of Tree %d : ",treein);
            inorder(trees[treein]);
            printf("\n\n");
            n++;
        }

        // Preorder Traversal of a Tree
        else if(select==4){
            int treein;
            printf("Enter the ID of the Tree : ");
            scanf("%d",&treein);
            if(treein<0 || treein>=treeindex){
                printf("Invalid Tree ID.\n");
                continue;
            }
            printf("---- Preorder Traversal of Tree %d : ",treein);
            preorder(trees[treein]);
            printf("\n\n");
            n++;
        }

        // Postorder Traversal of a Tree
        else if(select==5){
            int treein;
            printf("Enter the ID of the Tree : ");
            scanf("%d",&treein);
            if(treein<0 || treein>=treeindex){
                printf("Invalid Tree ID.\n");
                continue;
            }
            printf("---- Postorder Traversal of Tree %d : ",treein);
            postorder(trees[treein]);
            printf("\n\n");
            n++;
        }

        // Searching a value in the Tree
        else if(select==6){
            int val, treein;
            printf("Enter the ID of the Tree : ");
            scanf("%d",&treein);
            if(treein<0 || treein>=treeindex){
                printf("Invalid Tree ID.\n");
                continue;
            }
            printf("Enter the value to be searched : ");
            scanf("%d",&val);
            Node *res = search(trees[treein], val);
            if(res==NULL){
                printf("---- Value %d not found in Tree %d.\n\n", val, treein);
            }
            else{
                printf("---- Value %d found in Tree %d.\n\n", val, treein);
            }
            n++;
        }

        // Exiting the Program
        else if(select==9){
            break;
        }

        else{
            printf("---- Invalid Choice.\n\n");
            n++;
        }
    }
    return 0;
}
