/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 8														*/
/*	Topic: Stack implementation											*/
/*	File name: Stack													*/
/*	Date: 5/6/2016														*/
/*	Objective:	Evaluate an expression and push/pop scopes on the
				stack to evaluate if they are correctly placed			*/
/*	Comments:															*/
/************************************************************************/				

#include <stdio.h>
#include <stdlib.h>

/***** #define *****/
#define MAX_STACK_SIZE 100
#define EMPTYSTACK -1

/***** global variables *****/
// stack structure
typedef struct stack {
	int top_ptr;
	char elements[MAX_STACK_SIZE];
} MyStack;

// pointers to read and write files
FILE *rdFile, *wrFile;


// this function checks if a stack is empty, if yes, returns a 1
int IsStackEmpty(MyStack *stack)
{
	if(stack->top_ptr == EMPTYSTACK) return 1;
	else							 return 0;
}

// this function checks if a stack is full, if yes, returns a 1
int IsStackFull(MyStack *stack)
{
	if(stack->top_ptr >= MAX_STACK_SIZE) return 1;
	else								 return 0;
}

// this function pushes an element onto the top of the stack, if successful, returns a 1
int Push(MyStack *stack, char c)
{
	if(!IsStackFull(stack)) 
	{
		stack->elements[++(stack->top_ptr)] = c;
		printf("\nPUSHing %c on the stack", c);
		fprintf(wrFile, "\nPUSHing %c on the stack", c);
	}
	else
	{
		printf ("%s", "\n\nCannot push into a full stack");
		fprintf(wrFile, "\n\nCannot push into a full stack");
		printf("\n\nInvalid scopes in the expression");
		fprintf(wrFile, "\n\nInvalid scopes in the expression");
		exit (1);
	}
	return 1;
}

// this function pops an element from the top of stack
char Pop(MyStack *stack)
{
	if(!IsStackEmpty(stack)) 
	{
		printf("\nPOPping %c from the stack", stack->elements[stack->top_ptr]);
		fprintf(wrFile, "\nPOPping %c from the stack", stack->elements[stack->top_ptr]);

		return(stack->elements[(stack->top_ptr)--]);
	}
	else
	{
		printf ("%s", "\n\nCannot pop from an empty stack");
		fprintf(wrFile, "\n\nCannot pop from an empty stack");
		printf("\n\nInvalid scopes in the expression");
		fprintf(wrFile, "\n\nInvalid scopes in the expression");
		exit (1);
	}
}

// {x + (y - [a + b] ) * (c - [(d + e)] + k )} / (h - (j - (k - [l - n] ) ) ) + { u + [m * (p - q)] / r }
/***** main() *****/
void main()
{
	int i;
	char ch, stk_ch;

	MyStack Stack_Exp, *Stk_Ptr;

	Stk_Ptr = &Stack_Exp;

	Stk_Ptr->top_ptr = EMPTYSTACK;

	// open file to write
	wrFile = fopen ("Stack_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	rdFile = fopen ("Expression.txt" , "r");
	if (rdFile == NULL)	printf("\n\nError opening reading file"); 
	else
	{
		do 
		{
			ch = fgetc(rdFile);								// read one character from the file at a time
			if(ch >= 0 && ch <= 32) continue;				// ignore first 32 characters of the ASCII table, includes space and enter
			else if(ch >= 65 && ch <= 90 || ch >=97 && ch <= 122)		// check if 'ch' is an operand
			{
				printf("\n'%c' is an operand", ch);
				fprintf(wrFile, "\n'%c' is an operand", ch);
				
			}
			else if(ch == '+' || ch == '-' || ch == '*' || ch == '/')	// check if 'ch' is an operator
			{
				printf("\n'%c' is an operator", ch);
				fprintf(wrFile, "\n'%c' is an operator", ch);
			}		
			else if(ch == '(' || ch == '{' || ch == '[')	// check if 'ch' is beginning on a scope
			{
				Push(Stk_Ptr, ch);							// if yes, push on stack
			}
			else if(ch == ')' || ch == '}' || ch == ']')	// check if 'ch' is the end of a scope
			{
				stk_ch = Pop(Stk_Ptr);						// if yes, pop from stack to compare if it matches correct beginning of scope
				if((ch == ')' && stk_ch == '(') || (ch == '}' && stk_ch == '{') || (ch == ']' && stk_ch == '['))
				{
					printf("\n\nCorrect scope, %c %c\n", stk_ch, ch);
					fprintf(wrFile, "\n\nCorrect scope, %c %c\n", stk_ch, ch);
				}
				else
				{
					printf("\nIncorrect scope, %c %c", stk_ch, ch);
					fprintf(wrFile, "\nIncorrect scope, %c %c", stk_ch, ch);
					printf("\n\nInvalid scopes in the expression");
					fprintf(wrFile, "\n\nInvalid scopes in the expression");
					fclose (rdFile);		// close the read file
					fclose (wrFile);		// close the write file
					printf("\nPress any character and hit [Enter] to exit");
					scanf("%d", &i);
					return;
				}
			}
			else							// for any other character apart from ones taken care of above is encountered...
			{
				//printf("\n'%c' is an unknown character", ch);
				//fprintf(wrFile, "\n'%c' is an unknown character", ch);
			}
		}
		while (ch != EOF);					// read until end of file is reached
	}
	
	printf("\nEnd of valid expression! All scopes are correct!");
	fprintf(wrFile, "\nEnd of valid expression! All scopes are correct!");

	fclose (rdFile);						// close the read file
	fclose (wrFile);						// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}