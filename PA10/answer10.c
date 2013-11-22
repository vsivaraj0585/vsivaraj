
#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * new_stack = malloc(sizeof(Stack));
  new_stack -> list = NULL;

  return new_stack;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
if (stack != NULL)
    {
      while (stack->list != NULL)
	{
	  ListNode * ln = stack -> list -> next;
	  free(stack -> list);
	  stack -> list = ln;
	}
      
      free(stack);
    }
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if((stack == NULL) || (stack -> list == NULL))
    {
      return TRUE;
    }

    return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{
  if(stack -> list == NULL)
    {
      return -1;
    }

  ListNode * ln = stack -> list -> next;
  int val = stack -> list -> value;

  free(stack -> list);
  stack -> list = ln;

  return val;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  ListNode * ln = malloc(sizeof(ListNode));
  
  ln -> value = value;
  if(stack -> list == NULL)
    {
      ln -> next = NULL;
    }
  else
    {
      ln -> next = stack -> list;
    }
  stack -> list = ln;

}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void  array_copy(int * array, int * arr1, int len)
{
  int i;
  for(i = 0 ; i < len ;i++)
    {
      array[i] = arr1[i];
    }
}

void stackSort(int * array, int len)
{
  int ind1 = 0;
  int ind2 = 0;
  Stack * stack = Stack_create();
  int * arr = malloc(sizeof(int) *len);
  
  for(ind1 = 0; ind1 < len; ind1 ++)
    {
      if (stack -> list == NULL)
	{
	  Stack_push(stack, array[ind1]);
	}
      else
	{
     
	  while((stack -> list != NULL) && ((stack -> list -> value) < array[ind1]))
	    {
	      arr[ind2] = Stack_pop(stack);
	      ind2++;
	    }
	  Stack_push(stack, array[ind1]);
	}  
    }

  while(stack -> list != NULL)
    {
      arr[ind2] = Stack_pop(stack);
      ind2++;
    }
  Stack_destroy(stack);  
  array_copy(array, arr, len);	  
  free(arr);   

}


/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int min_index(int * array, int len)
{
  int lcv = 1;
  int min = array[0];
  int min_ind = 0;

  while(lcv < len)
    {
      if (array[lcv] < min)
	{
	  min = array[lcv];
	  min_ind = lcv;
	}
      lcv++;
    }

  return min_ind;
}

int max_index(int * array, int len)
{
  int lcv = 1;
  int max = array[0];
  int max_ind = 0;

  while(lcv < len)
    {
      if (array[lcv] > max)
	{
	  max = array[lcv];
	  max_ind = lcv;
	}
      lcv++;
    }

  return max_ind;
}

int isStackSortable(int * array, int len)
{
  if (len < 3)
    {
      return TRUE;
    }

  int max_ind = max_index(array, len);
  int right_min = 0;
  int left_max = 0;

  if(max_ind == (len - 1))
    {
      left_max = array[max_index(array, len - 1)];
      right_min = array[len - 1];
      if(left_max > right_min)
	{
	  return FALSE;
	}
      return isStackSortable(array, len - 1);
    }
  if(max_ind == 0)
    {
      left_max = 0;
      right_min = array[min_index(array + 1, len - 1) + 1];
      if(left_max > right_min)
	{
	  return FALSE;
	}
      return isStackSortable(array + 1, len - 1);
    }
  left_max = array[max_index(array , max_ind)];
  right_min = array[min_index(array + max_ind + 1, len - max_ind - 1)+ max_ind + 1];
  if(left_max > right_min) 
    {
      return FALSE;
    }
  return isStackSortable(array, max_ind);
  return isStackSortable(array + max_ind + 1, len - max_ind - 1);
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [0..k-1] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */
void genShapes(int k)
{

}




