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
    Node *root = NULL;

