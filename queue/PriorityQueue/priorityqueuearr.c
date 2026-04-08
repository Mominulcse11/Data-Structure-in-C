#include<stdio.h>

#define MAX 100

typedef struct {
    int data;
    int priority;
} item;

item pq[MAX];
int size = 0;

// Insert (sorted by priority)
void insert(int value, int priority){
    if(size == MAX){
        printf("Overflow\n");
        return;
    }
    int i = size - 1;

    // shift elements
    while(i >= 0 && pq[i].priority > priority){
        pq[i+1] = pq[i];
        i--;
    }

    pq[i+1].data = value;
    pq[i+1].priority = priority;
    size++;
}

// Delete (highest priority = first element)
void delete(){
    if(size == 0){
        printf("Underflow\n");
        return;
    }

    printf("Deleted: %d\n", pq[0].data);

    for(int i = 0; i < size-1; i++){
        pq[i] = pq[i+1];
    }
    size--;
}

// Front
void front(){
    if(size == 0){
        printf("Empty\n");
        return;
    }
    printf("Front: %d\n", pq[0].data);
}

// Rear
void rear(){
    if(size == 0){
        printf("Empty\n");
        return;
    }

    printf("Rear: %d\n", pq[size-1].data);
}

// Print
void print(){
    if(size == 0){
        printf("Empty\n");
        return;
    }

    printf("Queue: ");
    for(int i = 0; i < size; i++){
        printf("(%d,p=%d) ", pq[i].data, pq[i].priority);
    }
    printf("\n");
}

int main(){
    insert(12,5);
    insert(15,2);
    insert(5,7);

    print();
    front();
    rear();

    delete();
    print();
    rear();

    insert(7,1);
    print();
    front();

    delete();
    print();
    rear();

    insert(52,3);
    delete();
    insert(101,6);

    print();

    return 0;
}