/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 13														*/
/*	Topic: Binary Search Tree											*/
/*	File name: Queue													*/
/*	Date: 5/27/2016														*/
/*	Objective:	Implement a binary search tree							*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			

#include <stdio.h>
#include <stdlib.h>

/***** #define *****/
#define MAX_STACK_SIZE 5000
#define EMPTYSTACK -1

/***** global variables *****/
// individual binary search tree node as a structure
struct binary_search_tree {
	int number;
	struct binary_search_tree *left_child;
	struct binary_search_tree *right_child;
};

// individual stack element as a linked list node structure
struct stacklistnode {
	struct binary_search_tree *bintreeptr;
	struct stacklistnode *nextptr;
};

typedef struct binary_search_tree BST;
typedef struct binary_search_tree* BSTPtr;

typedef struct stacklistnode MyLinkedListNode;
typedef struct stacklistnode* MyLinkedListNodePtr;

// pointers to read and write files
FILE *rdFile, *wrFile;

/***** functions for linked list stack implementation *****/
// this function inserts a BST node as an element on the linked list stack top, if successful, returns a 1
int InsertLinkedListNode(MyLinkedListNodePtr *LinkedListRootPtr, BSTPtr BinaryTreeNodePtr)
{
	MyLinkedListNodePtr NewPtr = (MyLinkedListNodePtr) malloc (sizeof(MyLinkedListNode));

	if(NewPtr != NULL)								// dynamic memory allocation successful 
	{
		NewPtr->bintreeptr = BinaryTreeNodePtr;		// assign the binary node ptr to be inserted in the stack 

		NewPtr->nextptr = *LinkedListRootPtr;		// dereference pointer to pointer,
		*LinkedListRootPtr = NewPtr;				// dereference pointer to pointer,
		
		return (1);
	}
	else											// dynamic memory allocation unsuccessful 
	{
		printf ("%s", "\n\nUnable to allocate memory for a new linked list stack node.\n");
		fprintf(wrFile, "\n\nUnable to allocate memory for a new linked list stack node.\n");
		exit (1);
	}
}

// this function removes an element from the linked list stack top
BSTPtr RemoveLinkedListNode(MyLinkedListNodePtr *LinkedListTopPtr)
{	
	BSTPtr PoppedBSTPtr;
	MyLinkedListNodePtr TopPtr;

	if(*LinkedListTopPtr == EMPTYSTACK)
	{
		printf ("%s", "\n\nLinked list stack is empty. EXIT from REMOVE.\n");
		fprintf(wrFile, "\n\nLinked list stack is empty.EXIT from REMOVE.\n");
		exit (1);
	}
	else
	{
		TopPtr = *LinkedListTopPtr;
		PoppedBSTPtr = TopPtr->bintreeptr;
		*LinkedListTopPtr = TopPtr->nextptr;
		free(TopPtr);
	}
	return(PoppedBSTPtr);
}

// this function return the element's data from the linked list stack top
BSTPtr TopLinkedListNode(MyLinkedListNodePtr *LinkedListTopPtr)
{	
	if(*LinkedListTopPtr == NULL) return NULL;

	return((*LinkedListTopPtr)->bintreeptr);
}

