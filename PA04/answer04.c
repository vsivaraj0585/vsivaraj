/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */

void printpartition(int * arr, int index)
{
  int test;
  
  for (test = 0; test < index - 1; test++)
    {
      printf("%d + ", arr[test]);
    }
  printf("%d\n", arr[index - 1]);
}

void partition_all(int * arr, int index, int n)
{
  int test;

  if (n == 0)
    {
      printf("= ");
      printpartition(arr, index);
      return;
    }
  else
    {
      for (test = 1; test <= n; test++)
	{
	  arr[index] = test;
	  partition_all(arr, index + 1, n - test);
	}
    }
}

void partitionAll(int value)
{
  int * arr;
  
  printf("partitionAll %d\n", value);
  arr = malloc(sizeof(int) * value);
  partition_all(arr, 0, value);
  free (arr);
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */
int order_inc(int * arr, int count, int index, int ref)
{
  int test;
  int check;

  for (test = 0; test < index; test++)
    {
      check += arr[test];
    }

  if (check > ref)
    {
      return 0;
    }
    
  for (test = 0; test < index; test++)
    {
      if (arr[test] < arr[test + 1])
	{
	  count++;
	}
    }
  return count;
}
  
void partition_inc(int * arr, int index, int n, int check, int ref)
{
  int test;
  int count = 0;

  if ((n == 0) && (check >= index) && (arr[0] < (ref / 2)))
    {
      count = order_inc(arr, count, index, ref);
      if (count == (index - 1))
      {
	printf("= ");
	printpartition(arr, index);
	return;
      }
    }
  else
    {
      for (test = 1; test <= n; test++)
	{
	  if (test > check)
	    {
	      arr[index] = test;
	      check++;
	    }
	  partition_inc(arr, index + 1, n - test, check, ref);
	}
    }
}
void partitionIncreasing(int value)
{
  int * arr;
  int check = 0;
  
  printf("partitionIncreasing %d\n", value);
  printf("= %d\n", value);
  arr = malloc(sizeof(int) * value);
  partition_inc(arr, 0, value, check, value);
  free (arr);
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

int order_dec(int * arr, int count, int index)
{
  int test;
    
  for (test = 0; test < index; test++)
    {
      if (arr[test] > arr[test + 1])
	{
	  count++;
	}
    }
  return count;
}
  
void partition_dec(int * arr, int index, int n, int check, int ref)
{
  int test;
  int count = 0;

  if ((n == 0) && (check >= index) && (arr[0] > (ref / 2)))
    {
      //printf("= ");
      count = order_dec(arr, count, index);
      if (count == (index - 1))
      {
	  printpartition(arr, index);
	  return;
      }
    }
  else
    {
      for (test = n; test >= 1; test--)
	{
	  if (test > check)
	    {
	      arr[index] = test;
	      check++;
	    }
	  partition_dec(arr, index + 1, n - test, check, ref);
	}
    }
}

void partitionDecreasing(int value)
{
  int * arr;
  int check = 0;
  
  printf("partitionDecreasing %d\n", value);
  arr = malloc(sizeof(int) * value);
  partition_inc(arr, 0, value, check, value);
  free (arr);
}  


/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partition_odd(int * arr, int index, int n)
{
  int test;

  if (n == 0)
    {
      printf("= ");
      printpartition(arr, index);
      return;
    }
  else
    {
      for (test = 1; test <= n; test += 2)
	{
	  arr[index] = test;
	  partition_odd(arr, index + 1, n - test);
	}
    }
}

void partitionOdd(int value)
{
  int * arr;
  
  printf("partitionOdd %d\n", value);
  arr = malloc(sizeof(int) * value);
  partition_odd(arr, 0, value);
  free (arr); 
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */
void partition_even(int * arr, int index, int n)
{
  int test;

  if (n == 0)
    {
      printf("= ");
      printpartition(arr, index);
      return;
    }
  else
    {
      for (test = 2; test <= n; test += 2)
	{
	  arr[index] = test;
	  partition_even(arr, index + 1, n - test);
	}
    }
}
void partitionEven(int value)
{
  int * arr;
  
  printf("partitionEven %d\n", value);
  arr = malloc(sizeof(int) * value);
  partition_even(arr, 0, value);
  free (arr); 
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */


void partition_oddeven(int * arr, int index, int n, int check)
{
  int test;

  if (n == 0)
    {
      printf("= ");
      printpartition(arr, index);
      return;
    }
  else
    {
      if (check % 2 != 1)
	{
	  check++;
	  for (test = 1; test <= n; test += 2)
	    {
	      arr[index] = test;
	      partition_oddeven(arr, index + 1, n - test, check);
	    }
	}
      else
	{
	  check++;
	  for (test = 2; test <= n; test += 2)
	    {
	      arr[index] = test;
	      partition_oddeven(arr, index + 1, n - test, check);
	    }
	}
    }
}

void partitionOddAndEven(int value)
{
  int * arr;
  int check = 0;
  
  printf("partitionOddAndEven %d\n", value);
  arr = malloc(sizeof(int) * value);
  partition_oddeven(arr, 0, value, check);
  free (arr); 
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */



void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);

}
