#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the adjacency listkz
typedef struct node 
{
    int INFO;
    struct node *NEXT;
} NODE;

// Function to insert an edge (u, v) into the graph
void insert_edge(NODE* GRAPH[], int N, int u, int v) 
{
    if (u >= 0 && v >= 0 && u < N && v < N) 
    {
        NODE *new_node = (NODE*)malloc(sizeof(NODE));
        new_node->INFO = v;
        new_node->NEXT = NULL;

        if (GRAPH[u] == NULL) 
        {
            GRAPH[u] = new_node;
        } 
        else 
        {
            // Inserting at the beginning of the list for O(1) insertion
            new_node->NEXT = GRAPH[u];
            GRAPH[u] = new_node;
        }

        if (new_node != NULL) 
            printf("(%d,%d) Inserted!\n", u, v);
        else 
            printf("Insertion Failed!!!\n");
    }
}

// Function to delete an edge (u, v) from the graph
void delete_edge(NODE* GRAPH[], int N, int u, int v) 
{
    if (u >= 0 && v >= 0 && u < N && v < N) 
    {
        if (GRAPH[u] == NULL) 
        {
            printf("Edge doesn't exist!\n");
        } 
        else if (GRAPH[u]->INFO == v) 
        {
            NODE *ptr = GRAPH[u];
            GRAPH[u] = GRAPH[u]->NEXT;
            free(ptr);
            printf("(%d,%d) Deleted!\n", u, v);
        } 
        else 
        {
            NODE *curr_ptr = GRAPH[u]->NEXT;
            NODE *prev_ptr = GRAPH[u];
            while (curr_ptr != NULL) 
            {
                if (curr_ptr->INFO == v) 
                {
                    prev_ptr->NEXT = curr_ptr->NEXT;
                    free(curr_ptr);
                    printf("(%d,%d) Deleted!\n", u, v);
                    return;
                }
                prev_ptr = curr_ptr;
                curr_ptr = curr_ptr->NEXT;
            }
            printf("(%d,%d) Not Found!\n", u, v);
        }
    }
}

// Function to search for an edge (u, v)
void search_edge(NODE* GRAPH[], int N, int u, int v) 
{
    if (u >= 0 && v >= 0 && u < N && v < N) 
    {
        if (GRAPH[u] == NULL) 
        {
            printf("Edge doesn't exist!\n");
        } 
        else 
        {
            NODE *curr_ptr = GRAPH[u];
            while (curr_ptr != NULL) 
            {
                if (curr_ptr->INFO == v) 
                {
                    printf("(%d,%d) Found!\n", u, v);
                    return;
                }
                curr_ptr = curr_ptr->NEXT;
            }
            printf("(%d,%d) Not Found!\n", u, v);
        }
    }
}

// Function to print the entire adjacency list
void print(NODE* GRAPH[], int N) 
{
    printf("\n");
    for (int i = 0; i < N; i++) 
    {
        NODE *curr_ptr = GRAPH[i];
        printf("Vertex %d : ", i);
        while (curr_ptr != NULL) 
        {
            printf("%d ", curr_ptr->INFO);
            curr_ptr = curr_ptr->NEXT;
        }
        printf("\n");
    }
    printf("\n");
}

int main() 
{
    int N = 7;
    // Allocating an array of pointers to NODE
    NODE** GRAPH = (NODE**)calloc(N, sizeof(NODE*));

    // Initial Insertions
    insert_edge(GRAPH, N, 0, 1);
    insert_edge(GRAPH, N, 0, 2);
    insert_edge(GRAPH, N, 0, 3);
    insert_edge(GRAPH, N, 1, 4);
    insert_edge(GRAPH, N, 1, 5);
    insert_edge(GRAPH, N, 2, 5);
    insert_edge(GRAPH, N, 2, 6);
    insert_edge(GRAPH, N, 3, 6);
    insert_edge(GRAPH, N, 4, 0);
    insert_edge(GRAPH, N, 5, 3);
    insert_edge(GRAPH, N, 5, 6);
    insert_edge(GRAPH, N, 6, 1);

    printf("\nGraph after insertions:\n");
    print(GRAPH, N);

    // Searching
    search_edge(GRAPH, N, 0, 1); // Should be found
    search_edge(GRAPH, N, 1, 6); // Not found
    search_edge(GRAPH, N, 6, 1); // Should be found
    search_edge(GRAPH, N, 3, 5); // Not found

    // Deletions
    delete_edge(GRAPH, N, 0, 3); // Delete existing
    delete_edge(GRAPH, N, 2, 5); // Delete existing
    delete_edge(GRAPH, N, 1, 6); // Attempt non-existent

    printf("\nGraph after deletions:\n");
    print(GRAPH, N);

    // Final Insertions
    insert_edge(GRAPH, N, 2, 7); // Should fail (out of bounds)
    insert_edge(GRAPH, N, 3, 3);
    insert_edge(GRAPH, N, 5, 4);
    insert_edge(GRAPH, N, 3, 4);

    print(GRAPH, N);

    return 0;
}