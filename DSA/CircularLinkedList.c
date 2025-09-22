//
// Created by Anshumaan soni on 9/4/25.
//
#include <stdio.h>
#include <stdlib.h>

// The structure of a Node in the list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Creating and allocating the memory for a Node
Node* createNode(int val) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE); // Exit on failure
    }
    node->data = val;
    node->next = node;
    return node;
}

// Prints the circular linked list.
void print(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* temp = head;
    printf("List : \n");
    printf("Head -> ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("Head\n");
}

// Calculates the length of the circular linked list.
int length(Node* head) {
    if (head == NULL) {
        return 0;
    }
    int len = 0;
    Node* temp = head;
    do {
        temp = temp->next;
        len++;
    } while (temp != head);
    return len;
}

// Inserts a node at a specified position in the circular linked list.
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

    // Case 1: Inserting into an empty list
    if (*head_ref == NULL) {
        *head_ref = new_node;
        new_node->next = new_node;
        return;
    }

    // Case 2: Inserting at the beginning
    if (pos == 1) {
        Node* last_node = *head_ref;
        while(last_node->next != *head_ref) {
            last_node = last_node->next;
        }
        new_node->next = *head_ref;
        last_node->next = new_node;
        *head_ref = new_node;
    }
    // Case 3: Inserting in the middle or at the end
    else {
        Node* temp = *head_ref;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

// Deletes a node at a specified position.
void deleteNode(int pos, Node** head_ref) {
    Node* head = *head_ref;
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

    // Case 1: Deleting the only node
    if (len == 1 && pos == 1) {
        free(head);
        *head_ref = NULL;
        return;
    }

    // Case 2: Deleting the first node
    if (pos == 1) {
        Node* last_node = head;
        while(last_node->next != head) {
            last_node = last_node->next;
        }
        *head_ref = head->next;
        last_node->next = *head_ref;
        free(head);
    }
    // Case 3: Deleting from the middle or end
    else {
        Node* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        Node* node_to_delete = temp->next;
        temp->next = node_to_delete->next;
        free(node_to_delete);
    }
}

// Reverses the circular linked list.
Node* reverse(Node* head) {
    if (head == NULL) return NULL;

    Node *prev = NULL;
    Node *current = head;
    Node *next_node = NULL;

    // Store the last node to update its next pointer
    Node* last_node = head;
    while(last_node->next != head) {
        last_node = last_node->next;
    }

    do {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    } while (current != head);

    // Update the last node's next pointer to the new head (prev)
    last_node->next = prev;

    return prev;
}

// Concatenates two circular linked lists.
Node* concat(Node* head1, Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    Node* last1 = head1;
    while (last1->next != head1) {
        last1 = last1->next;
    }

    Node* last2 = head2;
    while (last2->next != head2) {
        last2 = last2->next;
    }

    last1->next = head2;
    last2->next = head1;

    return head1;
}

// Main function for user interaction.
int main() {
    int select = -1, listindex = 0;
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
            lists[listin2] = NULL;
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

    // Clean up all lists
    for (int i = 0; i < 5; i++) {
        if (lists[i] != NULL) {
            Node* current = lists[i];
            Node* head_to_free = current;
            do {
                Node* temp = current;
                current = current->next;
                free(temp);
            } while (current != head_to_free && current != NULL);
            lists[i] = NULL;
        }
    }
    printf("Program terminated.\n");
    return 0;
}