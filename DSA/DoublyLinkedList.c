//
// Created by Anshumaan soni on 8/25/25.
//

#include <stdio.h>
#include <stdlib.h>


// Structure of each Node of the List
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
    int index;
} Node;

// A single function to create a new node.
Node* createNode(int val) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    node->data = val;
    node->next = NULL;
    node->prev = NULL;
    node->index = 1;
    return node;
}

// Printing the List
void print(Node* head) {
    Node* temp = head;
    printf("List : \n");
    printf("Head -> ");
    while (temp != NULL) {
        printf("%d (idx:%d) -> ", temp->data, temp->index);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Finding the Length of the Linked List
int length(Node* head) {
    int len = 0;
    Node* temp = head;
    while (temp != NULL) {
        len++;
        temp = temp->next;
    }
    return len;
}

// Updates all indices in the list. Call this after any insertion or deletion.
void updateIndices(Node* head) {
    Node* temp = head;
    int i = 1;
    while (temp != NULL) {
        temp->index = i;
        i++;
        temp = temp->next;
    }
}

void insert(int pos, int val, Node** head_ref) {
    int len = length(*head_ref);

    if (pos == -1) {
        pos = len + 1;
    }

    if (pos < 1 || pos > len + 1) {
        printf("Invalid position.\n");
        return;
    }

    Node* new_node = createNode(val);
    if (new_node == NULL) return;

    if (pos == 1) {
        new_node->next = *head_ref;
        if (*head_ref != NULL) { // If the list was not empty
            (*head_ref)->prev = new_node;
        }
        *head_ref = new_node;
    } else {
        Node* temp = *head_ref;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        new_node->next = temp->next;
        if (temp->next != NULL) { // If not inserting at the very end
            temp->next->prev = new_node;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
    updateIndices(*head_ref);
}

// Deletion of a Node from the List
void deleteNode(int pos, Node **head_ref) {
    Node *head = *head_ref;
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    int len = length(head);
    if (pos == -1) {
        pos = len;
    }

    if (pos < 1 || pos > len) {
        printf("Invalid position.\n");
        return;
    }

    Node *temp = head;
    if (pos == 1) {
        *head_ref = head->next;
        if (*head_ref != NULL) {
            (*head_ref)->prev = NULL;
        }
        free(temp);
    } else {
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        Node *node_to_delete = temp->next;
        temp->next = node_to_delete->next;
        if (node_to_delete->next != NULL) {
            node_to_delete->next->prev = temp;
        }
        free(node_to_delete);
    }
    updateIndices(*head_ref);
}

// Reverses the list and updates indices correctly.
Node *reverse(Node *head) {
    if (head == NULL) return NULL;

    Node *temp = NULL;
    Node *current = head;

    while (current != NULL) {
        temp = current->prev;

        current->prev = current->next;
        current->next = temp;
        
        current = current->prev;
    }
    if (temp != NULL) {
        head = temp->prev;
    }

    updateIndices(head);
    return head;
}

Node* concat(Node* head1, Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    Node* temp = head1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = head2;
    head2->prev = temp; // This line is now safe because we already checked if head2 is NULL

    updateIndices(head1);
    return head1;
}

int main() {
    int select = -1, listindex = 0;
    // Initialize list pointers to NULL, which correctly represents an empty list.
    Node* lists[5] = {NULL, NULL, NULL, NULL, NULL};

    while (select != 7) {
        printf("\nWhat do you want to do?\n");
        printf("1 - Create List\n");
        printf("2 - Insert\n");
        printf("3 - Delete\n");
        printf("4 - Reverse\n");
        printf("5 - Concatenate\n");
        printf("6 - Print\n");
        printf("7 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &select);

        if (select == 1) {
            if (listindex == 5) {
                printf("Maximum number of lists reached.\n");
            } else {
                printf("List %d has been created. It is currently empty.\n", listindex);
                listindex++;
            }
        }

        else if (select == 2) {
            int pos, val, listin;
            printf("Enter the ID of the list: ");
            scanf("%d", &listin);
            if (listin < 0 || listin >= listindex) {
                printf("Invalid list ID.\n");
                continue;
            }
            printf("Enter the position (-1 for end): ");
            scanf("%d", &pos);
            printf("Enter the value: ");
            scanf("%d", &val);
            insert(pos, val, &lists[listin]);
            print(lists[listin]);
        }

        else if (select == 3) {
            int pos, listin;
            printf("Enter the ID of the list: ");
            scanf("%d", &listin);
            if (listin < 0 || listin >= listindex) {
                printf("Invalid list ID.\n");
                continue;
            }
            printf("Enter the position (-1 for end): ");
            scanf("%d", &pos);
            deleteNode(pos, &lists[listin]);
            print(lists[listin]);
        }

        else if (select == 4) {
            int listin;
            printf("Enter the ID of the list: ");
            scanf("%d", &listin);
            if (listin < 0 || listin >= listindex) {
                printf("Invalid list ID.\n");
                continue;
            }
            lists[listin] = reverse(lists[listin]);
            print(lists[listin]);
        }

        else if (select == 5) {
            int listin1, listin2;
            printf("Enter the ID of the first list: ");
            scanf("%d", &listin1);
            printf("Enter the ID of the second list: ");
            scanf("%d", &listin2);
            if (listin1 < 0 || listin1 >= listindex || listin2 < 0 || listin2 >= listindex) {
                 printf("Invalid list ID.\n");
                 continue;
            }
            lists[listin1] = concat(lists[listin1], lists[listin2]);
            lists[listin2] = NULL; // The second list is now part of the first one
            print(lists[listin1]);
        }

        else if (select == 6) {
            int listin;
            printf("Enter the ID of the list: ");
            scanf("%d", &listin);
            if (listin < 0 || listin >= listindex) {
                 printf("Invalid list ID.\n");
                 continue;
            }
            print(lists[listin]);
        }
    }

    for (int i = 0; i < 5; i++) {
        Node* current = lists[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    printf("Program terminated.\n");
    return 0;
}