/***** iterative functions to traverse through a binary search tree *****/
// this function prints BST nodes iteratively in post-order fashion
int Iterative_PostOrderTraversal(BSTPtr BSTRootPtr)
{
	BSTPtr CurrentBSTPtr = BSTRootPtr, TopLLBSTPtr;
	MyLinkedListNodePtr BST_LL_Ptr = NULL;
	int traversed = 0;

	printf ("%s", "\nIterative_PostOrderTraversal:\n");
	fprintf(wrFile, "\nIterative_PostOrderTraversal:\n");

	if(CurrentBSTPtr == NULL)
	{
		printf ("%s", "\nBST is empty.\n");
		fprintf(wrFile, "\nBST is empty.\n");
		return traversed;	
	}

	do
	{
		// Move to leftmost node
		while(CurrentBSTPtr != NULL)
		{
			// Push root's right child and then root to stack.
			if(CurrentBSTPtr->right_child != NULL) InsertLinkedListNode(&BST_LL_Ptr, CurrentBSTPtr->right_child);
			InsertLinkedListNode(&BST_LL_Ptr, CurrentBSTPtr);

			// Set root as root's left child.
			CurrentBSTPtr = CurrentBSTPtr->left_child;
		}
		
		// Pop an item from stack and set it as root.
		CurrentBSTPtr = RemoveLinkedListNode(&BST_LL_Ptr);

		// If the popped item has a right child and the right child is at top of stack...
		// then remove the right child from stack, push the root back and set root as root's right child.		
		if((CurrentBSTPtr->right_child != NULL) && (CurrentBSTPtr->right_child == TopLinkedListNode(&BST_LL_Ptr)))
		{
			TopLLBSTPtr = RemoveLinkedListNode(&BST_LL_Ptr);
			InsertLinkedListNode(&BST_LL_Ptr, CurrentBSTPtr);
			CurrentBSTPtr = CurrentBSTPtr->right_child;
		}
		// Else print root's data and set root as NULL.
		else  
		{
			printf ("%d ", CurrentBSTPtr->number);
			fprintf(wrFile, "%d ", CurrentBSTPtr->number);
			CurrentBSTPtr = NULL;
		}
	}	
	while(BST_LL_Ptr != NULL);

	traversed = 1;
	return traversed;
}

// this function prints BST nodes iteratively in in-order fashion
int Iterative_InOrderTraversal(BSTPtr BSTRootPtr)
{
	BSTPtr CurrentBSTPtr = BSTRootPtr;
	MyLinkedListNodePtr BST_LL_Ptr = NULL;
	int traversed = 0;

	printf ("%s", "\n\nIterative_InOrderTraversal:\n");
	fprintf(wrFile, "\n\nIterative_InOrderTraversal:\n");

	while(!traversed)
	{
		if(CurrentBSTPtr != NULL)
		{
			InsertLinkedListNode(&BST_LL_Ptr, CurrentBSTPtr);
			CurrentBSTPtr = CurrentBSTPtr->left_child;
		}
		else
		{
			if(BST_LL_Ptr != NULL)
			{
				CurrentBSTPtr = RemoveLinkedListNode(&BST_LL_Ptr);
				printf ("%d ", CurrentBSTPtr->number);
				fprintf(wrFile, "%d ", CurrentBSTPtr->number);
				
				CurrentBSTPtr = CurrentBSTPtr->right_child;
			}
			else 
			{
				traversed = 1;
				return traversed;
			}
		}
	}
}

// this function prints BST nodes iteratively in pre-order fashion
int Iterative_PreOrderTraversal(BSTPtr BSTRootPtr)
{
	BSTPtr CurrentBSTPtr = BSTRootPtr;
	MyLinkedListNodePtr BST_LL_Ptr = NULL;
	int traversed = 0;

	printf ("%s", "\nIterative_PreOrderTraversal:\n");
	fprintf(wrFile, "\nIterative_PreOrderTraversal:\n");

	if(CurrentBSTPtr == NULL) return traversed;
	else InsertLinkedListNode(&BST_LL_Ptr, CurrentBSTPtr);

	while(BST_LL_Ptr != NULL)
	{
		CurrentBSTPtr = RemoveLinkedListNode(&BST_LL_Ptr);
		printf ("%d ", CurrentBSTPtr->number);
		fprintf(wrFile, "%d ", CurrentBSTPtr->number);

		if(CurrentBSTPtr->right_child != NULL) 
		{
			InsertLinkedListNode(&BST_LL_Ptr, CurrentBSTPtr->right_child);
		}
		if(CurrentBSTPtr->left_child != NULL) 
		{
			InsertLinkedListNode(&BST_LL_Ptr, CurrentBSTPtr->left_child);
		}
	}
	traversed = 1;
	return traversed;
}

