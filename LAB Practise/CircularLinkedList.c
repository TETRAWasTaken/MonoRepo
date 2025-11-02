#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* createNode(int val){
    Node* node = (node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->data = val;
    node->next = node;
    return node;
}

void print(const Node* head) {
    if(head==NULL){
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

void insert(int pos, int val, Node** head_ref){
    Node* head = *head_ref;
    int len = length(head);

    if (pos < 1 || pos > len + 1) {
        printf("Invalid position.\n");
        return;
    }

    Node* new_node = createNode(val);
    if (pos==1) {
        if (head == NULL) {
            *head_ref = new_node;
        } else {
            Node* last_node = head;
            while(last_node->next != head) {
                last_node = last_node->next;
            }
            new_node->next = head;
            last_node->next = new_node;
            *head_ref = new_node;
        }
    } else {
        Node* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

void deleteNode(int pos, Node** head_ref){
    Node* head = *head_ref;
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    int len = length(head);
    if (pos < 1 || pos > len) {
        printf("Invalid position.\n");
        return;
    }

    if (len == 1 && pos == 1) {
        free(head);
        *head_ref = NULL;
        return;
    }

    if (pos == 1) {
        Node* last_node = head;
        while(last_node->next != head) {
            last_node = last_node->next;
        }
        Node* node_to_delete = head;
        *head_ref = head->next;
        last_node->next = *head_ref;
        free(node_to_delete);
    } else {
        Node* temp = head;
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }
        Node* node_to_delete = temp->next;
        temp->next = node_to_delete->next;
        free(node_to_delete);
    }
}

Node* reverse(Node* head){
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

    head->next = prev;

    return prev;
}

Node* concat(Node* head1, Node* head2){
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    Node* tail1 = head1;
    while (tail1->next != head1) {
        tail1 = tail1->next;
    }

    Node* tail2 = head2;
    while (tail2->next != head2) {
        tail2 = tail2->next;
    }

    tail1->next = head2;
    tail2->next = head1;

    return head1;
}

int main(){
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
            select = 0;
            continue;
        }
        if (select == 1) {
            if (listindex >= MAX_LISTS) {
                printf("Maximum number of lists reached.\n");
                continue;
            }
            lists[listindex] = NULL;
            printf("Created list with ID %d.\n", listindex);
            listindex++;
        }
        else if (select == 2) {
            int listin, pos, val;
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
            printf("Enter position to insert: ");
            if (scanf("%d", &pos) != 1) {
                printf("Invalid input for position.\n");
                clear_input_buffer();
                continue;
            }
            printf("Enter value to insert: ");
            if (scanf("%d", &val) != 1) {
                printf("Invalid input for value.\n");
                clear_input_buffer();
                continue;
            }
            insert(pos, val, &lists[listin]);
            print(lists[listin]);
        }
        else if (select == 3) {
            int listin, pos;
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
            printf("Enter position to delete: ");
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
            lists[listin1] = concat(lists[listin1], lists[listin2]);
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

    // Free all allocated memory
    for (int i = 0; i < listindex; i++) {
        free_list(lists[i]);
    }

    return 0;
}