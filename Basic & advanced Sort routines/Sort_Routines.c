/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 12														*/
/*	Topic: Sort Routines												*/
/*	File name: Sort_Routines											*/
/*	Date: 6/4/2016														*/
/*	Objective:	Implement 4 simple & 3 advanced	sort algorithms			*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 50

// pointers to read and write files
FILE *rdFile, *wrFile;

int print_options_to_choose(void)
{
	int choice;
	
	printf("\n");
	printf("\n1: Bubble Sort	(Simple sort routine).");
	printf("\n2: Insertion Sort (Simple sort routine).");
	printf("\n3: Selection Sort (Simple sort routine).");
	printf("\n4: Shell Sort		(Simple sort routine).");
	printf("\n5: Quick Sort		(Advanced sort routine).");
	printf("\n6: Heap Sort		(Advanced sort routine).");
	printf("\n7: Merge Sort		(Advanced sort routine).");
	printf("\n\n");

	fprintf(wrFile, "\n");
	fprintf(wrFile, "\n1: Bubble Sort	 (Simple sort routine).");
	fprintf(wrFile, "\n2: Insertion Sort (Simple sort routine).");
	fprintf(wrFile, "\n3: Selection Sort (Simple sort routine).");
	fprintf(wrFile, "\n4: Shell Sort	 (Simple sort routine).");
	fprintf(wrFile, "\n5: Quick Sort	 (Advanced sort routine).");
	fprintf(wrFile, "\n6: Heap Sort		 (Advanced sort routine).");
	fprintf(wrFile, "\n7: Merge Sort	 (Advanced sort routine).");
	fprintf(wrFile, "\n\n");
	
	printf("\nChoose the sort routine from above to sort the numbers or enter -1 to quit: ");
	fprintf(wrFile, "\nChoose the sort routine from above to sort the numbers or enter -1 to quit: ");

	scanf("%d", &choice);
	printf("\nYou chose: ");
	fprintf(wrFile, "\nYou chose: ");

	return choice;
}

void print_array(int *Num_Array[], const int size)
{
	int i;
	printf("\n\n");
	fprintf(wrFile, "\n\n");
	for(i=0; i < size; i++)							// print the numbers read
	{
		printf("%d ", Num_Array[i]);
		fprintf(wrFile, "%d ", Num_Array[i]);
	}
}

/***** Bubble_Sort *****/
void Bubble_Sort(int *Num_Array[], const int size)
{
	int i, j, temp;
	
	printf("Bubble Sort: ");
	fprintf(wrFile, "Bubble Sort: ");

	for(i=1; i <= size-1; i++)
	{
		for(j=0; j <= size-2; j++)
		{
			if(Num_Array[j] > Num_Array[j+1])
			{
				temp = Num_Array[j];
				Num_Array[j] = Num_Array[j+1];
				Num_Array[j+1] = temp;
			}
		}
	}
	print_array(Num_Array, size);
}

/***** Insertion_Sort *****/
void Insertion_Sort(int *Num_Array[], const int size)
{
	int i, j, key;
	
	printf("Insertion Sorting: ");
	fprintf(wrFile, "Insertion Sorting: ");

	for(i=1; i < size; i++)
	{
		key = Num_Array[i];
		j = i-1;
		
		while(key < Num_Array[j] && j >= 0)
		{	
			Num_Array[j+1] = Num_Array[j];
			j--;
		}
		Num_Array[j+1] = key;
	}
	print_array(Num_Array, size);
}

/***** Selection_Sort *****/
void Selection_Sort(int *Num_Array[], const int size)
{
	int i, j, temp, min_index;
	
	printf("Selection Sort: ");
	fprintf(wrFile, "Selection Sort: ");

	for(i=0; i < size-1; i++)
	{
		min_index = i;
		for(j=i+1; j < size; j++)
		{
			if(Num_Array[j] < Num_Array[min_index])
			{
				min_index = j;
			}
		}
		temp = Num_Array[min_index];
		Num_Array[min_index] = Num_Array[i];
		Num_Array[i] = temp;
	}
	print_array(Num_Array, size);
}

