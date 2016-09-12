/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 19														*/
/*	Topic: Linked List													*/
/*	File name: Dijkstra's_alogrithm										*/
/*	Date: 6/22/2016														*/
/*	Objective:	Implement Dijkstra's shortest path algorithm			*/
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

// this function calculates the shortest path based on the distance_matrix
int Dijkstras_Algorithm(int weight_matrix[][MAX_NODES], int source, int destination)
{
	int shortest_distance_from_source[MAX_NODES], traversed_nodes[MAX_NODES], shortest_path_traversed[MAX_NODES];
	int i,j, k = -1, min_dist = INFINITY, current_node;

	for(i=0; i < MAX_NODES; i++)
	{
		if(i == source) 
		{
			shortest_distance_from_source[i] = 0;			// initialize the array such that source is the node being selected first..
			//shortest_path_traversed[++k] = i;				// first node on the shortest path is the source
		}
		else shortest_distance_from_source[i] = INFINITY;
		
		traversed_nodes[i] = FALSE;							// currently no nodes are traversed thru, so all nodes are FALSE
	}

	for(i=0; i < MAX_NODES; i++)
	{
		for(j=0; j < MAX_NODES; j++)						// find the node with minimum distance node not included in the shortest_path array
		{
			if(shortest_distance_from_source[j] <= min_dist && traversed_nodes[j] == FALSE) 
			{
				min_dist = shortest_distance_from_source[j];
				current_node = j;
			}
		}
		
		shortest_path_traversed[++k] = current_node;

		// based on the adjacency matrix calculate the distance from current node to all adjacent nodes and check if we need to update the
		// shortest path array
		for(j=0; j < MAX_NODES; j++)					
		{
			if(weight_matrix[current_node][j] != NON_ADJACENT && 
			   shortest_distance_from_source[j] >= shortest_distance_from_source[current_node] + weight_matrix[current_node][j])
			{
				shortest_distance_from_source[j] = shortest_distance_from_source[current_node] + weight_matrix[current_node][j];
			}
		}
		min_dist = INFINITY;								// reset the minimum distance value for next comparison
		traversed_nodes[current_node] = TRUE;				// mark the next node that is traversed, so exclude from next iterations
	}
	return(shortest_distance_from_source[destination]);
}

/***** main() *****/
void main()
{
	int distance_matrix[MAX_NODES][MAX_NODES] = {0};
	int i, to_node, from_node, cost_weight, shortest_path;

	// open file to write
	wrFile = fopen ("Dijkstra's_Operations.txt", "w");
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

		printf("\nEnter the 'from' node (0-7) or -1 to quit: ");
		fprintf(wrFile, "\nEnter the 'from' node (0-7) or -1 to quit: ");
		scanf("%d", &from_node);

		if(from_node == -1) 
		{
			printf("\nYou chose to quit.\n");
			fprintf(wrFile, "\nYou chose to quit.\n");
			continue;
		}
		else
		{
			printf("\nEnter the 'to' node (0-7): ");
			fprintf(wrFile, "\nEnter the 'to' node (0-7): ");
			scanf("%d", &to_node);
		
			shortest_path = Dijkstras_Algorithm(distance_matrix, from_node, to_node);

			printf("\nShortest path between %d -> %d using Dijkstra's algorithm is %d", from_node, to_node, shortest_path);
			fprintf(wrFile, "\nShortest path between %d -> %d using Dijkstra's algorithm is %d", from_node, to_node, shortest_path);
		}
	}
	while(from_node != -1);

	fclose (wrFile);										// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}