/***** functions for binary search tree implementation *****/
// this function creates a node in the BST, if successful, returns the pointer to the newly created node, otherwise returns NULL
BSTPtr Create_BSTNode(int mynumber)
{
	
	BSTPtr NewPtr;

	NewPtr = (BSTPtr)malloc(sizeof(BST));

	if(NewPtr != NULL)								// dynamic memory allocation successful 
	{
		NewPtr->number = mynumber;					// assign the value to be inserted to the new node
		NewPtr->left_child = NULL;
		NewPtr->right_child = NULL;
		return(NewPtr);
	}
	else											// dynamic memory allocation unsuccessful 
	{
		printf ("%s", "\n\nUnable allocate memory for a new node.");
		fprintf(wrFile, "\n\nUnable allocate memory for a new node.");
		exit(1);
	}
}

// this function inserts a node in the BST, if successful returns 1 (iterative method)
int InsertBSTNode(BSTPtr *RootPtr, int mynumber)
{
	BSTPtr TempPtr = *RootPtr;

	if(TempPtr == NULL)								// BST is empty insert root node
	{
		*RootPtr = Create_BSTNode(mynumber);		// need to pass address of root pointer inorder to insert first node only
	}
	else
	{
		while(TempPtr != NULL)
		{	
			if(TempPtr->number == mynumber)			// duplicate entry is not allowed
			{
				printf ("\nDuplicate entry. %d already exists in the BST.\n\n", mynumber);
				fprintf(wrFile, "\nDuplicate entry. %d already exists in the BST.\n\n", mynumber);	
				return (-1);
			}
			else if(TempPtr->number > mynumber)		// number to be inserted is less than root node; insert in left child tree
			{
				if(TempPtr->left_child == NULL)		// if left child is NULL, insert into left child node
				{
					TempPtr->left_child = Create_BSTNode(mynumber);
					return (1);
				}
				else								// else traverse down the left child tree
				{
					TempPtr = TempPtr->left_child;
				}
			}	
			else									// number to be inserted is greater than root node; insert in right child tree
			{
				if(TempPtr->right_child == NULL)	// if right child is NULL, insert into right child node
				{
					TempPtr->right_child = Create_BSTNode(mynumber);
					return (1);
				}
				else								// else traverse down the right child tree
				{
					TempPtr = TempPtr->right_child;
				}
			}
		}
		return(1);
	}
}

// this function searches for a node in the BST, if successful, returns a 1
int SearchBSTNode(BSTPtr RootPtr, int search_node)
{
	int found = -1;

	BSTPtr SearchBSTPtr = RootPtr;
	
	while(SearchBSTPtr != NULL)
	{
		if(SearchBSTPtr->number > search_node) SearchBSTPtr = SearchBSTPtr->left_child;
		else if(SearchBSTPtr->number < search_node) SearchBSTPtr = SearchBSTPtr->right_child;
		else { found = 1; return found; }
	}
	return found;
}


