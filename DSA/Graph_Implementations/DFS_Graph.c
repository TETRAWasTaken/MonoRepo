#include "DFS_Graph.h"

void DFS(Graph* graph, int start) {
    if (graph == NULL || start < 0 || start >= graph->vertex) {
        printf("Invalid Graph\n");
        return;
    }

    // Initialize variables
    Stack* stack = createStack();
    bool* visited = (bool*)malloc(sizeof(bool) * graph->vertex);

    // Initialize visited array
    for (int i=0; i<graph->vertex; i++) {
        visited[i] = false;
    }

    // DFS Logic Flow
    push(stack, start);

    printf("\n----- DFS -----\n");
    while (!isEmpty(stack)) {
        int current = takeout(stack);
        if (!visited[current]) {
            visited[current] = true;
            printf("%d -> ", current);
            AdjList* pCrawl = returnList(current, graph);
            while (pCrawl != NULL) {
                int neighbour = pCrawl->dest;
                if (!visited[neighbour]) {
                    push(stack, neighbour);
                }
                pCrawl = pCrawl->next;
            }
        }
    }
    printf("\n");
    printf("----- Exiting DFS -----\n");

    freeStack(stack);
    free(visited);
}

int main() {
    int V = 15; // Number of vertices
    Graph* myGraph = createGraph(V);
    int select = 0;

    AddEdge(myGraph, 0, 1);
    AddEdge(myGraph, 0, 2);
    AddEdge(myGraph, 0, 3);
    AddEdge(myGraph, 1, 4);
    AddEdge(myGraph, 1, 5);
    AddEdge(myGraph, 2, 6);
    AddEdge(myGraph, 2, 7);
    AddEdge(myGraph, 3, 8);
    AddEdge(myGraph, 3, 9);
    AddEdge(myGraph, 4, 10);
    AddEdge(myGraph, 5, 11);
    AddEdge(myGraph, 6, 12);
    AddEdge(myGraph, 7, 13);
    AddEdge(myGraph, 8, 14);
    AddEdge(myGraph, 9, 0);  
    AddEdge(myGraph, 10, 1); 
    AddEdge(myGraph, 11, 2);
    AddEdge(myGraph, 12, 3);
    AddEdge(myGraph, 13, 4);
    AddEdge(myGraph, 14, 5);
    AddEdge(myGraph, 0, 14); 
    AddEdge(myGraph, 1, 13);
    AddEdge(myGraph, 2, 12);
    AddEdge(myGraph, 3, 11);
    AddEdge(myGraph, 4, 9);
    AddEdge(myGraph, 5, 8);
    AddEdge(myGraph, 6, 10);
    AddEdge(myGraph, 7, 0);

    printf("Graph with %d vertices created.\n", V);

    // Logic Flow
    while (1) {
        printf("\n----- Menu ------\n");
        printf(" 1 - Adjacency List\n");
        printf(" 2 - Depth First Search\n");
        printf(" -1 - Exit\n");
        scanf("%d", &select);
        printf("\n");
        if (select == 1) {
            printGraph(myGraph);
        }
        else if (select == 2) {
            int start;
            printf("Enter the starting vertex: ");
            scanf("%d", &start);
            DFS(myGraph, start);
        }
        else if (select == -1) {
            break;
        }
        else {
            printf("Invalid Input\n");
        }
    }

    // Free the allocated graph memory
    freeGraph(myGraph);

    return 0;
}