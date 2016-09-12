/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 9														*/
/*	Topic: Queue implementation											*/
/*	File name: Queue													*/
/*	Date: 5/13/2016														*/
/*	Objective:	Perform enque/deque operations on a queue based on
				reading a file input for command and data				*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			

#include <stdio.h>
#include <stdlib.h>

/***** #define *****/
#define MAX_QUEUE_SIZE 25
#define EMPTYQUEUE -1

/***** global variables *****/
// queue structure
typedef struct queue {
	int front_ptr, rear_ptr;
	char elements[MAX_QUEUE_SIZE];
} MyQueue;

// pointers to read and write files
FILE *rdFile, *wrFile;


// this function checks if the queue is empty, if yes, returns a 1
int IsQueueEmpty(MyQueue *queue)
{
	if(queue->front_ptr == queue->rear_ptr) return 1;
	else									return 0;
}

// this function checks if the queue is full, if yes, returns a 1
int IsQueueFull(MyQueue *queue)
{
	if(queue->rear_ptr == queue->front_ptr) return 1;
	else									return 0;
}

// this function inserts an element in the queue, if successful, returns a 1
int Insert(MyQueue *queue, int number)
{
	if(queue->front_ptr == MAX_QUEUE_SIZE - 1) queue->rear_ptr = 0;
	else									   (queue->rear_ptr)++;
	
	if(!IsQueueFull(queue)) 
	{

		queue->elements[queue->rear_ptr] = number;

		printf("\nINSERTing %d in the queue", number);
		fprintf(wrFile, "\nINSERTing %d in the queue", number);
	}
	else
	{
		printf ("%s", "\n\nCannot insert into a full queue");
		fprintf(wrFile, "\n\nCannot insert into a full queue");
		exit (1);
	}
	return 1;
}

// this function removes an element from the queue
int Remove(MyQueue *queue)
{
	if(!IsQueueEmpty(queue)) 
	{
		if(queue->front_ptr == MAX_QUEUE_SIZE - 1) queue->front_ptr = 0;
		else									   (queue->front_ptr)++;

		printf("\nREMOVing %d from the queue", queue->elements[queue->front_ptr]);
		fprintf(wrFile, "\nREMOVing %d from the queue", queue->elements[queue->front_ptr]);

		return(queue->elements[queue->front_ptr]);
	}
	else
	{
		printf ("%s", "\n\nCannot remove from an empty queue");
		fprintf(wrFile, "\n\nCannot remove from an empty queue");
		exit (1);
	}
}

// this function prints the queue contents from front_ptr to rear_ptr
void Print_Queue(MyQueue *queue)
{
	int print;
	print = queue->front_ptr;

	printf("\nCurrent Queue contents: ");
	fprintf(wrFile, "\nCurrent Queue contents: ");

	do		
	{
		print++;
		printf("%d ", queue->elements[print]);
		fprintf(wrFile, " %d", queue->elements[print]);

		if(print == MAX_QUEUE_SIZE - 1) print = 0;
	}
	while(print != queue->rear_ptr);
}

/***** main() *****/
void main()
{
	int i, num;
	char ch, ch_num[10];

	MyQueue NumQueue, *Q_Ptr;

	Q_Ptr = &NumQueue;

	Q_Ptr->front_ptr = EMPTYQUEUE;							// initialize front_ptr
	Q_Ptr->rear_ptr = EMPTYQUEUE;							// initialize rear_ptr

	// open file to write
	wrFile = fopen ("Queue_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	// read from input file
	rdFile = fopen ("queue_input.txt", "r");
	if (rdFile == NULL)	printf("\n\nError opening reading file"); 
	else
	{
		do 
		{
			ch = fgetc(rdFile);								// read space and ignore
			
			if(ch >= 0 && ch <= 32) continue;				// ignore first 32 characters of the ASCII table, includes space and enter
			
			else if(ch == 'E' || ch == 'e')					// check if Enque operation is to be performed
			{
				printf("\n>> ENQUEUE");
				fprintf(wrFile, "\n>> ENQUEUE");
				
				ch = fgetc(rdFile);							// read space and ignore
	
				i = 0;			
				do
				{
					ch = fgetc(rdFile);						// read the digit
					ch_num[i++] = ch;
				}
				while(ch >= 48 && ch <= 57);				// read only if digits, assume inputs are integers

				num = atoi(ch_num);							// convert string into integer number
				Insert(Q_Ptr, num);							// Insert the number into the queue
				Print_Queue(Q_Ptr);							// print the queue contents
			}
			
			else if(ch == 'D' || ch == 'd')					// check if Deque operation is to be performed
			{
				printf("\n<< DEQUEUE");
				fprintf(wrFile, "\n<< DEQUEUE");
					
				ch = fgetc(rdFile);							// read space and ignore
				
				num = Remove(Q_Ptr);						// Remove the number from the queue
				Print_Queue(Q_Ptr);							// print the queue contents
			}
		}
		while (ch != EOF);									// read until end of file is reached
	}
	
	fclose (rdFile);										// close the read file
	fclose (wrFile);										// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}