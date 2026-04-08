#include<stdio.h>
#include<limits.h>
#define MAX_SIZE 1000

int heap[MAX_SIZE];
int heapSize = 0;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
/*❑Put the new node in the next available spot.
❑Push the new node
upward, swapping with its parent until the new node reaches an acceptable location.*/
void shiftUp(int index);
void insert(int value){
    if(heapSize>=MAX_SIZE){
        printf("Heap is full !\n");
        return;
    }
    heap[heapSize] = value;
    shiftUp(heapSize);
    heapSize++;
}
/*❑The parent has a key that is >= new node, or
❑The node reaches the root.
❑The process of pushing the new node upward is called reheapification upward/shift Up.*/
void shiftUp(int index){
    while(index>0 && heap[(index - 1)/ 2]<heap[index]){  /*Min Heap:,while(index > 0 && heap[(index - 1)/2] > heap[index])*/ 
        swap(&heap[(index - 1) / 2], &heap[index]);
        index = (index - 1) / 2;
    }
}
/*❑Move the last node
onto the root.
❑Push the out-of-place node downward, swapping with its larger child until the new node reaches an acceptable location.*/
void shiftDown(int index);
int removeTop(){
    if(heapSize==0){
        printf("Heap is empty! \n");
        return INT_MIN;
    }
    int max = heap[0];
    heap[0] = heap[--heapSize];
    shiftDown(0);
    return max;
}
/*❑The children all have keys <= the out-of-place node, or
❑The node reaches the leaf.
❑The process of pushing the new node downward is called reheapification downward/shift Down.*/
void shiftDown(int index){
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left<heapSize && heap[left] > heap[largest] ){
        largest = left;
    }

    if(right <heapSize && heap[right] > heap[largest] ){
        largest = right;
    }

    if(largest != index){
        swap(&heap[index], &heap[largest]);
        shiftDown(largest);
    }
}
/*Min heap void shiftDown(int index){
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < heapSize && heap[left] < heap[smallest]){
        smallest = left;
    }

    if(right < heapSize && heap[right] < heap[smallest]){
        smallest = right;
    }

    if(smallest != index){
        swap(&heap[index], &heap[smallest]);
        shiftDown(smallest);
    }
}*/

void buildHeap(int array[] , int length ){
    if(length > MAX_SIZE){
        printf("Array too large!\n");
        return;
    }
    for(int i = 0 ; i<length ; i++){
        heap[i] = array[i];
    }
    heapSize = length;
    for (int i = (heapSize / 2) - 1; i >= 0;i--){
         shiftDown(i);
    }
}
/*Decreasing a Node’s key value to a Heap

❑Change its old value with new one
❑Push the node’s new key value downward, swapping with its children until the node reaches an acceptable location (shift down).*/
void decreaseKey(int index ,int newVal){
    if(index < 0 || index >= heapSize || newVal > heap[index]){
        printf("Invalid decreasekey!\n ");
        return;
    }
    heap[index] = newVal;
    shiftDown(index);
    //shiftUp( index ) in Minheap
}
/*Increasing a Node’s key value to a Heap
❑Change its old value with new one
❑Push the node’s new key value upward, swapping with its parent until the node reaches an acceptable location (shift up).*/
void increaseKey(int index ,int newVal){
    if(index<0 || index>=heapSize || newVal < heap[index]){
        printf("Invalid decreasekey!\n ");
        return;
    }
    heap[index] = newVal;
    shiftUp(index);
    //shiftDown(index) in Minheap
}
/*Removing from arbitrary index of a Heap
❑Firstly, change its value to INT_MAX (maximum positive number)
❑Apply increaseKey function
❑Remove top
❑Appy removeTop function*/
void removeArbitraryNode(int index ){
    if(index<0 || index>=heapSize ){
        printf("Invalid Index!\n ");
        return;
    }
    increaseKey(index, INT_MAX);
    //Minheap  decreaseKey(index, INT_MIN);
    removeTop();
}

void printHeap(const char *msg){
    printf("%s\n", msg);
    printf("Heap elements  ( size = %d): ", heapSize);
    for (int i = 0; i < heapSize;i++){
        printf("%d ", heap[i]);

    }
    printf("\n");
}

void main() {
insert(45);
insert(20);
insert(35);
insert(10);
insert(50);
insert(68);
insert(5);
insert(0);
printHeap("Heap after insertions");
printf("\n=== Removing the top (maximum) element ===\n");
int maxVal = removeTop();
printf("Removed top element: %d\n", maxVal);
printHeap("Heap after removing top");
printf("\n=== Increasing key at index 2 to 70 ===\n");
increaseKey(2, 70);
printHeap("Heap after increaseKey");
printf("\n=== Decreasing key at index 1 to 15 ===\n");
decreaseKey(1, 15);
printHeap("Heap after decreaseKey");
printf("\n=== Deleting arbitrary node at index 3 ===\n");
removeArbitraryNode(3);
printHeap("Heap after removeArbitraryNode");
printf("\n=== Building heap from array {12, 7, 6, 10, 8, 20, 15} ===\n");
int arr[] = {12, 7, 6, 10, 8, 20, 15};
buildHeap(arr, 7);
printHeap("Heap after buildHeap");
printf("\n=== Inserting more elements\n");
insert(100);
insert(55);
insert(25);
printHeap("Final heap state");
}
/*
| Operation         | Max Heap       | Min Heap       |
| ----------------- | -------------- | -------------- |
| shiftUp condition | parent < child | parent > child |
| shiftDown logic   | pick largest   | pick smallest  |
| increaseKey       | shiftUp        | shiftDown      |
| decreaseKey       | shiftDown      | shiftUp        |
| delete trick      | set INT_MAX    | set INT_MIN    |                                            */