#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct QUEUE
{
    int arr[SIZE];
    int front, rear;
}queue;

queue q;


void enqueue(int data)
{

    if(q.front == -1 && q.rear == -1)
    {
        ++q.front;
        q.arr[++q.rear] = data;

    }

    else{

        q.arr[++q.rear] = data;
    }
}

void dequeue()
{
    if(q.front > q.rear || ( q.front == -1 && q.rear == -1))
    {
        printf("QUEUE EMPTY....RESETTING\n");
        q.front = -1;
        q.rear = -1;
    }
    else
        printf("%d is dequeued\n",q.arr[q.front++]);

}


void display()
{
    int count = q.front;
    printf("\n");
    while(count <= q.rear)
    {
        printf("%d-> ",q.arr[count]);
        count++;
    }
    printf("\n\n");
}



int main()
{
    q.front = -1, q.rear = -1;
    int choice, temp;


  while(1)
    {
    printf("Enter:\n1\tEnqueue\n2\tDequeue\n3\tDisplay\n4\tExit\n");
    printf("ENTER YOUR CHOICE : ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1: printf("Enter the data: ");
                scanf("%d",&temp);
                enqueue(temp);
                break;
        case 2: dequeue();
                break;
        case 3: display();
                break;
        case 4: printf("\t\t\tTHANK YOU!\n");
                return 0;

        default: printf("INVALID!\n");
    }
  }
    return 0;

}