/***** Shell_Sort *****/
void Shell_Sort(int Num_Array[], const int num_array_size, int Incr_Array[], const int incr_array_size)
{
	int i=0, j=0, k=0, temp;
	
	printf("Shell Sort: ");
	fprintf(wrFile, "Shell Sort: ");

	while(Incr_Array[i] > 0)
	{
		for(j = Incr_Array[i]; j < num_array_size; j++)
		{
			temp = Num_Array[j];
			k = j;

			while((k > Incr_Array[i] - 1) && (Num_Array[k-Incr_Array[i]] >= temp))
			{
				Num_Array[k] = Num_Array[k-Incr_Array[i]];
				k -= Incr_Array[i];
			}
			
			Num_Array[k] = temp;
		}
		i++;		
	}
	
	print_array(Num_Array, num_array_size);
}

/***** Quick_Sort *****/
int Quick_Sort_Partition(int *Num_Array[], int left, int right, int pivot)
{
	int temp, left_index = left-1, right_index = right;
	
	while(1)
	{
		while(Num_Array[++left_index] < pivot);
		while(right_index > 0 && Num_Array[--right_index] > pivot);
		
		if(left_index >= right_index) break;
		else
		{
			temp = Num_Array[left_index];
			Num_Array[left_index] = Num_Array[right_index];
			Num_Array[right_index] = temp;
		}
	}

	temp = Num_Array[left_index];
	Num_Array[left_index] = Num_Array[right];
	Num_Array[right] = temp;

	return left_index;
}

void Quick_Sort(int *Num_Array[], const int size, int left, int right)
{
	int pivot_value, partition;

	if(right <= left) return;
	else
	{
		pivot_value = Num_Array[right];
		partition = Quick_Sort_Partition(Num_Array, left, right, pivot_value);
		Quick_Sort(Num_Array, size, left, partition-1);
		Quick_Sort(Num_Array, size, partition+1, right);
	}
}

/***** Heap_Sort *****/
void Sift_down(int *Num_Array[], int start_index, int end_index)
{
	int parent = start_index, child, temp;
		
	while((2*parent + 1) <= end_index)
	{
		child = 2*parent + 1;

		if((child+1 <= end_index) && (Num_Array[child] < Num_Array[child+1]))	// left & right children exist
		{
			child += 1;															// right child > left child
		}
		
		if(Num_Array[parent] < Num_Array[child])
		{
			temp = Num_Array[parent];											// if child > parent, swap
			Num_Array[parent] = Num_Array[child];
			Num_Array[child] = temp;

			parent = child;
		}
		else return;
	}
}

void Heapify(int *Num_Array[], const int size)
{
	int start_index = (size-2)/2;

	while(start_index >= 0)
	{
		Sift_down(Num_Array, start_index, size-1);
		start_index -= 1;														// go up the array
	}
}
	
void Heap_Sort(int *Num_Array[], const int size)
{
	int end, temp;
	
	printf("Heap Sort: ");
	fprintf(wrFile, "Heap Sort: ");

	Heapify(Num_Array, size);
	end = size - 1;
	
	while(end > 0)
	{
		temp = Num_Array[end];
		Num_Array[end] = Num_Array[0];
		Num_Array[0] = temp;

		end -= 1;

		Sift_down(Num_Array, 0, end);
	}	
	
	print_array(Num_Array, size);
}

