#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *prev;
    int data;
    struct Node *next;
} node;

node *head = NULL;
node *tail = NULL;

/* Create node */
node* createnode(int data) {
    node *temp = (node*)malloc(sizeof(node));
    if (temp == NULL) {
        printf("Heap overflow!\n");
        return NULL;
    }
    temp->prev = NULL;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

/* Insert at end */
void insert(int value) {
    node *temp = createnode(value);
    if (temp == NULL) return;

    if (head == NULL) {
        head = tail = temp;
        return;
    }

    tail->next = temp;
    temp->prev = tail;
    tail = temp;
}

/* Print forward */
void print_forward() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    node *temp = head;
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* Print backward */
void print_backward() {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }

    node *temp = tail;
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

/* Find Nth node from end */
void Find_Nth_Node_from_end(int N) {
    if (head == NULL) {
        printf("Empty list!\n");
        return;
    }

    if (N <= 0) {
        printf("Invalid position!\n");
        return;
    }

    node *temp = tail;
    int count = 1;

    while (temp != NULL && count < N) {
        temp = temp->prev;
        count++;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
    } else {
        printf("Nth node from end = %d\n", temp->data);
    }
}

/* Rotate right by 1 */
void Rotate_right() {
    if (head == NULL || head->next == NULL) {
        printf("Rotation not possible\n");
        return;
    }

    node *last = tail;

    tail = tail->prev;
    tail->next = NULL;

    last->prev = NULL;
    last->next = head;
    head->prev = last;

    head = last;
}

/* Rotate left by 1 */
void Rotate_left() {
    if (head == NULL || head->next == NULL) {
        printf("Rotation not possible\n");
        return;
    }

    node *first = head;

    head = head->next;
    head->prev = NULL;

    first->next = NULL;
    first->prev = tail;
    tail->next = first;

    tail = first;
}

/* MAIN */
int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);

    print_forward();
    print_backward();

    Find_Nth_Node_from_end(3);

    Rotate_right();
    print_forward();

    Rotate_left();
    print_forward();

    return 0;
}