// this function deletes a node from the BST & replaces it by its in-order successor, if successful, returns a 1
// inroder successor is leftmost node in the right subtree of the node to be deleted...
int DeleteBSTNode(BSTPtr *RootPtr, int delete_node)
{
	int deleted = 1;
	
	BSTPtr OriginalParentBSTPtr = NULL, InOrderBSTPtr = NULL, InOrderLeftChildBSTPtr = NULL, ParentBSTPtr = NULL, SearchBSTPtr = *RootPtr;

	while(SearchBSTPtr != NULL && SearchBSTPtr->number != delete_node)
	{
		OriginalParentBSTPtr = SearchBSTPtr;
		// if delete_node is less than current node, search down the left child tree
		if(delete_node < SearchBSTPtr->number) SearchBSTPtr = SearchBSTPtr->left_child;
		else								   SearchBSTPtr = SearchBSTPtr->right_child;
	}
		
	if(SearchBSTPtr == NULL)						// node to be deleted does not exist in the BST or BST is empty
	{				
		deleted = -1;
		return deleted;
	}
	
	if(SearchBSTPtr->left_child == NULL)			// node to be deleted has a right child
	{
		InOrderBSTPtr = SearchBSTPtr->right_child;
	}
	else if(SearchBSTPtr->right_child == NULL)		// node to be deleted has a left child
	{
		InOrderBSTPtr = SearchBSTPtr->left_child;
	}
	else											// node to be deleted has both left and right child, replace with inorder successor
	{
		ParentBSTPtr = SearchBSTPtr;
		InOrderBSTPtr = SearchBSTPtr->right_child;
		InOrderLeftChildBSTPtr = InOrderBSTPtr->left_child;
		while(InOrderLeftChildBSTPtr != NULL)
		{
			ParentBSTPtr = InOrderBSTPtr;
			InOrderBSTPtr = InOrderLeftChildBSTPtr;
			InOrderLeftChildBSTPtr = InOrderBSTPtr->left_child;
		}
		if(ParentBSTPtr != SearchBSTPtr)
		{
			ParentBSTPtr->left_child = InOrderBSTPtr->right_child;
			InOrderBSTPtr->right_child = SearchBSTPtr->right_child;
		}
		InOrderBSTPtr->left_child = SearchBSTPtr->left_child;
	}
	
	if(OriginalParentBSTPtr == NULL)
	{
		*RootPtr = InOrderBSTPtr;
	}
	else
	{
		if(SearchBSTPtr == OriginalParentBSTPtr->left_child) 
		{
			OriginalParentBSTPtr->left_child = InOrderBSTPtr;
		}
		else
		{
			OriginalParentBSTPtr->right_child = InOrderBSTPtr;
		}
	}
	
	free(SearchBSTPtr);
	return deleted;
}

/***** recursive functions to traverse through a binary search tree *****/
// this function prints BST nodes recursively in in-order fashion
void Recursive_InOrderTraversal(BSTPtr RootPtr)
{
	//printf ("%s", "\n\nRecursive_InOrderTraversal:\n");
	//fprintf(wrFile, "\n\nRecursive_InOrderTraversal:\n");

	if(RootPtr != NULL)
	{
		Recursive_InOrderTraversal(RootPtr->left_child);
		
		printf ("%d ", RootPtr->number);
		fprintf(wrFile, "%d ", RootPtr->number);

		Recursive_InOrderTraversal(RootPtr->right_child);
	}
	//printf ("%s", "NULL\n\n");
	//fprintf(wrFile, "NULL\n\n");
	//return;
}


// int InsertLinkedListNode(MyLinkedListNodePtr *LinkedListRootPtr, BSTPtr BinaryTreeNodePtr)
// BSTPtr RemoveLinkedListNode(MyLinkedListNodePtr *LinkedListRootPtr)


// this function prints BST nodes recursively in pre-order fashion
void Recursive_PreOrderTraversal(BSTPtr RootPtr)
{
	//printf ("%s", "\n\nRecursive_PreOrderTraversal:\n");
	//fprintf(wrFile, "\n\nRecursive_PreOrderTraversal:\n");

	if(RootPtr != NULL)
	{
		printf ("%d ", RootPtr->number);
		fprintf(wrFile, "%d ", RootPtr->number);

		Recursive_PreOrderTraversal(RootPtr->left_child);
		Recursive_PreOrderTraversal(RootPtr->right_child);
	}
	//printf ("%s", "NULL\n\n");
	//fprintf(wrFile, "NULL\n\n");
	//return;
}

// this function prints BST nodes recursively in post-order fashion
void Recursive_PostOrderTraversal(BSTPtr RootPtr)
{
	//printf ("%s", "\n\nRecursive_PostOrderTraversal:\n");
	//fprintf(wrFile, "\n\nRecursive_PostOrderTraversal:\n");

	if(RootPtr != NULL)
	{
		Recursive_PostOrderTraversal(RootPtr->left_child);
		Recursive_PostOrderTraversal(RootPtr->right_child);		

		printf ("%d ", RootPtr->number);
		fprintf(wrFile, "%d ", RootPtr->number);
	}
	//printf ("%s", "NULL\n\n");
	//fprintf(wrFile, "NULL\n\n");
	//return;
}



