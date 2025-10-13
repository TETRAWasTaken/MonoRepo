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
void print(const Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    const Node* temp = head;
    printf("List : \n");
    printf("Head -> ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("Head\n");
}

// Calculates the length of the circular linked list.
int length(const Node* head) {
    if (head == NULL) {
        return 0;
    }
    int len = 0;
    const Node* temp = head;
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
        Node* node_to_delete = head;
        *head_ref = head->next;
        last_node->next = *head_ref;
        free(node_to_delete);
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
    if (head == NULL) {
        return NULL;
    }

    Node *prev = NULL;
    Node *current = head;
    Node *next_node;

    do {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    } while (current != head);

    // After the loop, `prev` is the new head, and `head` (the original head) is the new tail.
    // Connect the new tail to the new head to restore the circular link.
    head->next = prev;

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

// Clears the input buffer after a failed scanf
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Main function for user interaction.
int main() {
    const int MAX_LISTS = 5;
    int select = -1, listindex = 0;
    Node* lists[MAX_LISTS] = {NULL};

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
        if (scanf("%d", &select) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            select = 0; // Set to a non-exit value to continue loop
            continue;
        }


        if (select == 1) {
            if (listindex == MAX_LISTS) {
                printf("Maximum number of lists reached.\n");
            } else {
                printf("List %d has been created. It is currently empty.\n", listindex);
                listindex++;
            }
        }
        else if (select == 2) {
            int pos, val, listin;
            printf("Enter the ID of the list: ");
            if (scanf("%d", &listin) != 1) {
                printf("Invalid input for list ID.\n");
                clear_input_buffer();
                continue;
            }
            if (listin < 0 || listin >= listindex) {
                printf("Invalid list ID.\n");
                continue;
            }
            printf("Enter the position (-1 for end): ");
             if (scanf("%d", &pos) != 1) {
                printf("Invalid input for position.\n");
                clear_input_buffer();
                continue;
            }
            printf("Enter the value: ");
            if (scanf("%d", &val) != 1) {
                printf("Invalid input for value.\n");
                clear_input_buffer();
                continue;
            }
            insert(pos, val, &lists[listin]);
            print(lists[listin]);
        }
        else if (select == 3) {
            int pos, listin;
            printf("Enter the ID of the list: ");
            if (scanf("%d", &listin) != 1) {
                printf("Invalid input for list ID.\n");
                clear_input_buffer();
                continue;
            }
            if (listin < 0 || listin >= listindex) {
                printf("Invalid list ID.\n");
                continue;
            }
            printf("Enter the position (-1 for end): ");
            if (scanf("%d", &pos) != 1) {
                printf("Invalid input for position.\n");
                clear_input_buffer();
                continue;
            }
            deleteNode(pos, &lists[listin]);
            print(lists[listin]);
        }
        else if (select == 4) {
            int listin;
            printf("Enter the ID of the list: ");
            if (scanf("%d", &listin) != 1) {
                printf("Invalid input for list ID.\n");
                clear_input_buffer();
                continue;
            }
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
            if (scanf("%d", &listin1) != 1) {
                printf("Invalid input for list ID.\n");
                clear_input_buffer();
                continue;
            }
            printf("Enter the ID of the second list: ");
            if (scanf("%d", &listin2) != 1) {
                printf("Invalid input for list ID.\n");
                clear_input_buffer();
                continue;
            }
            if (listin1 < 0 || listin1 >= listindex || listin2 < 0 || listin2 >= listindex) {
                printf("Invalid list ID.\n");
                continue;
            }
            if (listin1 == listin2) {
                printf("Cannot concatenate a list with itself.\n");
                continue;
            }
            lists[listin1] = concat(lists[listin1], lists[listin2]);
            lists[listin2] = NULL;
            print(lists[listin1]);
        }
        else if (select == 6) {
            int listin;
            printf("Enter the ID of the list: ");
            if (scanf("%d", &listin) != 1) {
                printf("Invalid input for list ID.\n");
                clear_input_buffer();
                continue;
            }
            if (listin < 0 || listin >= listindex) {
                printf("Invalid list ID.\n");
                continue;
            }
            print(lists[listin]);
        }
    }

    // Correctly clean up all lists to prevent memory leaks and use-after-free
    for (int i = 0; i < MAX_LISTS; i++) {
        Node* head = lists[i];
        if (head != NULL) {
            Node* current = head->next;
            // Free all nodes except the head
            while (current != head) {
                Node* temp = current;
                current = current->next;
                free(temp);
            }
            // Free the head node last
            free(head);
            lists[i] = NULL;
        }
    }
    printf("Program terminated.\n");
    return 0;
}