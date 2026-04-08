#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct Node{
    int data;
    struct Node *next;
} node;

node *head=NULL;
node *tail = NULL;
node *createnode(int data)
{
    node *temp = (node *)malloc(sizeof(node));
    if (temp == NULL)
    {
        printf("Heap memory exhausted\n");
        return NULL;
    }
    temp->data = data;
    temp->next = NULL;
    return temp;
}
void insertatend(int data) {
    node *t = createnode(data);
    if (t == NULL) return;

    if (head == NULL) {
        head = tail = t; 
        return;
    }
    
    tail->next = t;   
    tail = t;  
}       

void print (){
    if(head==NULL){
        printf("The list is empty!\n");
        return;
    }
    printf("The liked list is : ");

    node *temp = head;
    while(temp!=NULL){
        printf(" %d ->", temp->data);
        temp = temp->next;
    }
    printf(" NULL\n");
}

void findLargesTwo(){
    if(head==NULL || head->next==NULL){
        printf("List need at least two nodes!\n");
        return;
    }

    int first = INT_MIN;
    int second = INT_MIN;
    node *temp = head;

    while(temp!=NULL){
        if(temp->data>first){
            //New  largest   found
            second = first;
            first = temp->data;
        }
        else if(temp->data>second && temp->data!=first){
            //New second largest found
            second = temp->data;
        }
        temp = temp->next;
    }
    if (second == INT_MIN) {
        printf("No distinct second largest found.\n");
    } else {
        printf("Largest: %d, Second Largest: %d\n", first, second);
    }
}
void freeList() {
    node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(){

    insertatend(3);
    insertatend(1);
    insertatend(8);
    insertatend(44);
    insertatend(100);
    insertatend(99);
    insertatend(1003);
    insertatend(2);
    insertatend(999);
    print();

    findLargesTwo();

    freeList();
    return 0;
}