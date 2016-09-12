/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 20														*/
/*	Topic: Graphs														*/
/*	File name: Prim's_alogrithm											*/
/*	Date: 6/26/2016														*/
/*	Objective:	Build a minimum spanning tree using Prim's shortest 
				path algorithm											*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 8

/***** global variables *****/
#define TRUE 1
#define FALSE 0
#define INFINITY 9999
#define NON_ADJACENT -1

FILE *wrFile;

// this function displays the distance_matrix cost/weights
void PrintMatrix(int distance_matrix[][MAX_NODES])
{
	int row, column; 

	for(row=0; row < MAX_NODES; row++)
	{
		for(column=0; column < MAX_NODES; column++)
		{
			if(distance_matrix[row][column] == 0) distance_matrix[row][column] = NON_ADJACENT;
		}
	}

	printf("\nPrinting weight matrix contents:\n\n");
	fprintf(wrFile, "\nPrinting weight matrix contents:\n\n");

	for(column=0; column < MAX_NODES; column++)
	{
		printf("	%d", column);
		fprintf(wrFile, "	%d", column);
	}
	printf("\n");
	fprintf(wrFile, "\n");

	for(row=0; row < MAX_NODES; row++)
	{
		printf("%d:	", row);
		fprintf(wrFile, "%d:	", row);

		for(column=0; column < MAX_NODES; column++)
		{
			printf("%d	", distance_matrix[row][column]); 
			fprintf(wrFile, "%d	", distance_matrix[row][column]);

			if(column == MAX_NODES-1) { printf("\n"); fprintf(wrFile, "\n"); }
		}
	}
}

// this function builds a minimum spanning tree using the shortest path based on the distance_matrix
void Prims_Algorithm(int weight_matrix[][MAX_NODES], int root)
{
	int key[MAX_NODES], traversed_nodes[MAX_NODES], parent_nodes[MAX_NODES];
	int i,j, k = -1, min_dist = INFINITY, current_node;

	for(i=0; i < MAX_NODES; i++)
	{
		if(i == root) 
		{
			key[i] = 0;								// initialize the array such that source is the node being selected first..
			parent_nodes[i] = -1;					// root of MST
		}
		else key[i] = INFINITY;
		
		traversed_nodes[i] = FALSE;					// currently no nodes are traversed thru, so all nodes are FALSE
	}

	for(i=0; i < MAX_NODES; i++)
	{
		for(j=0; j < MAX_NODES; j++)				// find the node with minimum distance node not included in the shortest_path array
		{
			if(key[j] <= min_dist && traversed_nodes[j] == FALSE) 
			{
				min_dist = key[j];
				current_node = j;
			}
		}
		
		// based on the adjacency matrix calculate the distance from current node to all adjacent nodes and check if we need to update the
		// shortest path array
		for(j=0; j < MAX_NODES; j++)					
		{
			if(weight_matrix[current_node][j] != NON_ADJACENT && key[j] >= weight_matrix[current_node][j])
			{
				parent_nodes[j] = current_node;
				key[j] = weight_matrix[current_node][j];
			}	
		}
		min_dist = INFINITY;						// reset the minimum distance value for next comparison
		traversed_nodes[current_node] = TRUE;		// mark the next node that is traversed, so exclude from next iterations
	}

	printf("\nMinimum spanning tree using Prim's algorithm:\n\n");
	fprintf(wrFile, "\nMinimum spanning tree using Prim's algorithm:\n\n");
	for(k=1; k < MAX_NODES; k++)
	{
		printf("\n%d -> %d = %d\n", parent_nodes[k], k, weight_matrix[parent_nodes[k]][k]); 
		fprintf(wrFile, "\n%d -> %d = %d\n", parent_nodes[k], k, weight_matrix[parent_nodes[k]][k]); 
	}
}

/***** main() *****/
void main()
{
	int distance_matrix[MAX_NODES][MAX_NODES] = {0};
	int i, to_node, from_node, root_node, cost_weight;

	// open file to write
	wrFile = fopen ("Prim's_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	printf("\nEnter the 'from' node, 'to' node and the cost/weight of the arc between the two nodes to form a graph.\n\n");
	fprintf(wrFile, "\nEnter the 'from' node, 'to' node and the cost/weight of the arc between the two nodes to form a graph.\n\n");

	do
	{
		printf("\nEnter the 'from' node (0-7) or -1 to quit: ");
		fprintf(wrFile, "\nEnter the 'from' node (0-7) or -1 to quit: ");
		scanf("%d", &from_node);
		//printf("%d.\n", from_node);
		fprintf(wrFile, "%d.\n", from_node);

		if(from_node == -1) 
		{
			printf("\nYou chose to quit.\n");
			fprintf(wrFile, "\nYou chose to quit.\n");

			PrintMatrix(distance_matrix);
			continue;
		}
		else
		{
			printf("\nEnter the 'to' node (0-7): ");
			fprintf(wrFile, "\nEnter the 'to' node (0-7): ");
			scanf("%d", &to_node);
			//printf("%d.\n", to_node);
			fprintf(wrFile, "%d.\n", to_node);

			printf("\nEnter the weight/cost of the arc between the two nodes: ");
			fprintf(wrFile, "\nEnter the cost/weight of the arc between the two nodes: ");
			scanf("%d", &cost_weight);
			//printf("%d.\n", cost_weight);
			fprintf(wrFile, "%d.\n", cost_weight);

			distance_matrix[from_node][to_node] = cost_weight;
		}
	}
	while(from_node != -1);

	do
	{
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");

		printf("\nEnter the 'root' node (0-7) or -1 to quit: ");
		fprintf(wrFile, "\nEnter the 'from' node (0-7) or -1 to quit: ");
		scanf("%d", &root_node);

		if(root_node == -1) 
		{
			printf("\nYou chose to quit.\n");
			fprintf(wrFile, "\nYou chose to quit.\n");
			continue;
		}
		else
		{
			Prims_Algorithm(distance_matrix, root_node);
		}
	}
	while(root_node != -1);

	fclose (wrFile);										// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}