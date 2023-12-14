//
// Created by dania on 07.12.2023.
//

#ifndef ARCHIVER_PRIORETY_QUEUE_H
#define ARCHIVER_PRIORETY_QUEUE_H
#include <stdlib.h>
#include <stdio.h>
typedef enum {false,true}bool;
typedef struct Node{
    int data;
    char sym;
    struct Node* left;
    struct Node* right;
}Node;



typedef struct {
    int max_size;
    int size;
    Node **heap;
}priority_queue;


/*Sort of heap*/
int sort(Node* first,Node* second){
    return first->data> second->data;
}

/*swiftUP of heap*/
void swiftUP(priority_queue* queue,int index){
    while(index>0 && sort(queue->heap[(index-1)/2],queue->heap[index])){
        Node *tmp=queue->heap[(index-1)/2];
        queue->heap[(index-1)/2]=queue->heap[index];
        queue->heap[index]=tmp;
        index=(index-1)/2;
    }
}


/*swiftDOWN of heap*/
void swiftDOWN(priority_queue* queue,int i)
{
    int swapIndex = i;
    if (i*2 + 1< queue->size && sort(queue->heap[swapIndex],queue->heap[i*2 + 1])) {
        swapIndex = i*2 + 1;
    }
    if (i*2 + 2 < queue->size && sort(queue->heap[swapIndex],queue->heap[i*2 + 2])) {
        swapIndex = i*2 + 2;
    }
    if (i != swapIndex) {
        Node *tmp=queue->heap[swapIndex];
        queue->heap[swapIndex]=queue->heap[i];
        queue->heap[i]=tmp;
        swiftDOWN(queue,swapIndex);
    }
}

/*Insert in priority_queue*/
void insert(priority_queue* queue,Node* data){
    if(queue->size>=queue->max_size)
        return;
    queue->heap[queue->size++]=data;
    swiftUP(queue,queue->size-1);
}


/*Extract from priority_queue*/
Node* extract_min(priority_queue* queue){
    Node *result = queue->heap[0];
    queue->heap[0] = queue->heap[queue->size-1];
    queue->size--;
    swiftDOWN(queue,0);
    return result;
}


/*Constructor of priority_queue*/
void create_queue(priority_queue* queue,int max_size){
    queue->max_size=max_size;
    queue->size=0;
    queue->heap=(int*)malloc(max_size);
}

/*Print queue*/
void print_queue(priority_queue* queue){
    for(int i=0;i<queue->size;i++){
        printf("%c %d\n",queue->heap[i]->sym,queue->heap[i]->data);
    }
}


#endif //ARCHIVER_PRIORETY_QUEUE_H
