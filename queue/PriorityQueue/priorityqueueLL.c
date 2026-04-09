#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data, priority;
    struct Node *next;
} node;

node *head = NULL;

node* createnode (int data,int priority){
    node *temp = (node *)malloc(sizeof(node));
    if(temp==NULL){
        printf("Heap overflow!Memory not available\n");
        return NULL;
    }
    temp->data = data;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}
 //Enqueue based on priority
void enqueue(int data,int priority){
    node *temp = createnode(data,priority);
    if(temp==NULL){
        return;
    }
    // case 1:Empty Queue
    if(head ==NULL){
        head = temp;
        return;
    }

    //case 2: Higher priority than head
    if(priority>head->priority){
        temp->next = head;
        head = temp;
        return;
    }
    
    //case 3:Insert in middle or end for priority
    node *current = head;
    while(current->next!=NULL&& current->next->priority >=priority){

        current = current->next;
    }

    temp->next = current->next;
    current->next = temp;
}
//Dequeue highest priority element
void dequeue(){
    if(head ==NULL){
        printf(" Queue underflow!Queue is empty \n");
       
    }
    node *temp = head;
    head = head->next;
    printf("Removed: %d (priority %d)\n", temp->data, temp->priority);

    free(temp);
}
void updatePriority(int index, int newPriority){
    if(head == NULL){
        printf("Empty list\n");
        return;
    }

    node *current = head;
    node *prev = NULL;
    int i = 0;

    while(current != NULL && i < index){
        prev = current;
        current = current->next;
        i++;
    }

    if(current == NULL){
        printf("Invalid index\n");
        return;
    }

    int value = current->data;

    // remove node
    if(prev == NULL){
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);

    // reinsert with new priority
    enqueue(value, newPriority);
}
 void front (){
    if(head==NULL){
        printf("Queue is empty.\n");
        return ;
    }
    printf("Front Element: %d\n", head->data);  
}
void rear(){
    if(head==NULL){
        printf("Queue is empty.\n");
        return ;
    }
    node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    printf("Rear Element: %d\n", temp->data);  
}
void findMaxElement(){
    if(head == NULL){
        printf("Empty list\n");
        return;
    }

    node *current = head;
    int max = current->data;

    while(current != NULL){
        if(current->data > max){
            max = current->data;
        }
        current = current->next;
    }

    printf("Max value: %d\n", max);
}
void print (){
    //empty check
    if(head==NULL){
        printf("The queue is empty\n");
        return;
    }
    node *temp = head;
    printf("Queue : \n ");
    while(temp!=NULL){
        printf("(%d : %d) -> ", temp->data,temp->priority);
        temp=temp -> next;
        
    }
    printf("NULL\n");
}
int main(){

    enqueue(10, 3);
    enqueue(20, 7);
    enqueue(30, 2);
    enqueue(40, 0);

    print();
    findMaxElement();
    dequeue();
    front();
    rear();


    print();
    updatePriority(1, 9);
    printf("After updating \n");
    print();
    return 0;
}

/*
 Error Handling Cheat Sheet (EXAM GOLD)
🔹 createNode()

✔ malloc failure → Heap overflow

🔹 enqueue()

✔ New node NULL → stop
✔ Empty queue case
✔ Insert at front
✔ Insert in middle
✔ Insert at end

🔹 dequeue()

✔ Empty queue → Underflow
✔ Proper memory free

🔹 peek()

✔ Empty queue check

🔹 display()

✔ Empty queue handling
*/