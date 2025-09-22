// Created by Anshumaan Soni on 22/09/2025

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

// Main Function
int main(){
    Node *trees[5];
    int select, n=0, treeindex=0;

    // Main Loop
    while (n<5){
        printf("Select from the Options below : \n");
        printf("1 - Create a new Tree \n");
        printf("2 - Insert into Tree \n");
        printf("3 - Exit \n");
        printf("Enter your choice : ");
        scanf("%d",&select);

        // Creating a new Tree
        if(select==1){
            trees[treeindex]=NULL;
            printf("Tree %d has been created. It is currently empty.\n",treeindex);
            treeindex++;
            n++;
        }
        
        // Inserting into a Tree
        else if()
    }
}