/***** Merge_Sort *****/
void Merge_Array(int *Num_Array[], int start, int mid, int end)
{
    int i, j, k, first_array_index = 0, second_array_index = 0, merged_array_index = start;
    int Num_Array_1[MAX_ARRAY_SIZE], Num_Array_2[MAX_ARRAY_SIZE];
 
    for (i = 0; i < (mid - start + 1); i++) Num_Array_1[i] = Num_Array[start + i];
    for (j = 0; j < (end - mid); j++) Num_Array_2[j] = Num_Array[mid + 1 + j];
 
    while (first_array_index < (mid - start + 1) && second_array_index < (end - mid))
    {
        if (Num_Array_1[first_array_index] <= Num_Array_2[second_array_index]) Num_Array[merged_array_index++] = Num_Array_1[first_array_index++];
        else																   Num_Array[merged_array_index++] = Num_Array_2[second_array_index++];
    }

    while (first_array_index < (mid - start + 1)) Num_Array[merged_array_index++] = Num_Array_1[first_array_index++];
    while (second_array_index < (end - mid))	  Num_Array[merged_array_index++] = Num_Array_2[second_array_index++];
}

void Merge_Sort(int *Num_Array[], int start, int end)
{
	int mid;
	
	if(start < end)
	{
		mid = (start+end)/2;
		
		Merge_Sort(Num_Array, start, mid);
		Merge_Sort(Num_Array, mid+1, end);

		Merge_Array(Num_Array, start, mid, end);
	}
}

/***** main() *****/
void main()
{
	int i,x, user_choice, index, add_num;
	char ch, num[10];
	int Num_Array[MAX_ARRAY_SIZE]; 
	int Shell_Sort_Incr[4] = {5,3,1,0}, Shell_Sort_Incr_size = 4;

	// open file to write
	wrFile = fopen ("SortRoutine_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	// Prompt the user to choose a sort algorithm
	do
	{
		index = 0;
		// read from input file
		rdFile = fopen ("SortRoutine_Input.txt", "r");
		if (rdFile == NULL)	printf("\n\nError opening reading file"); 
		else
		{
			do 
			{
				ch = fgetc(rdFile);								// read a character from the input file
				
				if((ch >= -1 && ch <= 32) || (ch >= 58 && ch <= 255)) continue;		// ignore all characters except numbers
				
				else if(ch >= 48 && ch <= 57);					// read only if digits, assume inputs are integers
				{
					i = 0;			
					do
					{
						num[i++] = ch;
						ch = fgetc(rdFile);						// read a character from the input file
					}
					while(ch >= 48 && ch <= 57);				// read only if digits, assume inputs are integers

					add_num = atoi(num);						// convert string into integer number
					
					Num_Array[index++] = add_num;				// add the read number into the input array

					for(i=0;i<5;i++) num[i] = 255;				// clear num[] array
				}
			}
			while (ch != EOF);									// read until end of file is reached
			
			printf("\n\nReading original numbers from the file: \n");
			fprintf(wrFile, "\n\nReading original numbers from the file: \n");
			print_array(Num_Array, index);
		}

		user_choice = print_options_to_choose();
		
		switch(user_choice)
		{
		   case (-1):	printf("Quit."); fprintf(wrFile, "Quit.");	break;
			case (1):	Bubble_Sort(Num_Array, index); 					break;
			case (2):	Insertion_Sort(Num_Array, index);				break;
			case (3):	Selection_Sort(Num_Array, index);				break;
			case (4):	Shell_Sort(Num_Array, index, Shell_Sort_Incr, Shell_Sort_Incr_size);		break;
			case (5):	printf("Quick Sort: "); fprintf(wrFile, "Quick Sort: ");
						Quick_Sort(Num_Array, index, 0, index-1); print_array(Num_Array, index);	break;
			case (6):	Heap_Sort(Num_Array, index);					break;
			case (7):	printf("Merge Sort: "); fprintf(wrFile, "Merge Sort: ");
						Merge_Sort(Num_Array, 0, index-1); print_array(Num_Array, index);			break;
		   default:		printf("\nInvalid choice. Please choose the correct option to sort.");
						fprintf(wrFile, "\nInvalid choice. Please choose the correct option to sort.");
		}
		printf("\n\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n\n------------------------------------------------------------------------------\n");
	}
	while(user_choice != -1);

	fclose (rdFile);											// close the read file
	fclose (wrFile);											// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &x);
	return;
}