/***** main() *****/
void main()
{
	int i, add_num, search_node, found, delete_node, deleted;
	char ch, num[10];

	BSTPtr MyBSTRootPtr = NULL;
	
	// open file to write
	wrFile = fopen ("BinarySearchTree_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	// read from input file
	rdFile = fopen ("BinarySearchTree_Input.txt", "r");
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
				InsertBSTNode(&MyBSTRootPtr, add_num);		// insert a new node in the BST
				for(i=0;i<10;i++) num[i] = 0;				// reset num[] array
			}
		}
		while (ch != EOF);									// read until end of file is reached
		
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
		printf ("%s", "\n Recursive_InOrderTraversal:\n");
		fprintf(wrFile, "\n Recursive_InOrderTraversal:\n");
		Recursive_InOrderTraversal(MyBSTRootPtr);
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
		Iterative_InOrderTraversal(MyBSTRootPtr);
		
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
		printf ("%s", "\n Recursive_PreOrderTraversal:\n");
		fprintf(wrFile, "\n Recursive_PreOrderTraversal:\n");
		Recursive_PreOrderTraversal(MyBSTRootPtr);
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
		Iterative_PreOrderTraversal(MyBSTRootPtr);

		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
		printf ("%s", "\n Recursive_PostOrderTraversal:\n");
		fprintf(wrFile, "\n Recursive_PostOrderTraversal:\n");
		Recursive_PostOrderTraversal(MyBSTRootPtr);
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
		Iterative_PostOrderTraversal(MyBSTRootPtr);
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");

	}
	/*
	// prompt the user to search for nodes in the BST or quit...
	do
	{
		printf("\nEnter the node to be searched in the BST or -1 to quit: ");
		fprintf(wrFile, "\nEnter the node to be searched in the BST or -1 to quit: ");
		scanf("%d", &search_node);
		printf("\n");
		fprintf(wrFile, "\n");

		if(search_node == -1) 
		{
			printf("\nYou chose to quit.");
			fprintf(wrFile, "\nYou chose to quit.");
			
			continue;
		}
		
		found = SearchBSTNode(MyBSTRootPtr, search_node);		// search a node in the BST
		
		if(found == -1)
		{
			printf ("\n\nYou entered %d. Unable to find the node as it does not exist in the BST.\n\n", search_node);
			fprintf(wrFile, "\n\nYou entered %d. Unable to find the node as it does not exist in the BST.\n\n", search_node);
		}
		else
		{
			printf("\n\nYou entered %d. Found %d in the BST.\n\n", search_node, search_node);
			fprintf(wrFile, "\n\nYou entered %d. Found %d in the BST.\n\n", search_node, search_node);
		}
	}
	while(search_node != -1);
	*/
	
	// prompt the user to delete a node from the BST or quit...
	do
	{
		printf("\nEnter the node to be deleted in the BST or -1 to quit: ");
		fprintf(wrFile, "\nEnter the node to be deleted in the BST or -1 to quit: ");
		scanf("%d", &delete_node);
		printf("\n");
		fprintf(wrFile, "\n");

		if(delete_node == -1) 
		{
			printf("\nYou chose to quit.");
			fprintf(wrFile, "\nYou chose to quit.");
			
			continue;
		}
		
		deleted = DeleteBSTNode(&MyBSTRootPtr, delete_node);	// delete a node in the BST & replace by its in-order successor
		
		if(deleted == -1)
		{
			printf ("\n\nYou entered %d. Unable to delete the node as it does not exist in the BST.\n\n", delete_node);
			fprintf(wrFile, "\n\nYou entered %d. Unable to delete the node as it does not exist in the BST.\n\n", delete_node);
		}
		else
		{
			printf("\n\nYou entered %d. Deleted %d from the BST.\n\n", delete_node, delete_node);
			fprintf(wrFile, "\n\nYou entered %d. Deleted %d from the BST.\n\n", delete_node, delete_node);
			printf ("%s", "\nRecursive_InOrderTraversal printing after deleting the node:\n");
			fprintf(wrFile, "\nRecursive_InOrderTraversal printing after deleting the node:\n");
			Recursive_InOrderTraversal(MyBSTRootPtr);
		}
	}
	while(delete_node != -1);

	fclose (rdFile);											// close the read file
	fclose (wrFile);											// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}